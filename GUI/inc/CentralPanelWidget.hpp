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
