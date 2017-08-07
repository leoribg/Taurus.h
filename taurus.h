/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef TAURUS_H
#define TAURUS_H

#include "Arduino.h"

class taurus
{
  public:
    taurus(char *serial);
    void write_dActuator(char *actID, uint8_t value);
    int  read_dActuator(char *actID);
    void write_aActuator(char *actID, uint8_t value);
    int  read_aActuator(char *actID);
    void write_sensor(char *actID, uint8_t value);
    int  read_sensor(char *sensorID);
  private:
    int _pin;
    char *_serial;
};
#endif
