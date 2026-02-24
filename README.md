S# SEMBox - ESP32 Industrial Control System

Modern industrial dashboard for ESP32 with GPIO control capabilities.

## Project Structure

```
FIBRO_SEMBox/
├── data/                    # Web dashboard files (SPIFFS)
│   ├── index.html          # Main dashboard HTML
│   ├── style.css           # Industrial theme CSS
│   └── script.js           # Dashboard JavaScript
├── src/                     # ESP32 backend code
│   └── SEMBox.ino          # Main ESP32 firmware
├── SEMBox.ino              # (Old file - can be deleted)
└── README.md
```

## Features

- **Modern Industrial Dashboard**: Dark theme with professional industrial styling
- **GPIO Control**: Control GPIO 26, GPIO 27, and built-in LED
- **Real-time Status**: Live system status (uptime, memory, connected clients)
- **Quick Actions**: All ON/OFF buttons for fast control
- **Responsive Design**: Works on desktop and mobile devices
- **Keyboard Shortcuts**: Quick keyboard controls (1, 2, 3 for GPIO toggle)

## Required Libraries

Install these libraries in Arduino IDE (Sketch > Include Library > Manage Libraries):

1. **ESPAsyncWebServer** - Async HTTP Server
   - Download from: https://github.com/me-no-dev/ESPAsyncWebServer
   
2. **AsyncTCP** - TCP library for ESPAsyncWebServer
   - Download from: https://github.com/me-no-dev/AsyncTCP
   
3. **ArduinoJson** - JSON handling
   - Install via Library Manager

## Installation Steps

### 1. Install ESP32 Board Support
1. Open Arduino IDE
2. Go to File > Preferences
3. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to Tools > Board > Boards Manager
5. Search for "ESP32" and install

### 2. Install Required Libraries
Download and install ESPAsyncWebServer and AsyncTCP:
1. Download ZIP from GitHub links above
2. Sketch > Include Library > Add .ZIP Library

### 3. Install SPIFFS Upload Tool
1. Download ESP32FS plugin from: https://github.com/me-no-dev/arduino-esp32fs-plugin
2. Create a `tools` folder in your Arduino sketchbook location
3. Extract the plugin to `tools/ESP32FS/tool/esp32fs.jar`
4. Restart Arduino IDE

### 4. Upload Firmware
1. Open `src/SEMBox.ino` in Arduino IDE
2. Select your ESP32 board: Tools > Board > ESP32 Dev Module
3. Select COM port: Tools > Port
4. Click Upload

### 5. Upload Web Files to SPIFFS
1. Make sure the `data` folder is in the same directory as your .ino file
   - Copy `data` folder to `src/` folder, or
   - Open project from root directory
2. Tools > ESP32 Sketch Data Upload
3. Wait for upload to complete

## Usage

1. Power on ESP32
2. Connect to WiFi network:
   - **SSID**: `SEMBox-AP`
   - **Password**: `12345678`
3. Open browser and navigate to: `http://192.168.4.1`

## Keyboard Shortcuts

| Key | Action |
|-----|--------|
| 1 | Toggle GPIO 26 |
| 2 | Toggle GPIO 27 |
| 3 | Toggle Built-in LED |
| Shift+A | All ON |
| Shift+O | All OFF |
| R | Refresh Status |

## Configuration

Edit `src/SEMBox.ino` to customize:

```cpp
// Change Access Point credentials
const char* AP_SSID = "SEMBox-AP";
const char* AP_PASSWORD = "12345678";

// Change GPIO pins
const int GPIO_26 = 26;
const int GPIO_27 = 27;
```

## API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/` | GET | Dashboard page |
| `/26/on` | GET | Turn GPIO 26 ON |
| `/26/off` | GET | Turn GPIO 26 OFF |
| `/27/on` | GET | Turn GPIO 27 ON |
| `/27/off` | GET | Turn GPIO 27 OFF |
| `/LED/on` | GET | Turn LED ON |
| `/LED/off` | GET | Turn LED OFF |
| `/status` | GET | Get JSON status |

## Troubleshooting

1. **SPIFFS upload fails**: Make sure no Serial Monitor is open
2. **Cannot connect to AP**: Check WiFi credentials, try closer to ESP32
3. **Dashboard not loading**: Verify SPIFFS upload completed successfully
4. **GPIO not responding**: Check pin connections and Serial Monitor for errors

## License

This project is open source and available for personal and commercial use.
