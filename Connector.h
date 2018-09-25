#ifndef Connector_h
#define Connector_h //Basically, this prevents problems if someone accidently #include's your library twice

#include "Arduino.h"

class Sender
{
  public:
    Sender(int pin);
    void heartbeat ();
    void send(String* msg, int msgLength);
  private:
    int _pin;
};

class Receiver
{
  public:
    Receiver(int pin, int heartbeatAlarm, void (*fireAlarm)(), void (*stopAlarm)() );
    void listen(String* dest, int msgLength);
  private:
    int _pin;
    int _heartbeatAlarm;
    void (*_fireAlarm)();
    void (*_stopAlarm)();
};

#endif

// https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c