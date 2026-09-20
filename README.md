# Self-Powered IV Curve Tester with Single DSSC

An experimental design that **harvests energy from one dye-sensitized solar cell, then measures that same cell's I–V curve**. It uses 16 test loads, an ADS122C04 ADC, ESP32-S3 and e-paper display.

[One-page overview](https://weiweiweiopen.github.io/self-powered-iv-curve-tester-with-single-dssc/) · [KiCad project](hardware/solar-oracle-walkman-relay.kicad_pro) · [Energy calculations](docs/energy-budget.md)

## How can 0.7 V charge the system?

**U7, AEM10941, boosts the voltage** into three parallel 1.5 F supercapacitors (**4.5 F total**). It specifies cold start around **0.38 V / 3 µW**; this board targets **70% of Voc** for MPPT.

**0.7 V × 30 mA = 21 mW** if measured simultaneously under load. Energy accumulates with the main electronics off. **U8, TPS61023, then supplies 5 V** for short controller/relay operating bursts.

## Charging time and measurement count

| Item | Planning estimate—not a measured result |
|---|---|
| Storage thresholds | Ready ≈4.37 V; full ≈4.45 V; low-energy cutoff ≈3.48 V |
| Empty → full | **About 45–60 minutes** |
| Cutoff → full | **About 17–23 minutes** |
| Measurements per charge | **Roughly 2–5 complete cycles**, assuming **2–5 J drawn from storage per cycle** and an ≈11 J conservative usable budget |

Assumptions: continuous **21 mW under load**, **60–80% net charging efficiency**, electronics off while charging. If **0.7 V / 30 mA are Voc / Isc**, their product is not usable power: an assumed 0.5–0.7 fill factor gives about **1–2 hours** from empty. Lighting and cycle energy must be measured.

## What does K1 do?

**K1 switches the cell's positive terminal:**

- **Off:** cell → harvester; no coil holding power.
- **On:** cell → test loads, disconnected from the harvester input during the sweep.

Its non-latching coil uses **5 V, ~21 mA (~0.105 W)** from storage during measurement. Ground remains shared.

## Files and status

Open `hardware/solar-oracle-walkman-relay.kicad_pro` in **KiCad 10**. Schematics, libraries/models, BOM and matching GPIO definitions are included.

**PCB:** 0 unrouted, 0 DRC errors, 6 silkscreen warnings. **Prototype:** performance unmeasured; firmware is the GPIO/startup layer, with the measurement application still pending. [Verification](docs/verification.md).

Based on [IVcurve_tester](https://github.com/weiweiweiopen/IVcurve_tester), originally by Marc Dusseiller. See [LICENSE](LICENSE).
