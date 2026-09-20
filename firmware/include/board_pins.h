#pragma once
#include <cstddef>
// Approved relay-board routability map GPIO20260920. GPIO numbers, NOT connector pad numbers.
// Board: LOLIN S3 MINI V1.0.0 / ESP32-S3FH4R2 (quad flash/PSRAM).
namespace solar_oracle { namespace pins {
constexpr const char* REVISION = "GPIO20260920";
constexpr int ADC_DRDY_N = 2; // carrier J2 pad 2
constexpr int ANALOG_EN = 11; // carrier J2 pad 6
constexpr int BUTTON_N = 13; // carrier J2 pad 5
constexpr int EPD_BUSY = 17; // carrier J2 pad 22
constexpr int EPD_CS_N = 33; // carrier J2 pad 17
constexpr int EPD_DC = 21; // carrier J2 pad 21
constexpr int EPD_ENA = 16; // carrier J2 pad 30
constexpr int EPD_MISO = 37; // carrier J2 pad 18
constexpr int EPD_MOSI = 38; // carrier J2 pad 19
constexpr int EPD_RST_N = 36; // carrier J2 pad 27
constexpr int EPD_SCK = 44; // carrier J2 pad 26
constexpr int EPD_SRAM_CS_N = 35; // carrier J2 pad 28
constexpr int I2C_SCL = 9; // carrier J2 pad 15
constexpr int I2C_SDA = 8; // carrier J2 pad 14
constexpr int LOAD_OE_N = 34; // carrier J2 pad 20
constexpr int MCU_DONE = 12; // carrier J2 pad 4
constexpr int POWER_WARN_N = 7; // carrier J2 pad 13
constexpr int SCAN_MODE = 10; // carrier J2 pad 7
constexpr int SENSE_EN = 6; // carrier J2 pad 12
constexpr int SR_CLEAR_N = 5; // carrier J2 pad 11
constexpr int SR_CLOCK = 18; // carrier J2 pad 29
constexpr int SR_DATA = 43; // carrier J2 pad 25
constexpr int SR_LATCH = 15; // carrier J2 pad 24
constexpr int VCAP_ADC = 1; // carrier J2 pad 9
constexpr int ASSIGNED[] = {ADC_DRDY_N, ANALOG_EN, BUTTON_N, EPD_BUSY, EPD_CS_N, EPD_DC, EPD_ENA, EPD_MISO, EPD_MOSI, EPD_RST_N, EPD_SCK, EPD_SRAM_CS_N, I2C_SCL, I2C_SDA, LOAD_OE_N, MCU_DONE, POWER_WARN_N, SCAN_MODE, SENSE_EN, SR_CLEAR_N, SR_CLOCK, SR_DATA, SR_LATCH, VCAP_ADC};
constexpr bool unique() {
    for (std::size_t i=0; i<sizeof(ASSIGNED)/sizeof(ASSIGNED[0]); ++i)
        for (std::size_t j=i+1; j<sizeof(ASSIGNED)/sizeof(ASSIGNED[0]); ++j)
            if (ASSIGNED[i]==ASSIGNED[j]) return false;
    return true;
}
static_assert(unique(), "Duplicate GPIO assignment");
static_assert(VCAP_ADC==1 && I2C_SDA==8 && I2C_SCL==9, "Fixed analog/I2C mapping changed");
} }
