#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "appliance_control.h"
#include "temperature_sensor.h"
#include "power_management.h"

#define UPDATE_INTERVAL 1  // Update interval in seconds
#define MAX_COMMAND_LENGTH 256

// Function to process user commands
void processCommand(const char* command) {
    char cmd[MAX_COMMAND_LENGTH];
    char appliance[32];
    int value;
    
    if (sscanf(command, "%s %s %d", cmd, appliance, &value) >= 2) {
        ApplianceType type;
        
        // Determine appliance type
        if (strcmp(appliance, "ac") == 0) {
            type = APPLIANCE_AC;
        } else if (strcmp(appliance, "fridge") == 0) {
            type = APPLIANCE_FRIDGE;
        } else if (strcmp(appliance, "washer") == 0) {
            type = APPLIANCE_WASHER;
        } else {
            printf("Unknown appliance: %s\n", appliance);
            return;
        }

        // Process command
        if (strcmp(cmd, "toggle") == 0) {
            if (toggleAppliance(type)) {
                printf("%s turned %s\n", appliance, 
                    getApplianceStatus(type).isOn ? "ON" : "OFF");
            }
        } else if (strcmp(cmd, "temp") == 0) {
            if (setApplianceTemperature(type, value)) {
                printf("%s temperature set to %d°C\n", appliance, value);
            }
        } else if (strcmp(cmd, "mode") == 0) {
            if (setApplianceMode(type, value)) {
                printf("%s mode set to %d\n", appliance, value);
            }
        }
    } else if (strcmp(command, "status") == 0) {
        // Display system status
        printf("\nSystem Status:\n");
        printf("Total Power Consumption: %.2f W\n", getCurrentPowerConsumption());
        printf("Daily Consumption: %.2f kWh\n", getDailyPowerConsumption());
        
        for (int i = 0; i < APPLIANCE_COUNT; i++) {
            ApplianceStatus status = getApplianceStatus(i);
            const char* names[] = {"AC", "Refrigerator", "Washing Machine"};
            printf("\n%s:\n", names[i]);
            printf("  Status: %s\n", status.isOn ? "ON" : "OFF");
            printf("  Temperature: %d°C\n", status.temperature);
            printf("  Power: %.2f W\n", status.powerConsumption);
        }
    } else if (strcmp(command, "eco") == 0) {
        setEcoMode(true);
        printf("Eco mode enabled\n");
    } else if (strcmp(command, "help") == 0) {
        printf("\nAvailable commands:\n");
        printf("  toggle <appliance> - Toggle appliance power\n");
        printf("  temp <appliance> <value> - Set temperature\n");
        printf("  mode <appliance> <value> - Set mode\n");
        printf("  status - Show system status\n");
        printf("  eco - Enable eco mode\n");
        printf("  help - Show this help\n");
        printf("  exit - Exit program\n\n");
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    
    // Initialize all subsystems
    printf("Initializing LG Smart Home System...\n");
    initAppliances();
    initTemperatureSensors();
    initPowerManagement();
    
    printf("System initialized. Type 'help' for available commands.\n");
    
    // Main program loop
    while (1) {
        // Update system status
        updateApplianceStatus();
        updateTemperatureSensors();
        updatePowerConsumption();
        
        // Check for user input
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) != NULL) {
            // Remove newline
            command[strcspn(command, "\n")] = 0;
            
            if (strcmp(command, "exit") == 0) {
                printf("Shutting down system...\n");
                break;
            }
            
            processCommand(command);
        }
        
        // Sleep for update interval
        sleep(UPDATE_INTERVAL);
    }
    
    return 0;
} 