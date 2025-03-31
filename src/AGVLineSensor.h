#ifndef AGVLINESENSOR_H
#define AGVLINESENSOR_H

#include <Arduino.h>

class AGVLineSensor {
public:
    enum DataSource {
        ANALOG, ///< Use analog input to read line position.
        SERIAL_COMM ///< Use serial communication to read line position.
    };

private:
    int analogPin; ///< Analog pin for reading line position.
    int jpulsePin; ///< Pin for detecting junction pulses.
    int digitalSensorPins[8]; ///< Array of digital pins for individual sensors.
    int digitalSensorReadings[8]; ///< Internal array to store sensor readings.
    int uenPin; ///< UEN pin to control serial communication (optional).
    char lsaAddress; ///< Address of the line sensor for serial communication.
    HardwareSerial* serialPort; ///< Serial port used for communication.
    bool lineDetected; ///< Indicates whether a line is detected.
    bool serialOutputEnabled; ///< Tracks whether serial output is enabled.
    DataSource dataSource; ///< Current data source for reading line position.

    static constexpr int defaultDigitalSensorPins[8] = {36, 37, 38, 39, 40, 41, 42, 43}; ///< Default digital sensor pins.

public:
    /**
     * Constructs an AGVLineSensor object with optional custom parameters.
     * 
     * Initializes the sensor with the specified pins and settings. The default
     * configuration uses analog input for line detection and predefined digital pins.
     * 
     * @param[in] analogPin Analog pin for reading line position (default: A0).
     * @param[in] jpulsePin Pin for detecting junction pulses (default: 35).
     * @param[in] digitalSensorPins Array of 8 digital pins for individual sensors (default: defaultDigitalSensorPins).
     * @param[in] uenPin UEN pin to control serial communication (default: 34).
     * @param[in] lsaAddress Address of the line sensor for serial communication (default: 0x01).
     * @param[in] serialPort Serial port used for communication (default: &Serial1).
     * @param[in] source Data source for reading line position (default: ANALOG).
     * 
     * @example
     * AGVLineSensor lineSensor; // Uses default parameters.
     */
    AGVLineSensor(int analogPin = A0, int jpulsePin = 35, const int digitalSensorPins[8] = defaultDigitalSensorPins, int uenPin = 34, char lsaAddress = 0x01, HardwareSerial* serialPort = &Serial1, DataSource source = ANALOG);

    /**
     * Enables serial output by pulling the UEN pin LOW.
     * 
     * This method activates serial communication with the line sensor.
     * 
     * @example
     * lineSensor.enableSerialOutput();
     */
    void enableSerialOutput();

    /**
     * Disables serial output by pulling the UEN pin HIGH.
     * 
     * This method deactivates serial communication with the line sensor.
     * 
     * @example
     * lineSensor.disableSerialOutput();
     */
    void disableSerialOutput();

    /**
     * Checks if serial output is enabled.
     * 
     * @return True if serial output is enabled, false otherwise.
     * 
     * @example
     * bool isEnabled = lineSensor.isSerialOutputEnabled();
     */
    bool isSerialOutputEnabled();

    /**
     * Sets the data source for reading line position.
     * 
     * Configures the sensor to use either analog input or serial communication
     * for detecting the line position.
     * 
     * @param[in] source The data source to set (ANALOG or SERIAL_COMM).
     * 
     * @example
     * lineSensor.setDataSource(AGVLineSensor::SERIAL_COMM);
     */
    void setDataSource(DataSource source);

    /**
     * Sends a command to the line sensor via serial communication.
     * 
     * This method sends a command and associated data to the line sensor.
     * 
     * @param[in] command The command to send.
     * @param[in] data The data associated with the command.
     * 
     * @example
     * lineSensor.sendCommand('C', 0x00); // Sends a calibration command.
     */
    void sendCommand(char command, char data);

    /**
     * Calibrates the line sensor by sending a calibration command.
     * 
     * This method triggers the calibration process for the line sensor.
     * 
     * @example
     * lineSensor.calibrate();
     */
    void calibrate();

    /**
     * Reads the line position from the selected data source.
     * 
     * This method retrieves the line position as a float value. If no line is detected,
     * it returns -1.
     * 
     * @return The line position as a float. Returns -1 if no line is detected.
     * 
     * @example
     * float position = lineSensor.getLinePosition();
     */
    float getLinePosition();

    /**
     * Checks if a line is detected.
     * 
     * @return True if a line is detected, false otherwise.
     * 
     * @example
     * bool detected = lineSensor.isLineDetected();
     */
    bool isLineDetected();

    /**
     * Detects junctions using the jpulse pin.
     * 
     * This method checks if a junction is detected based on the jpulse pin state.
     * 
     * @return True if a junction is detected, false otherwise.
     * 
     * @example
     * bool junction = lineSensor.isJunctionDetected();
     */
    bool isJunctionDetected();

    /**
     * Reads the sensor inputs from the digital sensor pins and updates the internal array.
     * 
     * This method updates the internal array with the current readings from the digital sensor pins.
     * 
     * @example
     * lineSensor.readDigitalSensorInputs();
     */
    void readDigitalSensorInputs();

    /**
     * Gets the internal array of digital sensor readings.
     * 
     * @return A pointer to the internal array of digital sensor readings.
     * 
     * @example
     * const int* readings = lineSensor.getDigitalSensorReadings();
     */
    const int* getDigitalSensorReadings() const;
};

#endif