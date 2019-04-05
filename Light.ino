#include "Button.h" // Custom Button Class - Generates the Button functionality.
#include "Puzzle.h" // Custom Puzzle Class - Generates the Puzzles.

// Base Components
Puzzle puzzle;
int leds[5];
Button buttons[6];

// Dynamic Variables
bool comb[5];
bool check = true;
int lights = 5;

void setup() {
  // Sets the Serial port.
  Serial.begin(9600);

  // Connect all the LEDs and Buttons to their respective pins.
  leds[0] = 2;
  leds[1] = 3;
  leds[2] = 4;
  leds[3] = A2;
  leds[4] = A3;

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  buttons[0] = Button(13);
  buttons[1] = Button(12);
  buttons[2] = Button(11);
  buttons[3] = Button(8);
  buttons[4] = Button(10);
  buttons[5] = Button(A0);

  // Generate a puzzle.
  generatePuzzle(5);
}


void loop() {
  checkButtons();
}


// Check every Button if it is being pressed this 'frame' or not.
void checkButtons() {
  if (!check) return;

  for (int b = 0; b < lights; b++) {
    Button button = buttons[b];
    if (button.pressed()) {
      // If a Button is pressed, toggle the LEDs it's wired to respectively.      
      for (int i = 0; i < lights; i++) {
        bool newComb = comb[i] != button.comb[i];
        if (comb[i] != newComb) {
          comb[i] = newComb;
          int input = newComb ? HIGH : LOW;
          digitalWrite(leds[i], input);
        }
      }
    }
  }

  // Check if the puzzle is completed or not (are all the LEDs turned ON?)
  bool completed = true;
  for (int i = 0; i < lights; i++) {
    if (!comb[i]) {
      completed = false;
      break;
    }
  }

  // If the puzzle is completed or the Reset Button is pressed, generate a new puzzle.
  if (completed) victory();
  else if (buttons[5].pressed()) generatePuzzle(5);
}

// Keep the lights on for a second before reseting the puzzle.
void victory() {
  check = false;
  delay(1000);
  generatePuzzle(lights);
}

// Generate a new puzzle and flicker the LEDs to show when the puzzle is done generating.
void generatePuzzle(int _lights) {
  check = false;

  // Reset the LEDs.
  for (int i = 0; i < lights; i++) {
    comb[i] = false;
    digitalWrite(leds[i], LOW);
  }
  delay(500);
  
  lights = _lights;
  
  for (int i = 0; i < lights; i++) digitalWrite(leds[i], HIGH);
  delay(500);

  // Generate a new puzzle.
  puzzle.generate(lights);
  for (int i = 0; i < lights; i++) {
    buttons[i].mapButton(lights, puzzle.combs[i]);
  }

  // Flicker the LEDs.
  for (int i = 0; i < lights; i++) digitalWrite(leds[i], LOW);
  delay(100);
  for (int i = 0; i < lights; i++) digitalWrite(leds[i], HIGH);
  delay(100);
  for (int i = 0; i < lights; i++) digitalWrite(leds[i], LOW);
  delay(100);
  for (int i = 0; i < lights; i++) digitalWrite(leds[i], HIGH);
  delay(100);
  for (int i = 0; i < lights; i++) digitalWrite(leds[i], LOW);
  
  check = true;
}
