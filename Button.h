class Button {
  public:
    bool comb[5];

    Button() {}

    Button(int _pin) {
      pin = _pin;
      pinMode(pin, INPUT_PULLUP);
    }

    void mapButton(int _lights, bool _comb[]) {
      memcpy(comb, _comb, _lights);
    }

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
    
    bool oldPressed() {
      lastState = state;
      state = !digitalRead(pin);
      return state == HIGH && state != lastState;
    }

    bool pushPressed() {
      return !digitalRead(pin);
    }
    
  private:
    int pin;
    int state = HIGH;
    int lastState = LOW;
    unsigned long t = 0;
    unsigned long debounce = 200;
};
