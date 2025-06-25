# Spotify Controller Display with Arduino Mega

[![Python Version](https://img.shields.io/badge/python-3.x-blue.svg)](https://www.python.org/) [![Arduino](https://img.shields.io/badge/arduino-Mega-green.svg)](https://www.arduino.cc/)


## Overview

This project uses an **Arduino Mega**, a **16x2 LCD display**, and a **joystick module** to create a live Spotify playback info display. The Arduino shows the current song name, artist, and playback progress, allowing you to scroll through long text using the joystick. Data is fetched from the Spotify Web API by a Python script and sent via serial to the Arduino.


## Requirements

- **Hardware:**
  - Arduino Mega 2560
  - 16x2 LCD Display (wired in 4-bit mode)
  - Joystick module (with button)
  - Breadboard and jumper wires
  - Potentiometer (for LCD contrast)

- **Software:**
  - Python 3.x
  - `spotipy` Python library (`pip install spotipy`)
  - `pyserial` Python library (`pip install pyserial`)
  - Spotify Developer Account with a registered app for credentials
  - Arduino IDE
    
  ```bash
  pip install pyserial spotipy
  ```

## How to Use

### 1. Setup Hardware

- Connect the LCD and joystick according to the wiring detailed in the project documentation.
- Connect Arduino Mega to your PC via USB.

### 2. Prepare Spotify API Credentials

- Create a Spotify Developer app and obtain your `client_id`, `client_secret`, and set a redirect URI (e.g., `http://127.0.0.1:8888/callback`).
- Update these credentials in `spotify_controller.py`.

### 3. Upload Arduino Sketch

- Open `SpotifyController.ino` in Arduino IDE.
- Compile and upload it to your Arduino Mega.

### 4. Run Python Script

- Install required Python packages:

  ```bash
  pip install spotipy pyserial
  ```
### 5. Controls
- Joystick Left/Right: Scrolls the currently selected line (song name or artist/time).

- Joystick Button (click): Toggles scrolling control between the top line and bottom line.

- Hold joystick centered: Refreshes the display every second to update playback time.

## Notes
The project supports only data reading (no playback control) due to Spotify free account limitations.

Make sure your serial port (COM3 on Windows or /dev/ttyUSB0 on Linux) is correctly set in the Python script.

The project can be extended with additional features like play/pause status, brightness control, and multiple display modes.

## Demo
![ArduinoSpot](https://github.com/user-attachments/assets/da12e569-0dc1-49b7-9bd1-aef6218c3185)

