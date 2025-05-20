CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

SRCS = main.c appliance_control.c temperature_sensor.c power_management.c
OBJS = $(SRCS:.c=.o)
TARGET = smart_home_system

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Development targets
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Run the program
run: all
	./$(TARGET)

# Documentation
docs:
	@echo "Smart Home Control System Documentation"
	@echo "====================================="
	@echo "Build targets:"
	@echo "  make        - Build the system"
	@echo "  make debug  - Build with debug symbols"
	@echo "  make clean  - Remove built files"
	@echo "  make run    - Build and run the system"
	@echo ""
	@echo "Available commands in the system:"
	@echo "  toggle <appliance> - Toggle appliance power"
	@echo "  temp <appliance> <value> - Set temperature"
	@echo "  mode <appliance> <value> - Set mode"
	@echo "  status - Show system status"
	@echo "  eco - Enable eco mode"
	@echo "  help - Show help"
	@echo "  exit - Exit program" 