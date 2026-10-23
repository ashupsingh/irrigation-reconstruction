# irrigation: new reconstruction circuit

This is the new wiring design for the regenerated version, not a recovered original schematic. Ashutosh reports using ESP32, UNO and some Raspberry Pi testing across the original projects.

## Bill of materials

Capacitive moisture sensor; tank-level dry contact; reset button; DC pump with rated MOSFET driver and flyback protection.

## Pin map

| Symbol | Classic ESP32 DevKit | Arduino UNO |
|---|---|---|
| SENSOR | GPIO34 (ADC1) | A0 |
| INPUT_A | GPIO27 | D2 |
| INPUT_B | GPIO14 | D3 |
| OUT | GPIO26 | D8 |
| AUX | GPIO25 | D9 |

SENSOR = soil analog output; INPUT_A = water-available contact to GND; INPUT_B = reset button to GND; OUT = pump driver input.

## Connections and power

```text
Sensor signal -> voltage-compatible input in pin table -> MCU
MCU OUT/AUX -> rated driver input -> low-voltage load
MCU GND ----- sensor GND ----- driver logic GND
Separate load supply -> fuse/protection -> driver/load
```

ESP32 pins are not 5 V tolerant. For a 5 V analog or echo signal, a 10 kOhm upper and 15 kOhm lower divider yields approximately 3 V at 5 V input; verify the real voltage with a meter. This is not needed for a signal already constrained to 3.3 V. Use a common ground, input pull-down on active-high driver gates, decoupling and inductive suppression. Never power motors, servos, pumps, heaters or solenoids directly from a GPIO. Start with LEDs/dummy loads. GPIO34/35 are input-only; the sketches use them only as ADC inputs.

## Operating contract and limits

Recalibrate DRY_RAW/WET_RAW in the actual medium. Rail checks detect some wiring faults, not all. The pump timeout latches until reset.

## Build

Open `reconstruction/firmware/firmware.ino` in Arduino IDE. Select **ESP32 Dev Module** for the classic ESP32 or **Arduino Uno**. Install the matching board core. Servo sketches need ESP32Servo on ESP32, Servo on UNO. Fingerprint sketches need the Adafruit Fingerprint Sensor Library. The MPU6050 sketch uses Wire directly. Serial output is 115200 baud.

This firmware is newly reconstructed. Hardware operation and sensor calibration have not been performed here. See VALIDATION.md for exactly which checks were run.
