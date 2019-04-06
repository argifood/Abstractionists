#include <SoftwareSerial.h>
SoftwareSerial SIM900A(2,3); // RX | TX
char c = ' ';
bool canLoop = false;
void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  //Starting the communication
  SIM900A.begin(9600); 
  Serial.println("Please wait...");
  String response = "";
  
  delay(500);
  response = callCommand("AT+SAPBR=0,1"); //Closing any previous connections
  delay(500);

  response = callCommand("AT");
  if(response.equals("ERROR")){
    Serial.println("Something went wrong, restart");
    return;
  }
  else{
    response = callCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    if(response.equals("ERROR")){
      Serial.println("Something went wrong, restart");
      return;
    }
    else{
      response = callCommand("AT+SAPBR=3,1,\"APN\",\"internet.vodafone.gr\"");
      if(response.equals("ERROR")){
        Serial.println("Something went wrong, restart");
        return;
      }
      else{
        response = callCommand("AT+SAPBR=1,1");
        if(response.equals("ERROR")){
          Serial.println("Something went wrong, restart");
          return;
        }
        else{
          response = callCommand("AT+SAPBR=2,1");
          if(response.equals("ERROR")){
            Serial.println("Something went wrong, restart");
            return;
          }
          else{
            response = callCommand("AT+HTTPINIT");
            if(response.equals("ERROR")){
              Serial.println("Something went wrong, restart");
              return;
            }
            else{
              Serial.println("All good, we are ready to begin.");
              canLoop = true;
            }
          }
        }
      }
    }
  }
}

void loop()
{
  if(!canLoop)
    return;
  // Keep reading before you send to the Serial Monitor
  if (SIM900A.available())
  { 
    c = SIM900A.read();
    Serial.write(c);
  }
  // Keep reading before you send to SIM900
  if (Serial.available())
  { 
    c = Serial.read();
    SIM900A.write(c); 
  }
}

String callCommand(String cmd){
  String tmp = "";
  String response = "";
  boolean canContinue = false;
  int counter = 0; //If it reaches 5, there was definitely something wrong and we should stop

  //Calling the command until it works (sometimes some commands say ERROR the first time)
  while(!canContinue){
    cmd += "\r\n";
    char tempBuf[cmd.length() + 1];
    cmd.toCharArray(tempBuf, cmd.length()+1);
    SIM900A.write(tempBuf);
    while(true){
      if (SIM900A.available()){
        c = SIM900A.read();
        tmp += c;
        if(tmp.indexOf("OK") > 0){
          canContinue = true;
          break;
        }
        else if(tmp.indexOf("ERROR") > 0){
          canContinue = false;
          counter++;
          if(counter==5){
            return "ERROR";
          }
          break;
        }
      }
    }
    
    //Converting to byte array to use strtok
    //The response has 3 or more lines. The first line is our command, and the last is OK/ERROR
    //The lines in between are the response
    
    char *ptr = NULL;
    char charBuf[tmp.length() + 1];
    tmp.toCharArray(charBuf, tmp.length()+1);
    char *strings[10];
    byte index = 0;
    String result = "";
    ptr = strtok(charBuf, "\n");
    while(ptr != NULL)
    {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, "\n");
    }
    for(int n = 1; n < index-1; n++) //First and last lines are the ones we don't need
   { 
    response += strings[n];
   }
   return response;
  }
}
