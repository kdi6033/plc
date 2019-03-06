#include "Nextion.h"

NexText t0 = NexText(0, 1, "t0");
NexText b0 = NexText(0, 2, "b0");

int v=0;
char msg[100]={"abcd"};

NexTouch *nex_listen_list[] =
{
  &b0,
  NULL
};

void b0PushCallback(void *ptr) {
  t0.setText(msg);
}
  
void setup() {
  // put your setup code here, to run once:
  nexInit();
  Serial.begin(9600);
  Serial.println(msg);
  b0.attachPush(b0PushCallback);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  sprintf (msg, "p0%d.bco=%d%c%c%c",i,color,0xff,0xff,0xff);
  Serial1.print(msg);
  Serial1.print(msg);
  */
  delay(30);
  nexLoop(nex_listen_list);
  v=v+20;
}
