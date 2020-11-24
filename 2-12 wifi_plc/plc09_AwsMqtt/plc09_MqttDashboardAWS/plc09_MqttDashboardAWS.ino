// 회로도 및 보드 구매 : 통신보드 구매사이트 : https://smartstore.naver.com/i2r/products/4584482642
// plc에서 html 작성 참조 : https://youtu.be/Ule_wKCxJZc
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <arduino-timer.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
auto timer = timer_create_default(); // create a timer with default settings

String sChipId="";
char cChipId[40]="";
ESP8266WebServer server(80);

// mqtt를 위한 설정
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* outTopic = "/plc08/outTopic";
const char* inTopic = "/plc08/inTopic";
const char* clientName = ""; // AP 이름과 같이 
WiFiClient espClient;
PubSubClient client(espClient);
//json
StaticJsonDocument<300> doc;
DeserializationError error;
JsonObject root;

String inputString = "";         // 받은 문자열
int sendText=0,errorPlc=0,count=0;
//int LED = LED_BUILTIN;// 사용하지 마세요 serial1 통신과 충돌합니다.
int p4[8]={0},p0[10]={0},monit=0;
String sP4="";//보드출력상태를 모니터링한 값

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String s;
  deserializeJson(doc,payload);
  root = doc.as<JsonObject>();
  const char* sChipidin = root["chipid"];
  if( sChipId.equals(sChipidin)) {
    monit=root["monit"];
    DisplayP4(HexToBin(root["p4"]));
    sendTextToPlc();
  }
}

void publishMqtt() {
  String s="";
  char msg[100]={0};
  //s="{'chipid':'"+sChipId+"','p0':'"+String(p0[0]+p0[1]*2+p0[2]*4+p0[3]*8, HEX)+String(p0[4]+p0[5]*2, HEX)+"','p4':'"+String(p4[0]+p4[1]*2+p4[2]*4+p4[3]*8, HEX)+"'}";
  s="{\"chipid\":\""+sChipId+"\",\"p0\":\""+String(p0[4]+p0[5]*2, HEX)+String(p0[0]+p0[1]*2+p0[2]*4+p0[3]*8, HEX)+"\",\"p4\":\""+String(p4[0]+p4[1]*2+p4[2]*4+p4[3]*8, HEX)+"\"}";
  s.toCharArray(msg,s.length()+1);
  client.publish(outTopic, msg);
  Serial.println(" ");
  Serial.println(msg); 

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientName)) {
      
      Serial.println("connected");
      publishMqtt();
      // Once connected, publish an announcement...
      //client.publish(outTopic, "Reconnected");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void CheckMqtt() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

bool toggle_led(void *) {
  //Serial.println(count);
  if(monit==1) {
    String s = "\0";
    s +=char(5);
    //s += "00RSS0104%PW0";
    s += "00RSS0204%PW004%PW4";
    s +=char(4);
    Serial.println(" ");
    Serial.println(s); 
    Serial1.print(s);
    count++;
    if(count>1) //출력 에러체크
      errorPlc=1;
    publishMqtt();
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
  clientName=cChipId;
  
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
  Serial.println("connected... ");
  Serial.println(clientName);

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/monit", handleMonit);
  server.on("/scan", handleScan);
  server.on("/wifi", handleWifi);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  DisplayP0("00");

  // mqtt 설정
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
  
  if(WiFi.status() == WL_CONNECTED) {
    CheckMqtt();
  }
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
      errorPlc=0;
      count=0;
      displayPLC(inputString);
    }
  }
}

void displayPLC(String sI) {
  String s="";
  s=sI.substring(3, 6);
  if( s.equals("RSS")) {      
    s=sI.substring(12, 14);
    DisplayP0(HexToBin(s));
    s=sI.substring(19, 20);
    DisplayP4(HexToBin(s));
  }
  GoHome();
}

void DisplayP4(String s) {
  int p4r[4]={0};
  if(s.length()<=0)
    return;
  int i,j;
  j=0;
  for(i=0;i<4;i++) //초기화
    p4r[i]=0;
  sP4="";
  for(i=s.length()-1;i>=0;i--) {
    sP4+=s.charAt(i);
    p4r[j++]=s.charAt(i)-0x30;
  }
  for(i=s.length();i<4;i++)
    sP4+="0";
  for(i=0;i<4;i++)
    p4[i]=p4r[i];
}

void DisplayP0(String s) {
  if(s.length()<=0)
    return;
  int i,j;
  j=0;
  for(i=0;i<8;i++) //초기화
    p0[i]=0;
  for(i=s.length()-1;i>=0;i--)
    p0[j++]=s.charAt(i)-0x30;
}

void sendTextToPlc() {
  String s="";
  int out=p4[0]+p4[1]*2+p4[2]*4+p4[3]*8;
  s = "\0";
  s +=char(5);
  s += "00WSS0104%PW4000";
  s += String(out, HEX);
  s +=char(4);
  Serial.println(" ");
  Serial.println(s); 
  Serial1.print(s);
  sendText=1;
  errorPlc=0;
}
