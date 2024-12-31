#include "CentralPanelWidget.hpp"
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDir>
#include <QDebug>

CentralPanelWidget::CentralPanelWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    populateTTYDevices();
}

CentralPanelWidget::~CentralPanelWidget() {}

void CentralPanelWidget::setupUI()
{
    // Create the frames for layout
    ttyFrame = new QFrame(this);
    commandFrame = new QFrame(this);
    monitoringFrame = new QFrame(this);

    // Set up the TTY selection frame
    QVBoxLayout *ttyLayout = new QVBoxLayout;
    QLabel *ttyLabel = new QLabel("Select a tty device:");
    ttyComboBox = new QComboBox;
    
    // Add the baud rate combo box after the tty selection
    QLabel *baudRateLabel = new QLabel("Select baud rate:");
    baudRateComboBox = new QComboBox;
    baudRateComboBox->addItem("9600");
    baudRateComboBox->addItem("19200");
    baudRateComboBox->addItem("38400");
    baudRateComboBox->addItem("57600");
    baudRateComboBox->addItem("115200");

    ttyLayout->addWidget(ttyLabel);
    ttyLayout->addWidget(ttyComboBox);
    ttyLayout->addWidget(baudRateLabel);
    ttyLayout->addWidget(baudRateComboBox);
    ttyFrame->setLayout(ttyLayout);

    // Set up the command frame
    QHBoxLayout *commandLayout = new QHBoxLayout;
    QLabel *commandLabel = new QLabel("Enter a command:");
    commandLineEdit = new QLineEdit;
    sendButton = new QPushButton("Send");

    commandLayout->addWidget(commandLabel);
    commandLayout->addWidget(commandLineEdit);
    commandLayout->addWidget(sendButton);
    commandFrame->setLayout(commandLayout);

    // Set up the monitoring frame
    QVBoxLayout *monitoringLayout = new QVBoxLayout;
    QLabel *monitoringLabel = new QLabel("Monitoring:");
    monitoringTextEdit = new QTextEdit;
    monitoringTextEdit->setReadOnly(true);
    monitoringLayout->addWidget(monitoringLabel);
    monitoringLayout->addWidget(monitoringTextEdit);
    monitoringFrame->setLayout(monitoringLayout);

    // Main layout for the central widget
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ttyFrame);
    mainLayout->addWidget(commandFrame);
    mainLayout->addWidget(monitoringFrame);

    setLayout(mainLayout);
}

void CentralPanelWidget::populateTTYDevices()
{
    QDir dir("/dev");

    // Ensure the directory exists
    if (!dir.exists()) {
        qWarning() << "Directory /dev doesn't exist or is not accessible!";
        return;
    }

    // Get all entries (files and directories) in the /dev directory
    QStringList allDevices = dir.entryList(QDir::Files | QDir::System | QDir::NoDotAndDotDot);

    QStringList ttyDevices;
    // Filter out only tty devices
    for (const QString &entry : allDevices) {
        if (entry.contains("ACM") || entry.contains("USB")) {
            ttyDevices.append(entry);  // Add each TTY device to the list
        }
    }

    // Add the TTY devices to the combo box
    for (const QString &entry : ttyDevices) {
        ttyComboBox->addItem(entry);
    }
}
