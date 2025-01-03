#pragma once

#include <mutex>
#include <string>

class UARTSender {
 public:
  UARTSender(std::string const &ttyDevice, int baudRate = 9600);
  ~UARTSender();

  void setDevice(const std::string &device);
  void setBaudRate(int baudRate);
  void send(const std::string &message);
  std::string receive();
  int getFD() const { return fd; }

 private:
  void configureTTY(int tty_fd, int baudRate);
  int baudRateToTermiosFlag(int baudRate);
  void waitForArduinoReadiness();

  // Private method to initialize UART communication
  void initializeUART();

 private:
  int fd;  ///< File descriptor for the TTY device
  std::mutex uartSendMutex;
  std::mutex uartReceiveMutex;
  std::string ttyDevice_;  // TTY device (e.g., /dev/ttyUSB0)
  int baudRate_;           // Baud rate (e.g., 9600)
};