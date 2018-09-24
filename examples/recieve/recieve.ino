#include <Connector.h>

void fire_heartbeatAlarm ()
{
  Serial.print("Kein Heartbeat\n");
}

void stop_heartbeatAlarm ()
{
  Serial.print("Heartbeat back\n");
}

Receiver receiver(2, 2000, fire_heartbeatAlarm, stop_heartbeatAlarm);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Listening\n");
  int rcvData[8] = {9,9,9,9,9,9,9,9};
  receiver.listen (rcvData, 8);
  Serial.print("Received: ");
  for (int i=0; i<8; i++)
  {
    Serial.print(rcvData[i]);
  }
  Serial.print("\n");
}
