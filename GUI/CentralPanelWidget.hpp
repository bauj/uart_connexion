#ifndef CENTRALPANELWIDGET_HPP
#define CENTRALPANELWIDGET_HPP

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

class CentralPanelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralPanelWidget(QWidget *parent = nullptr);
    ~CentralPanelWidget();

private:
    void setupUI();
    void populateTTYDevices();

    QComboBox *ttyComboBox;
    QComboBox *baudRateComboBox;  // New combo box for baud rate
    QLineEdit *commandLineEdit;
    QTextEdit *monitoringTextEdit;
    QPushButton *sendButton;

    // Define the frames for layout
    QFrame *ttyFrame;
    QFrame *commandFrame;
    QFrame *monitoringFrame;
};

#endif // CENTRALPANELWIDGET_HPP
