#include <SoftwareSerial.h>
SoftwareSerial SIM900A(2,3); // RX | TX
char c = ' ';
void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  //Starting the communication
  SIM900A.begin(9600); 
  Serial.println("Please wait...");
  delay(1000);
  Serial.println("All set!");
  delay(1000);
  SIM900A.write("AT\r");
  
  String tmp = Serial.readStringUntil('\n');
  if(!tmp.equals("OK")){
    Serial.println(tmp);
    return;
  }
  else{
    
  }
  
  delay(1000);
  SIM900A.write("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r");
  delay(1000);
  SIM900A.write("AT+SAPBR=3,1,\"APN\",\"internet.vodafone.gr\"\r");
  delay(1000);
  SIM900A.write("AT+SAPBR =1,1\r");
  delay(5000);
  SIM900A.write("AT+SAPBR=2,1\r");
  delay(1000);
}
void loop()
{
  // Keep reading before you send to the Serial Monitor
  /*if (SIM900A.available())
  { c = SIM900A.read();
  Serial.write(c);}*/
  // Keep reading before you send to SIM900
  if (Serial.available())
  { c = Serial.read();
  SIM900A.write(c); 
  }
}
