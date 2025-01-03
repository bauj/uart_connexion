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
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QThread>
#include <memory>

#include "MainWindow.hpp"
#include "UARTWorkerReceiver.hpp"
#include "UARTWorkerSender.hpp"

class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(MainWindow *view, QObject *parent = nullptr);
  ~Controller();

 private:
  // Ensure threads are joined properly on exit
  void cleanUpThreads();

 public slots:
  void onTTYConnexionMade();
  void onCommandSent();
  void onMainWindowClosing();
  void onMessageReceived(
      const QString &message);  // Slot to handle incoming message

 private:
  MainWindow *view;

  std::shared_ptr<UARTSender> uartSender;

  // Sender Worker
  std::unique_ptr<UARTWorkerSender> uartWorkerSender;
  std::unique_ptr<QThread> senderThread;

  // Receiver Worker
  std::unique_ptr<UARTWorkerReceiver> uartWorkerReceiver;
  std::unique_ptr<QThread> receiverThread;
};

#endif  // CONTROLLER_HPP
