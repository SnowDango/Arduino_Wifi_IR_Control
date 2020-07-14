#include <ArduinoJson.h>
#include <WiFi.h>

String getSystem(String body) { //Systemの取り出し
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(body);
  if (!json.success()) {
    Serial.println("parseObject() failed");
    return "NOT";
  }
  return json["system"];
}

String getModeSystem(String body) { //Modeの取り出し
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(body);
  if (!json.success()) {
    Serial.println("parseObject() failed");
    return "NOT";
  }
  return json["mode"];
}

String readRequestBody(WiFiClient client) { //Bodyの取得
  int i = 0;
  char * res = (char *) malloc(sizeof(char) * 255);
  while (client.available()) {
    res[i++] = client.read();
  }
  String stringMain = res;
  char t[64];
  int len = stringMain.indexOf("}");
  strncpy( t, res, len + 1);
  String mainBody = t;

  return mainBody;
}
