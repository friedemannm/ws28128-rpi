#ifndef QWS2812B_H
#define QWS2812B_H

#include "ws28128-rpi/ws2812-rpi.h"
#include <QObject>
#include <QColor>

class QWS2812B : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(float brightness READ getBrightness WRITE setBrightness NOTIFY brightnessChanged)

public:
    explicit QWS2812B(int count = 24, QObject *parent = nullptr);

    QColor getColor() const;
    void setColor(const QColor &value);

    float getBrightness() const;
    void setBrightness(float brightness);

private:
    int _count;
    float _brightness = 100;

    QColor color;
    NeoPixel* _pixel = nullptr;

signals:
    void colorChanged();
    void brightnessChanged();
};

#endif // QWS2812B_H
