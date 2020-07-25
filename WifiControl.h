#include <WiFi.h>

const char* ssid     = "";
const char* password = "";

bool connectWifi(){
    unsigned long startTime = millis();
    bool returnBool = true;

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if(millis() - startTime > 10000){
          Serial.println();
            returnBool = false;
            break;
        }
    }
    return returnBool;
} 
