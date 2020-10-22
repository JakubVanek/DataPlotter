#ifndef MYPLOT_H
#define MYPLOT_H

#include "enums_defines_constants.h"
#include "plotdata.h"
#include "qcustomplot.h"
#include <QTimer>
#include <QWidget>

class MyPlot : public QCustomPlot {
  Q_OBJECT
public:
  explicit MyPlot(QWidget *parent = nullptr);
  void updateCursors(double *cursorPositions);
  void init();
  bool isChUsed(int ch) { return !graph(ch - 1)->data()->isEmpty(); }
  double getVDiv() { return vdiv; }
  double getHDiv() { return hdiv; }
  double getCHDiv(int ch) { return vdiv / abs(scales.at(ch - 1)); }
  double getChScale(int ch) { return abs(scales.at(ch - 1)); }
  bool isInverted(int ch) { return scales.at(ch - 1) < 0; }
  double getChOffset(int ch) { return offsets.at(ch - 1); }
  int getChStyle(int ch) { return channelSettings.at(ch - 1)->style; }
  QColor getChColor(int ch) { return channelSettings.at(ch - 1)->color; }
  void setChStyle(int ch, int style);
  void setChColor(int ch, QColor color);
  void setChName(int ch, QString name);
  QString getChName(int ch) { return channelSettings.at(ch - 1)->name; }
  void changeChOffset(int ch, double offset);
  void changeChScale(int ch, double scale);
  bool isPaused() { return plottingStatus == PlotStatus::run || plottingStatus == PlotStatus::single; }
  QVector<double> getOffsets() { return offsets; }
  QVector<double> getScales() { return scales; }
  QByteArray exportChannelCSV(char separator, char decimal, int channel, int precision, bool offseted, bool onlyInView);
  QByteArray exportAllCSV(char separator, char decimal, int precision, bool offseted, bool onlyInView, bool includeHidden);
  QPair<QVector<double>, QVector<double>> getDataVector(int ch, bool includeOffsets, bool onlyInView = false);
  double getChMinValue(int ch);
  double getChMaxValue(int ch);
  void clearCh(int ch) { this->graph(ch - 1)->data().data()->clear(); }

private:
  void resume();
  bool lastWasContinous = false;
  QVector<QVector<double> *> pauseBufferTime;
  QVector<QVector<double> *> pauseBufferValue;
  QVector<double> offsets;
  QVector<double> scales;
  double vdiv, hdiv;
  PlotSettings_t plotSettings;
  QVector<ChannelSettings_t *> channelSettings;
  int plotRangeType = PlotRange::fixedRange;
  QVector<QCPItemLine *> zeroLines;
  QVector<QCPItemLine *> cursors;
  void initCursors();
  void initZeroLines();
  int plottingStatus = PlotStatus::run;
  int plottingRangeType = PlotStatus::pause;
  double minTime();
  double maxTime();
  double graphLastTime(quint8 i);
  double minT = 0.0, maxT = 1.0;
  bool iHaveCursors = false;

public slots:
  void setCursorsAccess(bool allowed);
  void update();
  void setRangeType(int type);
  void pauseClicked();
  void singleTrigerClicked();
  void setVerticalDiv(double value);
  void setHorizontalDiv(double value);
  void setShowVerticalValues(bool enabled);
  void setShowHorizontalValues(bool enabled);
  void updateVisuals();
  void resetChannels();
  void rescale(int ch, double relativeScale);
  void reoffset(int ch, double relativeOffset);
  void newData(int ch, QVector<double> *time, QVector<double> *value, bool continous, bool sorted, bool ignorePause);
  void setRollingRange(double value) { plotSettings.rollingRange = value; }
  void setHorizontalPos(double value) { plotSettings.horizontalPos = value; }
  void setVerticalRange(double value) { plotSettings.verticalRange = value; }
  void setZoomRange(int value) { plotSettings.zoom = value; }
  void setVerticalCenter(int value) { plotSettings.verticalCenter = value; }

signals:
  void updateHPosSlider(double min, double max, int step);
  void showPlotStatus(int code);
  void updateDivs(double vertical, double horizontal);
  void setCursorBounds(PlotFrame_t frame);
};

#endif // MYPLOT_H
