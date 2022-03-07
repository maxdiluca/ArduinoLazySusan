


int seed = 1;

#include <Stepper.h>
#include <ezButton.h>

const int stepsPerRevolution = 32;  // change this to fit the number of steps per revolution
const int gearRed = 64; // for your motor
const int stepsPerOutRev = stepsPerRevolution * gearRed;

const int n_stimuli = 7;
const int n_repetitions = 5;
const int n_trials = n_stimuli * n_repetitions;


const int ledPin = 13;      // select the pin for the LED

// digital pin 12 has a pushbutton attached to it
const int pushButton = 12;


ezButton button(pushButton);


int buttonState;

//2048
//2ms
//500s/s
//4s rotation

// step sequence needs to be 1, 3, 2, 4
// initialize the stepper library on pins 8 through 11:  4, 2, 1, 3);
Stepper myStepper(stepsPerRevolution,    5, 3, 2, 4);//5, 3, 2, 4


int stepsRequired;


long randNumber;

int f;
int i;
int n;
int chosen_element;
int chosen_position;
int r;
int x;

int randomized_trials[n_stimuli * n_repetitions];
int ordered_array[n_stimuli + 1];

int currentstepangle;

const int stepsperdivision = stepsPerOutRev / n_stimuli;

int count = 0;

void setup() {

  // pinMode(button, INPUT_PULLUP);

  // initialize
  Serial.begin(115200);

  randomSeed(seed);//analogRead(0));

  button.setDebounceTime(50); // set debounce time to 50 milliseconds

  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  //create an array of stimuli
  for ( r = 0; r < n_repetitions; r = r + 1)
  {

    //define series of ordered stimuli for each repetition
    for ( i = 0; i < n_stimuli + 1; i = i + 1) {
      ordered_array[i] = i + 1;
      // Serial.print(ordered_array[i]);
    }
    //  Serial.println(" ");

    for (n = n_stimuli - 1; n > -1; n--) // here we pick random elements in the array until we got 'em all
    {
      chosen_position = random(n);
      chosen_element  = ordered_array[chosen_position];
      randomized_trials[count] = chosen_element ;
      count = count + 1;
      //    Serial.print( chosen_element );
      for ( x = chosen_position; x < n; x++) // here we shift all elements (who come AFTER the chosen one) in the array one place to the left
      {
        ordered_array[x] = ordered_array[x + 1];
      }

    }

    Serial.println(" ");


  }
  // Serial.println(-1);
  for ( i = 0; i < (n_trials); i = i + 1) {
    Serial.print(randomized_trials[i]);

  }
  Serial.println(" ");

  currentstepangle = 0;
  delay(500);


  //check that the button is not pressed; if it is, wait for it to be de-pressed and flash

  button.loop(); // MUST call the loop() function first
  int buttonState = button.getState();

  while (buttonState == 0)

  {
    button.loop(); // MUST call the loop() function first
    buttonState = button.getState();
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(50);

  }

  digitalWrite(ledPin, LOW);
  while (buttonState == 1)

  {
    button.loop(); // MUST call the loop() function first
    buttonState = button.getState();

  }


  for ( i = 0; i < 3; i = i + 1) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(200);
  }


  delay(1000);

  button.setCountMode(COUNT_FALLING);

}

int desiredstepangle;
int previous_sample = 0;
int current_sample = 0;
int trialcount = -1;


void loop() {


  if (trialcount < n_trials) {
    myStepper.setSpeed(800);//empty max 1100


    desiredstepangle = stepsperdivision * randomized_trials[trialcount];

    // Serial.print(currentstepangle);
    // Serial.print(desiredstepangle);
    //  Serial.println(desiredstepangle - currentstepangle);

    myStepper.step(desiredstepangle - currentstepangle);



    //indicate the touch time
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);

    delay(2000);

    /*if (abs(desiredstepangle-currentstepangle)<abs(stepsPerOutRev-(desiredstepangle-currentstepangle)))
       {
       Serial.println("clockwise");
       myStepper.step(desiredstepangle-currentstepangle);

       }else{
       Serial.println("counter-clockwise");
        myStepper.step(stepsPerOutRev-(desiredstepangle-currentstepangle));
       }*/

    // turn on led


    //start flashing to wait press and release button to go to next trial
    //   buttonState = digitalRead(pushButton);
    //  while (buttonState == 0)
    button.loop(); // MUST call the loop() function first

    button.loop(); // MUST call the loop() function first
    int buttonState = button.getState();

    while (buttonState == 0)

    {
      button.loop(); // MUST call the loop() function first
      buttonState = button.getState();
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
    digitalWrite(ledPin, LOW);

    while (buttonState == 1)

    {
      button.loop(); // MUST call the loop() function first
      buttonState = button.getState();

    }
    /*  delay(500);
        while (buttonState == 0)
          buttonState = digitalRead(pushButton);
        delay(100);
    */

    delay(100);
    trialcount = trialcount + 1;
    currentstepangle = desiredstepangle;

  }


  //
  // Serial.println(buttonState);
  //  // step one revolution in the other direction:
  //  Serial.println("counterclockwise");
  //  myStepper.step(-stepsRequired);
  //  delay(500);



}