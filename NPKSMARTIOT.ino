/*Plant watering system with new blynk update
   https://srituhobby.com
*/
//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Initialize the LCD display

char auth[] = "VBEXuDqzkQDJudGpj0_QKn44_m9ASM91";//Enter your Auth token
char ssid[] = "Sumavirus";//Enter your WIFI name
char pass[] = "suma1234";//Enter your WIFI password

BlynkTimer timer;
bool Relay = 0;
int Nitro ;
int php ;
int pot ; 

//Define component pins
#define sensor A0
#define waterPump D4
#define N D1
#define P D2
#define K D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  Serial.begin(9600);
  pinMode(N, OUTPUT);
  digitalWrite(N, HIGH);
  Serial.begin(9600);
  pinMode(P, OUTPUT);
  digitalWrite(P, HIGH);
  Serial.begin(9600);
  pinMode(K, OUTPUT);
  digitalWrite(K, HIGH);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);


  //Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the button value
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
  }
}
BLYNK_WRITE(V2){
  Nitro = param.asInt();
  if(Nitro == 0) {
    digitalWrite(N, HIGH);
  } else{
    digitalWrite(N, LOW);
     delay(Nitro);
  }
}
BLYNK_WRITE(V3){
  php = param.asInt();
  if(php == 0) {
    digitalWrite(P, HIGH);
  } else{
    digitalWrite(P, LOW);
     delay(php);
  }
}
BLYNK_WRITE(V4){
  pot = param.asInt();
  if(pot == 0) {
    digitalWrite(K, HIGH);
  } else{
    digitalWrite(K, LOW);
    delay(pot);
  }
}


//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);
}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}