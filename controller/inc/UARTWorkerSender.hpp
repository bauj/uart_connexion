#ifndef UARTWORKERSENDER_HPP
#define UARTWORKERSENDER_HPP

#include <QObject>
#include <QString>
#include <memory>

#include "UARTSender.hpp"

class UARTWorkerSender : public QObject {
  Q_OBJECT

 public:
  explicit UARTWorkerSender(std::shared_ptr<UARTSender> uartSender,
                            QObject* parent = nullptr);

 public slots:
  void sendCommand(const QString& command);

 signals:
  void messageSent(const QString& message);

 private:
  std::shared_ptr<UARTSender> uartSender;
};

#endif
