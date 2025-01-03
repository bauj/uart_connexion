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
#include "CentralPanelWidget.hpp"

#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

CentralPanelWidget::CentralPanelWidget(QWidget *parent) : QWidget(parent) {
  setupUI();
  populateTTYDevices();
}

CentralPanelWidget::~CentralPanelWidget() {}

void CentralPanelWidget::setupUI() {
  // Create the frames for layout
  ttyFrame = new QFrame(this);
  commandFrame = new QFrame(this);
  monitoringFrame = new QFrame(this);

  // Set up the TTY selection frame

  QVBoxLayout *ttyLayout = new QVBoxLayout;
  QLabel *ttyLabel = new QLabel("Select a tty device:");
  ttyComboBox = new QComboBox;
  ttyLayout->addWidget(ttyLabel);
  ttyLayout->addWidget(ttyComboBox);

  // Add the baud rate combo box after the tty selection
  QVBoxLayout *baudRateLayout = new QVBoxLayout;
  QLabel *baudRateLabel = new QLabel("Select baud rate:");
  baudRateComboBox = new QComboBox;
  baudRateComboBox->addItem("9600");
  baudRateComboBox->addItem("19200");
  baudRateComboBox->addItem("38400");
  baudRateComboBox->addItem("57600");
  baudRateComboBox->addItem("115200");
  baudRateLayout->addWidget(baudRateLabel);
  baudRateLayout->addWidget(baudRateComboBox);

  QHBoxLayout *ttyConnexionOptsLayout = new QHBoxLayout;
  ttyConnexionOptsLayout->addLayout(ttyLayout);
  ttyConnexionOptsLayout->addLayout(baudRateLayout);

  connectButton = new QPushButton("Connect");

  QVBoxLayout *ttyConnexionLayout = new QVBoxLayout;
  ttyConnexionLayout->addLayout(ttyConnexionOptsLayout);
  ttyConnexionLayout->addWidget(connectButton);

  ttyFrame->setLayout(ttyConnexionLayout);

  // Set up the command frame
  QHBoxLayout *commandLayout = new QHBoxLayout;
  QLabel *commandLabel = new QLabel("Enter a command:");
  commandLineEdit = new QLineEdit;
  sendButton = new QPushButton("Send");

  commandLayout->addWidget(commandLabel);
  commandLayout->addWidget(commandLineEdit);
  commandLayout->addWidget(sendButton);
  commandFrame->setLayout(commandLayout);
  commandFrame->setEnabled(false);

  // Set up the monitoring frame
  QVBoxLayout *monitoringLayout = new QVBoxLayout;
  QLabel *monitoringLabel = new QLabel("Monitoring:");
  monitoringTextEdit = new QTextEdit;
  monitoringTextEdit->setReadOnly(true);
  monitoringLayout->addWidget(monitoringLabel);
  monitoringLayout->addWidget(monitoringTextEdit);
  monitoringFrame->setLayout(monitoringLayout);
  monitoringFrame->setEnabled(false);

  // Main layout for the central widget
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(ttyFrame);
  mainLayout->addWidget(commandFrame);
  mainLayout->addWidget(monitoringFrame);
  mainLayout->setSpacing(10);
  mainLayout->setContentsMargins(10, 10, 10, 10);
  setLayout(mainLayout);
}

void CentralPanelWidget::populateTTYDevices() {
  QDir dir("/dev");

  // Ensure the directory exists
  if (!dir.exists()) {
    qWarning() << "Directory /dev doesn't exist or is not accessible!";
    return;
  }

  // Get all entries (files and directories) in the /dev directory
  QStringList allDevices =
      dir.entryList(QDir::Files | QDir::System | QDir::NoDotAndDotDot);

  QStringList ttyDevices;
  // Filter out only tty devices
  for (const QString &entry : allDevices) {
    if (entry.contains("ACM") ||
        entry.contains("USB") ||
        // entry.contains("ttyS") ||
        entry.contains("AMA")) {
      ttyDevices.append(entry);  // Add each TTY device to the list
    }
  }

  // Add the TTY devices to the combo box
  for (const QString &entry : ttyDevices) {
    ttyComboBox->addItem(entry);
  }
}
