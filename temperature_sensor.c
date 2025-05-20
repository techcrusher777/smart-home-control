#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "temperature_sensor.h"

// Global temperature sensor array
static TemperatureSensor sensors[3];  // AC, Fridge, Room

// Initialize random number generator
static void initRandom(void) {
    static bool initialized = false;
    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }
}

void initTemperatureSensors(void) {
    initRandom();
    
    // Initialize AC sensor
    sensors[SENSOR_AC].currentTemp = 25;
    sensors[SENSOR_AC].targetTemp = 25;
    sensors[SENSOR_AC].isActive = true;
    sensors[SENSOR_AC].lastReading = 25.0;
    
    // Initialize Fridge sensor
    sensors[SENSOR_FRIDGE].currentTemp = 4;
    sensors[SENSOR_FRIDGE].targetTemp = 4;
    sensors[SENSOR_FRIDGE].isActive = true;
    sensors[SENSOR_FRIDGE].lastReading = 4.0;
    
    // Initialize Room sensor
    sensors[SENSOR_ROOM].currentTemp = 22;
    sensors[SENSOR_ROOM].targetTemp = 22;
    sensors[SENSOR_ROOM].isActive = true;
    sensors[SENSOR_ROOM].lastReading = 22.0;
}

int readTemperature(int sensorId) {
    if (sensorId < 0 || sensorId >= 3 || !sensors[sensorId].isActive) {
        return -1;
    }
    
    // Simulate temperature reading with some noise
    float noise = ((float)rand() / RAND_MAX) * 2.0 - 1.0;  // Random value between -1 and 1
    sensors[sensorId].lastReading = sensors[sensorId].currentTemp + noise;
    
    // Update current temperature based on target and some thermal dynamics
    float diff = sensors[sensorId].targetTemp - sensors[sensorId].currentTemp;
    if (abs(diff) > 0.1) {
        // Simulate thermal inertia
        sensors[sensorId].currentTemp += diff * 0.1;
    }
    
    return (int)sensors[sensorId].currentTemp;
}

bool setTargetTemperature(int sensorId, int temperature) {
    if (sensorId < 0 || sensorId >= 3 || !sensors[sensorId].isActive) {
        return false;
    }
    
    // Validate temperature ranges based on sensor type
    switch (sensorId) {
        case SENSOR_AC:
            if (temperature < 16 || temperature > 30) {
                return false;
            }
            break;
        case SENSOR_FRIDGE:
            if (temperature < 2 || temperature > 8) {
                return false;
            }
            break;
        case SENSOR_ROOM:
            if (temperature < 16 || temperature > 30) {
                return false;
            }
            break;
    }
    
    sensors[sensorId].targetTemp = temperature;
    return true;
}

float getTemperatureReading(int sensorId) {
    if (sensorId < 0 || sensorId >= 3 || !sensors[sensorId].isActive) {
        return -1.0;
    }
    return sensors[sensorId].lastReading;
}

void updateTemperatureSensors(void) {
    // Update room temperature based on AC status and ambient conditions
    if (sensors[SENSOR_AC].isActive) {
        float acEffect = 0.0;
        if (sensors[SENSOR_AC].currentTemp < sensors[SENSOR_ROOM].currentTemp) {
            // Cooling effect
            acEffect = -0.1;
        } else if (sensors[SENSOR_AC].currentTemp > sensors[SENSOR_ROOM].currentTemp) {
            // Heating effect
            acEffect = 0.1;
        }
        
        // Apply AC effect to room temperature
        sensors[SENSOR_ROOM].currentTemp += acEffect;
        
        // Add some ambient temperature variation
        float ambientEffect = ((float)rand() / RAND_MAX) * 0.2 - 0.1;
        sensors[SENSOR_ROOM].currentTemp += ambientEffect;
    }
    
    // Update all sensor readings
    for (int i = 0; i < 3; i++) {
        if (sensors[i].isActive) {
            readTemperature(i);
        }
    }
} 