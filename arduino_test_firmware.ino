/*===========================================================================================================
      arduino_test_firmware

      This code is for testing and developing different functions for a 16 keys (4x4 matrix) keyboard.
      The intention of this is to have a macro keyboard powered by a Pro Micro development board and
      programed using Arduino, to make key combinations and other macro type features with the press
      of a single button.
      
      As for the components, currently a 4x4 generic matrix keyboard is being used, it only has 8 pins,
      4 being used as inputs and 4 as outputs. But any matrix configuration will work if the Matrix
      keyboard arrangement section is coded properly, regardless of the diode protection in each key,
      one thing to consider when coding the matrix is the diode orientation.

      In this case a generic pro micro is the board of choice, hence the GPIO used are the pins from 2 to 9,
      since the Arduino Keypad library is used for this sketch, pins from 2-5 are used as inputs and 6-9 are
      used as output, this is because this library lets current pass from row to column, and those are the
      pinouts configured in this sketch to be used as rows and columns, respectively. If you are using a
      simple matrix keyboard that has normally open switches you do not need to worry about the current
      direction, if you wire the keyboard differently just be sure to adjust the code accordingly. In case
      you have a diode protected matrix keyboard you will need to pay attention to the rows and columns
      configuration, although this protection is not needed since this library sets the unused pins to a
      high impedance, therefore protecting itself, adding diodes to your switches is just a safety
      redundancy.

      Created 28 Jun 2021
      By: Miguel Carreón
      Modified 2 Jul 2021
      By:  Miguel Carreón

      https://github.com/Miguel-Carreon/arduinoKeeb_firmware_test
===========================================================================================================*/
#include <Keypad.h>
#include <Keyboard.h>

//  Global variables declaration  //
char holdKey; //Sores a key that is being holded
unsigned long holdTime; //Stores time to compare it to current time in order to know if a key is being holded
int level = 0; //Indicates the current keyboard level

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

// Initialize a new Keypad class //
Keypad keypad = Keypad(makeKeymap(matrixKeeb), rowPins, colPins, ROWS, COLS);

void setup() {
  
  Serial.begin(9600); //Baud rate to 9600
  Keyboard.begin(); //Starts keyboard HID device

}

// Funtion to ignore mechanical bouncing  //
void debounce(int d){
      
  delay(d); //The argument in the debounce funtion declares the duration of the delay
  Keyboard.releaseAll(); //Releases keys
    
}

// Function to pres CTRL + SHIFT + ANYKEY //
void csMacro(uint8_t key){
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
  
}

// Funtion to press CTRL + ANYKEY //
void cMacro(uint8_t key){
  
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(key);
  
}

// Funtion to press CTRL + ANYKEY //
void sKey(uint8_t key){
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
}

// Funtion to use windows run (WINDOWS_KEY + R) //
void windowsRun(int d, String command){

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.release(KEY_LEFT_GUI);
  Keyboard.release('r');
  delay(d); //This delay is controlled by the first statement of this function argument
  //The ammount of tyme may vary on the system, the faster your computer the less time you should be able put
  Keyboard.print(command); //The seccond statement of this function's argument is what is printed, it should be a string inside double quotes e.g. "arduino.cc"
  Keyboard.releaseAll();
  delay(10);
  Keyboard.press(KEY_RETURN);
  debounce(100);
  
}

// Function to write Discord emojis //
void discordEmoji(String Emoji){
  Keyboard.print('>'); //The > character is what makes a colon to be printed in an Spanish (México) ANSI keyboard.
  Keyboard.print(Emoji); //The name of the emoji shall be written inside double quotes in the argument of this function e.g. "smile"
  Keyboard.print('>'); // If your keyboard language is English change both > for :
  debounce(100);
}

void loop() {

  char key = keypad.getKey(); //Stores the key pressed
  
  // Key single press //
  if (key){
    holdKey = key; //Stores the key pressed for the hold key section
    Serial.println(key);
    Keyboard.releaseAll(); //Each iteration release all keys
    
    /*Layer system, each time * is pressed in the matrix keyboard a new layer of keys is selected,
    this is usefull to virtually have more keys with the same ammount of physical keys.
    Each time * is pressed you go to the next layer, you start at layer 0, when you reach level 2 
    you start over at 0.*/
    if (key == '*'){
      level++;
      if (level > 2){ //Change this number to the ammount of layers desired
        level = 0;
      }
    } 

    //Level zero
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
        case '3':

          break;
        case 'A':
          windowsRun(40,"https>&&u.gg&");
          break;
        case '4':

           break;
        case '5':

           break;
        case '6':

           break;
        case 'B':

           break;
        case '7':

           break;
        case '8':

           break;
        case '9':

           break;
        case 'C':
          cMacro('a');
          debounce(100);
          break;
        case '0':
          windowsRun(40, "cmd");
          break;
        case '#':

           break;
        case 'D':
          windowsRun(40, "%temp%");
          debounce(100);
          break;
        }
    }

    //Level one
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
        case '5':

          break;
        case '6':

          break;
        case 'B':

          break;
        case '7':

          break;
        case '8':

          break;
        case '9':

          break;
        case 'C':

          break;
        case '0':

          break;
        case '#':

          break;
        case 'D':

          break;
      }
    }
    
    //Level two
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
        case '#':
          discordEmoji("ddpDanito");
          break;
        case 'D':
          discordEmoji("ddpMex");
          break;
      }
    }
  }

  // Key hold //
  if (keypad.getState() == HOLD){
    if ((millis() - holdTime) > 100){
      //Available space for key commands
      
      //Level zero
      if (level == 0){
        switch (holdKey){
          //Commands for level zero while holding
        }
      }
      
      //Level one
      else if (level == 1){
        switch (holdKey){
          //Commands for level one while holding
        }
      }
      
      //Level two
      else if (level == 2){
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

/* Levels for the sigle key press and key hold are the same, just put the command in the corresponding
   desired function*/
