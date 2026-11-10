# Mechanical assembly — R19

Use one matched hardware/enclosure variant throughout. RAW is USB-powered; CHARGE_SUPERCAP has additional power hardware and deeper rear clearance. Neither enclosure is intended for the legacy ADS122C04 board merely because its outline looks similar.

## Download and print

- [RAW native FreeCAD assembly](../enclosure/R19_RAW/R19_RAW.FCStd), [two-part STL print pack](../enclosure/R19_RAW/R19_RAW_STL.zip), [STEP parts](../enclosure/R19_RAW/STEP/), [editable source archive](../enclosure/R19_RAW/R19_RAW_editable_source.zip).
- [CHARGE_SUPERCAP native FreeCAD assembly](../enclosure/R19_CHARGE_SUPERCAP/R19_CHARGE_SUPERCAP.FCStd), [two-part STL print pack](../enclosure/R19_CHARGE_SUPERCAP/R19_CHARGE_SUPERCAP_STL.zip), [STEP parts](../enclosure/R19_CHARGE_SUPERCAP/STEP/), [editable source archive](../enclosure/R19_CHARGE_SUPERCAP/R19_CHARGE_SUPERCAP_editable_source.zip).

Each editable archive contains FreeCAD, Blender, STEP, STL, parameters, geometry inputs, build/check/export scripts and original QA reports. Unzip before use. Generated visualization caches and rejected historical variants are not required source files and are omitted. Archive CRC validation is not a substitute for physical fit validation.

Print one lower shell and one upper cover, in **millimetres at 1:1 scale**. Do not resize them in the slicer. The upper STL is already flipped into its supplied print orientation. The resin/printer combination, tilt, supports, wash and cure settings need to be qualified with the printing service; no universally validated resin profile is provided. Keep supports off glass/contact seating surfaces and inspect for residual resin, deformation and sharp edges after curing.

## Mechanical shopping list

| Item | Quantity / dimensions |
|---|---|
| Printed lower shell + upper cover | One each, matched R19 variant |
| Magnets | 16, diameter 5 mm × thickness 2.7 mm; eight opposing pairs |
| Conductive zebra strips | Two, 5 × 50 × 3 mm free height |
| DSSC upper glass | One, 66 × 60 × 1.6 mm OR 70 × 60 × 1.6 mm |
| DSSC lower glass | One, 60 × 60 × 1.6 mm, centered |
| RAW PCB fasteners | Four M3 × 6 low-head screws and M3 nuts |
| CHARGE PCB fasteners | Two front M3 × 8 and two rear M3 × 14 low-head screws and M3 nuts |
| Screw-head limits | Diameter ≤5.5 mm; height ≤2 mm |

The glass dimensions describe the mechanical interface, not a DSSC fabrication recipe. The source does not yet establish a complete, repeatable cell chemistry/sealing process. Magnet grade, holding force and conductive-strip electrical performance also require qualification. Do not substitute ordinary nonconductive foam for a zebra connector.

## Assembly order

1. Inspect the fabricated PCB and assembled components using that variant's BOM and pin/net references. Leave power disconnected. For the charge variant, discharge storage through an appropriate resistor and verify its voltage; never short a supercapacitor with a tool.
2. Dry-fit both cured shells without the PCB or glass. Check magnets in opposing pairs before fixing them; use adhesive compatible with the chosen resin and keep adhesive outside conductive contact areas.
3. Remove the upper cover, glass, zebra strips and PCB screws. Introduce the completed PCB through the rear entrance: its modeled starting position is 71.2 mm behind its final position and 1 mm above its final seating plane. Translate it forward, then lower it by 1 mm onto its supports. Do not bend the board under the magnet bridges.
4. Install the specified low-head M3 fasteners. For CHARGE, insert the rear nuts from the underside recesses; they must not protrude below the shell. Do not substitute longer screws that could strike components or glass.
5. Fit the two zebra strips over the designated contact pads. Place the DSSC with its conductive electrode surfaces aligned to the strips. The lower glass has no plastic support ledge underneath; do not add a shim that prevents the upper electrode from seating on the strips.
6. Lower the entire magnetic upper cover vertically. Its two 3.2 × 50 mm pressure feet nominally compress the 3 mm strips to 2.7 mm (10%). Stop if the glass rocks, binds or requires force. Nominal CAD compression is not a measured contact force.
7. Check glass retention, polarity, contact resistance and USB plug clearance before applying power. Use the bring-up checks for the actual electrical variant. Do not assume a displayed curve establishes calibration or autonomous charging performance.

## Dimensions and source detail

Both shells have an 84 × 142.4 mm footprint. RAW nominal thickness is 22.2 mm; CHARGE main thickness is 24.6 mm, up to 29.6 mm at the capacitor clearance. Sixteen magnets sit in rows above and below the window; this is the window-end-row revision, **not the rejected 94 mm side-ear version**.

Detailed original design notes, coordinates, glass cross-sections and claimed source checks:

- [RAW R19 notes](../enclosure/R19_RAW/README.md)
- [CHARGE R19 notes](../enclosure/R19_CHARGE_SUPERCAP/README.md)

The original notes record a physical approximately 0.2 mm contact gap that motivated this revision. New-print contact resistance, closure force and long-term resin/strip behavior are not established by the CAD checks. The magnet face gap is 2.05 mm; older 0.4 mm-gap assumptions must not be reused.

## Rebuild CAD

Use a Python environment that can import FreeCAD and Part. From an extracted variant directory, run its tools in order: build.py, check.py, check_board.py, thickness.py, export.py. Use Blender background mode with tools/blender.py for visualization; reopen the saved scene with the script's --verify option. See the variant README for the original sequence.

Normal rebuilds use packaged sources. The --bootstrap branch is an author-workspace import procedure and is not a portable build command. Do not run it on a fresh clone. Source QA is retained as historical evidence; no physical fit or electrical performance is implied by reopening a native file.
