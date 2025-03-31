# AGVLineSensor Library

An Arduino library for interfacing with the Cytron LSA08 line sensor used in Autonomous Ground Vehicles (AGVs) created by PNT Robotics.

## Features

- Support for both analog and serial communication interfaces
- Junction detection
- Individual sensor reading access
- Configurable pins and parameters

## Installation

1. Download this repository as a ZIP file.
2. In Arduino IDE: Sketch -> Include Library -> Add .ZIP Library...
3. Select the downloaded ZIP file.

## Usage

### Default Pins and Parameters

The default pins and parameters used in this library are configured for the Arduino Mega 2560. If you are using a different board, you may need to use custom initialization to specify the correct pins.

| Function                | Default Pin(s)                      | Default Parameter |
|-------------------------|-------------------------------------|-------------------|
| Analog Line Sensor Pin  | A0                                  |                   |
| Junction Pulse Pin      | 35                                  |                   |
| Digital Sensor Pins     | 36, 37, 38, 39, 40, 41, 42, 43      |                   |
| UEN Pin                 | 34                                  |                   |
| Serial Address          |                                     | 0x01              |
| Serial Port             |                                     | &Serial1          |
| Data Source             |                                     | ANALOG            |

### Basic Example

```cpp
#include <AGVLineSensor.h>

// Initialize with default settings
AGVLineSensor lineSensor;

void setup() {
    Serial.begin(115200);
}

void loop() {
    float position = lineSensor.getLinePosition();
  
    Serial.print("Line position: ");
    Serial.print(position);
    Serial.print(", Line detected: ");
    Serial.print(lineSensor.isLineDetected() ? "Yes" : "No");
    Serial.print(", Junction detected: ");
    Serial.println(lineSensor.isJunctionDetected() ? "Yes" : "No");

    delay(500);
}
```

### Advanced Features

- **Custom Initialization**: Configure the sensor with custom pins and parameters.
- **Calibration**: Calibrate the sensor for optimal performance.
- **Digital Sensor Readings**: Access individual sensor outputs.
- **Analog vs Serial Comparison**: Switch between analog and serial data sources.

## Examples

The library includes the following examples:

1. **BasicUsage**: Demonstrates basic functionality.
2. **CustomInitialization**: Shows how to initialize the sensor with custom parameters.
3. **CalibrationAndCommands**: Demonstrates calibration and sending custom commands.
4. **DigitalSensorReadings**: Shows how to read individual digital sensor outputs.
5. **AnalogVsSerial**: Compares results from analog and serial data sources.

## Documentation

See the header file and example sketches for detailed documentation.

## Author

- **Joel Devasia**  
  GitHub: [joeldevasia](https://github.com/joeldevasia)
