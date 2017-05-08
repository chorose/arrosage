#include <SPI.h>
#include <Ethernet.h>

/* Détails technique de la connexion ethernet */
byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0D, 0xB5, 0xBD };
byte ip[] = { 
  192, 168, 1, 101 };
int port = 8000;

// led sur pin 8 et source de courant sur pin 7
int led = 8;
int dc = 7;

// creation du server sur le port
EthernetServer server(port);

float tension, temp;
int tempValue, humiValue;

void setup()
{
  // moniteur serie pour le debug
  Serial.begin(9600);
  // Configuration de la connexion ethernet et du server
  Ethernet.begin(mac,ip);
  server.begin();

  // configuration des pins (bas par défaut)
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(dc, OUTPUT);
  digitalWrite(dc, LOW);
}

void loop()
{
  // Attente de la connexion d'un client
  EthernetClient client = server.available();
  if (client.connected()) {
    Serial.write("connexion OK\n");
    // si le client nous envoie quelque chose
    if (client.available()) {
      char c = client.read();
      //On regarde ce que le client nous demande
      switch(c){
      case 'A':
        // allumage de la led
        Serial.write("Arrosage\n");
        digitalWrite(led, HIGH);
        delay(3000);
        digitalWrite(led, LOW);
        break;
      case 'T':
        Serial.write("Temperature\n");
        tempValue = analogRead(A1);
        // Converti la lecture en tension
        tension = (tempValue * 5.0) / 1024;
        temp = (tension * 25) / 0.75;
        Serial.print(temp);
        break;
      case 'H':
        Serial.write("Humidite\n");
        // activation de la source de courant
        digitalWrite(dc, HIGH);
        // on attend 5s que le courant s'etablisse
        delay(5000);
        // on fait plusieurs mesures
        humiValue = analogRead(A0);
        delay(1000);
        Serial.println(humiValue);
        for(int i=0;i<1000;i++){
          // read the input on analog pin 0:
          humiValue = analogRead(A0);
          delay(1000);
        }
        // print out the value you read:
        Serial.println(humiValue);
        // desactivation de la source de courant
        digitalWrite(dc, LOW);
        break;
      }
    }
  }
}

