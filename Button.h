class Button {
  public:
    bool comb[5];

    Button() {}

    // Set the Button pin.
    Button(int _pin) {
      pin = _pin;
      pinMode(pin, INPUT_PULLUP);
    }

    // Connect the Button to a combination of LEDs.
    void mapButton(int _lights, bool _comb[]) {
      memcpy(comb, _comb, _lights);
    }

    // Check if the Button is pressed or not. Functionality has been added to turn it into a switch rather than a turbo button.
    bool pressed() {
      int reading = !digitalRead(pin);

      if (reading == HIGH && lastState == LOW && millis() - t > debounce) {
        state = (state == HIGH) ? LOW : HIGH;
        lastState = reading;
        t = millis();
        return true;
      }

      lastState = reading;
      return false;
    }
    
  private:
    int pin;
    int state = HIGH;
    int lastState = LOW;
    unsigned long t = 0;
    unsigned long debounce = 200;
};
