#include "Arduino.h"
#include "Connector.h"

Sender::Sender(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Sender::heartbeat()
{
  digitalWrite(_pin, HIGH);
  delay(2*2);
  digitalWrite(_pin, LOW);
}

void Sender::send(String* msg, int msgLength)
{
  // Start sending
  digitalWrite(_pin, HIGH);
  delay(2);
  digitalWrite(_pin, LOW);
  delay(2);

  // Data
  for (int iA=0; iA < msgLength; iA++)
  {
    for(int iB=7; 0<=iB; iB--)
    {
      if (((*msg)[iA] >> iB) & 0x01)
      {
        digitalWrite(_pin, HIGH);
      }
      else
      {
        digitalWrite(_pin, LOW);
      }
      delay(2);
    }
  }

  digitalWrite(2, LOW);
}