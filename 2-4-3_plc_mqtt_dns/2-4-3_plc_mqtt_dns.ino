#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

MDNSResponder mdns;

/*
 * 공유기 설정에서 i2r_ap_***** 로 되어있는 ap 공유기를 선택한다. 비밀번호는 00000000 이다.
 * 공유기를 입력하기 위해 크롬의 주소창에 "i2r.local"을 입력하여 공유기 설정을 선택한다.
 * 또는 http://i2r.local/wifi  http://192.168.4.1 을 입력해도 된다.
 * 입력 후 i2r.local 의 메인 페이지에 입력한 공유기의 이름과 주소가 정상적으로 출력되면
 * 공유기 주소를 선택해 인테넷이 연결될 서버의 주소를 선택한 후 
 * 설정에서 입력한 공유기를 선택하면 정상적으로 사용 할 수 있다.
 */

 /* AP 설정을 위한 변수 선언 */
const char *softAP_ssid = "i2r_ap_";
const char *softAP_password = "00000000";
String sAP_ssid;
char cAP_ssid[20];
int setAP=1;// 1 이면 ap 설정중 으로 메인 페이지에 주소 표시
 
/* hostname for mDNS. Should work at least on windows. Try http://i2r.local */
const char *myHostname = "i2r";

char ssid[32] = "";
char password[32] = "";

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;
// Web server
ESP8266WebServer server(80);
/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);
/** Should I connect to WLAN asap? */
boolean connect;
/** Last time I tried to connect to WLAN */
unsigned long lastConnectTry = 0;
/** Current WLAN status */
unsigned int status = WL_IDLE_STATUS;

// rs232 통신을 위한 설정
String inputString = "";         // 수신 데이타 저장
boolean stringComplete = false;  // 수신 완료되면 true
String s;  // 보내는 문자열
int count=0,j,serialj=0;
long lastMsg = 0;
int delayTime=4000; // serial 계측시간 mqtt로 메세지 보낸는 시간 (단위 ms)
char msg[100];
float fCO2,fTemp;

// mqtt를 위한 설정
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* outTopic = "/kdi6033/inTopic"; // 사용자가 결정해서 기록
const char* inTopic = "/kdi6033/outTopic"; // 사용자가 결정해서 기록
const char* clientName = ""; // AP 이름과 같이 사용
int outPin=0;  // RS485통신 D3 IO0 tx rx 방향 LOW-받기 HIGH-쓰기모드  
int no=1; //기기번호

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  delay(1000);
  pinMode(outPin, OUTPUT); //maa 485의 통신 방향 제어
  digitalWrite(outPin, LOW);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // AP 이름 자동으로 만듬
  sAP_ssid=String(softAP_ssid)+String(ESP.getChipId(),HEX);
  sAP_ssid.toCharArray(cAP_ssid,sAP_ssid.length());
  softAP_ssid=&cAP_ssid[0];
  clientName=softAP_ssid;
  setupApDns();

  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  server.on("/", handleRoot);
  server.on("/wifi", handleWifi);
  server.on("/wifisave", handleWifiSave);
  server.on("/generate_204", handleRoot);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleRoot);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.onNotFound ( handleNotFound );
  server.begin(); // Web server start
  Serial.println("HTTP server started");
  loadCredentials(); // Load WLAN credentials from network
  connect = strlen(ssid) > 0; // EEPROM에 와이파이 이름 저장 되어 있으면 WLAN 연결
  
  // mqtt 설정
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}
void setupApDns() {
  Serial.println(softAP_ssid);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid, softAP_password);
  delay(500); // Without delay I've seen the IP address blank
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  /* Setup the DNS server redirecting all the domains to the apIP */  
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
}

void connectWifi() {
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin ( ssid, password );
  int connRes = WiFi.waitForConnectResult();
  Serial.print ( "connRes: " );
  Serial.println ( connRes );
}

void callback(char* topic, byte* payload, unsigned int length) {
  // mqtt로 들어온 값을 RS232 통신 TX로 보냄
  digitalWrite(outPin, HIGH);
  delay(50);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  delay(20);
  digitalWrite(outPin, LOW);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientName)) {
      Serial.println("connected");
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
  // 센서 값을 브로커에 보낼 메세지 작성.
  serialEvent();
  client.loop();
}

// 시리얼통신으로 문자가 들어오면 처리한다.
void serialEvent() {
  if (stringComplete) {
    Serial.println(inputString);
    stringComplete = false;
    inputString.toCharArray(msg, inputString.length());
    CheckMsg();
    client.publish(outTopic,msg);  // RS232통신 RX 단자로 들어온 값 mqtt로 송신
    // clear the string:
    inputString = "";
  }
  if(Serial.available()){
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    for(int i=0;i<len;i++) {
      if(int(sbuf[i]) == 6) // PLC 응답은 6번으로 시작해서 3번으로 끝난다.
        inputString = "";
      if(int(sbuf[i]) == 3) 
        stringComplete=true;
     inputString += char(sbuf[i]);
    }
  }
}

int HexToInt(char hex) {
  if( hex <= '9')
    return hex - '0';
  else if (hex <= 'F')
    return hex-'A' +10;
  else if (hex <= 'f')
    return hex-'a' +10;
}

//아스키번호 0x20 아래는 mqtt 통신에서 깨져 이를 0x20으로 바꾼다.
void CheckMsg() {
  int i;
  for(i=0; i<200; i++)
    if(msg[i] >0 && msg[i] < 0x20)
      msg[i] = 0x20;
}

void loop() {
  if (connect) {
    Serial.println ( "Connect requested" );
    connect = false;
    connectWifi();
    lastConnectTry = millis();
  }
  {
    unsigned int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 60000) ) {
      /* If WLAN disconnected and idle try to connect */
      /* Don't set retry time too low as retry interfere the softAP operation */
      connect = true;
    }
    if (status != s) { // WLAN status change
      Serial.print ( "Status: " );
      Serial.println ( s );
      status = s;
      if (s == WL_CONNECTED) {  // wifi가 연결 되었을 때 할일
        /* Just connected to WLAN */
        Serial.println ( "" );
        Serial.print ( "Connected to " );
        Serial.println ( ssid );
        Serial.print ( "IP address: " );
        Serial.println ( WiFi.localIP() );

        // Setup MDNS responder=======================
        if (!MDNS.begin(myHostname)) {
          Serial.println("Error setting up MDNS responder!");
        } else {
          Serial.println("mDNS responder started");
          // Add service to MDNS-SD
          MDNS.addService("http", "tcp", 80);
        } //==========================================
        
      } else if (s == WL_NO_SSID_AVAIL) {
        WiFi.disconnect();
      }
    }
  }    
  
  //DNS
  dnsServer.processNextRequest();
  //HTTP
  server.handleClient();
  
  if(WiFi.status() == WL_CONNECTED) {
    CheckMqtt();
  }
}
