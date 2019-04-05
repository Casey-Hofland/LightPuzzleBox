#include "Button.h"
#include "Puzzle.h"

Puzzle puzzle;
bool comb[5];
int leds[5];
Button buttons[6];

bool check = true;
int lights = 5;

void setup() {
  Serial.begin(9600);

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

  generatePuzzle(5);
}


void loop() {
  checkButtons();
}


void checkButtons() {
  if (!check) return;

  for (int b = 0; b < lights; b++) {
    Button button = buttons[b];
    if (button.pressed()) {
      Serial.print(b);
      
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

  bool completed = true;
  for (int i = 0; i < lights; i++) {
    if (!comb[i]) {
      completed = false;
      break;
    }
  }
  if (completed) victory();
  else if (buttons[5].pressed()) {
    Serial.println("Reset");
    generatePuzzle(5);
  }
}

void victory() {
  check = false;
  delay(1000);
  generatePuzzle(lights);
}

void generatePuzzle(int _lights) {
  check = false;
  
  for (int i = 0; i < lights; i++) {
    comb[i] = false;
    digitalWrite(leds[i], LOW);
  }
  delay(500);
  
  lights = _lights;

  for (int i = 0; i < lights; i++) digitalWrite(leds[i], HIGH);
  delay(500);

  puzzle.generate(lights);
  for (int i = 0; i < lights; i++) {
    buttons[i].mapButton(lights, puzzle.combs[i]);
  }
  puzzle.printCombs();

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
