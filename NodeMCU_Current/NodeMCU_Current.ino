#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "lastproject-aa262.firebaseio.com"
#define FIREBASE_AUTH "6BS8TdnqVpPJkWI8IEMIrMPDrao5bly30xo2mteM"
#define WIFI_SSID "Mahasiswa Polinema"
#define WIFI_PASSWORD "tahap3lulus"

double Voltage = 0;
double Current = 0;
void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conncecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
//Voltage is Sensed 1000 Times for precision
   for(int i = 0; i < 1000; i++) {
   Voltage = (Voltage + (0.003320312 * analogRead(A0))); // (5 V / 1024 (Analog) = 0.00489) which converter Measured analog input voltage to 5 V Range
   }
  Voltage = (Voltage) /1000;
  Current = (Voltage - 1.65)/ 0.185; // Sensed voltage is converter to current
  Serial.print(analogRead(A0));
  Serial.print("\t Voltage Sensed (V) = ");
  Serial.print(Voltage,3);
  Serial.print("\t Current (A) = ");
  Serial.println(Current,3); 
  delay(500);

  Firebase.setFloat("Current", Current);
    if (Firebase.failed()) { 
    Serial.print("setting /message failed:"); 
    Serial.println(Firebase.error());   
    return;
    delay(500);
    }
}
