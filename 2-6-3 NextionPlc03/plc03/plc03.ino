
int v=0;
char msg[100];
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  int color;
  color=864;
  for(int i=0;i<8;i++) {
    sprintf (msg, "p0%d.bco=%d%c%c%c",i,color,0xff,0xff,0xff);
    Serial.println();
    Serial.print(msg);
    Serial1.print(msg);
    Serial1.print(msg);
  }
  delay(5000);
  color=2016;
  for(int i=0;i<8;i++) {
    sprintf (msg, "p0%d.bco=%d%c%c%c",i,color,0xff,0xff,0xff);
    Serial1.print(msg);
    Serial1.print(msg);
  }
  delay(5000);
  /*
  int a=9,b;
  for(int i=0;i<8;i++) {
    b=a&0x01;
    Serial.println(b);
    a=a>>1;
  }
  */
  //v=v+20;
  //delay(2000);
}
