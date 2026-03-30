# Smart Pill Reminder System — STM32 Microcontroller

A low-cost, standalone medication reminder device designed for elderly patients
who struggle to follow medication schedules.

**Developed at:** Embedded Systems Group, NIELIT Chennai  
**Supervised by:** Mr. Ishant Kumar Bajpai  
**Internship:** Online Internship in Embedded C — NIELIT Virtual Academy, MeitY, Govt. of India  
**Date:** August 2025

---

## The Problem
Nearly 50% of elderly patients miss their medication schedules — leading to
worsening health and unnecessary hospitalizations. Most commercial solutions
are either too expensive or too complicated for elderly users.

---

## What it does
A simple device that buzzes and flashes an LED at preset medication times.
One button press snoozes the alert for 5 minutes.

| Feature | Detail |
|---|---|
| Microcontroller | STM32F411CEU6 (ARM Cortex-M4, 72 MHz) |
| Alert | Buzzer (PA8) + LED (PC13) |
| Snooze | Tactile button on PB12 — 5 min delay |
| Alarm times | 3 daily schedules (8 AM, 2 PM, 8 PM) |
| Alert duration | 30 seconds unless snoozed |
| Timing accuracy | < 1 second deviation per day |
| Standby power | 3 mA (vs 20 mA for Arduino equivalents) |
| Total cost | Under ₹1,500 |

---

## Hardware
- STM32 Black Pill (STM32F411CEU6)
- Passive buzzer — connected to PA8 (PWM pin)
- LED + 220Ω resistor — connected to PC13
- Tactile push button + 10kΩ pull-down resistor — connected to PB12
- Powered via micro-USB (3.3V)
- No soldering needed — breadboard assembly

---

## Software & Tools
- **Language:** Embedded C
- **IDE:** STM32CubeIDE
- **Config tool:** STM32CubeMX (clock, GPIO, timer setup)
- **Debug/Flash:** ST-Link V2 over SWD
- **Libraries:** STM32 HAL, CMSIS
- **Serial monitor:** Tera Term / PuTTY

---

## How it works
1. STM32 RTC tracks time continuously
2. Every second, firmware checks if current hour matches a preset alarm time
3. On match — buzzer and LED activate simultaneously for 30 seconds
4. If snooze button is pressed — alert pauses for 5 minutes
5. After 30 seconds with no snooze — buzzer and LED turn off automatically

---

## Advantages over Arduino-based alternatives
| | STM32 (this project) | Arduino Uno |
|---|---|---|
| Standby current | 3 mA | 20 mA |
| Board size | 50% smaller | Larger |
| Clock accuracy | Internal 72 MHz | millis() based |
| Cost | Lower | Higher |

---

## Future improvements
- DS3231 RTC module for better long-term accuracy
- OLED display showing next dose time
- Bluetooth alerts to caregiver's phone
- Multiple medication profiles

---

## Files
- `main.c` — Full STM32 firmware
- `PILLREMINDERANWESHA.pdf` — Complete project report
