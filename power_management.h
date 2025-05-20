#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H

#include <stdbool.h>

// Power consumption thresholds (in watts)
#define POWER_THRESHOLD_WARNING 2000
#define POWER_THRESHOLD_CRITICAL 3000

// Power management structure
typedef struct {
    float currentConsumption;
    float peakConsumption;
    float dailyConsumption;
    bool isEcoMode;
} PowerManagement;

// Function declarations
void initPowerManagement(void);
float getCurrentPowerConsumption(void);
float getPeakPowerConsumption(void);
float getDailyPowerConsumption(void);
bool setEcoMode(bool enable);
void updatePowerConsumption(void);
bool isPowerConsumptionCritical(void);
void resetPowerStats(void);

#endif // POWER_MANAGEMENT_H 