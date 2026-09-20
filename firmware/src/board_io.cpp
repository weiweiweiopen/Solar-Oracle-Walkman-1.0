#include "board_io.h"
#include "board_pins.h"
#include <Arduino.h>
#include <SPI.h>
#include <driver/gpio.h>

namespace solar_oracle {
namespace {
bool initialised = false;

bool output(int pin, int level) {
    // Preload the output latch before enabling the pad driver to avoid a low glitch
    // on active-low CS/OE. Arduino digitalWrite-before-pinMode is core-dependent.
    if (gpio_set_level(static_cast<gpio_num_t>(pin), level) != ESP_OK) return false;
    gpio_config_t config{};
    config.pin_bit_mask = 1ULL << pin;
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    return gpio_config(&config) == ESP_OK;
}

bool input(int pin) {
    gpio_config_t config{};
    config.pin_bit_mask = 1ULL << pin;
    config.mode = GPIO_MODE_INPUT;
    // The board supplies the required bias resistors. No I2C pull-up into an
    // unpowered analog domain is enabled here.
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    return gpio_config(&config) == ESP_OK;
}
}

bool initialiseBoardPins() {
    initialised = false;
    bool ok = true;
    ok = output(pins::LOAD_OE_N, 1) && ok;
    ok = output(pins::EPD_ENA, 0) && ok;
    ok = output(pins::EPD_CS_N, 1) && ok;
    ok = output(pins::EPD_SRAM_CS_N, 1) && ok;
    ok = output(pins::SCAN_MODE, 0) && ok;
    ok = output(pins::SENSE_EN, 0) && ok;
    ok = output(pins::ANALOG_EN, 0) && ok;
    ok = output(pins::MCU_DONE, 0) && ok;
    ok = output(pins::SR_CLOCK, 0) && ok;
    ok = output(pins::SR_LATCH, 0) && ok;
    ok = output(pins::SR_CLEAR_N, 0) && ok;
    // Hold both clocks low and OE high before reclaiming UART0 TX (GPIO43).
    // Serial0.end() may reset its GPIOs, so configure DATA/SCK only afterward.
    Serial0.end();
    ok = output(pins::SR_DATA, 0) && ok;
    ok = output(pins::EPD_RST_N, 1) && ok;
    ok = output(pins::EPD_DC, 0) && ok;

    // GPIO44 is display SCK, GPIO43 is 595 DATA. Keep the console on USB CDC.
    ok = output(pins::EPD_SCK, 0) && ok;
    ok = output(pins::EPD_MOSI, 0) && ok;
    const int inputs[] = {pins::EPD_MISO, pins::EPD_BUSY, pins::BUTTON_N,
                          pins::POWER_WARN_N, pins::ADC_DRDY_N, pins::VCAP_ADC,
                          pins::I2C_SDA, pins::I2C_SCL};
    for (int pin : inputs) ok = input(pin) && ok;
    initialised = ok;
    return ok;
}

bool beginDisplaySpi() {
    if (!initialised) return false;
    SPI.begin(pins::EPD_SCK, pins::EPD_MISO, pins::EPD_MOSI, pins::EPD_CS_N);
    return true;
}
}
