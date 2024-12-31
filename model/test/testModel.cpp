#include <iostream>
#include <stdexcept>

#include "UARTSender.hpp"

int main(int argc, char* argv[]) {
  if (argc < 3 || argc > 4) {
    std::cerr << "Usage: " << argv[0] << " <message> <tty_device> [baud_rate]"
              << std::endl;
    return 1;
  }
  // Get the message, tty device, and baud rate from command line arguments
  std::string message = argv[1];
  std::string ttyDevice = argv[2];
  // Set the baud rate to the specified value or default to 9600
  int baudRate = (argc >= 4) ? std::atoi(argv[3]) : 9600;

  try {
    UARTSender sender1(ttyDevice, baudRate);
    sender1.send(message);
    std::cout << "Message sent successfull!" << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error : " << e.what() << std::endl;
    return 1;
  }

  return 0;
}