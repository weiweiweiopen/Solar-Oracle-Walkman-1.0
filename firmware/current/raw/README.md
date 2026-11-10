# Marc USB independent firmware — Adafruit 4814 correction

Display: Adafruit 4814 2.13 HD red/black/white, 250x122, SSD1680.
Uses the previously working ThinkInk_213_Tricolor_FPC7528B subclass,
_xram_offset=1 and rotation=0. The former JD79661/quadcolor configuration
is retired; unused vendor drivers are not selected by this application.

SPI SCK=36, MISO=18, MOSI=16, EPD_CS=37, DC=38, SRAM_CS=34.
RESET=-1 (onboard auto-reset), BUSY=-1 (testpad not wired). GPIO10/7 unused.
3.3V ONLY. Factory SJ1..SJ4 remain closed. SDCS hardware pulled high; no SD.
Display refresh waits the library's 13-second fixed delay when BUSY is absent.
Optional SSD1680 BUSY use has a 20-second sticky timeout, HIGH means busy.
No firmware can confirm panel completion without the BUSY wire; visual refresh
and SRAM, auto-reset, power-up remain physically UNVERIFIED.

Only this hardware project's firmware is changed. No flash/upload, root source,
active monitor, K1, Wi-Fi, credentials or measurement GPIO changes.
Existing scan/ADC/load-off safeguards and calibration constants are unchanged.
Measurement is UNCALIBRATED; nominal current calculation is not hardware protection.

Build: `pio run -d firmware` from the hardware project directory.
Compile result is recorded in the correction artifact report; compilation does not
establish hardware or mechanical fitness.
