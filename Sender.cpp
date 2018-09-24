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
  delay(2);
  digitalWrite(_pin, LOW);
}

void Sender::send(int msg[], int msgLength)
{
  // Start sending
  digitalWrite(_pin, HIGH);
  delay(1);
  digitalWrite(_pin, LOW);
  delay(1);

  // Data
  for (int i=0; i<msgLength; i++)
  {
    if(msg[i] == 0)
    {
      digitalWrite(_pin, LOW);
    }
    else
    {
      digitalWrite(_pin, HIGH);
    }
    delay(1);
  }

  digitalWrite(_pin, LOW);
}