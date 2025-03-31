#include <AGVLineSensor.h>

// Initialize the line sensor with default parameters
AGVLineSensor lineSensor;

void setup() {
    Serial.begin(115200);
    Serial.println("Calibration and Commands Example");

    // Calibrate the line sensor
    Serial.println("Calibrating the line sensor...");
    lineSensor.calibrate();
    delay(5000);
    Serial.println("Calibration complete.");
}

void loop() {
    // Send a custom command to the line sensor
    Serial.println("Sending custom command...");
    lineSensor.sendCommand('C', 0x00); // Callibrate command
    delay(2000);
}
