# Reproducibility and engineering status

## Matched sources

| Variant | Live/source PCB SHA-256 | Enclosure |
|---|---|---|
| CHARGE / ADG706, November 3 1206 | 616c3da3e4bc44d70b13c31cfe4f89f4864cd2c06f8c936f20d1d75454571154 | R19_CHARGE_SUPERCAP, window-end-row free-glass-seat revision |
| RAW / USB, November 3 1206 | 31ce579134b08f9587bb56e9721d32ac2f730266ce83713f7d6c6a4fc3672acb | R19_RAW, same mechanical revision family |

Each board is byte-identical to its enclosure's embedded PCB snapshot. The CHARGE source manifest's 27 inputs and RAW manifest's 14 inputs were independently hash-checked. A missing K1 STEP dependency was supplied from the matching R19 geometry source without changing PCB geometry or copper.

## Checks performed on November 10, 2026

| Check | RAW | CHARGE |
|---|---:|---:|
| Unrouted connections | 0 | 0 |
| Schematic/PCB parity differences | 0 | 0 |
| ERC findings | 0 | 0 |
| DRC courtyard-overlap errors | 10 | 10 |
| DRC silk-over-copper warnings | 4 | 8 |
| DRC text-thickness warnings | 1 | 1 |
| Native shell solids reopened | 2 valid single solids | 2 valid single solids |
| STL meshes checked | 2 closed, no nonmanifolds/self-intersections | 2 closed, no nonmanifolds/self-intersections |

Native KiCad 10 checks were rerun on the publication copies, including schematic parity and all track errors. No new severity overrides or exclusions were introduced. Original project rules and ignored checks remain in the project files. The courtyard errors concern the raised module arrangement; their physical clearance must be dispositioned by the builder, not assumed from the count remaining unchanged.

Evidence: [RAW DRC/ERC](../hardware/raw/verification/), [CHARGE DRC/ERC](../hardware/charge-adg706/verification/), [native CAD check](verification-1.0/native-cad-check.json), [STL check](verification-1.0/stl-check.json). Historical enclosure QA is retained inside each editable-source archive and is distinguished from these fresh checks.

## RAW firmware build

The board-matched RAW source and four vendored libraries compiled and linked successfully with PlatformIO Core 6.1.19 / espressif32 7.0.1: 19,684 bytes RAM and 304,157 bytes flash. Fourteen used GPIOs, all sixteen load values, and ADS1115 address/input match the current RAW schematic and PCB. No flashing or hardware test was performed. See [build versions and limitations](../firmware/current/BUILD.md).

## What remains before a verified independent build

1. **Charging firmware:** a complete, verified application matched to the current charge-adg706 board is not established. Legacy ADS122C04 GPIO code and RAW USB firmware are not substitutes for the charge-control/power-handshake sequence.
2. **Electrical qualification:** verify power rails, relay isolation, storage thresholds, cold start, loaded-cell power, leakage and measurement-cycle energy on assembled hardware. Do not transfer the older three-capacitor 4.5 F estimates to the two-capacitor revision.
3. **Calibration:** load values are candidates, not a calibration certificate. Measure assembled resistance and ADC scale/offset, and compare curves to a reference instrument. PUF repeatability/security remains a separate research question.
4. **Procurement:** the current BOM includes missing or TBD manufacturer part numbers. Capacitor/inductor ratings, packages, substitutions and stock must be checked. Gerber/drill ZIPs do not contain a complete pick-and-place/stencil/PCBA order.
5. **SLA and contact:** qualify resin, shrinkage, supports, cure, magnet grade/holding force and zebra-strip contact resistance. The revised free-glass-seat geometry responds to a previously observed approximately 0.2 mm gap; no new physical test is implied. The 2.05 mm magnet gap changes force relative to the old 0.4 mm assumption.
6. **DSSC cell reproduction:** mechanical glass/electrode interfaces are specified, but an exact cell fabrication, sealing and conditioning recipe matched to the photographed specimen is not established by these hardware files.

## Geometry assumptions

R19 models the e-paper module at 11.5 mm and ESP32 module at 9 mm maximum height. Some older KiCad visualization filenames still contain 12/13 mm. Refer to the enclosure source's module-height notes; measure actual modules before printing. CHARGE U207, L201 and L203 use conservative shape envelopes, not verified manufacturer solids. Nominal glass compression and modeled clearance are not force/lifetime measurements.

## Legacy reference

The original [ADS122C04 design verification](verification.md) and [energy calculations](energy-budget.md) apply only to hardware/solar-oracle-walkman-relay.*. Its 0-error DRC and three-capacitor energy budget must not be attributed to current hardware/raw or hardware/charge-adg706.
