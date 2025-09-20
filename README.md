# Thermistor-Based Temperature Control System

This project demonstrates a **thermistor-based temperature sensing and control system**.  
It combines **Arduino programming** for real-time temperature measurement and fan control, and **Python** for calibration through linear regression.

---

## 📖 Project Overview
- **Temperature Sensing**: Read values from a thermistor using Arduino and calculate temperature using the **Steinhart-Hart equation**.  
- **Fan Control**: Vary fan speed and indicate temperature ranges with LEDs based on the measured temperature.  
- **Data Analysis**: Use Python’s linear regression to model the relationship between temperature and voltage for calibration.

---

## 📂 Repository Structure
- TemperatureSensing.ino # Arduino code for thermistor temperature measurement
- FanControl.ino # Arduino code for fan speed control and LED indicators
- LinearRegression.py # Python script for regression analysis and visualization
- E&E Report.pdf # Full project report
- README.md # Documentation
---
## 🚀 How to Run
### Arduino
Open TemperatureSensing.ino or FanControl.ino in Arduino IDE.

Connect your Arduino board and upload the code.

Open the Serial Monitor to view temperature readings.

Python

Run the linear regression script:

python LinearRegression.py


The script prints regression coefficients and displays a plot of Voltage vs Temperature.
