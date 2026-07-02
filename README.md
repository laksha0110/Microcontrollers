# Microcontroller Labs

## Overview

This repository contains a collection of Embedded C projects developed on the Texas Instruments TM4C1294 microcontroller using Code Composer Studio (CCS).

The projects were completed as part of a Microcontroller Laboratory course and focus on low-level hardware interfacing, real-time programming, peripheral configuration, and embedded software development.

## Technologies

* Embedded C
* Code Composer Studio (CCS)
* TM4C1294 Microcontroller
* GPIO
* General Purpose Timers
* Interrupts (NVIC)
* Ultrasonic Distance Sensor (HC-SR04)

## Project Contents

### Lab 1 – GPIO and Keypad Interface

* GPIO configuration and control
* Hexadecimal keypad scanning
* 7-segment display interfacing
* Hardware/software interaction fundamentals

### Lab 2 – Timers and Distance Measurement

* General-purpose timer configuration
* Millisecond delay implementation
* Ultrasonic distance measurement
* LED pendulum display control

### Lab 3 – Interrupt-Driven Embedded Systems

* NVIC interrupt configuration
* Interrupt Service Routines (ISRs)
* Interrupt-based distance measurement
* Real-time event handling without busy waiting

## Lab 3 demonstration
[Watch demo](https://github.com/laksha0110/Microcontrollers/blob/main/TM4C1294ncpdt_Lab3/Lab3_demo.mp4)

In this demo, As the object goes further all the LEDs start to light up and as it gets closer fewer LEDs light up

## Learning Outcomes

Through these projects, I gained practical experience with:

* Microcontroller programming in C
* Peripheral configuration and register-level programming
* Sensor interfacing
* Timing and synchronization
* Interrupt-driven software design
* Embedded debugging and testing

#Lab 4 UART Communication using TM4C1294NCPDT

## Overview

This project was developed as part of **Microcontroller Lab 4** and demonstrates serial communication between a **TM4C1294NCPDT** microcontroller and a PC using the **UART protocol**. The project is implemented using **register-level programming** in C without external driver libraries.

## Features

- Configure UART6 for serial communication
- Transmit data from the microcontroller to the PC
- Receive character strings from the terminal
- Store and process user input
- Decode UART commands to control LEDs on Port M
- Support multiple baud rates and UART data formats

## Hardware & Software

- TM4C1294NCPDT LaunchPad
- Code Composer Studio (CCS)
- PuTTY Terminal
- UART6 (Port P)

## Commands

The following commands are supported to control the onboard LEDs:

```text
led+0
led+1
led+2
led+3

led-0
led-1
led-2
led-3
```
## Lab 4 demonstration
## UART Communication

![setup](images/terminal.png)
[Watch demo](https://github.com/laksha0110/Microcontrollers/blob/main/TM4C1294ncpdt_Lab3/Lab3_demo.mp4)


## Learning Outcomes

- UART configuration using registers
- Serial communication fundamentals
- GPIO alternate functions
- Character buffer handling
- Simple command parsing
- Embedded C programming

