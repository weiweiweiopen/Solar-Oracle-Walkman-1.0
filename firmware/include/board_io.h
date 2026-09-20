#pragma once

namespace solar_oracle {
// Call once at startup, before display/ADC libraries or any UART0 initialization.
// Returns false if an ESP-IDF GPIO operation failed. Leaves loads and analog power off.
bool initialiseBoardPins();

// Uses the explicit GPIO20260920 SPI pins. Does not enable or reset the display.
// Call after initialiseBoardPins(), before the ePaper driver's begin().
bool beginDisplaySpi();
}
