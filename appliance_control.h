#ifndef APPLIANCE_CONTROL_H
#define APPLIANCE_CONTROL_H

#include <stdbool.h>

// Appliance types
typedef enum {
    APPLIANCE_AC,
    APPLIANCE_FRIDGE,
    APPLIANCE_WASHER,
    APPLIANCE_COUNT
} ApplianceType;

// AC modes
typedef enum {
    AC_MODE_COOL,
    AC_MODE_HEAT,
    AC_MODE_FAN,
    AC_MODE_DRY
} ACMode;

// Washer modes
typedef enum {
    WASHER_MODE_NORMAL,
    WASHER_MODE_QUICK,
    WASHER_MODE_ECO,
    WASHER_MODE_HEAVY
} WasherMode;

// Appliance status structure
typedef struct {
    bool isOn;
    int temperature;
    union {
        ACMode acMode;
        WasherMode washerMode;
    } mode;
    float powerConsumption;
} ApplianceStatus;

// Function declarations
void initAppliances(void);
bool toggleAppliance(ApplianceType type);
bool setApplianceMode(ApplianceType type, int mode);
bool setApplianceTemperature(ApplianceType type, int temperature);
ApplianceStatus getApplianceStatus(ApplianceType type);
float getTotalPowerConsumption(void);
void updateApplianceStatus(void);

#endif // APPLIANCE_CONTROL_H 