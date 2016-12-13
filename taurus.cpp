/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "taurus.h"
#include <ESP8266WiFi.h>

const char* host = "104.131.189.228";// Taurus IP Address
const int httpPort = 80; // HTTP Port

// Use WiFiClient class to create TCP connections
WiFiClient client;

taurus::taurus(char *serial)
{
  _serial = serial;
}

void taurus::write_dActuator(char *actID, char *value)
{
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  char buffer[128];
  sprintf(buffer, "GET /ws/webresources/Digital/set?key=%s&actuator=%s&value=%s HTTP/1.1", _serial, actID, value);
  //Serial.println(buffer);
  client.println(buffer);
  client.println("Host: taurussystem.com");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  delay(100); // Can be changed
  while (client.available()) {
    String line = client.readStringUntil('\r');
    //Serial.print(line);
  }
  ;;Serial.println();
  //Serial.println("closing connection");
}

int taurus::read_dActuator(char *actID)
{
  static String line;
  static String dado;
    if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return -1;
  }
  char buffer[128];
  sprintf(buffer, "GET /ws/webresources/Digital/get?key=%s&&actuator=%s HTTP/1.1", _serial, actID);
  //Serial.println(buffer);
  client.println(buffer);
  client.println("Host: taurussystem.com");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  delay(100); // Can be changed
  while (client.available()) {
    line = client.readStringUntil('\r');
    //Serial.print(line);
    if(line.indexOf("valor")>0 && line.indexOf("}")>0)
    {
      int valpos = line.indexOf("valor");
      dado = line.substring(valpos + 7, valpos + 8);
      //Serial.println(dado);
      if (dado == "1")
      {
        //Serial.println("closing connection");
        return 1;
      }
      else 
      {
        //Serial.println("closing connection");
        return 0;
      }
    }
  }
}

void taurus::write_aActuator(char *actID, char *value)
{
  if (!client.connect(host, httpPort)) 
    {
      Serial.println("connection failed");
      return;
    }

    char buffer[128];
    sprintf(buffer, "GET /ws/webresources/Analog/set?key=%s&actuator=%s&value=%s HTTP/1.1", _serial, actID, value);
    //Serial.println(buffer);
    client.println(buffer);
    client.println("Host: taurussystem.com");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    delay(100); // Can be changed
    while (client.available()) {
      String line = client.readStringUntil('\r');
      //Serial.print(line);
    }
    //Serial.println();
    //Serial.println("closing connection");
}

int taurus::read_aActuator(char *actID)
{
  static String line;
  static String dado;
    if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return -1;
  }
  char buffer[128];
  sprintf(buffer, "GET /ws/webresources/Analog/get?key=%s&&actuator=%s HTTP/1.1", _serial, actID);
  //Serial.println(buffer);
  client.println(buffer);
  client.println("Host: taurussystem.com");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  delay(100); // Can be changed
  while (client.available()) {
    line = client.readStringUntil('\r');
    //Serial.print(line);
    if(line.indexOf("valor")>0 && line.indexOf("}")>0)
    {
      int valpos = line.indexOf("valor");
      int valfinal = line.indexOf("codigo");
      dado = line.substring(valpos + 7, valfinal - 2);
      //Serial.println(dado);
      //Serial.println("closing connection");
      return dado.toInt();
    }
  }
}

void taurus::write_sensor(char *actID, char *value)
{
  if (!client.connect(host, httpPort)) 
    {
      Serial.println("connection failed");
      return;
    }
    char buffer[128];
    int i=0;
    sprintf(buffer, "GET /ws/webresources/Sensor/set?key=%s&sensor=%s&value=%s HTTP/1.1", _serial, actID, value);
    //Serial.println(buffer);
    client.println(buffer);
    client.println("Host: taurussystem.com");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    delay(100); // Can be changed
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    //Serial.println();
    //Serial.println("closing connection");
}

int taurus::read_sensor(char *sensorID)
{
  static String line;
  static String dado;
    if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return -1;
  }
  char buffer[128];
  sprintf(buffer, "GET /ws/webresources/Sensor/get?key=%s&&sensor=%s HTTP/1.1", _serial, sensorID);
  //Serial.println(buffer);
  client.println(buffer);
  client.println("Host: taurussystem.com");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  delay(100); // Can be changed
  while (client.available()) {
    line = client.readStringUntil('\r');
    //Serial.print(line);
    if(line.indexOf("valor")>0 && line.indexOf("}")>0)
    {
      int valpos = line.indexOf("valor");
      int valfinal = line.indexOf("ultimoValor");
      dado = line.substring(valpos + 7, valfinal - 2);
      //Serial.println(dado);
      //Serial.println("closing connection");
      return dado.toInt();
    }
  }
}