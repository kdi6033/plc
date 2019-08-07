String inputString = "";         // 받은 문자열
String s;  // 보내는 문자열
int count,j;
int outPin=0;  // D3 IO0 tx rx 방향 LOW-받기 HIGH-쓰기모드  

long lastMsg = 0;
int delayTime=4000; //mqtt로 메세지 보낸는 시간 (단위 ms)

void setup() {
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, LOW);
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  // 보내는 문자열 작성
   s = "\0";
   s +=char(5);
   s += "00WSS0104%PW4000F";
   s +=char(4);
}

void loop() {
  serialEvent();

  long now = millis();
  if (now - lastMsg > delayTime) {
    lastMsg = now;
    count++;
    j=count%2;
    if(j==1) 
      s.setCharAt(17,'F');
    else 
      s.setCharAt(17,'0');
    //SendText();
    Serial.println(" ");
    Serial.println(s); 
    Serial1.print(s);
  }
}

/*
void SendText() {
    digitalWrite(outPin, HIGH);
    delay(20);
    Serial.print(s); 
    delay(20);
    digitalWrite(outPin, LOW);
}
*/

void serialEvent() {
  if(Serial.available() == false)
    return;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Serial.print(inChar);
  }
}
