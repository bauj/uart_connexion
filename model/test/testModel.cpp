/*
 * MIT License
 * 
 * Copyright (c) 2025, J. Hamma
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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