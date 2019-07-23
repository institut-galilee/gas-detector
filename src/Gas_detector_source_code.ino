#include <Servo.h>

Servo myservo;

// Definition des broches des actionneurs
int pin_led_rouge = 8;
int pin_led_verte = 9;
int pin_buzzer = 10;
int pin_servo = 11;
int pin_ventilo = 12;

// pin du capteur MQ2  
int pin_a = A2;  

int niveau_senseur = 200;

void setup()
{
  // Definir les broche du senseur comme entree
  pinMode(pin_a, INPUT);

  // Definir les actionneurs comme sortie
  pinMode(pin_led_rouge, OUTPUT);
  pinMode(pin_led_verte, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(pin_ventilo,OUTPUT);
  myservo.attach(pin_servo);
  
  // Initialiser le port serie pour le flux de transmission en bit/s
  Serial.begin(9600);
}

void loop()
{ 
  
  // Lecture de données sur l'entree analogique
  int valeur_analogique = analogRead(pin_a);

  // Afficher les donnees sur le moniteur serie (vers Pc et bluetooth)
  Serial.print(" Taux de gaz : ");
  Serial.print(valeur_analogique);
  Serial.println(" ppm");

  // Verifier le niveau de gaz/fumee 
  if (valeur_analogique > niveau_senseur)
  {
    // Detection de fuite de gaz
    digitalWrite(pin_led_rouge, HIGH);
    digitalWrite(pin_led_verte, LOW);
    digitalWrite(pin_buzzer, HIGH);
    digitalWrite(pin_ventilo, HIGH);
    myservo.write(90);
    Serial.println(" Alarme declenchee!!");
    Serial.println(" vanne fermee");
    
  }
  else
  {
    // Etat normal (Pas de fuite de gaz)
    digitalWrite(pin_led_rouge, LOW);
    digitalWrite(pin_led_verte, HIGH);
    digitalWrite(pin_buzzer, LOW);
    digitalWrite(pin_ventilo, LOW);
    Serial.println(" Alarme desactivee");
    Serial.println(" vanne ouverte");
     
  }
 
// petite pause
  delay(300); 
}


