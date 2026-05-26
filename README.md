# RobotFan

A smart fan controller built on the ESP32 S3 WROOM (40-pin) with radar-based person tracking, gesture control, TFT display, and RGB lighting.

## Features

- **Auto pan** — RD-03D 24GHz radar tracks a person left/right, TMC2209 drives a NEMA17 stepper to follow them
- **Presence detection** — RD-03E radar wakes the system from sleep when someone enters the room
- **Gesture menu** — PAJ7620U2 reads 9 gestures to navigate a TFT touchscreen menu
- **Comfort mode** — DHT11 auto-adjusts fan speed based on temperature
- **Mood ring** — Govee LED strips shift color with temperature
- **ARGB sync** — Corsair RS120 fans and Govee strips animate together

## Hardware

| Part | Notes |
|---|---|
| ESP32 S3 WROOM 40-pin (HOSYOND) | Main controller |
| 3.5" TFT ILI9488 SPI 480x320 | Menu display with touch |
| TMC2209 BigTreeTech | Stepper driver |
| NEMA17 FlashForge 17HD4063-06N | Pan motor |
| RD-03D 24GHz radar | X/Y person tracking |
| RD-03E 24GHz radar | Presence detection |
| PAJ7620U2 | Gesture sensor |
| DHT11 | Temperature/humidity |
| Corsair RS120 ARGB x3 | Fans |
| Govee 24V LED strips | Lighting |
| IRLZ44N | Pre-regulator |
| 24V→12V buck converter | Power |

## Pin Assignments

| Component | GPIO |
|---|---|
| TMC2209 STEP | 5 |
| TMC2209 DIR | 6 |
| PAJ7620 SDA | 20 |
| PAJ7620 SCL | 21 |
| RD-03D RX (Serial1) | 16 |
| RD-03D TX (Serial1) | 17 |
| RD-03E RX (Serial2) | 9 |
| RD-03E TX (Serial2) | 10 |
| DHT11 | 14 |
| TFT MOSI | 11 |
| TFT SCK | 12 |
| TFT CS | 13 |
| TFT DC | 15 |
| TFT RST | 7 |
| TFT BL | 46 |
| TFT Touch CS | 8 |
| Fan PWM 1 | 39 |
| Fan PWM 2 | 40 |
| Fan PWM 3 | 41 |

**Avoid:** GPIO 35, 36, 37 (internal flash), GPIO 0 (strapping pin)

## Power Architecture

```
24V supply → buck converter → 12V → IRLZ44N → 4.8V → ESP32 S3 VIN
24V → buck converter → 12V → Corsair RS120 fans
ESP32 S3 onboard regulator → 3.3V for all logic
TMC2209 VM → 24V direct
TMC2209 VDD → 3.3V from ESP32
RD-03D VCC → 5V pin on ESP32
RD-03E VCC → 3.3V pin on ESP32
PAJ7620 VCC → 3.3V pin on ESP32
```

## Serial Ports

- **UART port** (near EN button) → use for programming and serial monitor
- **Native USB port** (near BOOT button) → do NOT use for serial monitor

## Build Stages

- [x] Stage 1: Power rails + blink
- [x] Stage 2: LCD 16x2 I2C (Arduino R3, replaced by TFT)
- [x] Stage 3: RD-03E radar distance + gesture (Arduino R3)
- [x] Stage 4: TMC2209 + NEMA17 stepper (ESP32 S3)
- [ ] Stage 5: TFT menu (in progress)
- [ ] Stage 6: Full sensor integration
- [ ] Stage 7: ARGB lighting sync
