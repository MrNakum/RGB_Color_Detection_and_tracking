#include <Servo.h>
#include <LiquidCrystal.h>

Servo servox;
Servo servoy;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define  servopinx   9   // digital pin for servo x
#define  servopiny   10  // digital servo for pin y

#define  servocenterx   90  // center po#define  of x servo
#define  servocentery   90  // center po#define  of y  servo

#define  screenmaxx   1080 // max screen horizontal 
#define  screenmaxy   720    // max screen vertical 

int valx = 0;       // store x data from serial port
int valy = 0;
int posx = 0;
int posy = 0;

void setup() {


  // put your setup code here, to run once:
  Serial.begin(57600);
  lcd.begin(16, 4);

  pinMode(servopinx, OUTPUT);
  pinMode(servopiny, OUTPUT);

  servoy.attach(servopiny);
  servox.attach(servopinx);

  servox.write(servocenterx);
  servoy.write(servocentery);


}

void loop() {

  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    String Xcord = Serial.readStringUntil(',');
    String Ycord = Serial.readStringUntil('\0');

    int XC = Xcord.toInt();
    int YC = Ycord.toInt();

    int posX1 = map(XC, 0 , screenmaxx , 180 , 0);
    int posY1 = map(YC, 0 , screenmaxy , 180 , 0);

    servox.write(posX1);
    servoy.write(posY1);

    posx = servox.read();
    posy = servoy.read();


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

