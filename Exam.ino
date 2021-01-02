#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define SCK  18
#define SDA  23
#define RES  17
#define DC  16
#define CS  5

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, CS, DC, RES);

//Setting up the variables and assigning pins
int STARTbutton = 2;
int CLICKbutton = 22;
int led = 21;

//Setting up the variables for the timer
long startTime = 0;
long endTime = 0;
long reactionTime = 0;
long totalTime = 0;


void setup() {
  //Initializing the serial communication
  Serial.begin(115200);

  //Initializing the display
  u8g2.begin();

  //Setting up the buttons and LED
  pinMode(STARTbutton, INPUT);
  pinMode(CLICKbutton, INPUT);
  pinMode(led, OUTPUT);

  //Turns the LED off
  digitalWrite(led, HIGH);

  // Random number generator
  randomSeed(analogRead(0));
}

void loop() {
  u8g2.setFont(u8g2_font_profont11_tr);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.drawStr(5, 32, "Press START to begin"); // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);

  Serial.println("Press START button to begin test");
  Serial.println();

  //Waits for the START button to be pressed
  while (digitalRead(STARTbutton)) {}
  //Waits for the START button to be released
  while (!digitalRead(STARTbutton)) {}

  u8g2.clearBuffer();
  u8g2.drawStr(32, 30, "Get ready!"); // write something to the internal memory
  u8g2.sendBuffer();
  u8g2.clearBuffer();
  delay(1000);
  u8g2.setFont(u8g2_font_inb24_mf);
  u8g2.clearBuffer();
  u8g2.drawStr(55, 40, "3"); // write something to the internal memory
  u8g2.sendBuffer();
  u8g2.clearBuffer();
  delay(1000);
  u8g2.clearBuffer();
  u8g2.drawStr(55, 40, "2"); // write something to the internal memory
  u8g2.sendBuffer();
  u8g2.clearBuffer();
  delay(1000);
  u8g2.clearBuffer();
  u8g2.drawStr(55, 40, "1"); // write something to the internal memory
  u8g2.sendBuffer();
  u8g2.clearBuffer();
  delay(1000);
  u8g2.clearBuffer();
  u8g2.drawStr(35, 40, "GO!"); // write something to the internal memory
  u8g2.sendBuffer();
  u8g2.clearBuffer();
  delay(1000);

  Serial.println("Get ready in");
  Serial.println();
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println();

  //The test starts and runs through 10 recordings
  for (int i = 0; i < 10; i++) { //Going through the loop 10 times
    delay(random(500, 3000)); //A random delay between 0,5-3 sec
    digitalWrite(led, LOW); //Turns the LED on
    startTime = millis(); //Records the start time when LED turns on
    while (digitalRead(CLICKbutton)) {} //Waits for the CLICK button to be pressed
    while (!digitalRead(CLICKbutton)) {} //Waits for the CLICK button to be released
    digitalWrite(led, HIGH); //Turns the LED off
    endTime = millis(); //Records the time from when LED was turned on and then turned off
    reactionTime = endTime - startTime; //Calculates the reaction time
    totalTime += reactionTime; //Calculates the total time between each reaction time
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    delay(1000);

    u8g2.setCursor(40, 32);
    u8g2.setFont(u8g2_font_profont11_tr);
    u8g2.print(i + 1);
    u8g2.print(": ");
    u8g2.print(reactionTime);
    u8g2.println(" ms");
    u8g2.sendBuffer();
  }
  delay(2000);
  //The test is done and the average reaction time is printed out
  //u8g2.setCursor(40,32);
  Serial.println();
  Serial.print("Avg = ");
  Serial.print(totalTime / 10);
  Serial.println(" ms");
  Serial.println();

  u8g2.clearBuffer();
  u8g2.setCursor(32, 32);
  u8g2.println();
  u8g2.print("Avg = ");
  u8g2.print(totalTime / 10);
  u8g2.println(" ms");
  u8g2.println();
  u8g2.sendBuffer();
  delay(5000);
}
