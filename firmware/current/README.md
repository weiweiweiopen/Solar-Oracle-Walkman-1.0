# Solar Oracle Walkman 1.0 — RAW firmware

## Supported target

**raw/** is the existing October 18 independent firmware, matched against the November 3, 2026 raw 1206 PCB. It is NOT compatible firmware for charge-adg706 or the older ADS122C04 / shift-register relay hardware. Hardware behavior remains unqualified; do not attach an unknown DUT.

The current raw PCB SHA-256 is 31ce579134b08f9587bb56e9721d32ac2f730266ce83713f7d6c6a4fc3672acb. Fourteen used MCU GPIOs, the ADC address/input connection, and all sixteen nominal load values match fresh schematic netlist and PCB pad-net evidence. See BUILD.md and THIRD_PARTY.md.

No firmware is supplied for charge-adg706. Its SCAN_MODE=GPIO12 relay switching, POWER_WARN_N=GPIO11, MCU_DONE=GPIO13 / TPL5111 lifecycle and R14/R15/R16=68/62/56 ohm loads require a dedicated implementation. The raw application has none of these power/relay controls and has 49.9/30.1/20 ohm values instead. Do not flash raw onto charge hardware.

## Preserved behavior and limits

- USB-powered LOLIN S3 Mini; ADS1115 at 0x48, AIN0, ±4.096 V gain setting, 128 SPS. ADC gain range is not the permitted input voltage.
- Adafruit 4814 SSD1680 250×122 red/black/white panel; SRAM; auto-reset; no wired BUSY. Uses fixed 13-second refresh wait. No panel-completion proof is possible without BUSY.
- SCAN command or press/release scans 16 channels. Button or ! aborts a measurement. Load EN is disabled for switching, errors, logging and display refresh.
- UNCALIBRATED. Path resistance includes unknown switch/contact/trace resistance; all measuredPathOhms remain NAN. 3.0 V / 5 mA software stops are diagnostics, not hardware protection or DUT ratings.
- No Wi-Fi credentials, network application, SD feature, compiled binaries, build cache or device upload in this package.

Original firmware source and vendored libraries are unchanged. Added release documentation, parent MIT license, a supplementary historical SSD1680 patch, and checksum inventory are packaging-only additions. Keep all vendored sources and license notices; do not replace them with unpatched registry libraries.
