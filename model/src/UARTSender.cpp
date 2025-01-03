#include "UARTSender.hpp"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <chrono>   // For std::chrono::milliseconds
#include <cstring>  // for strerror
#include <iostream>
#include <sstream>  // For std::this_thread::sleep_for
#include <stdexcept>
#include <thread>  // For std::this_thread::sleep_for

UARTSender::UARTSender(std::string const& ttyDevice, int baudRate)
    : ttyDevice_{ttyDevice}, baudRate_{baudRate} {
  initializeUART();
  waitForArduinoReadiness();
}

UARTSender::~UARTSender() {
  if (this->fd != -1) {
    close(fd);
  }
}

void UARTSender::initializeUART() {
  if (ttyDevice_.find("ACM") == std::string::npos &&
      ttyDevice_.find("USB") == std::string::npos &&
      // ttyDevice_.find("ttyS") == std::string::npos &&
      ttyDevice_.find("AMA") == std::string::npos) {
    throw std::runtime_error(
        "No TTY devices containing USB nor ACM nor ttyS nor AMA found.");
  }

  this->fd = open(ttyDevice_.c_str(), O_RDWR | O_NOCTTY);
  if (this->fd == -1) {
    std::cerr << "Failed to open TTY device: " << ttyDevice_ << std::endl;
    std::cerr << "Error: " << strerror(errno)
              << std::endl;  // Output the error string
    throw std::runtime_error("Failed to open TTY device: " + ttyDevice_);
  }

  std::cout << "Successfully opened TTY device: " << ttyDevice_ << std::endl;

  // flush both buffers (transmit and receive)
  usleep(1000);
  ioctl(fd, TCFLSH, 2);

  try {
    // Configure the TTY device (set baud rate, etc.)
    configureTTY(this->fd, baudRate_);

  } catch (const std::exception& e) {
    // Ensure proper resource cleanup if something goes wrong
    close(this->fd);
    throw std::runtime_error("Error while sending message to TTY device: " +
                             std::string(e.what()));
  }
}

void UARTSender::waitForArduinoReadiness() {
  char buffer[1024];
  ssize_t bytesRead;
  std::stringstream messageBuffer;  // String stream to accumulate data
  auto startTime = std::chrono::steady_clock::now();
  const std::chrono::seconds timeoutDuration(
      5);  // Timeout duration of 5 seconds

  std::cout << " > Waiting for the serial readiness ..." << std::endl;

  // Continuously read data from the serial port until we get the "READY"
  // message
  while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[bytesRead] = '\0';  // Null-terminate the buffer
    messageBuffer << buffer;   // Append the read data to the messageBuffer

    // Check if the accumulated message contains "READY"
    std::string message = messageBuffer.str();
    if (message.find("READY") != std::string::npos) {
      std::cout << "Device is ready for communication.\n";
      return;  // "READY" found, exit the function
    }

    // Check if the timeout has expired
    auto elapsedTime = std::chrono::steady_clock::now() - startTime;
    if (elapsedTime > timeoutDuration) {
      throw std::runtime_error("Timeout waiting for Arduino READY signal.");
    }
  }

  if (bytesRead <= 0) {
    throw std::runtime_error("Failed to receive READY signal from Arduino");
  }
}

void UARTSender::configureTTY(int tty_fd, int baudRate) {
  struct termios tty;

  // Get the current TTY settings
  if (tcgetattr(tty_fd, &tty) != 0) {
    throw std::runtime_error("Error getting TTY attributes");
  }

  // Set input/output baud rates
  cfsetispeed(&tty, baudRateToTermiosFlag(baudRate));
  cfsetospeed(&tty, baudRateToTermiosFlag(baudRate));

  // Set the serial port parameters

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit characters
  tty.c_iflag &= ~IGNBRK;                      // Disable break processing
  tty.c_lflag = 0;  // No signaling characters, no echo, no canonical processing
  tty.c_oflag = 0;  // No remapping, no delays
  tty.c_cc[VMIN] = 1;    // Read at least 1 character
  tty.c_cc[VTIME] = 10;  // Timeout in deciseconds (0.5 seconds)

  tty.c_cflag |= (CLOCAL | CREAD);    // Ignore modem controls, enable reading
  tty.c_cflag &= ~(PARENB | PARODD);  // Disable parity
  tty.c_cflag &= ~CSTOPB;             // 1 stop bit
  tty.c_cflag &= ~CRTSCTS;            // Disable RTS/CTS hardware flow control

  // Apply the settings
  if (tcsetattr(tty_fd, TCSANOW, &tty) != 0) {
    throw std::runtime_error("Error setting TTY attributes");
  }
}

int UARTSender::baudRateToTermiosFlag(int baudRate) {
  switch (baudRate) {
    case 9600:
      return B9600;
    case 19200:
      return B19200;
    case 38400:
      return B38400;
    case 57600:
      return B57600;
    case 115200:
      return B115200;
    default:
      throw std::invalid_argument("Unsupported baud rate");
  }
}

void UARTSender::send(const std::string& message) {
  std::lock_guard<std::mutex> lock(uartSendMutex);
  std::string messageWithNewline = message + "\n";
  if (write(fd, messageWithNewline.c_str(), messageWithNewline.size()) == -1) {
    throw std::runtime_error("Failed to write to UART: " +
                             std::string(std::strerror(errno)));
  }
}

std::string UARTSender::receive() {
  // std::lock_guard<std::mutex> lock(uartReceiveMutex);
  char buffer[1024];
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 500000;  // 500 ms

  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);

  int retval = select(fd + 1, &readfds, nullptr, nullptr, &timeout);
  if (retval == -1) {
    throw std::runtime_error("Error in select()");
  } else if (retval == 0) {
    // Timeout, no data available
    return "";
  }

  ssize_t bytesRead = ::read(fd, buffer, sizeof(buffer) - 1);
  if (bytesRead == -1) {
    throw std::runtime_error("Failed to read from UART: " +
                             std::string(std::strerror(errno)));
  }
  buffer[bytesRead] = '\0';
  return std::string(buffer);
}

void UARTSender::setDevice(const std::string& device) {
  ttyDevice_ = device;
  // Reinitialize the UART connection with the new device if needed
  initializeUART();
}

void UARTSender::setBaudRate(int baud) {
  baudRate_ = baud;
  // Update UART settings if needed based on new baud rate
}