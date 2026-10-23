# New build test plan

These are tests to perform on the reconstructed build, not results already measured. Start with indicators/dummy loads and verify the supply and input voltage limits from CIRCUIT.md.

| Input / condition | Expected observation |
|---|---|
| Dry calibrated sensor, full tank | Pump starts |
| Moisture above stop threshold | Pump stops |
| Empty tank, rail-valued input or 20-second pump interval | Pump off; fault latched until reset |

For every test record date, firmware commit, exact component/module, measured supply voltage, input, output and elapsed time. Mark each pass/fail only after observing it. Keep failed trials and calibration readings. Sensor thresholds must be calibrated for the actual module.
