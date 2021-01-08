#include "myfftplot.h"

MyFFTPlot::MyFFTPlot(QWidget *parent) : MyPlot(parent) {
  addGraph();
  xAxis->setSubTicks(false);
  yAxis->setSubTicks(false);
  this->xAxis->setRange(0, 1000);
  this->yAxis->setRange(0, 100);
  setGridHintX(-2);
  setGridHintY(-2);
  graph(0)->setFillBase(-50);
}

QByteArray MyFFTPlot::exportCSV(char separator, char decimal, int precision) {
  QByteArray output = (QString("frequency%1amplitude\n").arg(separator)).toUtf8();
  for (QCPGraphDataContainer::iterator it = graph(0)->data()->begin(); it != graph(0)->data()->end(); it++) {
    output.append(QString::number(it->key, 'f', precision).replace('.', decimal).toUtf8());
    output.append(separator);
    output.append(QString::number(it->value, 'f', precision).replace('.', decimal).toUtf8());
    output.append('\n');
  }
  return output;
}

QPair<unsigned int, unsigned int> MyFFTPlot::getVisibleSamplesRange() {
  if (graph(0)->data()->isEmpty())
    return (QPair<unsigned int, unsigned int>(0, 0));
  int i = 0;
  while (graph(0)->data()->at(i)->key < xAxis->range().lower)
    i++;
  int min = i;
  while (graph(0)->data()->at(i)->key <= xAxis->range().upper && i < graph(0)->data()->size())
    i++;
  int max = i - 1;
  return (QPair<unsigned int, unsigned int>(min, max));
}

void MyFFTPlot::newData(QSharedPointer<QCPGraphDataContainer> data) {
  graph(0)->setData(data);
  if (autoSize)
    autoset();
  this->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
}

void MyFFTPlot::clear() {
  graph(0)->data().data()->clear();
  this->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
}

void MyFFTPlot::setStyle(int style) {
  if (style == GraphStyle::line) {
    graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    graph(0)->setLineStyle(QCPGraph::lsLine);
    graph(0)->setBrush(Qt::NoBrush);
  } else if (style == GraphStyle::point) {
    graph(0)->setScatterStyle(POINT_STYLE);
    graph(0)->setLineStyle(QCPGraph::lsNone);
    graph(0)->setBrush(Qt::NoBrush);
  } else if (style == GraphStyle::linePoint) {
    graph(0)->setScatterStyle(POINT_STYLE);
    graph(0)->setLineStyle(QCPGraph::lsLine);
    graph(0)->setBrush(Qt::NoBrush);
  } else if (style == GraphStyle::filled) {
    graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    graph(0)->setLineStyle(QCPGraph::lsLine);
    graph(0)->setBrush(graph(0)->pen().color());
  }
  this->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
}

void MyFFTPlot::setAutoSize(bool en) {
  autoSize = en;
  setMouseControlls(!en);
  autoset();
  this->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
}

void MyFFTPlot::autoset() {
  bool foundrange;
  QCPRange yRange = graph(0)->data()->valueRange(foundrange);
  QCPRange xRange = graph(0)->data()->keyRange(foundrange);
  if (yRange.lower >= 0)
    yRange.lower = 0;
  else
    yRange.lower = -50;

  yRange.upper = GlobalFunctions::ceilToNiceValue(yRange.upper);
  xRange.lower = 0;
  xRange.upper = xRange.upper;
  xAxis->setRange(xRange);
  yAxis->setRange(yRange);
}
