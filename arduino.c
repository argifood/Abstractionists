#include <SoftwareSerial.h>
//#include "Timer.h"

//Timer t;
SoftwareSerial SIM900A(2,3); // RX | TX
char c = ' ';
bool canLoop = false;
unsigned long time_now = 0;
void setup() 
{
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  
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
              getPumps();
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
 time_now = millis(); 
  while(millis() < time_now + 200){
      
  }
  callHttpCommand("AT+HTTPACTION=0");
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 200){
      
  }
  callCommand("AT+HTTPREAD");
  time_now = millis(); 
  while(millis() < time_now + 200){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  
  callCommand("AT+HTTPREAD");
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 200){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  callCommand("AT+HTTPREAD");
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 200){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  //
  String temp = callRequestCommand("AT+HTTPREAD");

  char str[temp.length()+1];
  temp.toCharArray(str, temp.length()+1);

    String values[3][2];
    int keysCounter = 0;
    values[0][0] = "";
    values[1][0] = "";
    values[2][0] = "";
    values[0][1] = "";
    values[1][1] = "";
    values[2][1] = "";
  
    // Returns first token 
    char* token = strtok(str, ","); 
    char* temp2;
    while (token != NULL) { 
       // Serial.println(token);
        int valuesCounter = 0;
        String temp2 = token;
        for(int i = 0; i<temp2.length()+1; i++){
          if(temp2.charAt(i) != '-'){
            values[keysCounter][valuesCounter] += temp2.charAt(i);
          }
          if(temp2.charAt(i) == '-'){
            valuesCounter++;
          }
        }
        keysCounter++;
        token = strtok(NULL, ","); 
    }
 //   Serial.println(values[1][1]);
    digitalWrite(values[0][0].toInt(), values[0][1]=="L"?LOW:HIGH);
    digitalWrite(values[1][0].toInt(), values[1][1]=="L"?LOW:HIGH);
    digitalWrite(values[2][0].toInt(), values[2][1]=="L"?LOW:HIGH);
    //Serial.println(values[1][1]);
}

void getPumps(){
  Serial.println("STARTING");
  String response = "";
  callCommand("AT+HTTPPARA=\"URL\",\"abstractionists.alwaysdata.net/api/getPumps.php\"");
  time_now = millis(); 
  while(millis() < time_now + 500){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 500){
      
  }
  callHttpCommand("AT+HTTPACTION=0");
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 150){
      
  }
  callCommand("AT+HTTPREAD");
  time_now = millis(); 
  while(millis() < time_now + 150){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  
  callCommand("AT+HTTPREAD");
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 150){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  callCommand("AT+HTTPREAD");
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  time_now = millis(); 
  while(millis() < time_now + 150){
      
  }
  while(SIM900A.available()){
    c = SIM900A.read();
  }
  //
  String temp = callRequestCommand("AT+HTTPREAD");
  Serial.println(temp);
  canLoop=true;
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

String callHttpCommand(String cmd){
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
        if(tmp.indexOf("+HTTPACTION") > 0){
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
    for(int n = 3; n < index-1; n++) //First and last lines are the ones we don't need
   { 
    response += strings[n];
   }
   return response;
  }
}
String callRequestCommand(String cmd){
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
    for(int n = 3; n < index-1; n++) //First and last lines are the ones we don't need
   { 
    response += strings[n];
   }
   response.trim();
   return response;
  }
}
