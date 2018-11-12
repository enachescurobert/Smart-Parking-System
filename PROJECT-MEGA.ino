//Display config
#include "LiquidCrystal.h"
// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(52,53,48,49,50,51); //8,9,4,5,6,7

//Servo
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 20;    // variable to store the servo position

/*4x4 Matrix Keypad connected to Arduino
This code prints the key pressed on the keypad to the serial port*/
#include <Keypad.h>
#define Password_Lenght 7 // Give enough room for six chars + NULL char
char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad
//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {29,28,27,26}; //Rows 0 to 3
byte colPins[numCols]= {25,24,23,22}; //Columns 0 to 3
//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

// IR Obstacle Collision Detection Module
int LED = 46; // Use the onboard Uno LED
int isObstaclePin = 45; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE


void setup() {

lcd.begin(16,2);
myservo.attach(47);// attaches the servo on pin 47 to the servo object
    pinMode(LED, OUTPUT);
    pinMode(isObstaclePin, INPUT);
    Serial.begin(9600);   
}



void loop()
{



  myservo.write(pos);
  lcd.setCursor(0,0);
  lcd.print("Parola:");

  customKey = myKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count,1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Parola este ");

    if(!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
      {
        lcd.print("Buna");
        for (pos = 20; pos <= 145; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(30);                       // waits 15ms for the servo to reach the position
      }
      delay(5000);
      for (pos = 145; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
         lcd.clear();
          lcd.print("Cade bariera, ");
        lcd.setCursor(0,1);
        lcd.print("nu intrati!");
        delay(100);
          }}
        else
      lcd.print("Gresita");

    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
    lcd.clear();
    clearData();   
  }

    isObstacle = digitalRead(isObstaclePin);
    if (isObstacle == LOW) {
        Serial.println("P2 ocupat!");
        digitalWrite(LED, LOW);
    } else {
        Serial.println("P2 liber");
        digitalWrite(LED, HIGH);
    }
    delay(200);



}

void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size, 
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
