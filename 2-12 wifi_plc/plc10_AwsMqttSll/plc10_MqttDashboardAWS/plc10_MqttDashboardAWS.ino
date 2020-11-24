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
const char *host = "-ats.iot.us-west-2.amazonaws.com";
const char* outTopic = "/plc08/outTopic";
const char* inTopic = "/plc08/inTopic";
const char *thingId = "";          // 사물 이름 (thing ID) 
//const char* clientName = ""; // AP 이름과 같이 
WiFiClient espClient;
//PubSubClient client(espClient);
//json
StaticJsonDocument<300> doc;
DeserializationError error;
JsonObject root;

String inputString = "";         // 받은 문자열
int sendText=0,errorPlc=0,count=0;
//int LED = LED_BUILTIN;// 사용하지 마세요 serial1 통신과 충돌합니다.
int p4[8]={0},p0[10]={0},monit=0;
String sP4="";//보드출력상태를 모니터링한 값

// 사물 인증서 (파일 이름: xxxxxxxxxx-certificate.pem.crt)
const char cert_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAOQ3aNyDDRz1urVllhcEPX7S8wJeMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
2C72J9fylSWjz8TwJb4PVgv77gs9QraTCZWt+Lo3IftgJJHOM0R9Cv8+/BMo/yVu
uhJYX28+7PORM0FHMFESTGYiccyii1Z6Cj2otg59a770RU+GlDJ0t80xM3THavPa
Wa69k6H+F6gGOz9EUMKsGHvR97ZfX3gUHDkV0MsrOx78u7KO6ASTyLHq2caDoA==
-----END CERTIFICATE-----
)EOF";
// 사물 인증서 프라이빗 키 (파일 이름: xxxxxxxxxx-private.pem.key)
const char key_str[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAuxdXlNVbWm+DB185caB9AyXpRmFRYAyI2v3dVTm/bz/5I1Cs
AUyDbCbnHBRslwtTRStt7FcB6sID8sj5d+rLFGDLKB7cmdw9tEcOS4Q1d0HxSugX
tvSthrwTgQfe5Pf22d2WJV+dt3xC+AR3SgpoiU6LVwvZJ5iLj6yn69ysMdtxfQjz
7fAncQKBgQC2I45sOS6xVx1+KOhQ+3QvST4O2hrw3sedA3vlorS7Wg0vajSZFELo
qjKDU8njRc8Lgdx/K71XIlo+CoBoLflxUHvmYpCN1gycyWJMvgKbnApVwttJm30z
zJQkfoMU4uPy/L2JJRyIpLKKxlVAqhYpw0koEMwTI7+cJsFe5BmNEw==
-----END RSA PRIVATE KEY-----

)EOF";
// Amazon Trust Services(ATS) 엔드포인트 CA 인증서 (서버인증 > "RSA 2048비트 키: Amazon Root CA 1" 다운로드)
const char ca_str[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

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

X509List ca(ca_str);
X509List cert(cert_str);
PrivateKey key(key_str);
WiFiClientSecure wifiClient;
PubSubClient client(host, 8883, callback, wifiClient); //set  MQTT port number to 8883 as per //standard

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
    if (client.connect(thingId)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(outTopic, "hello world");
      publishMqtt();
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      wifiClient.getLastSSLError(buf,256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      //delay(5000);
    }
  }
}

/*
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
*/

// Set time via NTP, as required for x.509 validation
void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
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
  //clientName=cChipId;
  thingId=&cChipId[0]; //mqtt 통신에서 사용
  
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
  //client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);
  wifiClient.setTrustAnchors(&ca);
  wifiClient.setClientRSACert(&cert, &key);
  setClock();
  client.setCallback(callback);
  Serial.println("AWS connected");
  Serial.println(WiFi.localIP());
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
