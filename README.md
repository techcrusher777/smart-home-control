# smart-home-control
 Smart Home Control System - An embedded systems project for smart appliance management
#  Smart Home Control System

![ Smart Home Control System]

A comprehensive smart home control system for LG appliances, designed for embedded systems and interview purposes. This project demonstrates real-time control, monitoring, and energy management capabilities for smart home appliances.

1. 📋 Table of Contents
- [Features](#features)
- [Preview](#preview)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Technical Details](#technical-details)
- [Development](#development)
- [Contributing](#contributing)
- [License](#license)

2. ✨ Features

* Core Features
- **Appliance Control**: Manage AC, refrigerator, and washing machine
- **Temperature Management**: Real-time temperature monitoring and control
- **Power Management**: Track and optimize power consumption
- **Web Interface**: Modern, responsive control panel

3. Power Consumption Analysis
- **Interactive Graphs**: Real-time visualization of power consumption and savings
- **Time-based Analysis**: View consumption data for:
  - Last 24 hours
  - Last 7 days
  - Last 30 days
- **Energy Savings Tracking**:
  - Total power consumption monitoring
  - Energy savings calculation
  - Cost savings estimation
- **Eco Mode Integration**:
  - Toggle eco mode for energy optimization
  - Visual feedback on savings impact
  - Automatic power consumption adjustments

4. 🖼️ Preview

 Web Interface
![Web Interface]
*Modern, responsive web interface for controlling appliances*

 Power Consumption Graph
![Power Graph]
*Interactive power consumption and savings visualization*

 Appliance Control
![Appliance Control]
*Individual appliance control cards with real-time status*

4. 📁 Project Structure
```
lg-smart-home/
├── src/                    # Source files
│   ├── main.c             # Main program entry point
│   ├── appliance_control.c # Appliance control implementation
│   ├── temperature_sensor.c # Temperature sensor implementation
│   └── power_management.c  # Power management implementation
├── include/                # Header files
│   ├── appliance_control.h
│   ├── temperature_sensor.h
│   └── power_management.h
├── web/                    # Web interface
│   ├── home.html          # Main web interface
│   └── style.css          # Styling
├── docs/                   # Documentation
│   └── images/            # Screenshots and diagrams
├── Makefile               # Build configuration
└── README.md             # Project documentation
```

5. 🚀 Installation

 Prerequisites
- GCC compiler (MinGW for Windows)
- Make utility
- Modern web browser
- Git

 Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/lg-smart-home-control.git
   cd lg-smart-home-control
   ```

2. Build the project:
   ```bash
   make clean
   make
   ```

3. Run the system:
   ```bash
   make run
   ```

4. Open the web interface:
   - Open `web/home.html` in your web browser

6. 💻 Usage

 Command Line Interface
```bash
# Basic Commands
help                    # Show available commands
status                  # Display system status
toggle ac              # Toggle AC power
temp ac 25             # Set AC temperature to 25°C
mode washer eco        # Set washer to eco mode
eco                    # Enable eco mode

# Power Management
power status           # Show power consumption
power graph           # Display power consumption graph
power savings         # Show energy savings
```

7. Web Interface
1. **Appliance Control**
   - Power toggle buttons
   - Temperature sliders
   - Mode selection
   - Status indicators

2. **Power Consumption Analysis**
   - Interactive time-based graphs
   - Energy savings visualization
   - Cost calculation
   - Eco mode toggle

8. 🔧 Technical Details

 Temperature Control
- AC: 16°C to 30°C
- Refrigerator: 2°C to 8°C
- Real-time temperature monitoring
- Automatic temperature regulation

 Power Management
- Real-time power consumption tracking
- Energy savings calculation
- Cost estimation (based on local rates)
- Eco mode optimization
- Historical data analysis

 👨‍💻 Development

 Building from Source
1. Install dependencies:
   - MinGW (for Windows)
   - Make utility
   - Git

2. Clone and build:
   ```bash
   git clone https://github.com/techcrusher777/lg-smart-home-control.git
   cd lg-smart-home-control
   make
   ```

 Running Tests
```bash
make test
```

 🤝 Contributing
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

 📝 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

 📸 Screenshots
   ![homeinterface](https://github.com/user-attachments/assets/af0a9690-f4f1-4168-9ce1-0f53cac1ff64)
   ![graph](https://github.com/user-attachments/assets/c5614dc4-6fc6-454d-b8e1-33fa9d04fdc6)
   ![help and quide](https://github.com/user-attachments/assets/a976cc1b-079e-4f4d-906d-936edd1e5340)




 🔗 Links
- [Project Documentation]
- [Issue Tracker](https://github.com/techcrusher777/lg-smart-home-control/issues)
- [Pull Requests](https://github.com/techcursher777/lg-smart-home-control/pulls)
