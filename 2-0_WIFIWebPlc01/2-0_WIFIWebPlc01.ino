/*
 ip로 접속
 버튼으로 PLC 제어
 */
#include <ESP8266WiFi.h>

const char* ssid = "i2r";
const char* password = "00000000";

const int ledPin =  2;
boolean bLED = false; 
String s;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  delay(10);
  
  // Connect to WiFi network
  Serial.println();
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
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
    
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("new client");

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  if (req.indexOf("/?do=ON") > 0) {
    bLED = true;
    digitalWrite(ledPin, LOW);
    //s=String.Format("%c",0x05,"00WSS0004%PW40003","%c",0x05);
    s = "\0";
    s +=char(5);
    s += "00WSS0104%PW4000F";
    s +=char(4);
    Serial.print(s); 
    //Serial.println(F("LED is ON"));
  }
  else if (req.indexOf("/?do=OFF") > 0) {
    bLED = false;
    digitalWrite(ledPin, HIGH);
    s = "\0";
    s +=char(5);
    s += "00WSS0104%PW40000";
    s +=char(4);
    Serial.print(s); 
    //Serial.println(F("LED is OFF")); 
  }

  // Prepare the response
  //표준 http 응답 헤더 전송 시작
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          //본문(상황에 맞는 웹 페이지) 전달
          //client.println("<!DOCTYPE HTML>");, HTML5 사용시
          client.println("<html>");  //웹 페이지 작성은 HTML사용
          client.println("<body>");
   //색 선택 부분 만들기
          client.println("<br />");
          //client.println(F("<form method=\"post\">")); 
          client.println(F("<form method=\"get\">")); 
          if(!bLED) { 
            bLED=true;
            //bLED=false;
            client.println(F("<input type=\"hidden\" name=\"do\" value=\"ON\">")); 
            client.println(F("<input type=\"button\" name=\"button1\" value=\"PLC ON\" onclick=\"submit();\" style=\"height:150px; width:300px;  font-size:50px; \" >")); 
          } 
          else { 
            //bLED=true;
            bLED=false;
            client.println(F("<input type=\"hidden\" name=\"do\" value=\"OFF\">")); 
            client.println(F("<input type=\"button\" name=\"button1\" value=\"PLC OFF\" onclick=\"submit();\" style=\"height:150px; width:300px;  font-size:50px; \" >")); 
          } 
          client.println(F("</form>")); 

          client.println("</body>");
          client.println("</html>");


  delay(1);
  Serial.println("Client disonnected");
}
