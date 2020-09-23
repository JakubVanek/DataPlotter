#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include "settings.h"
#include <QApplication>
#include <QByteArrayMatcher>
#include <QMutex>
#include <QObject>
#include <QSerialPort>
#include <QThread>

class SerialThread : public QThread {
  Q_OBJECT
public:
  SerialThread();
  ~SerialThread();

signals:
  void error(QString);
  void connectionResult(bool, QString);
  void newCommand(QByteArray);
  void newData(QByteArray);

private:
  QMutex mutex;
  void run() override;
  QString port;
  int baud;
  int lineTimeout = 5;

public slots:
  void begin(QString portName, int baudRate);
  void end();
};

#endif // SERIALTHREAD_H
