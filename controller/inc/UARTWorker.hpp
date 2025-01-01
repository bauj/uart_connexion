#ifndef UARTWORKER_HPP
#define UARTWORKER_HPP

#include <QObject>
#include <QString>

#include "UARTSender.hpp"

class UARTWorker : public QObject {
  Q_OBJECT

 public:
  explicit UARTWorker(const QString &device, int baudRate,
                      QObject *parent = nullptr);
  ~UARTWorker();

 public slots:
  void sendCommand(const QString &command);
  void start();

 signals:
  void messageSent(
      const QString &message);  // Emitting this signal to notify the GUI
  void finished();              // To notify that the worker is done

 private:
  UARTSender uartSender;
};

#endif  // UARTWORKER_HPP
