#include <Connector.h>

void fireHBalarm ()
{
  Serial.print("Kein Heartbeat\n");
}

void stopHBalarm ()
{
  Serial.print("Heartbeat back\n");
}

Receiver receiver(2, 2000, fireHBalarm, stopHBalarm);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Listening\n");
  String msg = "_____";
  receiver.listen (&msg, 5);
  Serial.print(msg);
  Serial.print("\n");
}
