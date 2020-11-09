#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <arduino-timer.h>
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
int p4[8]={0},p0[10]={0},monit=0;

// 사용하는 AP에 따라 수정
//String s1="http://172.30.1.";
String s1="http://192.168.0.";
char msg[100];
int i=0;
const int ledPin =  LED_BUILTIN;// the number of the LED pin

bool toggle_led(void *) {
  if(monit==1) {
    wifiScanOne(ipNo);
    count++;
    if(count>1) //출력 에러체크
      errorPlc=1;
  }
  return true; 
}

void setup() {
  pinMode(ledPin, OUTPUT);
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(19200);
  WiFiManager wm;
  // 사용하는 AP에 따라 수정
  wm.setSTAStaticIPConfig(IPAddress(192,168,0,200), IPAddress(192,168,0,1), IPAddress(255,255,255,0));  // set static ip,gw,sn
  //wm.setSTAStaticIPConfig(IPAddress(172,30,1,200), IPAddress(172,30,1,254), IPAddress(255,255,255,0));  // set static ip,gw,sn
 
  // AP 이름 자동으로 만듬 i2r-chipid
  sChipId = "i2r-"+String(ESP.getChipId(),HEX);
  sChipId.toCharArray(cChipId,sChipId.length()+1);
  Serial.println(sChipId);

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
  server.on("/monit", handleMonit);
  server.on("/menu", handleMenu);
  server.on("/scan", handleScan);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
  wifiScan();
  Serial.println("Finish Scan");
  
  // call the toggle_led function every 1000 millis (1 second)
  timer.every(5000, toggle_led);
}

void loop() {
  timer.tick(); // tick the timer
  server.handleClient();
}

void wifiScanOne(int ipScan) {
  WiFiClient client;
  HTTPClient http;
  int httpCode=0;
  String payload="";
  String s="";
  http.setTimeout(1000);       // http 응답 대기시간 설정
  
    s=s1+String(ipScan)+"/scan"; 
    Serial.println(s);
    if ((WiFi.status() == WL_CONNECTED)) {
      Serial.print("[HTTP] begin...\n");
      //s="http://117.16.176.76";
      if (http.begin(client, s)) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        httpCode = http.GET();
        
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
          // file found at server
          //if (httpCode == 200 ) {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            //Serial.println("OK");
            payload = http.getString();
            Serial.println(payload);
            setValue(payload);
            actIp[countScaned++]=ipScan;
            count=0;
            errorPlc=0;
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
      } else {
        Serial.printf("[HTTP} Unable to connect\n");
      }
    }  
}

void wifiScan() {
  countScaned=0;
  for(int i=38;i<44;i++) {
    digitalWrite(ledPin, i%2);
    wifiScanOne(i);
  }  
  digitalWrite(ledPin, 1);
  Serial.print("countScaned:");
  Serial.println(countScaned);
  makeMenu();
  if(countScaned>0) {
    ipNo=actIp[0];
  }

  for(i=0;i<countScaned;i++) {
    Serial.println(actIp[i]);
  }
}

void setValue(String payload) {
  //Serial.println(payload);
  deserializeJson(doc,payload);
  root = doc.as<JsonObject>();
  String inP0 = root["p0"];
  String inP4 = root["p4"];
  monit = root["monit"];
  DisplayP0(inP0);
  DisplayP4(inP4);
  GoHome();

}

void DisplayP4(String s) {
  if(s.length()<=0)
    return;
  int i,j;
  j=0;
  for(i=0;i<4;i++) //초기화
    p4[i]=0;
  for(i=0;i<s.length();i++) {
    p4[i]=s.charAt(i)-0x30;
  }
}

void DisplayP0(String s) {
  if(s.length()<=0)
    return;
  int i,j;
  j=0;
  for(i=0;i<8;i++) //초기화
    p0[i]=0;
  for(i=0;i<s.length();i++)
    p0[j++]=s.charAt(i)-0x30;
}
