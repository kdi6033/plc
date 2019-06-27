String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String s;
int count,j;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

   s = "\0";
   s +=char(5);
   s += "00WSS0104%PW4000F";
   s +=char(4);
}

void loop() {
  serialEvent();

  count++;
  j=count%2;
  if(j==1) 
    s.setCharAt(17,'F');
  else 
    s.setCharAt(17,'0');
  Serial1.print(s); 
  delay(4000);
}

void serialEvent() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  if(Serial.available() == false) 
    return;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
  }
  stringComplete = true;
}
