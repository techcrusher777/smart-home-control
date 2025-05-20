#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appliance_control.h"
#include "temperature_sensor.h"
#include "power_management.h"

// Global appliance status array
static ApplianceStatus appliances[APPLIANCE_COUNT];

// Power consumption constants (in watts)
#define AC_POWER_CONSUMPTION 1500
#define FRIDGE_POWER_CONSUMPTION 200
#define WASHER_POWER_CONSUMPTION 2000

void initAppliances(void) {
    // Initialize AC
    appliances[APPLIANCE_AC].isOn = false;
    appliances[APPLIANCE_AC].temperature = 25;
    appliances[APPLIANCE_AC].mode.acMode = AC_MODE_COOL;
    appliances[APPLIANCE_AC].powerConsumption = 0;

    // Initialize Refrigerator
    appliances[APPLIANCE_FRIDGE].isOn = true;  // Fridge is always on
    appliances[APPLIANCE_FRIDGE].temperature = 4;
    appliances[APPLIANCE_FRIDGE].powerConsumption = FRIDGE_POWER_CONSUMPTION;

    // Initialize Washing Machine
    appliances[APPLIANCE_WASHER].isOn = false;
    appliances[APPLIANCE_WASHER].mode.washerMode = WASHER_MODE_NORMAL;
    appliances[APPLIANCE_WASHER].powerConsumption = 0;
}

bool toggleAppliance(ApplianceType type) {
    if (type >= APPLIANCE_COUNT) {
        return false;
    }

    // Special case for fridge - can't be turned off
    if (type == APPLIANCE_FRIDGE) {
        return false;
    }

    appliances[type].isOn = !appliances[type].isOn;
    
    // Update power consumption
    if (appliances[type].isOn) {
        switch (type) {
            case APPLIANCE_AC:
                appliances[type].powerConsumption = AC_POWER_CONSUMPTION;
                break;
            case APPLIANCE_WASHER:
                appliances[type].powerConsumption = WASHER_POWER_CONSUMPTION;
                break;
            default:
                break;
        }
    } else {
        appliances[type].powerConsumption = 0;
    }

    return true;
}

bool setApplianceMode(ApplianceType type, int mode) {
    if (type >= APPLIANCE_COUNT || !appliances[type].isOn) {
        return false;
    }

    switch (type) {
        case APPLIANCE_AC:
            if (mode >= AC_MODE_COOL && mode <= AC_MODE_DRY) {
                appliances[type].mode.acMode = mode;
                // Adjust power consumption based on mode
                if (mode == AC_MODE_FAN) {
                    appliances[type].powerConsumption = AC_POWER_CONSUMPTION * 0.3;
                } else {
                    appliances[type].powerConsumption = AC_POWER_CONSUMPTION;
                }
                return true;
            }
            break;
            
        case APPLIANCE_WASHER:
            if (mode >= WASHER_MODE_NORMAL && mode <= WASHER_MODE_HEAVY) {
                appliances[type].mode.washerMode = mode;
                // Adjust power consumption based on mode
                switch (mode) {
                    case WASHER_MODE_ECO:
                        appliances[type].powerConsumption = WASHER_POWER_CONSUMPTION * 0.7;
                        break;
                    case WASHER_MODE_QUICK:
                        appliances[type].powerConsumption = WASHER_POWER_CONSUMPTION * 0.5;
                        break;
                    default:
                        appliances[type].powerConsumption = WASHER_POWER_CONSUMPTION;
                }
                return true;
            }
            break;
            
        default:
            break;
    }
    
    return false;
}

bool setApplianceTemperature(ApplianceType type, int temperature) {
    if (type >= APPLIANCE_COUNT || !appliances[type].isOn) {
        return false;
    }

    switch (type) {
        case APPLIANCE_AC:
            if (temperature >= 16 && temperature <= 30) {
                appliances[type].temperature = temperature;
                setTargetTemperature(SENSOR_AC, temperature);
                return true;
            }
            break;
            
        case APPLIANCE_FRIDGE:
            if (temperature >= 2 && temperature <= 8) {
                appliances[type].temperature = temperature;
                setTargetTemperature(SENSOR_FRIDGE, temperature);
                return true;
            }
            break;
            
        default:
            break;
    }
    
    return false;
}

ApplianceStatus getApplianceStatus(ApplianceType type) {
    if (type >= APPLIANCE_COUNT) {
        ApplianceStatus empty = {0};
        return empty;
    }
    return appliances[type];
}

float getTotalPowerConsumption(void) {
    float total = 0;
    for (int i = 0; i < APPLIANCE_COUNT; i++) {
        total += appliances[i].powerConsumption;
    }
    return total;
}

void updateApplianceStatus(void) {
    // Update AC status based on temperature sensor
    if (appliances[APPLIANCE_AC].isOn) {
        int currentTemp = readTemperature(SENSOR_AC);
        int targetTemp = appliances[APPLIANCE_AC].temperature;
        
        // Simulate temperature control
        if (appliances[APPLIANCE_AC].mode.acMode == AC_MODE_COOL && currentTemp > targetTemp) {
            // Cooling in progress
            appliances[APPLIANCE_AC].powerConsumption = AC_POWER_CONSUMPTION;
        } else if (appliances[APPLIANCE_AC].mode.acMode == AC_MODE_HEAT && currentTemp < targetTemp) {
            // Heating in progress
            appliances[APPLIANCE_AC].powerConsumption = AC_POWER_CONSUMPTION;
        } else {
            // Temperature reached, reduce power
            appliances[APPLIANCE_AC].powerConsumption = AC_POWER_CONSUMPTION * 0.3;
        }
    }

    // Update fridge status
    if (appliances[APPLIANCE_FRIDGE].isOn) {
        int currentTemp = readTemperature(SENSOR_FRIDGE);
        int targetTemp = appliances[APPLIANCE_FRIDGE].temperature;
        
        // Simulate fridge compressor cycling
        if (currentTemp > targetTemp + 1) {
            appliances[APPLIANCE_FRIDGE].powerConsumption = FRIDGE_POWER_CONSUMPTION;
        } else if (currentTemp < targetTemp - 1) {
            appliances[APPLIANCE_FRIDGE].powerConsumption = FRIDGE_POWER_CONSUMPTION * 0.1;
        }
    }
} 