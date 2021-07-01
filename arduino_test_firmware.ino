#include <Keypad.h>
#include <Keyboard.h>

char holdKey;
unsigned long holdTime;
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

void discordEmoji(String Emoji){
  Keyboard.print('>');
  Keyboard.print(Emoji);
  Keyboard.print('>');
  debounce(100);
}

void loop() {

  char key = keypad.getKey();

  if (key){
    holdKey = key;
    Serial.println(key);
    Keyboard.releaseAll();
    if (key == '*'){
      level++;
      if (level > 2){
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
          windowsRun(40, "cmd");
          break;
        case 'D':
          windowsRun(40, "%temp%");
          debounce(100);
          break;
        case 'C':
          cMacro('a');
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
        case '3':
          csMacro('t');
          debounce(100);
          break;
        case 'A':
          cMacro('t');
          debounce(100);
          break;
        case '4':
          csMacro('p');
          debounce(100);
          break;
      }
    }
    else if (level == 2){
      switch(key){
        case '1':
          discordEmoji("ddpVirolo");
          break;
        case '2':
          discordEmoji("ddpSexy");
          break;
        case '3':
          discordEmoji("ddpVirus");
          break;
        case 'A':
          discordEmoji("ddpdios");
          break;
        case '4':
          discordEmoji("ddpAlien");
          break;
        case '5':
          discordEmoji("ddpPelon");
          break;
        case '6':
          discordEmoji("papaBless");
          break;
        case 'B':
          discordEmoji("ddpDozal");
          break;
        case '7':
          discordEmoji("ddpFeto");
          break;
        case '8':
          discordEmoji("ddpFeto2");
          break;
        case '9':
          discordEmoji("ddpSemamaron");
          break;
        case 'C':
          discordEmoji("ddpBlanco3");
          break;
        case '0':
          discordEmoji("ddpBlanco2");
          break;
        case 'D':
          discordEmoji("ddpMex");
          break;
      }
    }
  }

  if (keypad.getState() == HOLD){
    if ((millis() - holdTime) > 100){
      //Available space for key commands
      if (level == 2){
        switch (holdKey){
          case '1':
            discordEmoji("ddpVirolo");
            break;
        }
      }
      holdTime = millis();
    }
  }
}
