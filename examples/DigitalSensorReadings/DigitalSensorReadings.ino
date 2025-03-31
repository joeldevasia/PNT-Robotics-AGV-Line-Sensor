#include <AGVLineSensor.h>

// Initialize the line sensor with default parameters
AGVLineSensor lineSensor;

void setup() {
    Serial.begin(115200);
    Serial.println("Digital Sensor Readings Example");
}

void loop() {
    // Read digital sensor inputs
    lineSensor.readDigitalSensorInputs();
    const int* readings = lineSensor.getDigitalSensorReadings();

    // Print the readings
    Serial.print("Digital Sensor Readings: ");
    for (int i = 0; i < 8; i++) {
        Serial.print(readings[i]);
        Serial.print(" ");
    }
    Serial.println();

    delay(500);
}
