#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "i2r"; // 와이파이 AP 이름
const char* password = "00000000";  //와이파이 비밀번호
//const char* ssid = "AndroidHotspot7147"; // 와이파이 AP 이름
//const char* password = "01033887147";  //와이파이 비밀번호
const char* mqtt_server = "broker.mqtt-dashboard.com"; //브로커 주소
const char* outTopic = "/kdi6033/inTopic"; // 사용자가 결정해서 기록
const char* inTopic = "/kdi6033/outTopic"; // 사용자가 결정해서 기록
const char* clientName = "/kdi/603333Client";  // 다음 이름이 중복되지 않게 꼭 수정 바람 - 생년월일 추천
int outPin=0;  // RS485통신 D3 IO0 tx rx 방향 LOW-받기 HIGH-쓰기모드  

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[200];

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, LOW);
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  digitalWrite(BUILTIN_LED, HIGH); 
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // mqtt로 들어온 값을 RS232 통신 TX로 보냄
  digitalWrite(outPin, HIGH);
  delay(50);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  delay(20);
  digitalWrite(outPin, LOW);

  /*
  String inString="";
  for (int i = 0; i < length; i++) {
    inString += (char)payload[i];
  }
 */
  //통신이 되고 있음을 led로 표시
  digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(50);
  digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientName)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic, "Reconnected");
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
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  serialEvent();
}

void serialEvent() {
  if (stringComplete) {
    //Serial.println(inputString);
    for(int i=0;i<inputString.length();i++)  
      msg[i]=inputString.charAt(i);
    msg[inputString.length()]=0;
    CheckMsg();
    client.publish(outTopic,msg);  // RS232통신 RX 단자로 들어온 값 mqtt로 송신
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  if(Serial.available() == false)
    return;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:`
    inputString += inChar;
  }
  stringComplete = true;
}

//아스키번호 0x20 아래는 mqtt 통신에서 깨져 이를 0x20으로 바꾼다.
void CheckMsg() {
  int i;
  for(i=0; i<200; i++)
    if(msg[i] >0 && msg[i] < 0x20)
      msg[i] = 0x20;
}

