#ifndef UARTWORKERRECEIVER_HPP
#define UARTWORKERRECEIVER_HPP

#include <QObject>
#include <QString>
#include <memory>
#include <atomic>
#include "UARTSender.hpp"

class UARTWorkerReceiver : public QObject {
  Q_OBJECT

 public:
  explicit UARTWorkerReceiver(std::shared_ptr<UARTSender> uartSender, QObject* parent = nullptr);
  ~UARTWorkerReceiver();

 public slots:
  void listenForMessages();
  void stopListening();

 signals:
  void messageReceived(const QString& message);

 private:
  std::shared_ptr<UARTSender> uartSender;
  std::atomic<bool> isListening{true};
};

#endif
