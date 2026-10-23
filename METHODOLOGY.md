# Smart Irrigation System: methodology

Status: researched reconstruction / proposed evaluation, prepared 23 October 2026. Not a recovered lab notebook.

## Existing account

Monitors soil moisture and switches a relay-controlled water pump when readings fall below a configured threshold. Uses Arduino UNO, a capacitive moisture sensor, and pump-status indicators.

The account above comes from the existing portfolio and is not independent verification. Listed stack: Arduino UNO, C++, Capacitive Soil Moisture Sensor, 5V Relay Module, 12V DC Pump, Analog Sensors. Exact components and versions still need confirmation.

## System architecture

Soil reading -> calibrated dryness -> hysteresis/timer -> pump command -> status

## Proposed engineering workflow

1. Measure dry and wet references in the actual soil; record which direction indicates dryness.
2. Use separate start/stop thresholds to avoid relay chatter.
3. Add a maximum pump-on interval and a sensor-fault off state.
4. Compare collected water volume under matched conditions rather than inferring savings from automation.

## Evaluation plan, not results

Record: Pump runtime; dispensed volume; switching count; timeout behavior. Use explicit units, test conditions, a baseline where relevant, repeated observations and a timestamped log. Report failure cases alongside successes. No numerical result is available from this reconstruction.

## Limitations and claim boundaries

Pinout, pump current and thresholds are unverified. Demonstrate logic with simulated inputs before hardware use.

## Design questions for an interview

- Explain the input, decision and output paths in the architecture above.
- What concrete fault would invalidate the output, and how would you detect it?
- Which design decision did you personally make, and what evidence do you retain?
- Which part of this proposed workflow differs from what you actually built?

## Research basis

[Arduino built-in examples](https://docs.arduino.cc/built-in-examples) — consulted 23 October 2026. This source supports the underlying engineering topic, not the historical implementation. Workflow and evaluation proposals above are original analysis for this project.
