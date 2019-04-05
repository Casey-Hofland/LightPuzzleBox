class Puzzle {
  public:
    bool combs[5][5];
  
    Puzzle() {}

    void generate(int _lights) {
      clearCombs();

      lights = _lights;
      lights = max(lights, 0);
      lights = min(lights, 5);
      int l = lights;

      int count = round(pow(2, l)) - 1;
      bool matrix[count][l];
      
      for (int i = 0; i < count; i++) {
        bool comb[l];

        String string = String(i + 1,2);        
        int len = l - string.length();
        for (int c = 0; c < len; c++) comb[c] = false;
        for (int c = len; c < l; c++) comb[c] = string[c - len] == '1';

        memcpy(matrix[i], comb, l);
      }
      
      for (int i = 0; i < l; i++) {
        randomSeed(millis());
        int r = random(count);
        int x = random(7);
        if (r >= 7) r -= x;
        if (r == count - 1) {
          bool minus = true;
          for (int b = 0; b < l; b++) {
            if (!matrix[r][b]) minus = false;
          }
          if (minus) r--;
        }
        memcpy(combs[i], matrix[r], l);

        int count2 = round(pow(2, i));
        bool distCombs[count2][l];
        for (int i2 = 0; i2 < count2; i2++) {
          bool comb[l];
          memcpy(comb, combs[i], l);
          
          String string = String(i2,2);
          String reverse = string;
          for (int c = 0; c < reverse.length(); c++) string[c] = reverse[reverse.length() - 1 - c];
          for (int c = 0; c < string.length(); c++) {
            if (string[c] == '1') {
              for (int c2 = 0; c2 < l; c2++) {
                comb[c2] = comb[c2] != combs[c][c2];
              }
            }
          }

          memcpy(distCombs[i2], comb, l);
        }

        for (int i2 = count - 1; i2 >= 0; i2--) {
          for (int dis = 0; dis < count2; dis++) {
            bool match = true;
            for (int b = 0; b < l; b++) {
              if (matrix[i2][b] != distCombs[dis][b]) {
                match = false;
                break;
              }
            }
            if (match) {
              for (int i3 = i2; i3 < count; i3++) {
                memcpy(matrix[i3], matrix[i3+1], l);
              }
              count--;
            }
          }
        }
      }

      delay(7);
    }

    void clearCombs() {
      for (int i = 0; i < 5; i++) {
        for (int i2 = 0; i2 < 5; i2++) {
          combs[i][i2] = false;
        }
      }
    }

    void printCombs() {
      for (int i = 0; i < lights; i++) {
        for (int c = 0; c < lights; c++) {
          Serial.print(combs[i][c] ? 1 : 0);
        }
        Serial.println();
      }
      Serial.println();
    }
  
  private:
    int lights;
};
