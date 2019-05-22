#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

MDNSResponder mdns;

/*
 * 공유기 설정에서 i2r_ap_***** 로 되어있는 ap 공유기를 선택한다. 비밀번호는 00000000 이다.
 * 공유기를 입력하기 위해 크롬의 주소창에 "i2r.local"을 입력하여 공유기 설정을 선택한다.
 * 또는 http://i2r.local/wifi  http://192.168.4.1 을 입력해도 된다.
 * 입력 후 i2r.local 의 메인 페이지에 입력한 공유기의 이름과 주소가 정상적으로 출력되면
 * 공유기 주소를 선택해 인테넷이 연결될 서버의 주소를 선택한 후 
 * 설정에서 입력한 공유기를 선택하면 정상적으로 사용 할 수 있다.
 * hostname for mDNS. Should work at least on windows. Try http://i2r.local 
 * 프로토콜은 {"name": sChipID, "gate":1, "motor":1}*/

 /* AP 설정을 위한 변수 선언 */
const char *softAP_ssid = "i2r_ap_plc_";
const char *softAP_password = "00000000";
String sAP_ssid,sChipID;
char cAP_ssid[20];
char cChipID[10]; // Json에서 Mac address를 고유 ID로 사용
 
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
float fO2,fTemp;

// mqtt를 위한 설정
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* outTopic = "/i2r_plc/inTopic";
const char* inTopic = "/i2r_plc/outTopic";
const char* clientName = ""; // AP 이름과 같이 사용
int no=1; //기기번호

WiFiClient espClient;
PubSubClient client(espClient);
const int ledPin =  LED_BUILTIN;// the number of the LED pin
int nGate=0; //gate on=1 off=0

//json을 위한 설정
StaticJsonDocument<200> doc;
DeserializationError error;
JsonObject root;

//plc 제어를 위한 선언
int nChange=0;
int p0[9]={0},p4[9]={0};
//int outPin=0;  // D3 IO0 tx rx 방향 LOW-받기 HIGH-쓰기모드  
int preOut=0;
const char* command="";  //mqtt로 전송된 명령어 처리
int mqttOn=0;  // mqtt로 메세지가 있으면 PLC로 통신 보냄  0 or 1,2

void setup() {
  //pinMode(outPin, OUTPUT);
  //digitalWrite(outPin, LOW);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // AP 이름 자동으로 만듬
  sChipID=String(ESP.getChipId(),HEX);
  sChipID.toCharArray(cChipID,sChipID.length()+1);
  sAP_ssid=String(softAP_ssid)+String(ESP.getChipId(),HEX);
  sAP_ssid.toCharArray(cAP_ssid,sAP_ssid.length()+1);
  softAP_ssid=&cAP_ssid[0];
  clientName=softAP_ssid;
  setupApDns();

  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.on("/p40", handleP40);
  server.on("/p41", handleP41);
  server.on("/p42", handleP42);
  server.on("/p43", handleP43);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/wifi", handleWifi);
  server.on("/wifisave", handleWifiSave);
  server.on("/scan", handleScan);
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
  if( sChipID.equals(sChipidin)) {
    const char* act = root["act"];
    s="write";
    if( s.equals(act)) {
      command = root["comm"];
      mqttOn=1;
      delay(500);
      SendText();
    }
    s="read";
    if( s.equals(act)) {
      int nP0=p0[0]+p0[1]*2+p0[2]*4+p0[3]*8+p0[4]*16+p0[5]*32;
      int nP4=p4[0]+p4[1]*2+p4[2]*4+p4[3]*8;
      s="{\"chipid\":\""+sChipID+"\","+"\"ip\":\""+WiFi.localIP().toString()+"\","+"\"class\":\"plc-ls-k120s\""+","
          +"\"p0\":"+nP0+","+"\"p4\":"+nP4+"}";
       for(int i=0;i<s.length();i++)
          msg[i]=s.charAt(i);
       msg[s.length()]=0;
       //sprintf (msg, "\{\"name\":\"o2\",\"no\":%d,\"value\": %.2f}",(int)no, (float)fO2);
       Serial.println(msg);
       client.publish(outTopic, msg);
    }
  }
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
  else {
    if(mqttOn==3) {
      mqttOn=0;
      client.publish(outTopic, msg);
    }
  }
  // 센서 값을 브로커에 보낼 메세지 작성.
  serialEvent();
  long now = millis();
  if (now - lastMsg > delayTime) {
    lastMsg = now;
    SendText(); //plc에 입력값 요청
    // print the string when a newline arrives:
    // 센서 값을 브로커에 보낼 메세지 작성.
    //sprintf (msg, "\{\"name\":\"o2\",\"no\":%d,\"value\": %.2f}",(int)no, (float)fO2);
    //Serial.println(msg);
    //client.publish(outTopic, msg);
  }
  client.loop();
}

void SendText() {
    String s;
    int out;
    int returnDelay=18;
    
    out=p4[0]+p4[1]*2+p4[2]*4+p4[3]*8;
    
    if(mqttOn==1) {
      s = "\0";
      s +=char(5);
      s += command;
      s +=char(4);
      mqttOn=2;
    }
    else if(preOut!=out) {
      s = "\0";
      s +=char(5);
      s += "00WSS0104%PW4000";
      s += String(out, HEX);
      s +=char(4);
      returnDelay=20;
    }
    // 입력포트의 값을 읽어온다.
    else {
      s = "\0";
      s +=char(5);
      s += "00RSS0104%PW0";
      s +=char(4);  
      returnDelay=18;
    }
    Serial1.print(s); 
    Serial.println(s); 
    preOut=out;
}

// PLC에서 시리얼통신으로 문자가 들어오면 처리한다.
void serialEvent() {
  if (stringComplete) {
    String inTag=inputString.substring(3,6);
    Serial.println(inTag);
    if(inTag.equals("RSS")) {
      int j=HexToInt(inputString.charAt(12))*16+HexToInt(inputString.charAt(13));
      for(int i=0;i<6;i++) {
        p0[i]=j%2;
        j=j>>1;
        //Serial.println(p0[i]);
      }
     }
    
    // clear the string:
    inputString = "";
    stringComplete=false;
  }
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Serial.write(inChar);
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    //if (inChar == '\n') {
    if (inChar == char(3)) {
      stringComplete = true;
      if(mqttOn==2) {
        //Serial.println("***");
        for(int i=0;i<inputString.length();i++)
          msg[i]=inputString.charAt(i);
        msg[inputString.length()]=0;
        //Serial.println(msg);
        //Serial.println("***");
        mqttOn=3;
      }
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
      connect = true;
    }
    if (status != s) { // WLAN status change
      Serial.print ( "Status: " );
      Serial.println ( s );
      status = s;
      if (s == WL_CONNECTED) {  // wifi가 연결 되었을 때 할일
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
