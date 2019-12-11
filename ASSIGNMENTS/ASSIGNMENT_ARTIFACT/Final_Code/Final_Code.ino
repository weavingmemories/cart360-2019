       const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4; // Echo Pin of Ultrasonic Sensor

// LED PINS
#define LED_PIN_1 8
#define LED_PIN_2 9
#define LED_PIN_3 10
#define LED_PIN_4 11
#define LED_PIN_5 12

// TOUCH SENSOR PIN
#define TOUCH_PIN A0

// MAX IN ARRAY
// col
#define MAX_PATTERN 10
// row
//#define MAX_AMOUNT 5

// random pin chose:

const byte ledPins [] = {8, 9, 10, 11, 12};
byte ledPin;

// pattern array
const byte pattern[MAX_PATTERN];
// counter for how many pattern entries we have
int countPattern =0;
// counter for how many rows we have been through
//int countAmount =0;

// timer
long duration, cm;
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
 // Serial.print(cm);
 // Serial.print("cm");
 // Serial.println();
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void detectPresence() {
  if (cm <= 30 && timePassed >= 3000) {

    if (hasAlreadyArrived == false) {
    //  startPattern();
  //  Serial.println("Start");
      timePassed = 0;
      startTime = millis();
    }

    Serial.println("arrived");
    hasAlreadyArrived = true;
    timePassed = 0;
    startTime = millis();
  }

  if (cm >= 30 && timePassed >= 5000) {
  //  Serial.println("left");
    hasAlreadyArrived = false;
    timePassed = 0;
    startTime = millis();
  }

}

void checkTouch() {

  int pinValue = analogRead(TOUCH_PIN);
  Serial.println(pinValue);

  if (pinValue >= 900 ) {

    // This is where you pick random led
   // ledPin = ledPins [random(0, 6)];
   // Serial.println(ledPin);
  //  digitalWrite(ledPin, HIGH);
  digitalWrite(LED_PIN_1,HIGH);
    // Now, add to array
     // if (countPattern < MAX_PATTERN) {
     // pattern[countPattern] = ledPin;
    //  countPattern++;
     // Serial.println(countPattern);
      } else {
    digitalWrite(ledPin, LOW);
  }

}

void startPattern() {
  digitalWrite(LED_PIN_1, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_1, LOW);
  Serial.println("Pattern complete");
}
