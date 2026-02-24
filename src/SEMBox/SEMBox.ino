/*********
  SEMBox ESP32 Industrial Control System
  Backend Server with SPIFFS Support
  
  Libraries needed:
  - ESPAsyncWebServer: https://github.com/me-no-dev/ESPAsyncWebServer
  - AsyncTCP: https://github.com/me-no-dev/AsyncTCP
  - SPIFFS (included with ESP32 core)
  
  To upload the web files to SPIFFS:
  1. Install "ESP32 Sketch Data Upload" tool in Arduino IDE
  2. Place HTML/CSS/JS files in the "data" folder
  3. Tools > ESP32 Sketch Data Upload
*********/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

// ===========================================
// Configuration
// ===========================================

// Network credentials - Access Point mode
const char* AP_SSID = "SEMBox-AP";
const char* AP_PASSWORD = "12345678";

// Network credentials - Station mode (uncomment to use)
// const char* STA_SSID = "YourWiFiSSID";
// const char* STA_PASSWORD = "YourWiFiPassword";

// Server port
const int SERVER_PORT = 80;

// GPIO Pin definitions
const int GPIO_26 = 26;
const int GPIO_27 = 27;
const int LED_PIN = LED_BUILTIN;

// ===========================================
// Global Variables
// ===========================================

// Create AsyncWebServer object on port 80
AsyncWebServer server(SERVER_PORT);

// GPIO States
String gpio26State = "off";
String gpio27State = "off";
String ledState = "off";

// System variables
unsigned long startTime = 0;
int clientCount = 0;

// ===========================================
// Function Prototypes
// ===========================================
void initSPIFFS();
void initGPIO();
void initWiFi();
void initWebServer();
String getStatus();
String processor(const String& var);
void handleGPIO26On(AsyncWebServerRequest *request);
void handleGPIO26Off(AsyncWebServerRequest *request);
void handleGPIO27On(AsyncWebServerRequest *request);
void handleGPIO27Off(AsyncWebServerRequest *request);
void handleLEDOn(AsyncWebServerRequest *request);
void handleLEDOff(AsyncWebServerRequest *request);
void handleStatus(AsyncWebServerRequest *request);
void handleNotFound(AsyncWebServerRequest *request);

// ===========================================
// Setup
// ===========================================
void setup() {
    Serial.begin(115200);
    Serial.println("\n\n========================================");
    Serial.println("  SEMBox Industrial Control System");
    Serial.println("  Starting up...");
    Serial.println("========================================\n");
    
    // Record start time
    startTime = millis();
    
    // Initialize components
    initSPIFFS();
    initGPIO();
    initWiFi();
    initWebServer();
    
    Serial.println("\n========================================");
    Serial.println("  System Ready!");
    Serial.println("========================================\n");
}

// ===========================================
// Main Loop
// ===========================================
void loop() {
    // Main loop is mostly handled by AsyncWebServer
    // Add any periodic tasks here
    
    delay(10);
}

// ===========================================
// Initialization Functions
// ===========================================

/**
 * Initialize SPIFFS filesystem
 */
void initSPIFFS() {
    Serial.print("[SPIFFS] Initializing... ");
    
    if (!SPIFFS.begin(true)) {
        Serial.println("FAILED!");
        Serial.println("[SPIFFS] An error occurred while mounting SPIFFS");
        return;
    }
    
    Serial.println("OK");
    
    // List files in SPIFFS
    Serial.println("[SPIFFS] Files found:");
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.printf("  - %s (%d bytes)\n", file.name(), file.size());
        file = root.openNextFile();
    }
}

/**
 * Initialize GPIO pins
 */
void initGPIO() {
    Serial.print("[GPIO] Initializing pins... ");
    
    pinMode(GPIO_26, OUTPUT);
    pinMode(GPIO_27, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    // Set initial states (all off)
    digitalWrite(GPIO_26, LOW);
    digitalWrite(GPIO_27, LOW);
    digitalWrite(LED_PIN, LOW);
    
    Serial.println("OK");
    Serial.println("[GPIO] Pins configured: GPIO26, GPIO27, Built-in LED");
}

/**
 * Initialize WiFi in Access Point mode
 */
void initWiFi() {
    Serial.print("[WiFi] Setting up Access Point... ");
    
    // Configure as Access Point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    
    IPAddress IP = WiFi.softAPIP();
    
    Serial.println("OK");
    Serial.printf("[WiFi] SSID: %s\n", AP_SSID);
    Serial.printf("[WiFi] Password: %s\n", AP_PASSWORD);
    Serial.printf("[WiFi] IP Address: %s\n", IP.toString().c_str());
    Serial.printf("[WiFi] Dashboard URL: http://%s\n", IP.toString().c_str());
}

/**
 * Initialize Web Server routes
 */
void initWebServer() {
    Serial.print("[Server] Configuring routes... ");
    
    // Serve static files from SPIFFS
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    
    // GPIO 26 routes
    server.on("/26/on", HTTP_GET, handleGPIO26On);
    server.on("/26/off", HTTP_GET, handleGPIO26Off);
    
    // GPIO 27 routes
    server.on("/27/on", HTTP_GET, handleGPIO27On);
    server.on("/27/off", HTTP_GET, handleGPIO27Off);
    
    // LED routes
    server.on("/LED/on", HTTP_GET, handleLEDOn);
    server.on("/LED/off", HTTP_GET, handleLEDOff);
    
    // Status endpoint (JSON)
    server.on("/status", HTTP_GET, handleStatus);
    
    // 404 handler
    server.onNotFound(handleNotFound);
    
    // Start server
    server.begin();
    
    Serial.println("OK");
    Serial.printf("[Server] Listening on port %d\n", SERVER_PORT);
}

// ===========================================
// Request Handlers
// ===========================================

void handleGPIO26On(AsyncWebServerRequest *request) {
    Serial.println("[GPIO] GPIO 26 -> ON");
    gpio26State = "on";
    digitalWrite(GPIO_26, HIGH);
    request->send(200, "text/plain", "GPIO 26 ON");
}

void handleGPIO26Off(AsyncWebServerRequest *request) {
    Serial.println("[GPIO] GPIO 26 -> OFF");
    gpio26State = "off";
    digitalWrite(GPIO_26, LOW);
    request->send(200, "text/plain", "GPIO 26 OFF");
}

void handleGPIO27On(AsyncWebServerRequest *request) {
    Serial.println("[GPIO] GPIO 27 -> ON");
    gpio27State = "on";
    digitalWrite(GPIO_27, HIGH);
    request->send(200, "text/plain", "GPIO 27 ON");
}

void handleGPIO27Off(AsyncWebServerRequest *request) {
    Serial.println("[GPIO] GPIO 27 -> OFF");
    gpio27State = "off";
    digitalWrite(GPIO_27, LOW);
    request->send(200, "text/plain", "GPIO 27 OFF");
}

void handleLEDOn(AsyncWebServerRequest *request) {
    Serial.println("[GPIO] Built-in LED -> ON");
    ledState = "on";
    digitalWrite(LED_PIN, HIGH);
    request->send(200, "text/plain", "LED ON");
}

void handleLEDOff(AsyncWebServerRequest *request) {
    Serial.println("[GPIO] Built-in LED -> OFF");
    ledState = "off";
    digitalWrite(LED_PIN, LOW);
    request->send(200, "text/plain", "LED OFF");
}

void handleStatus(AsyncWebServerRequest *request) {
    // Create JSON response
    JsonDocument doc;
    
    doc["gpio26"] = gpio26State;
    doc["gpio27"] = gpio27State;
    doc["led"] = ledState;
    doc["uptime"] = (millis() - startTime) / 1000;
    doc["clients"] = WiFi.softAPgetStationNum();
    doc["memory"] = String(ESP.getFreeHeap() / 1024) + " KB";
    doc["ip"] = WiFi.softAPIP().toString();
    
    String response;
    serializeJson(doc, response);
    
    request->send(200, "application/json", response);
}

void handleNotFound(AsyncWebServerRequest *request) {
    Serial.printf("[Server] 404 Not Found: %s\n", request->url().c_str());
    request->send(404, "text/plain", "Not Found");
}

// ===========================================
// Utility Functions
// ===========================================

/**
 * Get system status as JSON string
 */
String getStatus() {
    JsonDocument doc;
    
    doc["gpio26"] = gpio26State;
    doc["gpio27"] = gpio27State;
    doc["led"] = ledState;
    doc["uptime"] = (millis() - startTime) / 1000;
    doc["clients"] = WiFi.softAPgetStationNum();
    doc["freeHeap"] = ESP.getFreeHeap();
    
    String output;
    serializeJson(doc, output);
    return output;
}
