#include "Arduino.h"
#include "Connector.h"

Receiver::Receiver(int pin, int heartbeatAlarm, void (*fireAlarm)(), void (*stopAlarm)() )
{
  pinMode(pin, INPUT);
  _pin = pin;
  _heartbeatAlarm = heartbeatAlarm;
  _fireAlarm = fireAlarm;
  _stopAlarm = stopAlarm;
}

void Receiver::listen(String* dest, int msgLength)
{
  long lastHeartbeat = millis();
  int hbAlarm = 0;

  // Startsequenz
  while(true)
  {
    delay(2);
    
    // Daten / Heartbeat lesen
    if (digitalRead(_pin) == HIGH)
    {
      delay(2);
      
      // Heartbeat yes/no
      if (digitalRead(_pin) == HIGH)
      {
        // Heartbeat
        lastHeartbeat = millis();
      }
      else
      {
        delay(2);
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
  for (int iA=0; iA<msgLength; iA++)
  {
    char current = 0x00;
    for(int iB=0; iB<8; iB++)
    {
      current = (current << 1) | digitalRead(_pin);
      delay(2);
    }
    (*dest)[iA] = current;
  }
}