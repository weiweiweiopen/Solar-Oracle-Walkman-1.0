# Build and reproducibility

## Verified build — 2026-11-10

Fresh compile and link: **PASS**, PlatformIO exit code 0, 158.84 seconds including toolchain download. RAM 19,684 / 327,680 bytes; flash 304,157 / 1,310,720 bytes. No device discovery, upload, flashing or hardware tests were performed.

Environment:
- macOS arm64; PlatformIO Core 6.1.19 (existing Python 3.9 virtual environment).
- espressif32 7.0.1; board lolin_s3_mini; Arduino framework.
- framework-arduinoespressif32 3.20017.241212+sha.dcc1105b.
- tool-esptoolpy 2.41100.0 (4.11.0).
- toolchain-riscv32-esp and toolchain-xtensa-esp32s3 8.4.0+2021r2-patch5.
- SPI/Wire 2.0.0; vendored versions listed in THIRD_PARTY.md.

The exact original platformio.ini is included unchanged. It pins the Espressif platform, not every transitive tool package in an independent lockfile. Above versions are the resolved, tested set. A clean tool installation needs access to PlatformIO's package registry. Original local PlatformIO warned about Core 6.2.0 being available and Python LibreSSL/urllib3 compatibility; neither warning prevented this build. No tool upgrade was performed.

## Rebuild (no upload)

From this package directory, with PlatformIO Core 6.1.19 available:

    pio --version
    pio run -d raw -e lolin_s3_mini

Do not add an upload target. The command above only builds. Do not transplant a root-project config.h or build its root src; those are a different hardware mapping and can contain private Wi-Fi configuration.

Sources are content-reproducible through SHA256SUMS. Compare the resulting resolved package versions and compile status to the list above. Bit-for-bit deterministic firmware binaries are NOT claimed: the audit build's flash usage differs by 32 bytes from the historical October 18 report (304,125 bytes), despite identical application/vendor source and listed major package versions. Embedded paths/build metadata or other environment differences were not isolated. No prebuilt image is shipped.

## Verification and use limits

Fresh schematic/PCB checks passed for raw: 160 unique numbered electrical pad keys (duplicate physical pads with one number are represented once), 0 pad-net mismatches; 14 used GPIO checks; 16 nominal load values; ADS1115 0x48/AIN0 interface. Charge: 324 unique numbered electrical pad keys, 0 mismatches; three additional lifecycle GPIOs and three resistor values differ from the raw implementation. Unnumbered switch mounting pads and board-only mounting holes are excluded from the electrical key comparison. This is connectivity/value compatibility, not routing DRC, device behavior, measurement accuracy, panel fit or power-safety validation.

Before hardware use, independently verify EN load disconnection, DUT voltage/current and reverse/power-off behavior, actual path resistances and ADC calibration, collector/contact resistance, display refresh/SRAM/reset, and voltage/power/thermal limits. No known-safe DUT range is established by this audit. See raw/calibration-record.md.
