#include <AGVLineSensor.h>

// Custom pin configuration
const int customDigitalPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// Note: Default pins in this library are configured for Arduino Mega 2560.
// Use custom initialization if using a different board or pin configuration.

// Initialize the line sensor with custom parameters
AGVLineSensor lineSensor(A1, 10, customDigitalPins, 11, 0x02, &Serial2, AGVLineSensor::SERIAL_COMM);

void setup() {
    Serial.begin(115200);
    Serial.println("Custom Initialization Example");
}

void loop() {
    // Read the line position
    float position = lineSensor.getLinePosition();
    if (lineSensor.isLineDetected()) {
        Serial.print("Line position: ");
        Serial.println(position);
    } else {
        Serial.println("No line detected.");
    }

    delay(500);
}
