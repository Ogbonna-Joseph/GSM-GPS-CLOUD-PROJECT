#include <Wire.h>    // Library for I2C Communication with DS3231 Module
#include <DHT.h>
#include <SoftwareSerial.h>
SoftwareSerial myserial(2, 3); // RX: 10, TX:11
#include <ArduinoJson.h>


 
//RTC_DS3231 r

void   ShowSerialData();
int  Signal();
void SendData();
String JsononData();
String JsonoffData();

void setup()
{
  myserial.begin(9600);        // the GPRS baud rate
  Serial.begin(9600);
  Serial.println("Initializing..........");
//  dht.begin();
  Wire.begin();
//  DynamicJsonBuffer jsonBuffer;
}
 
void loop()
{
  
}
 
 
void ShowSerialData()
{
  while(myserial.available()!=0)
  Serial.write(myserial.read());
  delay(2000); 
  
}

int Signal(){
    int volt = analogRead(0);
    return volt;
  }

void SendData(){
    if(Signal>200){
        Serial.println("");
        Serial.println("************************************************************");
  
 
        Serial.print("Signal: ");
        Serial.print(Signal());
        delay(1000);
       
       
       /********************GSM Communication Starts********************/
       
        if (myserial.available())
        Serial.write(myserial.read());
       
        myserial.println("AT");
        delay(3000);
       
        myserial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
        delay(6000);
        ShowSerialData();
       
        myserial.println("AT+SAPBR=3,1,\"APN\",\"internet.ng.airtel.com\"");//APN
        delay(6000);
        ShowSerialData();
       
        myserial.println("AT+SAPBR=1,1");
        delay(3000);
        ShowSerialData();
       
        myserial.println("AT+SAPBR=2,1");
        delay(3000);
        ShowSerialData();
       
       
        myserial.println("AT+HTTPINIT");
        delay(3000);
        ShowSerialData();
       
        myserial.println("AT+HTTPPARA=\"CID\",1");
        delay(3000);
        ShowSerialData();
       
        myserial.println("AT+HTTPPARA=\"URL\",\"https://omni-chi.vercel.app/api/ping\""); //Server address
        delay(4000);
        ShowSerialData();
       
        myserial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
        delay(4000);
        ShowSerialData();
       
       
        myserial.println("AT+HTTPDATA=" + String(JsononData().length()) + ",100000");
        Serial.println(JsononData());
        delay(4000);
        ShowSerialData();
       
        myserial.println(JsononData());
        delay(6000);
        ShowSerialData;
       
        myserial.println("AT+HTTPACTION=1");
        delay(6000);
        ShowSerialData();
      
        myserial.println("AT+HTTPHEAD");
        delay(6000);
        ShowSerialData();
       
       
        myserial.println("AT+HTTPREAD");
        delay(6000);
        ShowSerialData();
       
        myserial.println("AT+HTTPTERM");
        delay(10000);
        ShowSerialData;
       
        /********************GSM Communication Stops********************/
       
            
      }
    else{
      Serial.print("****************************************************");
      Serial.println("Signal/Power is been turned off");
      }
  }

  String JsononData(){
      DynamicJsonDocument doc(1024);
      doc["Status"] = "Signal source power is ON ";
      doc["Date"] = "12 May, 2021 ";
      doc["Time"]   = "12:30 PM ";
      doc["Address"][0] = "gps Coordinate";
      doc["Address"][1]   = "Ada George","Port Harcourt";
      doc["Voltage Value"]   = Signal();
      serializeJsonPretty(doc, myserial);
      return String(myserial) ;
    }

 String JsonoffData(){
      DynamicJsonDocument doc(1024);
      doc["Status"] = "Signal source power is OFF ";
      doc["Date"] = "12 May, 2021 ";
      doc["Time"]   = "12:30 PM ";
      doc["Address"][0] = "gps Coordinate";
      doc["Address"][1]   = "Ada George","Port Harcourt";
      doc["Voltage Value"]   = Signal();
      serializeJsonPretty(doc, myserial);
      return String(myserial) ;
      
    }
