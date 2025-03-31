#include "AGVLineSensor.h"

// Define the static constexpr array
constexpr int AGVLineSensor::defaultDigitalSensorPins[8];

AGVLineSensor::AGVLineSensor(int analogPin, int jpulsePin, const int digitalSensorPins[8], int uenPin, char lsaAddress, HardwareSerial* serialPort, DataSource source)
    : analogPin(analogPin), jpulsePin(jpulsePin), uenPin(uenPin), lsaAddress(lsaAddress), serialPort(serialPort), lineDetected(false), serialOutputEnabled(false), dataSource(source) {
    for (int i = 0; i < 8; i++) {
        this->digitalSensorPins[i] = digitalSensorPins[i];
    }

    if (uenPin != -1) {
        pinMode(uenPin, OUTPUT);
        if (source == SERIAL_COMM) {
            enableSerialOutput(); // Enable serial output by default for SERIAL_COMM
        } else {
            disableSerialOutput();
        }
    }

    bool isDefaultPins = true;
    for (int i = 0; i < 8; i++) {
        if (digitalSensorPins[i] != defaultDigitalSensorPins[i]) {
            isDefaultPins = false;
            break;
        }
    }

    if (isDefaultPins) {
        Serial.println("Using default digital sensor pins.");
    } else {
        Serial.println("Using custom digital sensor pins.");
    }

    for (int i = 0; i < 8; i++) {
        pinMode(this->digitalSensorPins[i], INPUT);
    }
}

void AGVLineSensor::enableSerialOutput() {
    if (uenPin != -1) {
        digitalWrite(uenPin, LOW);
    }
    serialOutputEnabled = true;
}

void AGVLineSensor::disableSerialOutput() {
    if (uenPin != -1) {
        digitalWrite(uenPin, HIGH);
    }
    serialOutputEnabled = false;
}

bool AGVLineSensor::isSerialOutputEnabled() {
    return serialOutputEnabled;
}

void AGVLineSensor::setDataSource(DataSource source) {
    dataSource = source;
    if (source == SERIAL_COMM) {
        enableSerialOutput(); // Enable serial output when DataSource is SERIAL_COMM
    } else {
        disableSerialOutput(); // Disable serial output for other data sources
    }
}

void AGVLineSensor::sendCommand(char command, char data) {
    serialPort->begin(9600);
    char checksum = lsaAddress + command + data;
    serialPort->write(lsaAddress);
    serialPort->write(command);
    serialPort->write(data);
    serialPort->write(checksum);
}

void AGVLineSensor::calibrate() {
    sendCommand('C', 0x00);
}

float AGVLineSensor::getLinePosition() {
    if (dataSource == ANALOG) {
        float position = analogRead(analogPin) / 920.7 * 70.0;
        lineDetected = position < 70.0;
        return lineDetected ? position : -1;
    } else if (dataSource == SERIAL_COMM && isSerialOutputEnabled()) {
        if (!serialPort) {
            return -1;
        }

        for (int retries = 0; retries < 3; retries++) { // Retry up to 3 times
            serialPort->end(); // Clear the serial buffer
            serialPort->begin(9600); // Reinitialize serial communication
            delay(10); // Allow some time for the sensor to respond

            if (serialPort->available() >= 1) {
                int position = serialPort->read();

                lineDetected = position <= 70; // Corrected condition
                if (lineDetected) {
                    return position; // Return position if line is detected
                }
            }
            delay(5); // Short delay before retrying
        }
    }
    return -1; // Return -1 if no valid data is received after retries
}

bool AGVLineSensor::isLineDetected() {
    return lineDetected;
}

bool AGVLineSensor::isJunctionDetected() {
    return digitalRead(jpulsePin) == HIGH;
}

void AGVLineSensor::readDigitalSensorInputs() {
    for (int i = 0; i < 8; i++) {
        digitalSensorReadings[i] = digitalRead(digitalSensorPins[i]);
    }
}

const int* AGVLineSensor::getDigitalSensorReadings() const {
    return digitalSensorReadings;
}