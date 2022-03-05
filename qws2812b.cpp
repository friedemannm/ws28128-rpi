#include "qws2812b.h"

QWS2812B::QWS2812B(int count, QObject *parent) : QObject(parent),
    _count(count)
{
    _pixel = new NeoPixel(count);
}

QColor QWS2812B::getColor() const
{
    return color;
}

void QWS2812B::setColor(const QColor &value)
{
    for(int i = 0; i < _count; i++)
    {
        _pixel->setPixelColor(i, value.red(), value.green(), value.blue());
    }

    _pixel->show();
    color = value;
    Q_EMIT colorChanged();
}

float QWS2812B::getBrightness() const
{
    return _brightness;
}

void QWS2812B::setBrightness(float brightness)
{
    _brightness = brightness;
    _pixel->setBrightness(_brightness);
    _pixel->show();
    Q_EMIT brightnessChanged();
}
