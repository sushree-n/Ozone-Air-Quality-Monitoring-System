#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MQUnifiedsensor.h>
#define BLYNK_PRINT Serial
char auth[] = "Op3FjVJkwo4-ni8G7z4XPfDzSKAK2cXJ";
 
/* WiFi credentials */
char ssid[] = "Nivas_2.4G";
char pass[] = "april2008";
 
BlynkTimer timer;
int mq135_value=0;
float Temp_value=0;
float Hum_value=0;
int mq2_value=0;
char Received_data;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
  WiFi.begin(ssid, pass); 
  //Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, pass);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());   
}

void loop() {
  if (Serial.available())
  {
      Received_data=Serial.read(); //Get next character from bluetooth
      if(Received_data=='M') mq135_value=Serial.parseInt(); 
      if(Received_data=='N') mq2_value=Serial.parseInt();
      if(Received_data=='T') Temp_value=Serial.parseFloat(); 
      if(Received_data=='H') Hum_value=Serial.parseFloat(); 
  
      Serial.print(" Smoke sen is = ");
      Serial.print(mq135_value);
      Serial.print(" PPM  ");
  
      Serial.print(" Gas output is = ");
      Serial.print(mq2_value);
      Serial.print(" PPM  ");
   
      Serial.print(" Temperature is = ");
      Serial.print(Temp_value);
      Serial.print(" C ");
  
      Serial.print(" Humidity is = ");
      Serial.print(Hum_value);
      Serial.println(" % ");
    }
    timer.run(); // Initiates SimpleTimer
    Blynk.run();
}

void getSendData()
{
  Received_data=Serial.read(); //Get next character from bluetooth
  if(Received_data=='M') mq135_value=Serial.parseInt(); 
  if(Received_data=='N') mq2_value=Serial.parseInt();
  if(Received_data=='T') Temp_value=Serial.parseFloat(); 
  if(Received_data=='H') Hum_value=Serial.parseFloat(); 
  Blynk.virtualWrite(V2, mq135_value); //virtual pin V3
  Blynk.virtualWrite(V3, Temp_value);
  Blynk.virtualWrite(V4, mq2_value);
  Blynk.virtualWrite(V5, Hum_value);
  if (mq135_value > 300 )
  {
    Blynk.notify("Smoke Detected!!!"); 
  }
  if (mq2_value > 800 )
  {
    Blynk.notify("Possible Gas Leak"); 
  }
}
