#include <Connector.h>

Sender sender(2);

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  Serial.print("3x Heartbeat\n");
  for (int  i=0; i<3; i++)
  {
    sender.heartbeat();
    delay (1500);
  }

  Serial.print("Sending\n");
  int sendData[8] = {1,1,1,0,0,1,1,1};
  sender.send(sendData, 8);

  Serial.print("No Heartbeat\n");
  delay(5000);
}
