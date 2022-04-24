
#include "DFRobot_RGBLCD1602.h"
#include <Pixy2.h>

// Signature1 = Blue
// Signature2 = Yellow
// Signature3 = Green
// Signature4 = Red

// This is the main Pixy object 
Pixy2 pixy;

const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show

int red_count = 0;
int green_count = 0;
int blue_count = 0;
int yellow_count = 0;

int current_index = -1;
int sig = 0;

void setup() {
  
    Serial.begin(115200);
    Serial.print("Starting...\n");
  
    pixy.init();
    /**
     *  @brief initialize the LCD and master IIC
     */ 
    lcd.init();
    
    lcd.setRGB(colorR, colorG, colorB);

    displayLCD();
   
    delay(1000);
}

void loop() {
   int i; 
  // grab blocks!
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();

      if( current_index != pixy.ccc.blocks[i].m_index ){
          current_index = pixy.ccc.blocks[i].m_index;
          switch( pixy.ccc.blocks[i].m_signature){
             case 1:blue_count++;   break;
             case 2:yellow_count++; break;
             case 3:green_count++;  break;
             case 4:red_count++;    break;
          }
          
          updateDisplay(); 
       }
      
    }
  }  
}
void displayLCD()
{
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Red:");

    lcd.setCursor(4, 0);
    lcd.print(red_count);

    lcd.setCursor(9, 0);
    lcd.print("G:");

    lcd.setCursor(11, 0);
    lcd.print(green_count);

    lcd.setCursor(0, 1);
    lcd.print("Blue:");

    lcd.setCursor(5, 1);
    lcd.print(blue_count);


    lcd.setCursor(9, 1);
    lcd.print("Y:");

    lcd.setCursor(11, 1);
    lcd.print(yellow_count);

 
}
void updateDisplay()
{
   lcd.clear();
   displayLCD();
}
