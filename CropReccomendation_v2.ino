#include <SFE_BMP180.h>
#include <Wire.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN 7


SFE_BMP180 pressure;
#define ALTITUDE 1655.0 

void setup()
{
  Serial.begin(9600);
  Serial.println("REBOOT");

  

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    

    Serial.println("BMP180 init fail\n\n");
    while(1); 
  }
}

void loop()
{
  char status;
  double T,P,p0,a;

 
  
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");
  
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);

  status = pressure.startTemperature();
  if (status != 0)
  {
    
    delay(status);


    status = pressure.getTemperature(T);
    if (status != 0)
    {
      
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      Serial.print((9.0/5.0)*T+32.0,2);
      Serial.println(" deg F");
      
      
      status = pressure.startPressure(3);
      if (status != 0)
      {
        
        delay(status);


        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");


          p0 = pressure.sealevel(P,ALTITUDE); 
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");


          a = pressure.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  delay(5000);  
}
