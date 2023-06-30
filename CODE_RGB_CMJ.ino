#include <Wire.h>
#include <Adafruit_TCS34725.h>


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

#define redLED  2    // Broche de la LED rouge
#define greenLED 3  // Broche de la LED verte
#define blueLED 4   // Broche de la LED bleue

void setup() {
  Serial.begin(9600);
 
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  if (!tcs.begin()) {
    Serial.println("Capteur de couleur TCS3472 introuvable !");
    while (1);
  }

  tcs.setInterrupt(false);
}

void loop() {
  uint16_t clear, red, green, blue;

  tcs.getRawData(&red, &green, &blue, &clear);

  Serial.println("rouge");
  Serial.println(red);
  Serial.println("vert ");
  Serial.println(green);
  Serial.println("bleu");
  Serial.println(blue);
  Serial.println();

  
//   //Allumer la LED correspondante à la couleur détectée
//   
if (red < 100 && green < 300 && blue > 300) { //bleu detecter
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED,LOW);
  digitalWrite(blueLED, HIGH);
  Serial.println("bleu");
  delay(2000);}
else if (red < 110 && green > 200 && blue < 180) { //vert detecter
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED,HIGH);
  digitalWrite(blueLED, LOW);
  Serial.println("vert");
  delay(2000);}
else if (red > 290 && green < 120 && blue < 120){ //rouge detecter
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED,LOW);
  digitalWrite(blueLED, LOW);
  Serial.println("rouge");
  delay(2000);}
else if (red > 450 && green > 450 &&  blue < 370 ) { //jaune detecter
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED,HIGH);
  digitalWrite(blueLED, LOW);
  Serial.println("Jaune");
  delay(2000);}
//else if (red < 320 && green > 300 && green < 650 && blue < 650 && green > 300) { //cyan detecter
//  digitalWrite(redLED, LOW);
//  digitalWrite(greenLED,HIGH);
//  digitalWrite(blueLED, HIGH);
//  Serial.println("Cyan");
//  delay(2000);}
else if ( red > 75 && green < 120 && blue > 70) { //magenta detecter
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED,LOW);
  digitalWrite(blueLED, HIGH);
  Serial.println("Magenta");
  delay(2000);}
else { digitalWrite(redLED, LOW);
  digitalWrite(greenLED,LOW);
  digitalWrite(blueLED, LOW);
  delay(500);}
}
