//Working test
#include <Keypad.h>
#include <Keyboard.h>

int level = 0;

const byte ROWS = 4; //The keeboard has four rows
const byte COLS = 4; //The keeboard has four columns

//Matrix keyboard arrangement
char matrixKeeb[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //Respective pinout for the rows
byte colPins[COLS] = {5, 4, 3, 2}; //Respective pinout for the columns

//Initializa a new Keypad class
Keypad keypad = Keypad(makeKeymap(matrixKeeb), rowPins, colPins, ROWS, COLS);

void setup() {
  
  Serial.begin(9600);
  Keyboard.begin(); //Starts HID device

}

void debounce(int d){
      
  delay(d);
  Keyboard.releaseAll(); //Releases keys
    
}

void csMacro(uint8_t key){
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
  
}

void cMacro(uint8_t key){
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(key);
  
}

void sKey(uint8_t key){
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
}


void windowsRun(int d, String command){

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.release(KEY_LEFT_GUI);
  Keyboard.release('r');
  delay(d);
  Keyboard.print(command);
  Keyboard.releaseAll();
  delay(10);
  Keyboard.press(KEY_RETURN);
  debounce(100);
  
}

void loop() {

  char key = keypad.getKey();

  if (key){
    Serial.println(key);
    Keyboard.releaseAll();
    if (key == '*'){
      level++;
      if (level > 3){
        level = 3;
      }
    }

    else if (key == '#'){
      level--;
      if (level < 0){
        level = 0;
      }
    } 

    if (level == 0){
      switch(key){
        case '1':
          csMacro(KEY_F2);
          debounce(100);
          break;
        case '2':
          csMacro('d');
          debounce(100);
          break;
        case '0':
          windowsRun(20, "cmd");
          break;
        case 'D':
          windowsRun(20, "%temp%");
          debounce(100);
          break;
         case 'A':
          windowsRun(40,"https>&&u.gg&");
          break;
        }
    }

    else if (level == 1){
      switch(key){
        case '1':
          csMacro(KEY_F1);
          debounce(100);
          break;
        case '2':
          csMacro('g');
          debounce(100);
          break;
      }
    }
    else if (level == 2){
      switch(key){
        case '1':
          csMacro('t');
          debounce(100);
          break;
        case '2':
          cMacro('t');
          debounce(100);
          break;
        case '3':
          csMacro('p');
          debounce(100);
          break;
      }
    }
    else if (level == 3){
      switch(key){
        case '1':
          Keyboard.write('>');
          Keyboard.print("ddpVirolo");
          Keyboard.write('>');
          debounce(100);
          break;
        case '2':
          Keyboard.write('>');
          Keyboard.print("ddpSexy");
          Keyboard.write('>');
          debounce(100);cmd
          break;
      }
    }
  }
}
