#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>
#include <QObject>
#include <QVector>

#define PLOT_STATUS_RUN 1
#define PLOT_STATUS_PAUSE 2
#define PLOT_STATUS_SINGLETRIGER 3

#define PLOT_RANGE_FREE 0
#define PLOT_RANGE_FIXED 1
#define PLOT_RANGE_ROLLING 2

#define PLOT_STYLE_LINE 0
#define PLOT_STYLE_POINT 1
#define PLOT_STYLE_LINEANDPIONT 2
#define PLOT_STYLE_HIDDEN 3

#define DATA_MODE_DATA_UNKNOWN 0
#define DATA_MODE_DATA_STRING 1
#define DATA_MODE_DATA_BINARY 2
#define DATA_MODE_TERMINAL 3
#define DATA_MODE_MESSAGE_INFO 4
#define DATA_MODE_MESSAGE_WARNING 5

#define CHANNEL_COUNT 64
#define BUFFER_LINE_TIMEOUT 5

#define CMD_BEGIN "<cmd>"
#define TIMEOUT_SYMBOL "<timeout>"
#define CMD_END "<end>"

#define CMD_OUTPUT_LEVEL_NONE 0
#define CMD_OUTPUT_LEVEL_LOW 1
#define CMD_OUTPUT_LEVEL_HIGH 2

#define PORT_NUCLEO_DESCRIPTION_IDENTIFIER "ST"

#define MATH_ADD 0
#define MATH_SUB 1
#define MATH_MUL 2
#define MATH_DIV 3
#define MATH_XY 4

const QString lineEndings[4] = {"", "\n", "\r", "\r\n"};

//                             0      1      2      3      4      5      6       7
const float refreshRates[8] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 100.0f, 144.0f};

//                                     0       1       2       3      4      5      6     7     8     9    10   11  12 13 14  15  16  17  18   19   20   21    22    23    24     25     26     27      28      29      30
const double logaritmicSettings[31] = {0.0001, 0.0002, 0.0005, 0.001, 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};

const QColor defaultColors[8] = {Qt::darkRed, Qt::darkBlue, Qt::darkGreen, Qt::darkYellow, Qt::darkMagenta, Qt::darkCyan, Qt::darkGray, Qt::black};

const uint32_t colorCodes256[256] = {0x000000, 0x800000, 0x008000, 0x808000, 0x000080, 0x800080, 0x008080, 0xc0c0c0, 0x808080, 0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff, 0x00ffff, 0xffffff, 0x000000, 0x00005f, 0x000087, 0x0000af, 0x0000d7, 0x0000ff, 0x005f00, 0x005f5f, 0x005f87, 0x005faf,
                                     0x005fd7, 0x005fff, 0x008700, 0x00875f, 0x008787, 0x0087af, 0x0087d7, 0x0087ff, 0x00af00, 0x00af5f, 0x00af87, 0x00afaf, 0x00afd7, 0x00afff, 0x00d700, 0x00d75f, 0x00d787, 0x00d7af, 0x00d7d7, 0x00d7ff, 0x00ff00, 0x00ff5f, 0x00ff87, 0x00ffaf, 0x00ffd7, 0x00ffff,
                                     0x5f0000, 0x5f005f, 0x5f0087, 0x5f00af, 0x5f00d7, 0x5f00ff, 0x5f5f00, 0x5f5f5f, 0x5f5f87, 0x5f5faf, 0x5f5fd7, 0x5f5fff, 0x5f8700, 0x5f875f, 0x5f8787, 0x5f87af, 0x5f87d7, 0x5f87ff, 0x5faf00, 0x5faf5f, 0x5faf87, 0x5fafaf, 0x5fafd7, 0x5fafff, 0x5fd700, 0x5fd75f,
                                     0x5fd787, 0x5fd7af, 0x5fd7d7, 0x5fd7ff, 0x5fff00, 0x5fff5f, 0x5fff87, 0x5fffaf, 0x5fffd7, 0x5fffff, 0x870000, 0x87005f, 0x870087, 0x8700af, 0x8700d7, 0x8700ff, 0x875f00, 0x875f5f, 0x875f87, 0x875faf, 0x875fd7, 0x875fff, 0x878700, 0x87875f, 0x878787, 0x8787af,
                                     0x8787d7, 0x8787ff, 0x87af00, 0x87af5f, 0x87af87, 0x87afaf, 0x87afd7, 0x87afff, 0x87d700, 0x87d75f, 0x87d787, 0x87d7af, 0x87d7d7, 0x87d7ff, 0x87ff00, 0x87ff5f, 0x87ff87, 0x87ffaf, 0x87ffd7, 0x87ffff, 0xaf0000, 0xaf005f, 0xaf0087, 0xaf00af, 0xaf00d7, 0xaf00ff,
                                     0xaf5f00, 0xaf5f5f, 0xaf5f87, 0xaf5faf, 0xaf5fd7, 0xaf5fff, 0xaf8700, 0xaf875f, 0xaf8787, 0xaf87af, 0xaf87d7, 0xaf87ff, 0xafaf00, 0xafaf5f, 0xafaf87, 0xafafaf, 0xafafd7, 0xafafff, 0xafd700, 0xafd75f, 0xafd787, 0xafd7af, 0xafd7d7, 0xafd7ff, 0xafff00, 0xafff5f,
                                     0xafff87, 0xafffaf, 0xafffd7, 0xafffff, 0xd70000, 0xd7005f, 0xd70087, 0xd700af, 0xd700d7, 0xd700ff, 0xd75f00, 0xd75f5f, 0xd75f87, 0xd75faf, 0xd75fd7, 0xd75fff, 0xd78700, 0xd7875f, 0xd78787, 0xd787af, 0xd787d7, 0xd787ff, 0xd7af00, 0xd7af5f, 0xd7af87, 0xd7afaf,
                                     0xd7afd7, 0xd7afff, 0xd7d700, 0xd7d75f, 0xd7d787, 0xd7d7af, 0xd7d7d7, 0xd7d7ff, 0xd7ff00, 0xd7ff5f, 0xd7ff87, 0xd7ffaf, 0xd7ffd7, 0xd7ffff, 0xff0000, 0xff005f, 0xff0087, 0xff00af, 0xff00d7, 0xff00ff, 0xff5f00, 0xff5f5f, 0xff5f87, 0xff5faf, 0xff5fd7, 0xff5fff,
                                     0xff8700, 0xff875f, 0xff8787, 0xff87af, 0xff87d7, 0xff87ff, 0xffaf00, 0xffaf5f, 0xffaf87, 0xffafaf, 0xffafd7, 0xffafff, 0xffd700, 0xffd75f, 0xffd787, 0xffd7af, 0xffd7d7, 0xffd7ff, 0xffff00, 0xffff5f, 0xffff87, 0xffffaf, 0xffffd7, 0xffffff, 0x080808, 0x121212,
                                     0x1c1c1c, 0x262626, 0x303030, 0x3a3a3a, 0x444444, 0x4e4e4e, 0x585858, 0x626262, 0x6c6c6c, 0x767676, 0x808080, 0x8a8a8a, 0x949494, 0x9e9e9e, 0xa8a8a8, 0xb2b2b2, 0xbcbcbc, 0xc6c6c6, 0xd0d0d0, 0xdadada, 0xe4e4e4, 0xeeeeee};

struct BinDataSettings_t {
  int bits = 8;
  double valueMin = 0;
  double valueMax = 255;
  double timeStep = 1;
  int numCh = 1;
  int firstCh = 1;
  bool continuous = false;
};

struct ChannelSettings_t {
  QColor color = QColor(Qt::black);
  int style = PLOT_STYLE_LINE;
};

struct PlotSettings_t {
  double rollingRange = 100;
  int zoom = 1000;
  double horizontalPos = 500;
  double verticalRange = 10;
  int verticalCenter = 0;
};

Q_DECLARE_METATYPE(BinDataSettings_t)
Q_DECLARE_METATYPE(ChannelSettings_t)
Q_DECLARE_METATYPE(PlotSettings_t)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define CMD_END_LENGTH (sizeof(CMD_END) - 1)
#define TIMEOUT_SYMBOL_LENGTH (sizeof(TIMEOUT_SYMBOL) - 1)
#define CMD_BEGIN_LENGTH (sizeof(CMD_BEGIN) - 1)

#endif // SETTINGS_H
