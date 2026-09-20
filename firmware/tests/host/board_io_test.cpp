#include "board_io.h"
#include "board_pins.h"
#include <Arduino.h>
#include <SPI.h>
#include <driver/gpio.h>
#include <array>
#include <cassert>
#include <map>
#include <vector>

MockSerial Serial0;
MockSPI SPI;
static std::map<int,int> levels, modes;
static std::vector<int> configured;
static std::array<int,4> spiPins;
static int serialEnds=0, spiBegins=0, failPin=-1;
void MockSerial::end() {
    using namespace solar_oracle;
    assert(levels[pins::LOAD_OE_N]==1);
    assert(modes[pins::SR_CLOCK]==GPIO_MODE_OUTPUT && levels[pins::SR_CLOCK]==0);
    assert(modes[pins::SR_LATCH]==GPIO_MODE_OUTPUT && levels[pins::SR_LATCH]==0);
    assert(modes[pins::SR_CLEAR_N]==GPIO_MODE_OUTPUT && levels[pins::SR_CLEAR_N]==0);
    ++serialEnds;
    // Model UART shutdown resetting its pads: GPIO must be configured afterward.
    modes[43]=GPIO_MODE_INPUT; modes[44]=GPIO_MODE_INPUT;
}
void MockSPI::begin(int a,int b,int c,int d) { spiPins={a,b,c,d}; ++spiBegins; }
int gpio_set_level(gpio_num_t pin,int value) { levels[pin]=value; return pin==failPin ? -1 : ESP_OK; }
int gpio_config(const gpio_config_t* c) {
    assert(c->pull_up_en==0 && c->pull_down_en==0 && c->intr_type==0);
    for(int pin=0;pin<49;++pin) if(c->pin_bit_mask & (1ULL<<pin)) {
        if(c->mode==GPIO_MODE_OUTPUT) assert(levels.count(pin)); // latch was loaded first
        modes[pin]=c->mode; configured.push_back(pin);
    }
    return ESP_OK;
}
int main() {
    using namespace solar_oracle;
    assert(!beginDisplaySpi());
    assert(initialiseBoardPins());
    assert(configured.front()==pins::LOAD_OE_N && levels[pins::LOAD_OE_N]==1);
    for(int pin:{pins::SCAN_MODE,pins::ANALOG_EN,pins::SENSE_EN,pins::MCU_DONE,
                 pins::EPD_ENA,pins::SR_CLEAR_N,pins::SR_DATA,pins::SR_CLOCK,pins::SR_LATCH})
        assert(levels[pin]==0 && modes[pin]==GPIO_MODE_OUTPUT);
    for(int pin:{pins::EPD_CS_N,pins::EPD_SRAM_CS_N,pins::EPD_RST_N}) assert(levels[pin]==1);
    for(int pin:{pins::EPD_MISO,pins::EPD_BUSY,pins::BUTTON_N,pins::POWER_WARN_N,
                 pins::ADC_DRDY_N,pins::VCAP_ADC,pins::I2C_SDA,pins::I2C_SCL})
        assert(modes[pin]==GPIO_MODE_INPUT);
    assert(!modes.count(3) && !modes.count(14) && !modes.count(4));
    assert(pins::SR_DATA==43 && modes[43]==GPIO_MODE_OUTPUT && levels[43]==0);
    assert(modes[44]==GPIO_MODE_OUTPUT);
    assert(beginDisplaySpi() && serialEnds==1 && spiBegins==1);
    assert((spiPins==std::array<int,4>{44,37,38,33}));
    failPin=pins::SCAN_MODE;
    assert(!initialiseBoardPins());
    assert(!beginDisplaySpi() && spiBegins==1);
    assert(levels[pins::ANALOG_EN]==0 && levels[pins::SENSE_EN]==0);
}
