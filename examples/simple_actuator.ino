
#include "Arduino.h"       
#include <ESP8266WiFi.h>    
#include <taurus.h>         

const char* ssid = "SSID";   
const char* password = "PASS";
char*actID = "ACT_ID";
int act_status;

taurus taurus ("TAURUS_SERIAL");

void setup()
{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  act_status = taurus.read_dActuator(actID);
  digitalWrite(LED_BUILTIN, act_status);
}
