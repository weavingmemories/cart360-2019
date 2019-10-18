/********************** ETUDE 3 CART 360 2019 *******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  loopMODE ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */

 /*
  * The reason why different tones are generated on button press is due to the resistor ladder.
  * The amount of voltage being sent through the circuit depends on how much resistance is being
  * enforced- which in turn is sending a certain number to analogRead. In the code, by using the
  * amount of voltage in the tone() function, we are translating voltage to frequency.
  */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes =0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 
int mode =0; // start at off

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);

  Serial.begin(9600);

  pinMode(LED_PIN_R,OUTPUT);
  pinMode(LED_PIN_G,OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
// checking the state of the button
 int buttonState = digitalRead(BUTTON_MODE_PIN);

//if the state is HIGH aka pressed

if (buttonState == HIGH) {
//shift through the modes
  mode++;
// avoid bouncing (cycling through modes too fast)
  delay(200);
// will loop through 5 states (0-4), when it reaches 5, it will reset to 0!
  if (mode % 5 == 0) {
    mode = 0; 
  }
}
  
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  // So in this instance, the switch is checking what mode the button has cycled to, and will change the RGB
  // LED accordingly by writing the RGB values to the pins defined in Setup.
  switch (mode) {
  case 0:
    //turn off the LEDs when mode equals 0
    analogWrite(LED_PIN_R,0);
    analogWrite(LED_PIN_G,0);
    analogWrite(LED_PIN_B,0);
    break;
  case 1:
    //change color to blue when mode equals 1
    analogWrite(LED_PIN_R,0);
    analogWrite(LED_PIN_G,0);
    analogWrite(LED_PIN_B,255);
    break;
  case 2:
    //change color to red when mode equals 2
    analogWrite(LED_PIN_R,255);
    analogWrite(LED_PIN_G,0);
    analogWrite(LED_PIN_B,0);
    break;
  case 3:
    //change color to green when mode equals 3
    analogWrite(LED_PIN_R,0);
    analogWrite(LED_PIN_G,255);
    analogWrite(LED_PIN_B,0);
    break;
  case 4:
    // change color to purple when mode equals 4
    analogWrite(LED_PIN_R,150);
    analogWrite(LED_PIN_G,50);
    analogWrite(LED_PIN_B,230);
    break;
    
}
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode ==0) { 
    reset();
  }
  else if(mode ==1) {
    live();
  }
  else if(mode ==2) {
    record();
  }
  
  else if(mode ==3) {
    play();
  }
   
   else if(mode ==4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
// This code is going through the array, making sure to stop at countNotes (the amount of notes recorded
// and setting the values to 0 (therefore empty)
{
  for (int i=0; i<countNotes; i++) {
     notes[i] = 0;
    
  }
  countNotes = 0;
  
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
  // We are reading the amount of voltage being sent through the resistor chain:
    int volts = analogRead(NOTE_IN_PIN);
    
    Serial.println(volts);

    // This if statement is to reduce noise, making sure the buzzer only plays
    // when the voltage is over a certain amount (aka a button is pressed)
    // It plays the amount of voltage as a frequency, for the constant duration of 200.
    
    if (volts > 8) {
    tone(BUZZER_PIN, volts, duration);
    delay(duration);
    }
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{

    int volts = analogRead(NOTE_IN_PIN);
    
    if (volts > 8) {
    tone(BUZZER_PIN, volts, duration);
    delay(duration);

    // If countNotes hasn't exceeded the maximum amount of notes it can hold in the array,
    // store the voltage (frequency) into the array slot, and then increment countNotes to
    // continuously add notes in the array one at a time.
    
    if (countNotes < MAX_NOTES) {
      notes[countNotes] = volts;
      countNotes++;
      Serial.println(countNotes);
      
    }

   }
    

    
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // This for loop goes through the notes array, making sure to only go through
  // the amount of notes recorded (countNotes) and playing each one's recorded voltage/frequency.
  
  for(int i=0; i < countNotes; i++) {
    tone(BUZZER_PIN, notes[i], duration);
    
    Serial.println(notes[i]);
    delay(duration);

  // This if statement checks in the for loop to see if the mode change button is being pressed.
  // If it is, stop the for loop and allow the button press to change to the next mode.
  
    if (digitalRead(BUTTON_MODE_PIN) == HIGH) {
      break;
    }
  }
  
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode()
{
  // For this mode, I implemented the random function to go through the array and
  // play a random value contained within the array (within countNotes).
  // Of course, the rest is the same as play().
  
  int randomTone = random(0,countNotes);
  for(int i=0; i < countNotes; i++) {
    tone(BUZZER_PIN, notes[randomTone], duration);
    
    Serial.println(randomTone);
    delay(duration);

    if (digitalRead(BUTTON_MODE_PIN) == HIGH) {
      break;
    }
  }
}

/**************************************************************************/
