#include <Servo.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo servox;
Servo servoy;

#define servopinx   9   // digital pin for servo x
#define servopiny   10  // digital servo for pin y

#define servocenterx   90  // center po#define  of x servo
#define servocentery   90  // center po#define  of y  servo

#define screenmaxx   1080 // max screen horizontal 
#define screenmaxy   720    // max screen vertical 

#define servomaxx   180   // max degree servo horizontal (x) can turn
#define servomaxy   180

#define distancex  10 // x servo rotation steps
#define distancey  10  // y servo rotation steps

int valx = 0;
int valy = 0;
int posx = 0;
int posy = 0;
int incx = 20;
int incy = 20;

void setup() {

  // put your setup code here, to run once:
  Serial.begin(2000000);
  lcd.begin(20, 4);

  pinMode(servopinx, OUTPUT);
  pinMode(servopiny, OUTPUT);

  servoy.attach(servopiny);
  servox.attach(servopinx);

  servox.write(servocenterx);
  delay(100);
  servoy.write(servocentery);
  delay(100);

}

void loop() {

  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  {
    String Xcord = Serial.readStringUntil(',');
    String Ycord = Serial.readStringUntil('\0');

    int XC = Xcord.toInt();
    int YC = Ycord.toInt();

    valx = word (XC);
    valy = word(YC);

    //servox.write(posX1);
    //servoy.write(posY1);

    posx = servox.read();
    posy = servoy.read();

    if (valx < (screenmaxx / 2 - incx)) {
      if ( posx >= incx ) posx += distancex;
    }
    else if (valx > screenmaxx / 2 + incx) {
      if (posx <= servomaxx - incx) posx -= distancex;
    }
    if (valy < (screenmaxy / 2 - incy)) {
      if (posy >= 5)posy += distancey;
    }
    else if (valy > (screenmaxy / 2 + incy)) {
      if (posy <= 175)posy -= distancey;
    }
    servox.write(posx);
    servoy.write(posy);

  }
  lcd.setCursor(0, 0);
  lcd.print("Baering :");
  lcd.setCursor(12, 0);
  lcd.print(posx);
  lcd.setCursor(0, 1);
  lcd.print("Elevation :");
  lcd.setCursor(12, 1);
  lcd.print(posy);
  lcd.clear();
}


