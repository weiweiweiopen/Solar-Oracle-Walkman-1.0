# Energy estimate basis

These are calculations from the current schematic plus explicit assumptions, **not measurements**.

## Charging

- C1–C3: three **1.5 F, 5 V-rated** capacitors in parallel: nominal **4.5 F**.
- AEM10941 custom configuration: R80=549 kΩ, R81=9.31 kΩ, R82=143 kΩ, R83=1.74 MΩ.
- With `RT = R80 + R81 + R82 + R83`, the datasheet's nominal 1 V threshold equations give:
  - Full: `RT / R80 = 4.44683 V`.
  - Ready: `RT / (R80 + R81) = 4.37268 V`.
  - Undervoltage: `RT / (R80 + R81 + R82) = 3.48107 V`.
- Both SELMPP pins are low: the harvester targets **70% of Voc**. This fixed ratio is not proof of the actual DSSC maximum-power point.

```text
E = ½ C V²
Energy from empty to full = 44.49 J
Energy from cutoff to full = 17.23 J

Pinput = 0.7 V × 0.030 A = 0.021 W   [only if simultaneous under load]
Assumed net charging power = 60–80% × Pinput = 12.6–16.8 mW
Time = energy / net charging power

Empty → full: 44.1–58.9 minutes
Cutoff → full: 17.1–22.8 minutes
```

The net-efficiency assumption includes conversion and standby/leakage losses; it is not a datasheet efficiency guarantee. Cold-start behavior, capacitance tolerance and changing illumination can extend charging time. These times assume charging is not interrupted by measurement activity.

If the cell rating is **Voc=0.7 V and Isc=30 mA**, use measured maximum-power output instead. For illustration only, fill factor 0.5–0.7 gives 10.5–14.7 mW input. Combined with the same assumed efficiency range, empty-to-full becomes approximately **63–118 minutes**. No fill factor has been measured for this particular cell.

## Measurement count

The nominal energy between **ready and cutoff** is **15.76 J**. Using −10% initial capacitance tolerance and a further 20% engineering reserve gives:

```text
15.76 J × 0.9 × 0.8 = 11.34 J conservative planning budget
N = floor(11.34 J / energy per complete cycle)

Assumed 2 J/cycle → 5 cycles
Assumed 5 J/cycle → 2 cycles
```

Using the ready threshold rather than full is deliberate: the system can become eligible to wake before reaching full charge. Count estimates assume no replenishment between cycles and must include boot, scan, analog circuitry, display update, relay hold, radio activity, converter loss and any idle interval.

K1 is **Omron G6K-2F-Y DC5**: nominal 237 Ω coil, approximately 21.1 mA / 105.5 mW at 5 V. At an illustrative 6.4 s hold time, its coil alone consumes about **0.675 J at 5 V**, or **0.794 J from storage** assuming 85% 5 V converter efficiency. This is not the energy of a complete measurement cycle. The 2–5 J/cycle range remains an assumption until firmware and hardware are measured.

## Sources

- [AEM10941 datasheet](https://e-peas.com/documents/AEM10941/DS-AEM10941.pdf): cold start, MPPT selection and custom threshold equations.
- [TPS61023](https://www.ti.com/product/TPS61023): stored-energy-to-5 V boost converter.
- [Omron G6K](https://components.omron.com/us-en/products/relays/G6K): DC5 coil ratings.
- Current [BOM](../hardware/BOM.csv), [POWER schematic](../hardware/power.kicad_sch) and [SWITCHING schematic](../hardware/switching.kicad_sch).
