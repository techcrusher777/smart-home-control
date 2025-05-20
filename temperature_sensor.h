#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <stdbool.h>

// Temperature sensor structure
typedef struct {
    int currentTemp;
    int targetTemp;
    bool isActive;
    float lastReading;
} TemperatureSensor;

// Function declarations
void initTemperatureSensors(void);
int readTemperature(int sensorId);
bool setTargetTemperature(int sensorId, int temperature);
float getTemperatureReading(int sensorId);
void updateTemperatureSensors(void);

// Sensor IDs
#define SENSOR_AC 0
#define SENSOR_FRIDGE 1
#define SENSOR_ROOM 2

#endif // TEMPERATURE_SENSOR_H 