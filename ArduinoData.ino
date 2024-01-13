#include <dht.h>
#include <MQUnifiedsensor.h>
#define dht_apin 8 

dht DHT;
int LED1 = 12;
int smokeA0 = 5;
int smokeSensorThreshold = 300;
int gasA0 = 3;
int gasSensorThreshold = 800;
const int buzzer=11;
String M;
String N;
String T;
String H;
String S;

void setup(){
 
  pinMode(LED1, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(gasA0, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  
}
 
void loop(){
    DHT.read11(dht_apin);
    float h=DHT.humidity;
    H="H"+String(h)+"#";
    float t=DHT.temperature;
    T="T"+String(t)+"#";
    int analogSensor1 = analogRead(smokeA0);
    int analogSensor2 = analogRead(gasA0);
    M="M"+String(analogSensor1)+"#";
    N="N"+String(analogSensor2)+"#";
    S=M+N+T+H;
    Serial.print(" ");
    Serial.println(S);
    if (analogSensor1 > smokeSensorThreshold)
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(buzzer, HIGH);  
      delay(1000);
      digitalWrite(buzzer, LOW); 
    }
    else if(analogSensor2 > gasSensorThreshold)
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(buzzer, HIGH);  
      delay(1000);
      digitalWrite(buzzer, LOW);
    }
    else
    {
      digitalWrite(LED1, LOW);
      digitalWrite(buzzer, LOW);
    }
    delay(2500);
 
}
