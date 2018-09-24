#include "Arduino.h"
#include "Connector.h"

Receiver::Receiver(int pin, int heartbeatAlarm, void (*fireAlarm)(), void (*stopAlarm)() )
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _heartbeatAlarm = heartbeatAlarm;
  _fireAlarm = fireAlarm;
  _stopAlarm = stopAlarm;
}

void Receiver::listen(int dest[], int msgLength)
{
  long lastHeartbeat = millis();
  int hbAlarm = 0;

  // Startsequenz
  while(true)
  {
    delay(1);
    
    // Daten / Heartbeat lesen
    if (digitalRead(_pin) == HIGH)
    {
      delay(1);
      
      // Heartbeat yes/no
      if (digitalRead(_pin) == HIGH)
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
        _stopAlarm();
      }
    }
    else
    {
      if (millis()-lastHeartbeat > _heartbeatAlarm) 
      {
        hbAlarm = 1;
        _fireAlarm();
      }
    }
  }

  // Daten Empfangen
  for (int i=0; i<msgLength; i++)
  {
    dest[i] = digitalRead(_pin);
    delay(1);
  }
}