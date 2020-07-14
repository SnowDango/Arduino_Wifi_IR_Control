#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <HeatpumpIR.h>
#include <PanasonicHeatpumpIR.h>

const uint16_t send_light_pin = 12;
const uint16_t send_air_pin = 13;

void irControl(String systemStr, String modeStr) {
  if (systemStr == "cellingLight") {
    if (modeStr == "on") {
      Serial.println("CellingLight ON");
      IRsend irsend(send_light_pin);
      irsend.begin();
      irsend.sendNEC(0xE73045BA, 32);
    } else if (modeStr == "off") {
      Serial.println("CellingLight OFF");
      IRsend irsend(send_light_pin);
      irsend.begin();
      irsend.sendNEC(0xE730D12E, 32);
    }
  } else if (systemStr == "airConditionar") {
    if (modeStr == "cool") {
      Serial.println("AirConditinar Cool");
      IRSenderESP32 irSender(send_air_pin, 0);
      PanasonicDKEHeatpumpIR *heatpumpIR;
      heatpumpIR = new PanasonicDKEHeatpumpIR();
      heatpumpIR->send(irSender, POWER_ON, MODE_COOL, FAN_AUTO, 26, VDIR_AUTO, HDIR_AUTO);
    } else if (modeStr == "hot" ) {
      Serial.println("AirConditinar HOT");
      IRSenderESP32 irSender(send_air_pin, 0);
      PanasonicDKEHeatpumpIR *heatpumpIR;
      heatpumpIR = new PanasonicDKEHeatpumpIR();
      heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_AUTO, 22, VDIR_AUTO, HDIR_AUTO);
    } else if (modeStr == "off") {
      Serial.println("AirConditinar OFF");
      IRSenderESP32 irSender(send_air_pin, 0);
      PanasonicHeatpumpIR *heatpumpIR;
      heatpumpIR = new PanasonicDKEHeatpumpIR();
      heatpumpIR->send(irSender, POWER_OFF, MODE_COOL, FAN_AUTO, 26, VDIR_AUTO, HDIR_AUTO);
    }
  }
}

void irControl(int lightOn, int lightOff, int airCool, int airHot, int airOff) {
  if (lightOff == HIGH) { //　light off
    IRsend irsend(send_light_pin);
    irsend.begin();
    irsend.sendNEC(0xE730D12E, 32);
    Serial.println("light off");
    delay(500);
  } else if (airOff == HIGH) { // air conditioner off
    Serial.println("air off");
    IRSenderESP32 irSender(send_air_pin, 0);
    PanasonicHeatpumpIR *heatpumpIR;
    heatpumpIR = new PanasonicDKEHeatpumpIR();
    heatpumpIR->send(irSender, POWER_OFF, MODE_COOL, FAN_AUTO, 26, VDIR_AUTO, HDIR_AUTO);
    delay(500);
  } else if (lightOff == HIGH) { // light on
    IRsend irsend(send_light_pin);
    irsend.begin();
    irsend.sendNEC(0xE73045BA, 32);
    Serial.println("light on");
    delay(500);
  } else if (airCool == HIGH) { // air conditioner mode cool
    Serial.println("cool on");
    IRSenderESP32 irSender(send_air_pin, 0);
    PanasonicDKEHeatpumpIR *heatpumpIR;
    heatpumpIR = new PanasonicDKEHeatpumpIR();
    heatpumpIR->send(irSender, POWER_ON, MODE_COOL, FAN_AUTO, 26, VDIR_AUTO, HDIR_AUTO);
    delay(500);
  } else if (airHot == HIGH) { // air conditioner mode hot
    Serial.println("hot on");
    IRSenderESP32 irSender(send_air_pin, 0);
    PanasonicDKEHeatpumpIR *heatpumpIR;
    heatpumpIR = new PanasonicDKEHeatpumpIR();
    heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_AUTO, 22, VDIR_AUTO, HDIR_AUTO);
    delay(500);
  }
}
