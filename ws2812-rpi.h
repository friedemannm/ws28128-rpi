#ifndef WS2812_RPI_H
#define WS2812_RPI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <signal.h>

#include <vector>
#include "ws2812-rpi-defines.h"

class NeoPixel {
public:
    NeoPixel(unsigned int n);
    ~NeoPixel();

    void begin();
    void show();

    unsigned char setPixelColor(unsigned int n, unsigned char r, unsigned char g, unsigned char b);
    unsigned char setPixelColor(unsigned int n, Color_t c);
    bool setBrightness(float b);

    std::vector<Color_t> getPixels();
    float getBrightness();
    Color_t getPixelColor(unsigned int n);

    unsigned int numPixels();

    void clear();

    static Color_t wheel(uint8_t wheelPos);
    void colorWipe(Color_t c, uint8_t wait);
    void rainbow(uint8_t wait);
    void rainbowCycle(uint8_t wait);
    void theaterChase(Color_t c, uint8_t wait);
    void theaterChaseRainbow(uint8_t wait);
    void effectsDemo();

private:
    static void printBinary(unsigned int i, unsigned int bits);
    static unsigned int reverseWord(unsigned int word);

    void terminate(int dummy);
    void fatal(char *fmt, ...);

    unsigned int mem_virt_to_phys(void *virt);
    unsigned int mem_phys_to_virt(uint32_t phys);
    void* map_peripheral(uint32_t base, uint32_t len);

    void clearPWMBuffer();
    void clearLEDBuffer();

    static Color_t RGB2Color(unsigned char r, unsigned char g, unsigned char b);
    static Color_t Color(unsigned char r, unsigned char g, unsigned char b);

    void setPWMBit(unsigned int bitPos, unsigned char bit);
    unsigned char getPWMBit(unsigned int bitPos);

    void initHardware();
    void startTransfer();

    unsigned int numLEDs;
    std::vector<Color_t> LEDBuffer;
    float brightness;
    unsigned int PWMWaveform[NUM_DATA_WORDS];

    static struct control_data_s *ctl;
    page_map_t *page_map;
    static uint8_t *virtbase;

    static volatile unsigned int *pwm_reg;
    static volatile unsigned int *clk_reg;
    static volatile unsigned int *dma_reg;
    static volatile unsigned int *gpio_reg;
};

#endif