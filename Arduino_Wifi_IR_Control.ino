#include "WebTextCtl.h"
#include "IRSendControl.h"
#include "WifiControl.h"

// pin number
#define light_on_button 27
#define light_off_button 16
#define cool_button 17
#define hot_button 25
#define stop_button 26

// 使用するWi-Fiとそのパスワードに書き換えてください

IPAddress ip(192,168,1,50);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress DNS(192,168,1,1);

// ポート80番を使用
WiFiServer server(80);

// HTTPリクエストを格納する変数
String header;

// 値の設定に使用する変数
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

void setup() {
  Serial.begin(115200);

  WiFi.config(ip, gateway, subnet, DNS); 

  if(connectWifi()){
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  }else{
    //ESP.reset();
  }

  pinMode(light_on_button,INPUT) ;
  pinMode(light_off_button,INPUT) ; 
  pinMode(cool_button,INPUT);
  pinMode(hot_button,INPUT);
  pinMode(stop_button,INPUT);
}

void loop(){
  
  if(WiFi.status() != WL_CONNECTED){ // Wifi切れた時
    Serial.println("Wifi disconnect."); 
    if(connectWifi()){
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      server.begin();
    }else{
      //ESP.reset();
    }
  }else{
    WiFiClient client = server.available();   // Listen for incoming clients
    if (client) {                    
      Serial.println("New Client.");  
      String currentLine = "";           
      while (client.connected()) {     
        if (client.available()) {      
          char c = client.read();       
          Serial.write(c);
          header += c;
          if (c == '\n') {
            if (currentLine.length() == 0) {
              break;
            } else {
              currentLine = "";
            }
          } else if (c != '\r') {
            currentLine += c;
          }
        }
      }  
      String requestBody = readRequestBody(client);
      String systemStr = getSystem(requestBody);
      String modeStr = getModeSystem(requestBody);
      if(systemStr!="NOT" || modeStr!="NOT"){
        irControl(systemStr,modeStr);
      } 

      client.write("{Content-Type: application/json ,payload: {Text : \"OK\"}}");
      
      client.stop();
      header = "";
    }
  }
  irControl(digitalRead(light_on_button), digitalRead(light_off_button) ,
    digitalRead(cool_button) , digitalRead(hot_button) , digitalRead(stop_button)); 
}
