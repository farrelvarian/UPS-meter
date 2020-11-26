#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

//Inisiasi Firebase dan Accesss Point
#define FIREBASE_HOST "lastproject-aa262.firebaseio.com"
#define FIREBASE_AUTH "6BS8TdnqVpPJkWI8IEMIrMPDrao5bly30xo2mteM"
#define WIFI_SSID "Mahasiswa Polinema"
#define WIFI_PASSWORD "tahap3lulus"


//Inisiasi Variable
float vout = 0.0;
float Voltage = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
int rawvalue = 0;


void setup(){
  
  //Set Connecting Access Point 
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conncecting"); 

  //Pending  Connect
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }

  //nodeMCU to access Point connected
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Authentification to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop(){
  
  // read the value at analog input loop for 1000x
  for(int a=0;a<=1000;a++){
  rawvalue =rawvalue + analogRead(A0);
 }

 //Execution data from analog read
  rawvalue = (rawvalue/1000);
  vout = (rawvalue * 3.146) / 1024; // see text
  Voltage = vout / (R2/(R1+R2));

  //Display on Serial Monitor
  Serial.print(analogRead(A0));Serial.print("\t Voltage (V) =   ");Serial.println(Voltage,3);
  delay(500);

    //Make variable and send to firebase
    Firebase.setFloat("Voltage", Voltage);
    delay(1000);

    //Display on Serial Monitor if nodeMCU doesn't connected with Firebase 
    if (Firebase.failed()) { 
    Serial.print("setting /message failed:"); 
    Serial.println(Firebase.error());   
    return;
    delay(1000);
    }
}
