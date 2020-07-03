#include <IRremote.h>
#include <Arduino.h>
#include <PanasonicHeatpumpIR.h>

// pin number
#define light_on_button 12
#define light_off_button 8
#define cool_button 7
#define hot_button 4
#define stop_button 2

void setup(){
  // setting button pin mode 
    pinMode(light_on_button,INPUT) ;
    pinMode(light_off_button,INPUT) ; 
    pinMode(cool_button,INPUT);
    pinMode(hot_button,INPUT);
    pinMode(stop_button,INPUT);

    // Serial begin speed = 115200
    Serial.begin(115200);
}

void loop(){

  // read button state 
    unsigned int light_on_status = digitalRead(light_on_button);
    unsigned int light_off_status = digitalRead(light_off_button);
    unsigned int air_cool_on_status = digitalRead(cool_button);
    unsigned int air_hot_on_status = digitalRead(hot_button);
    unsigned int air_off_status = digitalRead(stop_button);

    // 
    
    if(light_off_status == LOW){ //　light off
        IRsend irsend;
        irsend.sendNEC(0xE730D12E,32);
        Serial.println("light off");
      }else if(air_off_status == LOW){ // air conditioner off
        Serial.println("air off");
        IRSenderPWM irSender(3);
        PanasonicHeatpumpIR *heatpumpIR;
        heatpumpIR = new PanasonicDKEHeatpumpIR();
        heatpumpIR->send(irSender, POWER_OFF, MODE_COOL, FAN_AUTO, 26, VDIR_AUTO, HDIR_AUTO);
      }else if(light_on_status == LOW){ // light on
        IRsend irsend;
        irsend.sendNEC(0xE73045BA,32);
        Serial.println("light on");
      }else if(air_cool_on_status == LOW){ // air conditioner mode cool
        Serial.println("cool on");
        IRSenderPWM irSender(3);
        PanasonicDKEHeatpumpIR *heatpumpIR;
        heatpumpIR = new PanasonicDKEHeatpumpIR();
        heatpumpIR->send(irSender, POWER_ON, MODE_COOL, FAN_AUTO, 26, VDIR_AUTO, HDIR_AUTO);
      }else if(air_hot_on_status == LOW){ // air conditioner mode hot
        Serial.println("hot on");
        IRSenderPWM irSender(3);
        PanasonicDKEHeatpumpIR *heatpumpIR;
        heatpumpIR = new PanasonicDKEHeatpumpIR();
        heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_AUTO, 22, VDIR_AUTO, HDIR_AUTO);
      }

      //delay time between this loop and next loop
    delay(500);
}
