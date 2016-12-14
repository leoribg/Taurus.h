# Taurus.h
Taurus library for ESP8266

### BRIEF DOCUMENTATION

Create an instance for Taurus:

```sh
taurus taurus("TAURUS_SERIAL");
```

Write value in a digital actuator:

```sh
taurus.write_dActuator(char *actID, char *value);
```

Read value of a digital actuator:

```sh
int data = taurus.read_dActuator(char *actID);
```
Write value in a analog actuator:

```sh
taurus.write_aActuator(char *actID, char *value);
```

Read value of a analog actuator:

```sh
int data = taurus.read_aActuator(char *actID);
```

Write data in a sensor:

```sh
taurus.write_sensor(char *actID, char *value);
```

Read data of a sensor:

```sh
int data = taurus.read_sensor(char *sensorID);
```

By: Leonardo Gonçalves

[![N|Solid](http://104.131.189.228/assets/taurus/images/pic02.png)](https://taurussystem.com)

