/*********
  SEMBox ESP32 Industrial Control System
  Main Controller - Handles GPIO, WiFi, and Server Logic
  
  Libraries needed:
  - ESPAsyncWebServer: https://github.com/me-no-dev/ESPAsyncWebServer
  - AsyncTCP: https://github.com/me-no-dev/AsyncTCP
  - ArduinoJson: https://github.com/bblanchon/ArduinoJson
  
  Web UI is defined in: web_content.h
*********/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <Preferences.h>

// Include web content (HTML, CSS, JS)
#include "web_content.h"

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
const int LED_PIN = LED_BUILTIN;

// ===========================================
// Global Variables
// ===========================================

// Create AsyncWebServer object on port 80
AsyncWebServer server(SERVER_PORT);

// Preferences for NVS storage
Preferences preferences;

// GPIO States
String ledState = "off";

// Rotary Table Parameters (stored in NVS)
int tableDivision = 360;
float tableRatio = 90.0;

// System variables
unsigned long startTime = 0;
int clientCount = 0;

// ===========================================
// Function Prototypes
// ===========================================
void initGPIO();
void initWiFi();
void initWebServer();
void initNVS();
String getStatus();

// Request Handlers
void handleLEDOn(AsyncWebServerRequest *request);
void handleLEDOff(AsyncWebServerRequest *request);
void handleStatus(AsyncWebServerRequest *request);
void handleParamsSave(AsyncWebServerRequest *request);
void handleParamsLoad(AsyncWebServerRequest *request);
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
    initNVS();
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
    
    // Example: You can add sensor readings, automation logic, etc.
    
    delay(10);
}

// ===========================================
// Initialization Functions
// ===========================================

/**
 * Initialize GPIO pins
 */
void initGPIO() {
    Serial.print("[GPIO] Initializing pins... ");
    
    pinMode(LED_PIN, OUTPUT);
    
    // Set initial state (off)
    digitalWrite(LED_PIN, LOW);
    
    Serial.println("OK");
    Serial.println("[GPIO] Pins configured: Built-in LED");
}

/**
 * Initialize NVS (Non-Volatile Storage)
 */
void initNVS() {
    Serial.print("[NVS] Initializing storage... ");
    
    preferences.begin("sembox", false);  // false = read/write mode
    
    // Load saved parameters or use defaults
    tableDivision = preferences.getInt("division", 360);
    tableRatio = preferences.getFloat("ratio", 90.0);
    
    Serial.println("OK");
    Serial.printf("[NVS] Division: %d\n", tableDivision);
    Serial.printf("[NVS] Ratio: 1:%.3f\n", tableRatio);
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
    
    // Serve embedded web content (from web_content.h)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });
    
    server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });
    
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/css", style_css);
    });
    
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "application/javascript", script_js);
    });
    
    // LED routes
    server.on("/LED/on", HTTP_GET, handleLEDOn);
    server.on("/LED/off", HTTP_GET, handleLEDOff);
    
    // Parameters routes (NVS)
    server.on("/params/save", HTTP_GET, handleParamsSave);
    server.on("/params/load", HTTP_GET, handleParamsLoad);
    
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
    
    doc["led"] = ledState;
    doc["uptime"] = (millis() - startTime) / 1000;
    doc["clients"] = WiFi.softAPgetStationNum();
    doc["freeHeap"] = ESP.getFreeHeap();
    doc["totalHeap"] = ESP.getHeapSize();
    doc["flashSize"] = ESP.getFlashChipSize();
    doc["sketchSize"] = ESP.getSketchSize();
    doc["division"] = tableDivision;
    doc["ratio"] = tableRatio;
    doc["ip"] = WiFi.softAPIP().toString();
    
    String response;
    serializeJson(doc, response);
    
    request->send(200, "application/json", response);
}

void handleParamsSave(AsyncWebServerRequest *request) {
    JsonDocument doc;
    
    if (request->hasParam("division") && request->hasParam("ratio")) {
        int newDivision = request->getParam("division")->value().toInt();
        float newRatio = request->getParam("ratio")->value().toFloat();
        
        // Validate
        if (newDivision >= 1 && newDivision <= 9999 && newRatio >= 1 && newRatio <= 9999) {
            tableDivision = newDivision;
            tableRatio = newRatio;
            
            // Save to NVS
            preferences.putInt("division", tableDivision);
            preferences.putFloat("ratio", tableRatio);
            
            Serial.printf("[NVS] Saved: Division=%d, Ratio=1:%.3f\n", tableDivision, tableRatio);
            
            doc["success"] = true;
            doc["division"] = tableDivision;
            doc["ratio"] = tableRatio;
        } else {
            doc["success"] = false;
            doc["error"] = "Invalid values (1-9999)";
        }
    } else {
        doc["success"] = false;
        doc["error"] = "Missing parameters";
    }
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
}

void handleParamsLoad(AsyncWebServerRequest *request) {
    JsonDocument doc;
    
    doc["division"] = tableDivision;
    doc["ratio"] = tableRatio;
    
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
    
    doc["led"] = ledState;
    doc["uptime"] = (millis() - startTime) / 1000;
    doc["clients"] = WiFi.softAPgetStationNum();
    doc["freeHeap"] = ESP.getFreeHeap();
    doc["totalHeap"] = ESP.getHeapSize();
    doc["flashSize"] = ESP.getFlashChipSize();
    doc["sketchSize"] = ESP.getSketchSize();
    doc["division"] = tableDivision;
    doc["ratio"] = tableRatio;
    
    String output;
    serializeJson(doc, output);
    return output;
}
