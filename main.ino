#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ PB1, /* data=*/PB0, /* cs=*/ 5, /* dc=*/ 6, /* reset=*/ 7);
int PA3state, PA4state = 0;
int people = 0, comedata = 0, xs = 0;
int timedelay = 0;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  u8g2.begin();

  pinMode(PA3, INPUT);
  pinMode(PA4, INPUT);
  pinMode(PC13, OUTPUT);

}

void loop()
{
  PA3state = digitalRead(PA3);
  PA4state = digitalRead(PA4);

//  timedelay++;
//  if (timedelay >= 5000000)
//  {
//    timedelay = 0;
//    u8g2.clearBuffer();
//    u8g2.sendBuffer();
//  }

//  if (Serial2.available() > 0)
//  {
//    comedata = Serial2.parseInt();
//    xs = people + comedata;
//    Serial.print("count=");
//    Serial.println(xs);
//    showSerial(xs);
//  }

  while (PA3state == LOW && PA4state == LOW)
  {
    PA3state = digitalRead(PA3);
    PA4state = digitalRead(PA4);
    timedelay == 0;

    if (PA3state == HIGH && PA4state == LOW)
    {
      people++;
      // xs = people + comedata;
      //Serial.println(people);
      showSerial(xs);
      delay(300);
    }

    else if (PA3state == LOW && PA4state == HIGH)
    {
      people--;
      showSerial(xs);
      delay(300);
    }
  }
}



void showSerial(int xs) {
  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_wqy12_t_chinese3); // choose a suitable font
  u8g2.drawStr(30, 10, "T C O P S");
  u8g2.drawStr(10, 25, "Count of People :");
  u8g2.setCursor(105, 25);
  u8g2.setFont(u8g2_font_wqy14_t_chinese3);
  u8g2.print(xs);
  u8g2.sendBuffer();          // transfer internal memory to the display
}
