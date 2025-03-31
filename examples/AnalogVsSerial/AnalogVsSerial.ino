#include <AGVLineSensor.h>

// Initialize the line sensor with default parameters
AGVLineSensor lineSensor;

void setup() {
    Serial.begin(115200);
    Serial.println("Analog vs Serial Example");

    // Set data source to analog
    lineSensor.setDataSource(AGVLineSensor::ANALOG);
    Serial.println("Data source set to ANALOG.");
}

void loop() {
    // Read line position using the analog data source
    float positionAnalog = lineSensor.getLinePosition();
    bool detectedAnalog = lineSensor.isLineDetected();

    // Switch to serial data source
    lineSensor.setDataSource(AGVLineSensor::SERIAL_COMM);
    float positionSerial = lineSensor.getLinePosition();
    bool detectedSerial = lineSensor.isLineDetected();

    // Switch back to analog data source
    lineSensor.setDataSource(AGVLineSensor::ANALOG);

    // Print results in a single line
    Serial.print("Analog - Position: ");
    Serial.print(positionAnalog);
    Serial.print(", Detected: ");
    Serial.print(detectedAnalog ? "Yes" : "No");
    Serial.print(" | Serial - Position: ");
    Serial.print(positionSerial);
    Serial.print(", Detected: ");
    Serial.println(detectedSerial ? "Yes" : "No");

    delay(2000);
}
