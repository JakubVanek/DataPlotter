#ifndef NEWSERIALPARSER_H
#define NEWSERIALPARSER_H

#include "enums_defines_constants.h"
#include <QDebug>
#include <QObject>
#include <QThread>

class NewSerialParser : public QObject {
  Q_OBJECT
public:
  explicit NewSerialParser(QObject *parent = nullptr);
  ~NewSerialParser();
  void init();

signals:
  /// Pošle zprávu do záznamu
  void sendDeviceMessage(QByteArray header, bool warning, bool ended);
  /// Předá zprávu od zařízení
  void sendMessage(QByteArray header, QByteArray message, MessageLevel::enumerator type);
  /// Pošle obsah bufferu
  void sendBuffer(QByteArray buffer);
  /// Pošle data do terminálu
  void sendTerminal(QByteArray message);
  /// Pošle nastavení (jedno, ne celý úsek)
  void sendSettings(QByteArray message);
  /// Pošle bod ke zpracování
  void sendPoint(QByteArrayList data);
  /// Pošle kanál ke zpracování
  void sendChannel(QByteArray data, unsigned int ch, QByteArray timeRaw);
  /// Potvrdí připravenost
  void ready();

private:
  void resetChHeader();
  bool channelHeaderOK = false;
  QByteArray channelTime;
  uint32_t channelLength;
  int channelNumber;
  void fatalError(const char *header, QByteArray &message);
  enum readResult { incomplete = 0, complete = 1, notProperlyEnded = 2 };
  enum delimiter { comma, semicolon, dollar, none };
  void sendMessageIfAllowed(const char *header, QByteArray &message, MessageLevel::enumerator type);
  void sendMessageIfAllowed(const char *header, QString &message, MessageLevel::enumerator type);
  DataMode::enumerator currentMode = DataMode::unknown;
  OutputLevel::enumerator debugLevel = OutputLevel::info;
  QByteArray buffer;
  QByteArray pendingDataBuffer;
  QByteArrayList pendingPointBuffer;
  void parseMode(QChar modeChar);
  readResult bufferPullFull(QByteArray &result);
  void changeMode(DataMode::enumerator mode, DataMode::enumerator previousMode, QByteArray modeName);
  readResult bufferPullBeforeSemicolumn(QByteArray &result, bool removeNewline = false);
  QByteArray bufferDebug;
  readResult bufferPullPoint(QByteArrayList &result);
  uint32_t arrayToUint(QByteArray array, bool &isok);
  readResult bufferPullChannel(QByteArray &result);

public slots:
  /// Zpracuje data
  void parse(QByteArray newData);
  /// Nastavý úroveň výpisu
  void setDebugLevel(OutputLevel::enumerator debugLevel) { this->debugLevel = debugLevel; }
  /// Clear buffers
  void clearBuffer();
  /// Show content of buffers
  void showBuffer();
  /// Set messages level
  void setMsgLevel(OutputLevel::enumerator level) { debugLevel = level; }
  /// Vymaže buffer a potvrdí připravenost
  void getReady();
};

#endif // NEWSERIALPARSER_H
