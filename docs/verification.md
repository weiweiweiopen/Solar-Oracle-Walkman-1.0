# What has been checked?

The published PCB and schematic source files are byte-identical to the completed local design. They were copied into this clean repository and checked again with **KiCad 10.0.5**.

| Check | Result |
|---|---|
| Unrouted connections | 0 |
| DRC errors | 0 |
| DRC warnings | 6 existing silkscreen-over-copper warnings at C1, C2 and C3 |
| Schematic/PCB parity differences | 0 |
| ERC findings | 0 |
| GPIO/netlist consistency | All 24 assigned GPIOs match |
| Host initialization/SPI tests | Passed |

The existing project severities and exclusions were preserved. The raw reports list all ignored checks; no new exclusions were added. The legacy-named `solar-oracle-walkman-final.kicad_dru` is retained as supplied and is not automatically paired with the relay project. The source design reserves In1.Cu for GND.

## Scope

- **Hardware:** 175 footprints, four copper layers, routed PCB and filled In1 GND plane; custom footprints and local 3D models included.
- **Firmware:** GPIO definitions and startup/SPI initialization, with host tests. This is not a complete measurement application or a flashable image.
- **Not yet verified:** physical assembly, cold-start/charging measurements, switching transients, measurement accuracy, radio performance or fabrication release.
- Charging times and cycle counts in the overview are calculated scenarios, not test results.

## Reproduce

From the repository root, with KiCad 10, Python 3 and `clang++` installed:

```sh
kicad-cli sch export netlist --format kicadxml --output hardware/netlist.xml hardware/solar-oracle-walkman-relay.kicad_sch
kicad-cli sch erc --format json --severity-all --output hardware/verification/erc.json hardware/solar-oracle-walkman-relay.kicad_sch
kicad-cli pcb drc --format json --severity-all --all-track-errors --schematic-parity --output hardware/verification/drc.json hardware/solar-oracle-walkman-relay.kicad_pcb
python3 -B firmware/tests/check_board_io.py . --live
```

Raw results and design hashes are in [`hardware/verification/`](../hardware/verification/). The GitHub workflow runs the GPIO/netlist and host tests; the native KiCad checks above were run locally for this publication.
Absolute machine paths in generated XML metadata are normalized for portability; its pin/net data is unchanged.

## Attribution

The project descends from [IVcurve_tester](https://github.com/weiweiweiopen/IVcurve_tester); the original MIT copyright notice is retained. The relay STEP model originates from the KiCad 3D model collection and retains its embedded metadata. Standard KiCad library assets and third-party models retain their respective licensing terms; the repository's MIT notice does not relicense them.
