// 회로도 및 보드 구매 : 통신보드 구매사이트 : https://smartstore.naver.com/i2r/products/4584482642
// plc에서 html 작성 참조 : https://youtu.be/Ule_wKCxJZc
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <arduino-timer.h>
auto timer = timer_create_default(); // create a timer with default settings

String sChipId="";
char cChipId[40]="";
ESP8266WebServer server(80);

String inputString = "";         // 받은 문자열
String s;
//int LED = LED_BUILTIN;// 사용하지 마세요 serial1 통신과 충돌합니다.
int p4[8]={0},p0[10]={0},monit=0;


bool toggle_led(void *) {
  if(monit==1) {
    s = "\0";
    s +=char(5);
    s += "00RSS0104%PW0";
    s +=char(4);
    Serial.println(" ");
    Serial.println(s); 
    Serial1.print(s);
  }
  return true; 
}

void setup() {
  // call the toggle_led function every 1000 millis (1 second)
  timer.every(5000, toggle_led);
  
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial1.begin(19200);
  
  //pinMode(LED, OUTPUT);

  // AP 이름 자동으로 만듬 i2r-chipid
  sChipId = "i2r-"+String(ESP.getChipId(),HEX);
  sChipId.toCharArray(cChipId,sChipId.length()+1);
  Serial.println(sChipId);

  //WiFiManager
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;
  // wm.resetSettings(); //reset settings - for testing

  if (!wm.autoConnect(cChipId)) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected... :)");

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/monit", handleMonit);
  server.on("/scan", handleScan);
  server.on("/wifi", handleWifi);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  DisplayPlc("00");
}

void DisplayPlc(String s) {
  if(s.length()<=0)
    return;
  int i,j;
  j=0;
  for(i=0;i<8;i++) //초기화
    p0[i]=0;
  for(i=s.length()-1;i>=0;i--)
    p0[j++]=s.charAt(i)-0x30;
  for(i=0;i<s.length();i++)
    Serial.println(p0[i]);  
  GoHome();
}

// string hex를 string bin으로 전환
String HexToBin(String sIn) {
  //hex 문자를 비트문자로
  String s;
  char arr[50]="";
  sIn.toCharArray(arr,sIn.length()+1);
  s=strtol(arr, NULL, 16); //hex문자열을 dec문자열로
  s=String(s.toInt(), BIN); //dec문자열을 bin문자열로
  return s;
}


void loop() {
  timer.tick(); // tick the timer
  server.handleClient();
  serialEvent();
}

void serialEvent() {
  if(Serial.available() == false)
    return;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.print(inChar);
    // add it to the inputString:
    if(inChar==0x06)
      inputString="";
    inputString += inChar;
    if(inChar==0x03) {
      Serial.println(inputString);
      s="";
      s=inputString.substring(12, 14);
      Serial.println(s);
      s=HexToBin(s);
      Serial.println(s);
      DisplayPlc(s);
    }
  }
}
