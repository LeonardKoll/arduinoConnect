#include "Arduino.h"
#include "Connector.h"

Sender::Sender(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Sender::heartbeat()
{
  digitalWrite(outPin, HIGH);
  delay(2);
  digitalWrite(outPin, LOW);
}

void Sender::send(int msg[], int msgLength)
{
  // Start sending
  digitalWrite(outPin, HIGH);
  delay(1);
  digitalWrite(outPin, LOW);
  delay(1);

  // Data
  for (int i=0; i<msgLength; i++)
  {
    if(msg[i] == 0)
    {
      digitalWrite(outPin, LOW);
    }
    else
    {
      digitalWrite(outPin, HIGH);
    }
    delay(1);
  }

  digitalWrite(outPin, LOW);
}