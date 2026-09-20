# GPIO20260920 — approved J2 routability mapping

Target: LOLIN S3 MINI V1.0.0 / ESP32-S3FH4R2, Quad-SPI flash and PSRAM.
Hardware authority is the paired `hardware/solar-oracle-walkman-relay.kicad_pro` and PCB at the repository root.
Use this firmware directory with this GPIO-remapped board. The original project's firmware remains paired with the original board.

## Changed GPIO constants

| Signal | GPIO | Carrier J2 pad |
|---|---:|---:|
| ADC_DRDY_N | 2 | 2 |
| SENSE_EN | 6 | 12 |
| ANALOG_EN | 11 | 6 |
| SCAN_MODE | 10 | 7 |
| SR_LATCH | 15 | 24 |
| EPD_CS_N | 33 | 17 |
| EPD_MISO | 37 | 18 |
| EPD_MOSI | 38 | 19 |
| EPD_DC | 21 | 21 |
| EPD_ENA | 16 | 30 |
| EPD_RST_N | 36 | 27 |
| EPD_SRAM_CS_N | 35 | 28 |

SR_DATA=43, SR_CLOCK=18, SR_CLEAR_N=5, LOAD_OE_N=34, EPD_SCK=44, EPD_BUSY=17,
I2C_SDA=8, I2C_SCL=9, VCAP_ADC=1, MCU_DONE=12, BUTTON_N=13, POWER_WARN_N=7 remain unchanged.
GPIO3, GPIO4 and GPIO14 remain unused. GPIO19/20 remain the module's USB pins.

## Startup and integration

- Call `initialiseBoardPins()` first. The existing fail-low/fail-disabled sequencing is retained.
- OE is HIGH and both 595 clocks plus CLEAR are LOW before `Serial0.end()`.
- GPIO43 remains 595 DATA and GPIO44 remains display SCK. Keep logging on native USB CDC; do not restart UART0 on these pins.
- `beginDisplaySpi()` now calls `SPI.begin(44, 37, 38, 33)` through named constants.
- Pass the named display CS/DC/RESET/BUSY/SRAM-CS constants to the display driver; retain its power/reset sequence.
- After analog power is enabled and stable, initialize I2C with `Wire.begin(pins::I2C_SDA, pins::I2C_SCL, 100000)`.
- Preserve 595 zero-word initialization and the original 16 load-channel order.

## Verification

From the repository root, `python3 firmware/tests/check_board_io.py . --live` checks `hardware/netlist.xml` against all 24 GPIO constants,
then compiles/runs the host startup/SPI tests. The SPI expectation is `{44,37,38,33}`.
This package contains the board-I/O layer, not the complete measurement/display application or a flashable firmware image.
No ESP32 cross-compilation, flashing or physical hardware test is claimed.

`pin_map.csv` records current GPIOs and physical J2 pads; use the PCB for current coordinates.
