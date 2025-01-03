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
#include "UARTWorkerReceiver.hpp"

#include <QDebug>
#include <QThread>
#include <chrono>
#include <thread>

UARTWorkerReceiver::UARTWorkerReceiver(std::shared_ptr<UARTSender> uartSender,
                                       QObject* parent)
    : QObject(parent), uartSender(std::move(uartSender)) {}

UARTWorkerReceiver::~UARTWorkerReceiver() { stopListening(); }

void UARTWorkerReceiver::listenForMessages() {
  std::string accumulatedMessage;

  while (this->isListening) {
    // Receive a chunk from UART
    std::string message = uartSender->receive();
    if (!message.empty()) {
      accumulatedMessage += message;  // Add the new chunk to the buffer
      // Check if the message contains a newline, meaning it's complete
      size_t pos;
      while ((pos = accumulatedMessage.find("\n")) != std::string::npos) {
        // Extract the full message and emit it
        std::string completeMessage = accumulatedMessage.substr(0, pos);
        completeMessage.erase(
            std::remove(completeMessage.begin(), completeMessage.end(), '\n'),
            completeMessage.cend());  // Remove newlines

        accumulatedMessage.erase(
            0, pos + 1);  // Remove the complete message from the buffer

        emit messageReceived(
            QString::fromStdString(completeMessage));  // Emit the full message
      }
    }

    // Sleep briefly to prevent excessive CPU usage
    QThread::msleep(100);
  }
}

void UARTWorkerReceiver::stopListening() {
  this->isListening = false;
}
