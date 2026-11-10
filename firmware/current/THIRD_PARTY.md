# Source and license provenance

The application was copied byte-for-byte from IVcurve_tester-main/hardware/solar-oracle-walkman-raw/firmware, not from the project's root src or legacy relay firmware. The containing project's existing MIT license, Copyright (c) 2024 Marc Dusseiller, is preserved as raw/LICENSE. No separate license was present inside the original independent firmware directory; this package preserves the parent project's license without inventing a new copyright owner or relicensing third-party code. Upstream project attribution: https://github.com/dusjagr/IVcurve_tester ; historical hardware design notes identify f9a75be640c3651594d7e1b18a765c956d8d8d5c as their Marc USB architecture reference, not as a commit containing this later independent firmware.

| Vendored library | Version | License file retained | License |
|---|---|---|---|
| Adafruit ADS1X15 | 2.6.2 | raw/lib/Adafruit ADS1X15/license.txt | BSD-3-Clause, Adafruit Industries 2012 |
| Adafruit BusIO | 1.17.4 | raw/lib/Adafruit BusIO/LICENSE | MIT, Adafruit Industries 2017 |
| Adafruit EPD | 4.6.13 + local modifications | raw/lib/Adafruit EPD/license.txt | MIT, limor fried 2025 |
| Adafruit GFX Library | 1.12.6 | raw/lib/Adafruit GFX Library/license.txt | BSD-2-Clause, Adafruit Industries 2012 |

Individual source and font notices remain intact; the package-level summaries do not replace them. The original raw/library-sources.json preserves upstream tagged archive URLs and recorded SHA-256 values. Those historical archive hashes were not independently re-downloaded in this audit. Release file hashes identify the actual vendored source being delivered, including modifications.

## Local EPD changes — do not discard

The original epd-4.6.13-local.patch is preserved unchanged. It records 1 MHz EPD/SRAM SPI, SPI-pointer propagation to SRAM, sticky ioFailed state and bounded/error-aware driver operations, including the retired JD79661 path. The selected current panel is SSD1680, not JD79661.

The original patch predates the final SSD1680 correction and does not include it. The added epd-ssd1680-4814-correction.patch records the exact delta between the retained October 18 before/firmware snapshot and current source: sticky 20-second HIGH-active BUSY timeout. It is a historical delta, not a claim of a freshly verified complete diff against upstream. Vendored source is authoritative; neither patch should be applied again to this package. The application subclass's _xram_offset=1 and RESET/BUSY=-1 settings remain in src/main.cpp and include/board_pins.h.

All 205 original non-cache firmware files were eventually read from the current source after native iCloud download requests and exactly matched the local October 18 candidate backup. No reconstructed configuration or guessed constants were used. The exact platformio.ini SHA-256 is 6a55ff9df6135c74a96da789037615a035342c5699f5ba782c1e11530b16809d.

PlatformIO downloads the Espressif platform, Arduino-ESP32 framework and toolchain separately. They are not vendored or redistributed here; retain their respective notices if distributing their source or future linked binaries.
