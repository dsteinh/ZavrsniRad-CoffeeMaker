 #include "ESP8266WiFi.h"
#include <Servo.h> 
const char* ssid = "ssid";//Unesite naziv vaše wifi mreže
const char* password = "password"; //Unesite vašu lozinku
int servoPin = 16;                 //Pin na kojem se Servo  nalazi
WiFiServer server(80);             //otvaramo server na portu 80
  int relay = 4;        
Servo myservo; 
  int prelay = 5;
  int pos = 50;

void setup() {
   pinMode(relay, OUTPUT); 
   pinMode(prelay, OUTPUT);
Serial.begin(115200); //POZOR! promjeniti u Serial monitoru baud rate na 115200 baud.
//U suprotnom će se dobiveni znakovi krivo interpretirati te se neće moći razumjeti.
delay(10);

digitalWrite(relay,HIGH);
digitalWrite(prelay,HIGH);        //Postavljanje pina relay OUTPUT-a na HIGH sto znaci da je ugasen jel koristim obrnutu logiku
//Spajanje na WiFi mrežu
Serial.println();
Serial.println();
Serial.print("Spajanje na ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) { //Ispisivanje "." znaka sve dok se ne spoji na definiranu WiFi mrežu
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi spojen");
//Pokreni server
server.begin();
Serial.println("Server pokrenut");
//Ispiši IP adresu
Serial.print("Kopiraj ovu adresu u preglednik: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}
void loop() {
// Provjeri je li klijent spojen
WiFiClient client = server.available();
if (!client) {
return;
}
// Čekaj dok klijent ne pošalje neke podatke
Serial.println("Novi klijent");
while(!client.available()){
delay(1);
}
// Pročitaj prvu liniju zahjeva
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
// Interpretiraj zahtjev
int value1 = HIGH;
if (request.indexOf("/LED=ON") != -1) {     //ako http adresa zavrsava sa /LED=ON pokrece se slijedece
myservo.attach(servoPin); 
myservo.write(180);
  for(pos = 180; pos>=130; pos-=3)     // goes from 180 degrees to 50 degrees
  {                               
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos = 130; pos < 180; pos += 3)  // goes from 50 degrees to 180 degrees
  {                                  // in steps of 3 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }



delay(2000);
 digitalWrite(relay, LOW); //kuhalo se pokrene
      delay(8000);
 digitalWrite(relay, HIGH);
    delay(2000);
digitalWrite(prelay, LOW); //pumpa se pokrene
delay(2000);
digitalWrite(prelay, HIGH);
            }
            
// Postavi stanje po zahtjevu
// Vrati odgovor klijentu
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("");
client.println("");
client.print("sklop sada");
if(value1 == HIGH) {
client.print("radi");
} else {
client.print("ne radi");
}
client.println("<br><br>");
client.println("<a href='/LED=ON'><button>Upali sklop</button></a>");
client.println("");
delay(1);
Serial.println("Klijent je iskljucen");
Serial.println("");
}
