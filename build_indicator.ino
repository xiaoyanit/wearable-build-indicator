#include <SPI.h>
#include <Adb.h>

#define RED 5
#define GREEN 6
#define BLUE 9
#define BUTTON A5

Connection * connection;

void adbEventHandler(Connection * connection, adb_eventType event, uint16_t length, uint8_t * data)
{
  if (event == ADB_CONNECTION_RECEIVE)
  {
    byte signal = data[0];
    int signalInt = (int) signal;
    if (signalInt == 0) {
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
    } else {
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
    }
  }
}

void setup()
{
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE, OUTPUT); 
 pinMode(BUTTON, INPUT);
 Serial.begin(57600);
 
 digitalWrite(RED, HIGH);
 
 ADB::init();
 connection = ADB::addConnection("tcp:4567", true, adbEventHandler);  
}

void loop()
{
  if (digitalRead(BUTTON)) {
    digitalWrite(BLUE, HIGH);
    uint16_t data = 12;
    connection->write(2, (uint8_t*)&data);
    delay(1000);
  } else {
    digitalWrite(BLUE, LOW);
  }
  
  ADB::poll();
}

