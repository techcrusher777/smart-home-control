#include <stdio.h>
#include <time.h>
#include "power_management.h"
#include "appliance_control.h"

// Global power management structure
static PowerManagement powerMgmt;

// Time tracking for daily consumption
static time_t lastUpdateTime;
static float hourlyConsumption[24] = {0};

void initPowerManagement(void) {
    powerMgmt.currentConsumption = 0;
    powerMgmt.peakConsumption = 0;
    powerMgmt.dailyConsumption = 0;
    powerMgmt.isEcoMode = false;
    lastUpdateTime = time(NULL);
    
    // Initialize hourly consumption array
    for (int i = 0; i < 24; i++) {
        hourlyConsumption[i] = 0;
    }
}

float getCurrentPowerConsumption(void) {
    return powerMgmt.currentConsumption;
}

float getPeakPowerConsumption(void) {
    return powerMgmt.peakConsumption;
}

float getDailyPowerConsumption(void) {
    return powerMgmt.dailyConsumption;
}

bool setEcoMode(bool enable) {
    if (powerMgmt.isEcoMode == enable) {
        return false;  // No change
    }
    
    powerMgmt.isEcoMode = enable;
    
    // Apply eco mode settings
    if (enable) {
        // Reduce AC temperature by 1 degree
        setApplianceTemperature(APPLIANCE_AC, 
            getApplianceStatus(APPLIANCE_AC).temperature - 1);
        
        // Set washer to eco mode if it's on
        if (getApplianceStatus(APPLIANCE_WASHER).isOn) {
            setApplianceMode(APPLIANCE_WASHER, WASHER_MODE_ECO);
        }
    }
    
    return true;
}

void updatePowerConsumption(void) {
    // Get current total power consumption
    powerMgmt.currentConsumption = getTotalPowerConsumption();
    
    // Update peak consumption if necessary
    if (powerMgmt.currentConsumption > powerMgmt.peakConsumption) {
        powerMgmt.peakConsumption = powerMgmt.currentConsumption;
    }
    
    // Update time-based consumption tracking
    time_t currentTime = time(NULL);
    struct tm* timeInfo = localtime(&currentTime);
    int currentHour = timeInfo->tm_hour;
    
    // Calculate time difference in hours
    double hoursDiff = difftime(currentTime, lastUpdateTime) / 3600.0;
    
    if (hoursDiff >= 1.0) {
        // Update hourly consumption
        hourlyConsumption[currentHour] += powerMgmt.currentConsumption * hoursDiff;
        
        // Update daily consumption
        powerMgmt.dailyConsumption = 0;
        for (int i = 0; i < 24; i++) {
            powerMgmt.dailyConsumption += hourlyConsumption[i];
        }
        
        // Reset hourly consumption at midnight
        if (currentHour == 0) {
            for (int i = 0; i < 24; i++) {
                hourlyConsumption[i] = 0;
            }
        }
        
        lastUpdateTime = currentTime;
    }
    
    // Check for critical power consumption
    if (isPowerConsumptionCritical()) {
        printf("WARNING: Critical power consumption detected!\n");
        if (powerMgmt.isEcoMode) {
            // In eco mode, try to reduce consumption
            if (getApplianceStatus(APPLIANCE_AC).isOn) {
                setApplianceMode(APPLIANCE_AC, AC_MODE_FAN);
            }
        }
    }
}

bool isPowerConsumptionCritical(void) {
    return powerMgmt.currentConsumption >= POWER_THRESHOLD_CRITICAL;
}

void resetPowerStats(void) {
    powerMgmt.peakConsumption = 0;
    powerMgmt.dailyConsumption = 0;
    for (int i = 0; i < 24; i++) {
        hourlyConsumption[i] = 0;
    }
    lastUpdateTime = time(NULL);
} 