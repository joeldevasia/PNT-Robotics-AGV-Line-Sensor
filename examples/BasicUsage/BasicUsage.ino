#include <AGVLineSensor.h>

// Initialize the line sensor with default parameters
AGVLineSensor lineSensor;

void setup() {
    Serial.begin(115200);
    Serial.println("AGV Line Sensor Example");
}

void loop() {
    // Read the line position
    float position = lineSensor.getLinePosition();
    Serial.print("Line position: ");
    Serial.print(position);
    Serial.print(", Line detected: ");
    Serial.print(lineSensor.isLineDetected() ? "Yes" : "No");
    Serial.print(", Junction detected: ");
    Serial.println(lineSensor.isJunctionDetected() ? "Yes" : "No");

    delay(500);
}
