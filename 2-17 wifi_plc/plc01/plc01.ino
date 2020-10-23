// 참조 소스프로그램 2-0-1-1 https://youtu.be/ERWf64Vv3Ug 
// 회로도 및 보드 구매 : 통신보드 구매사이트 : https://smartstore.naver.com/i2r/products/4584482642
#include <arduino-timer.h>

auto timer = timer_create_default(); // create a timer with default settings
String inputString = "";         // 받은 문자열
String s;  // 보내는 문자열
int count;

bool toggle_led(void *) {
  count++;
  int i=count%16;
  String s1=s;
  s1 += String(i,HEX);
  s1 +=char(4);
  Serial.println(" ");
  Serial.println(s1); 
  Serial1.print(s1);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
  return true; // repeat? true
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // set LED pin to OUTPUT
  // call the toggle_led function every 1000 millis (1 second)
  timer.every(1000, toggle_led);
  
  Serial.begin(19200);
  Serial1.begin(19200);

  // 보내는 문자열 작성
   s = "\0";
   s +=char(5);
   s += "00WSS0104%PW4000";
}

void loop() {
  timer.tick(); // tick the timer
  serialEvent();
}

void serialEvent() {
  if(Serial.available() == false)
    return;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Serial.print(inChar);
  }
}
