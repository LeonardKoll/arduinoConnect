#include "Arduino.h"
#include "Connector.h"

Receiver::(int pin, int heartbeatAlarm, void (*fireAlarm)(), void (*stopAlarm)() )
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _heartbeatAlarm = heartbeatAlarm;
  void (*_fireAlarm)() = void (*fireAlarm)();
  void (*_stopAlarm)() = void (*stopAlarm)();
}

void listen(int dest[], int msgLength)
{
  long lastHeartbeat = millis();
  int hbAlarm = 0;

  // Startsequenz
  while(true)
  {
    delay(1);
    
    // Daten / Heartbeat lesen
    if (digitalRead(inPin) == HIGH)
    {
      delay(1);
      
      // Heartbeat yes/no
      if (digitalRead(inPin) == HIGH)
      {
        // Heartbeat
        lastHeartbeat = millis();
      }
      else
      {
        delay(1);
        // Data - switch to recv mode.
        break;
      } 
    }

    // Heartbeat analysieren
    if (hbAlarm)
    {
      if (millis()-lastHeartbeat < _heartbeatAlarm) 
      {
        hbAlarm = 0;
        (*_stopAlarm)();
      }
    }
    else
    {
      if (millis()-lastHeartbeat > _heartbeatAlarm) 
      {
        hbAlarm = 1;
        (*_fireAlarm)();
      }
    }
  }

  // Daten Empfangen
  for (int i=0; i<msgLength; i++)
  {
    dest[i] = digitalRead(inPin);
    delay(1);
  }
}