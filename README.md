# ECU-Communication-Using-CAN-Protocol

Project Overview

This project demonstrates the implementation of CAN (Controller Area Network) protocol for communication between two embedded nodes using the LPC2129 ARM7 microcontroller. The system simulates a basic automotive control network where different vehicle functions such as headlights, indicators, and speed data are transmitted from one node to another through the CAN bus.

In this project, one LPC2129 board acts as the transmitter node and the other acts as the receiver node. The transmitter node reads input signals such as headlight status, left/right indicator signals, and speed data obtained using an ADC input. These values are packaged into a CAN message and transmitted over the CAN bus.

The receiver node receives the CAN message and performs corresponding actions such as turning ON LEDs (representing headlights and indicators), displaying data on an LCD, and triggering a buzzer when an indicator is active. An additional Rydolabz board is used to control the buzzer functionality.

This project demonstrates how CAN communication enables reliable and efficient data exchange between multiple embedded systems, similar to the architecture used in modern vehicles for communication between ECUs.

Objectives

To implement CAN protocol communication between two LPC2129 nodes.
To simulate vehicle lighting and indicator control.
To transmit speed data using ADC from one node to another.
To display received data on an LCD display.
To generate a buzzer alert when vehicle indicators are active.

Hardware Components Used

LPC2129 ARM7 Microcontroller (2 boards)
CAN Transceiver (for CAN communication)
16x2 LCD Display
LEDs (Headlight, Left Indicator, Right Indicator)
Potentiometer / Analog input for ADC (Speed simulation)
Buzzer
Rydolabz Development Board
Power Supply

System Architecture

The system is divided into two CAN nodes:

Node 1 – Transmitter
This node is responsible for collecting input data and transmitting it through the CAN bus.

Functions:
Reads headlight ON/OFF status
Reads left and right indicator signals
Reads speed value using ADC
Packs the data into a CAN frame
Sends the CAN message to the receiver node

Node 2 – Receiver
This node receives CAN messages and performs corresponding actions.

Functions:
Receives CAN data from transmitter
Controls LEDs for headlight and indicators
Displays received information on LCD
Activates buzzer when left or right indicator is ON

Working Principle

The transmitter node reads inputs from switches and ADC.
The data is formatted into a CAN message frame.
The CAN controller sends the data over the CAN bus.
The receiver node reads the CAN message.
Based on the received data:
LEDs are turned ON/OFF to represent headlights and indicators.
Speed or system data is displayed on the LCD.
A buzzer is activated when an indicator is turned ON.

This communication demonstrates how different embedded modules in vehicles exchange information through the CAN protocol.

Software Tools Used

Embedded C
Keil uVision IDE
Flash Magic (for microcontroller programming)

Applications

Automotive electronic systems
Vehicle dashboard control systems
Industrial distributed embedded networks
CAN-based communication systems

Future Improvements
Add more vehicle parameters such as temperature or fuel level.
Implement real-time speed sensors.
Add wireless monitoring system.
Integrate multiple nodes to simulate a full vehicle CAN network.

Conclusion

This project successfully demonstrates CAN-based communication between two LPC2129 microcontroller nodes. The system shows how vehicle-related signals such as headlights, indicators, and speed data can be transmitted and processed across a network. The project highlights the importance of CAN protocol in building reliable and scalable embedded communication systems used in modern automotive applications.
