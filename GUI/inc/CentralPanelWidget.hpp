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
#ifndef CENTRALPANELWIDGET_HPP
#define CENTRALPANELWIDGET_HPP

#include <QComboBox>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class CentralPanelWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CentralPanelWidget(QWidget *parent = nullptr);
  ~CentralPanelWidget();

  QComboBox *getTTYComboBox() const { return ttyComboBox; }
  QComboBox *getBaudRateComboBox() const { return baudRateComboBox; }
  QLineEdit *getCommandInput() const { return commandLineEdit; }
  QTextEdit *getMonitoringTextEdit() const { return monitoringTextEdit; }
  QPushButton *getConnectButton() const { return connectButton; }
  QPushButton *getSendButton() const { return sendButton; }
  QFrame *getCommandFrame() const { return commandFrame; }
  QFrame *getMonitoringFrame() const { return monitoringFrame; }

 private:
  void setupUI();
  void populateTTYDevices();

  QComboBox *ttyComboBox;
  QComboBox *baudRateComboBox;  // New combo box for baud rate
  QLineEdit *commandLineEdit;
  QTextEdit *monitoringTextEdit;
  QPushButton *connectButton;
  QPushButton *sendButton;

  // Define the frames for layout
  QFrame *ttyFrame;
  QFrame *commandFrame;
  QFrame *monitoringFrame;
};

#endif  // CENTRALPANELWIDGET_HPP
