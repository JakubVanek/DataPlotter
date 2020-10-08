#ifndef OUTPUTWORKER_H
#define OUTPUTWORKER_H

#include "enums_defines_constants.h"
#include <QDebug>
#include <QObject>
#include <QThread>

class OutputWorker : public QObject {
  Q_OBJECT

private:
  int outputLevel = OutputLevel::low;
  QString beginMark;
  QString endMark;
  QString timeoutMark;

public:
  explicit OutputWorker(QObject *parent = nullptr);
  ~OutputWorker();

signals:
  void output(QString data);

public slots:
  void input(QByteArray message, int type);
  void setLevel(int level) { outputLevel = level; };
};

#endif // OUTPUTWORKER
