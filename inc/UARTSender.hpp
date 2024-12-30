#pragma once

#include <string>

class UARTSender {
 public:
 UARTSender(std::string const& ttyDevice, int baudRate = 9600);
 ~UARTSender();

 void send(const std::string &message);
 private:
  int fd; ///< File descriptor for the TTY device
  void configureTTY(int tty_fd, int baudRate);
  int baudRateToTermiosFlag(int baudRate);
  void waitForArduinoReadiness();
};