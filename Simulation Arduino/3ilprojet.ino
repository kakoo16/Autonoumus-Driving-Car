#include <Servo.h>

Servo myservo;
Servo myservo1;  // create servo object to control a servo

Servo myservo2;
// create servo object to control a servo
int pin_servo = 6;       // Pin sur lequel est branché le servo
int pos1 = 0;             // variable permettant de conserver la position du servo
int angle_initial = 80;   //angle initial
int angle_final = 180;   //angle final
int increment = 1;       //incrément entre chaque position
bool angle_actuel = false;

const int TRIG_PIN = 12;
const int ECHO_PIN = 13;
long lecture_echo;    // crée une variable de type « long » et du nom de « lecture_echo » qui servira à stocker la valeur que réceptionne le capteur.
long distance_cm;     // crée une variable de type « long » et du nom de « distance_cm » qui représente la distance qui sépare le capteur de l’objet.

int pos = 0;



void setup() {
   Serial.begin(9600);                       
  while(!Serial){;} 
  myservo.attach(pin_servo);
  myservo1.attach(10); 
  myservo2.attach(11);
  
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}

void loop() {

  for (pos = angle_initial; pos <= angle_final; pos += increment) { 
     
    myservo.write(pos); 
                
    delay(30); 
    if (angle_actuel) {
        Serial.println(myservo.read());
        obstacle();
       
    }
  }
  
  
  for (pos = angle_final; pos >= angle_initial; pos -= increment) { 
    // Fait le chemin inverse
    
    myservo.write(pos); 
                 
    delay(30);   
    if (angle_actuel) {
        Serial.println(myservo.read());
         obstacle();
    }
  }



}
  


  void obstacle(){


  long duration, distanceCm, distanceIn;
 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);
 
  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;
  distanceIn = duration / 74 / 2;

      if (distanceCm <= 40)
  {

  
  for (pos = 180; pos >= 0; pos -= 1) { 
     myservo1.write(pos);
    // myservo2.write(pos);
    delay(15);                     
  }

  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
   // myservo1.write(pos);  
    myservo2.write(pos);
    delay(15);                       
  }
 
  }
  else
  {
    Serial.print(distanceIn);
    Serial.print("in: ");
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }
  
 
    }
       
