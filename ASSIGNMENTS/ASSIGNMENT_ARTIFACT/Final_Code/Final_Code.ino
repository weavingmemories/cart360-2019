const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor
#define LED_PIN_1 8 // LED pin 1
#define LED_PIN_2 9
#define LED_PIN_3 10
#define LED_PIN_4 11
#define LED_PIN_5 12
#define TOUCH_PIN A0

// For everything re: the random pin, I referenced:
// https://www.learnrobotics.org/blog/random-led-generator-using-arduino-uno/

// random pin chose:

const byte ledPins [] = {8,9,10,11,12};
byte ledPin;


long duration, cm;

// timer
unsigned long startTime;
unsigned long timePassed;

boolean hasAlreadyArrived = false;

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  pinMode (LED_PIN_1, OUTPUT);
  pinMode (LED_PIN_2, OUTPUT);
  pinMode (LED_PIN_3, OUTPUT);
  pinMode (LED_PIN_4, OUTPUT);
  pinMode (LED_PIN_5, OUTPUT);
  startTime = millis();
  Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
timePassed = millis() - startTime;
 Serial.println(timePassed);
calcDistance();
detectPresence();
checkTouch();
}

void calcDistance() {
     
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void detectPresence() {
  if (cm <= 30 && timePassed >= 3000) {

    if (hasAlreadyArrived == false) {
      startPattern();
      timePassed =0;
      startTime = millis();
    }

    Serial.println("arrived");
    hasAlreadyArrived = true;
    timePassed= 0;
    startTime = millis();
  }

  if (cm >= 30 && timePassed >= 5000) {
    digitalWrite(LED_PIN,LOW);
    Serial.println("left");
    hasAlreadyArrived = false;
    timePassed =0;
    startTime = millis();
  }

}

void checkTouch() {
  
  pinValue = analogRead(THEPIN);
  Serial.println(pinValue);

 if (pinValue >= 900 ) {

  // This is where you pick random led
  ledPin = ledPins [random(0,6)];
  
  digitalWrite(LED_PIN, HIGH);
    
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void startPattern() {
  digitalWrite(LED_PIN_1,HIGH);
  digitalWrite(LED_PIN_2,HIGH);
  digitalWrite(LED_PIN_3,HIGH);
  digitalWrite(LED_PIN_4,HIGH);
  digitalWrite(LED_PIN_5,HIGH);
  delay(1000);
  digitalWrite(LED_PIN_1,LOW);
  digitalWrite(LED_PIN_2,LOW);
  digitalWrite(LED_PIN_3,LOW);
  digitalWrite(LED_PIN_4,LOW);
  digitalWrite(LED_PIN_5,LOW);
  Serial.println("Pattern complete");
}

/*
   Select a random LED to turn on
   Print out the name of the color
   in the Serial Monitor
void random_led() {
  // pick a pin number 9-13 because we have LEDs on those pins...
  int random_led = random(9, 13);
  
  // generate our map of the random LED to the map of our array
  int color_map = map(random_led, 9, 12, 0, 3);
  Serial.print("Color is... ");
  // Use the random array number to print out the color
  Serial.println(led_colors[color_map]);

  //turn the LED on, then off for 1/2 second
  digitalWrite(random_led, HIGH);
  delay(500);
  digitalWrite(random_led, LOW);
  delay(500);
}
*/
