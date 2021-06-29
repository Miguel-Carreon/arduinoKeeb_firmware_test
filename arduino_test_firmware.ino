//Stable Version

#include <Keypad.h>
#include <Keyboard.h>

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

void csMacro(uint8_t key){
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
  
}

void cMacro(uint8_t key){
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(key);
  
}

void loop() {

  char key = keypad.getKey();

  if (key){
    Serial.println(key);
    switch(key){
      //CTRL+SHIFT+KEY
      case '1':
        csMacro(KEY_F2);
        break;
      case '2':
        csMacro('d');
        break;
      case '3':
        csMacro(KEY_F1);
        break;
      case 'A':
        csMacro('g');
        break;
      case '4':
        csMacro('t');
        break;
      case '5':
        csMacro('p');
        break;
    //CTRL+KEY
      case '6':
        cMacro(KEY_TAB);
        break;
      case 'B':
        cMacro('s');
        break;
      case '7':
        cMacro('x');
        break;
      case '8':
        cMacro('c');
        break;
      case '9':
        cMacro('v');
        break;
      case 'C':
        cMacro('y');
        break;
      case '*':
        cMacro('z');
        break;
      case '0':
        cMacro('1');
        break;
      case '#':
        cMacro('7');
        break;
      case 'D':
        cMacro('8');
        break;
    }

    delay(100);
    Keyboard.releaseAll(); //Releases keys
  }

}
