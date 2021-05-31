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
#include <ACROBOTIC_SSD1306.h>
#include <Ticker.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D7, D4); // RX, TX
//SoftwareSerial mySerial(D7, D8); // RX, TX

Ticker ticker;
#define TRIGGER_PIN 0 // trigger pin 0(D3) 2(D4)
WiFiManager wm;

//json을 위한 설정
StaticJsonDocument<200> doc;
DeserializationError error;
JsonObject root;

ESP8266WebServer server(80);

//String sChipId="";
//char cChipId[40]="";
//int count=0,countScaned=0,actIp[255]={0};
//int ipNo; //현재 선택되어 동작중인 IP
char mac[20];  //mac address
String sMac;

String inputString = "";    // 받은 문자열
int sendText=0,errorPlc=0;
int Out[8]={0},In[10]={0};  // plc 입력과 출력 저장 
int monit=0;                //모니터링 on/off
int act=0;

char msg[100];
int i=0;
const int ledPin =  LED_BUILTIN;// the number of the LED pin

void tick()
{
  crd16Rtu();
  act=1;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(19200);
  //Serial1.begin(19200);
  mySerial.begin(19200);

  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  //Oled Setup
  Wire.begin(); 
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setFont(font5x7);
  oled.setTextXY(2,6);              // Set cursor position, start of line 0
  oled.putString(" Set WiFi");
  oled.setTextXY(4,6);              // Set cursor position, start of line 0
  oled.putString(" 192.168.4.1");
 
  //이름 자동으로 생성
  byte hardwareMAC[12];  //WIFI MAC address
  WiFi.macAddress(hardwareMAC);
  sprintf(mac,"%02x%02x%02x%02x%02x%02x",hardwareMAC[5], hardwareMAC[4], hardwareMAC[3], hardwareMAC[2], hardwareMAC[1], hardwareMAC[0]);  
  sMac=mac;

  //wifi manager 참조유튜브  https://youtu.be/mJFd7g4jedw  //https://youtu.be/EzEG_2HcOQo
  //reset settings - wipe credentials for testing
  //wm.resetSettings();

  char i2rMac[30];
  sprintf(i2rMac,"i2r-%02x%02x%02x%02x%02x%02x",hardwareMAC[5], hardwareMAC[4], hardwareMAC[3], hardwareMAC[2], hardwareMAC[1], hardwareMAC[0]);  
  if (!wm.autoConnect(i2rMac)) {
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.print("connected... :");
  Serial.print(WiFi.localIP().toString());

  oled.setTextXY(2,6);              // Set cursor position, start of line 0
  oled.putString(" Connected    ");
  oled.setTextXY(4,6);              // Set cursor position, start of line 0
  oled.putString(WiFi.localIP().toString());

  ticker.attach(5, tick);  //0.1 초도 가능
  //ticker.detach();
  
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  serialEvent();
  if ( digitalRead(TRIGGER_PIN) == LOW ) 
    factoryDefault();
}

// trigger pin 0(D3) 2(D4)
void factoryDefault() {
  Serial.println("Factory Reset");
  //WiFiManager wm;
  //wm.startConfigPortal("");
  wm.resetSettings();
  wm.resetSettings();
  //ESP.reset();
  ESP.restart();
}
void serialEvent() {
  if(mySerial.available() == false)
    return;
  while (mySerial.available()) {
    // get the new byte:
    char inChar = (char)mySerial.read();
    Serial.print(inChar,HEX);
    // add it to the inputString:
    inputString += inChar;
  }
  Serial.println("");
  if(monit==1 && act==1 && inputString.length() >= 6) {
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
  String s;
  int si,sj,len;
  char str[24];

  if(act == 2) {
    //str[24] =  {0x00,0x0f,0x00,0x00,0x00,0x0a,0x02,0xff,0x00,0x00,0x00};  //비트연속출력 len=9
    str[0]=0x00; str[1]=0x0f; str[2]=0x00; str[3]=0x00; str[4]=0x00;
    str[5]=0x0a; str[6]=0x02; str[7]=0xff; str[8]=0x00; str[9]=0x00; str[10]=0x00;
    len=9;
    str[7]=Out[0]+Out[1]*2+Out[2]*4+Out[3]*8+Out[4]*16+Out[5]*32;
  }
  else if(monit==1) {
    //str[24] =  {0x00,0x02,0x00,0x00,0x00,0x08,0x00,0x00}; // 비트 입력영역 읽기 len=6
    str[0]=0x00; str[1]=0x02; str[2]=0x00; str[3]=0x00; str[4]=0x00;
    str[5]=0x08; str[6]=0x00; str[7]=0x00; 
    len=6;
    act=1;
  }
  else
    return;

  inputString = "";
  uint8_t * data = (uint8_t *) &str[0];
  si=crc16(data, len, 0x8005, 0xFFFF, 0x0000, true,  true  );
  sj=si&0xff;
  str[len]=sj;
  sj=si>>8;
  str[len+1]=sj;

  for(int i=0;i<len+2;i++)
    mySerial.print(str[i]);
}
