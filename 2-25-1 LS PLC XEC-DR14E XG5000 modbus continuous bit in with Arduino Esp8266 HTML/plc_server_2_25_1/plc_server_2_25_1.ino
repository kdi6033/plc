// 다음 메뉴얼 참조하세요.
// LS산전 사용설명서_XGB Cnet_V1.8.pdf 9-14 페이지 비트연속출력으로 프로그램 
// crc16 rtu를 사용하기 위해 다음 라이브러리 설치하세요.
// crc16 modbus
//  https://github.com/RobTillaart/CRC
//  AUTHOR: Rob Tillaart

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <arduino-timer.h>
#include "CRC.h"
auto timer = timer_create_default(); // create a timer with default settings

//json을 위한 설정
StaticJsonDocument<200> doc;
DeserializationError error;
JsonObject root;

ESP8266WebServer server(80);

String sChipId="";
char cChipId[40]="";
int count=0,countScaned=0,actIp[255]={0};
int ipNo; //현재 선택되어 동작중인 IP

String inputString = "";         // 받은 문자열
int sendText=0,errorPlc=0;
int Out[8]={0},In[10]={0},monit=0;

char msg[100];
int i=0;
const int ledPin =  LED_BUILTIN;// the number of the LED pin

bool toggle_led(void *) {
  crd16Rtu();
  return true; 
}

void setup() {
  pinMode(ledPin, OUTPUT);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(19200);
  Serial1.begin(19200);
  WiFiManager wm;
 
  // AP 이름 자동으로 만듬 i2r-chipid
  sChipId = "i2r-"+String(ESP.getChipId(),HEX);
  sChipId.toCharArray(cChipId,sChipId.length()+1);
  Serial.println(sChipId);

  //wifi manager 참조유튜브  https://youtu.be/mJFd7g4jedw  //https://youtu.be/EzEG_2HcOQo
  //reset settings - wipe credentials for testing
  //wm.resetSettings();
  if (!wm.autoConnect(cChipId)) {
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.print("connected... :");
  Serial.print(WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");

  // call the toggle_led function every 1000 millis (1 second)
  timer.every(5000, toggle_led);
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
    Serial.print(inChar,HEX);
    // add it to the inputString:
    inputString += inChar;
  }
  Serial.println("");
  if(inputString.length() >= 6) {
    int b=1;
    for(int i=1;i<=8;i++) {
        int c=inputString.charAt(3)&b;
        if(c!=0)
          c=0x01;
        In[i-1]=c;
        Serial.print(c,HEX);
        Serial.print(" ");
        b*=2;
      }
    inputString="";
    Serial.println("");
  }
}

// 아두이노에서 RS485 출력을 내보낸다.
void crd16Rtu() {
  //char str[24] =  {0x00,0x0f,0x00,0x00,0x00,0x0a,0x02,0xff,0x00,0x00,0x00};  //비트연속출력 len=9
  char str[24] =  {0x00,0x02,0x00,0x00,0x00,0x08,0x00,0x00}; // 비트 입력영역 읽기 len=6
  String s;
  int si,sj,len;

  len=6;
  //str[7]=Out[0]+Out[1]*2+Out[2]*4+Out[3]*8+Out[4]*16+Out[5]*32;
  
  uint8_t * data = (uint8_t *) &str[0];
  si=crc16(data, len, 0x8005, 0xFFFF, 0x0000, true,  true  );
  sj=si&0xff;
  str[len]=sj;
  sj=si>>8;
  str[len+1]=sj;

  for(int i=0;i<len+2;i++)
    Serial1.print(str[i]);
}
