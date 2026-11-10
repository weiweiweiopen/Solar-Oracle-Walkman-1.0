# Build guide

## 1. Get the whole source tree

    git clone https://github.com/weiweiweiopen/Solar-Oracle-Walkman-1.0.git
    cd Solar-Oracle-Walkman-1.0

GitHub's Code → Download ZIP also works. Download the entire repository rather than an isolated PCB: schematics use sub-sheets, local symbols/footprints and models. Enclosure editable-source ZIPs contain the Blender scene, geometry inputs and rebuild scripts; extract the ZIP for the selected variant before editing.

## 2. Select one build

- **RAW / USB:** hardware/raw/KiCad/Marc_USB.kicad_pro + enclosure/R19_RAW + firmware/current/raw. This is the available compiled measurement application. Calibration and physical bring-up remain necessary.
- **CHARGE / ADG706:** hardware/charge-adg706/KiCad/Marc_USB.kicad_pro + enclosure/R19_CHARGE_SUPERCAP. The current complete charging application is not supplied. This is a hardware/CAD development target, not a working standalone firmware kit.
- **Legacy relay:** hardware/solar-oracle-walkman-relay.kicad_pro and firmware/include, firmware/src. Separate ADS122C04 design, not interchangeable with either current variant.

## 3. Tools and bill of materials

- KiCad 10 with its standard symbol, footprint and 3D-model libraries. Publication checks used 10.0.5.
- FreeCAD with Part/Mesh/MeshPart for CAD changes; the stored assembly metadata identifies 1.1R20260725. STEP is included for other CAD systems. Blender is needed only for editing/rebuilding the presentation scene.
- PlatformIO Core 6.1.19 for the RAW application. The checked platform is espressif32 7.0.1; exact resolved framework/toolchain versions are in [firmware build documentation](../firmware/current/BUILD.md).
- PCB fabrication and electronics assembly tools, a current-limited bench supply, multimeter, reference resistances/instrument and magnification for inspection. Use appropriate training and ESD precautions.
- SLA print service and the glass, zebra strips, magnets and fasteners listed in the [mechanical guide](assembly.md).

Electrical purchasing starts at the selected board's assembly/元件表.csv and 1206_負載電阻採購表.csv, alongside its interactive BOM HTML and pin/net CSV. Confirm manufacturer part numbers and every TBD entry before purchasing. A 1% nominal load value is not an assembled-path calibration. The R19 glass dimensions alone are not a DSSC cell chemistry/sealing recipe.

## 4. Review and fabricate electronics

Open the project and inspect the full schematic hierarchy and PCB. Both current boards are two-layer layouts and the enclosure assumes 1.6 mm total PCB thickness. Review [current verification results](reproducibility.md), including the ten courtyard errors per board. Resolve/document their physical clearance and any procurement issues before manufacture; do not disable checks to make a green report.

Use the selected board's fabrication/1206_20261103 ZIP for Gerber and PTH/NPTH drill data. It is not a complete turnkey assembly order: stencil/paste and pick-and-place outputs are not supplied by that ZIP. Have the assembler review board stack-up, finish, copper weight, component heights, polarity, reflow constraints and modules. Do not mix the older 2512 resistor fabrication files or the legacy four-layer design into this build.

For inspection, run from repository root (adjust the KiCad executable path for your OS):

    kicad-cli sch erc --format json --severity-all --output /tmp/raw-erc.json hardware/raw/KiCad/Marc_USB.kicad_sch
    kicad-cli pcb drc --format json --severity-all --all-track-errors --schematic-parity --output /tmp/raw-drc.json hardware/raw/KiCad/Marc_USB.kicad_pcb

Replace raw with charge-adg706 to check the charging design. Compare findings, not just exit codes; DRC may write an error report while returning success.

## 5. Build RAW firmware

    pio --version
    pio run -d firmware/current/raw -e lolin_s3_mini

Keep the vendored libraries: the EPD driver contains required local changes. Do not replace them with an unpatched registry download or apply the included historical patches a second time. The project builds for LOLIN S3 Mini, not ESP32-C3. No Wi-Fi configuration is required or included.

**Do not flash this application onto CHARGE hardware.** That board additionally requires SCAN_MODE on GPIO12, POWER_WARN_N on GPIO11 and MCU_DONE on GPIO13. Its last three nominal load resistors are 68/62/56 ohms rather than RAW's 49.9/30.1/20 ohms. A shared MCU does not imply a compatible application.

After verifying you have the RAW board, checking power rails/shorts/polarity and identifying the correct USB port, PlatformIO can flash the built application:

    pio run -d firmware/current/raw -e lolin_s3_mini -t upload --upload-port YOUR_PORT
    pio device monitor -b 115200 --port YOUR_PORT

These are builder instructions, not a claim that uploading or a physical test was performed for this release. Disconnect the DSSC during initial power/USB checks. Do not infer allowable DUT voltage from the ADC gain setting or software diagnostic thresholds.

## 6. Validate the measurement path

The RAW application uses ADS1115 address 0x48, AIN0, sixteen ADG706 load selections and an Adafruit 4814 SSD1680 250×122 display. Send SCAN or press/release the button to request a sweep; the button or ! aborts a measurement. Verify load-disable behavior before connecting a cell.

Measure the actual total resistance of every selected path, including switch, contact and PCB resistance. Record ADC gain/offset against a reference. The shipped measuredPathOhms values are NAN and indicate uncalibrated operation; do not fill them with invented results. Consult [calibration notes](../firmware/current/raw/calibration-record.md).

The panel uses auto-reset and no wired BUSY signal, with a fixed 13-second refresh wait. Seeing a successful build or a completed delay does not verify the panel's refresh, SRAM or reset behavior. Inspect a test refresh physically.

## 7. Print and assemble the enclosure

Follow [mechanical assembly](assembly.md). Verify printed fit and contact before final assembly. Both variants use two shell parts and a whole removable lid. Use the correct fastener lengths and never force glass into an interference fit. For charge hardware, verify discharged storage before handling or disassembly.

## 8. Record the independent build

Keep the commit ID, selected variant, BOM substitutions, printer/resin/cure settings, actual glass and module dimensions, calibrated load values, test conditions and observed results. A meaningful replication includes these measurements, not just matching filenames. The [open engineering items](reproducibility.md) identify what is not yet established.
