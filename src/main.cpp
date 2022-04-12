#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>


//declaration des constantes
const int MOTOR_PIN    = 1; 
const int LED_PIN      = 6; 

//declaration des variables
int recieveData = 0;
int position = 0;
int previousBottom = 0;

Servo myservo; // creation de l'objet servo


//fonction pour detecter s'il y'a un envoi de données
void receiveEvent(int a){

  recieveData = Wire.read();   //mettre la valeur recue dans la variable recieveData
  
}


void setup() {
  
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(9);                  //adresse de recevoir de données
  Wire.onReceive(receiveEvent);
  myservo.attach(1);  

}

void loop() {

  if(previousBottom != recieveData){
    switch (recieveData)
    {
    case 1:
      position = 180;
      previousBottom = 1;
      break;
    
    case 2:
      position += 1;
      previousBottom = 2;
      break;

    case 3:
      position -= 1;
      previousBottom = 3;
      break;

    case 4:
      position = 0;
      previousBottom = 4;
      break;

    }

  }

  if (position == 0){
    digitalWrite(LED_PIN, LOW);
  }else{digitalWrite(LED_PIN, HIGH);}

  myservo.write(position);

  Serial.println(recieveData);
  Serial.println(position);
  delay(1000);
}