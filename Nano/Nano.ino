String inData;
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(10, 11); // RX | TX
 
void setup() 
{
    Serial.begin(74880);   
    ESPserial.begin(74880);  
}
void loop() 
{
 while (ESPserial.available() > 0)
    {
        char recieved = ESPserial.read();
        inData += recieved; 
        if (recieved == '\n')
        {
           // Serial.print("Arduino Received: ");
           // Serial.print(inData);
             String data = inData.substring(5);
             data = getValue(data,' ',0);
             String data1 = getValue(data,'=',0);
             String data2 = getValue(data,'=',1);
             Serial.print(data1);
             Serial.print(" ");
             Serial.print(data2);
            inData = ""; // Clear recieved buffer
            Serial.println();
        }
    }
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
