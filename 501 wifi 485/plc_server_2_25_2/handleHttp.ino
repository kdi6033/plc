// html->string 변환사이트 다음 유튜브 참조하세요 https://youtu.be/eY4K7Wu7fgc
// 변환 사이트
// http://davidjwatts.com/youtube/esp8266/esp-convertHTM.html#
// https://tomeko.net/online_tools/cpp_text_escape.php?lang=en
String webHeadMonit="<html> <head> <meta http-equiv='refresh' content='1; url='http://localhost' method='get' /> <meta name='viewport' content='width=device-width, initial-scale=1.0'/> <meta http-equiv='Content-Type' content='text/html;charset=utf-8' /> <style> body { background: #eab0dc; font-family: \"Lato\", sans-serif; } .button { border: none; border-color:black; color: white; padding: 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .buttonMenu { padding: 5px 24px; margin-left:20%; background-color:black; border: none; border-color:black; color:white; text-align: left; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .sidenav { height: 100%; width: 0; position: fixed; z-index: 1; top: 0; left: 0; background-color: #111; overflow-x: hidden; transition: 0.5s; padding-top: 60px; } .sidenav a { padding: 8px 8px 8px 32px; text-decoration: none; font-size: 18px; color: #818181; display: block; transition: 0.3s; } .sidenav a:hover { color: #f1f1f1; } .sidenav .closebtn { position: absolute; top: 0; right: 25px; font-size: 36px; margin-left: 50px; } .button-on {border-radius: 100%; background-color: #4CAF50;} .button-off {border-radius: 100%;background-color: #707070;} .button-ledon {border-radius: 100%; padding: 10px; font-size: 8px; margin: 0px 0px; background-color: #ff4500;} .button-ledoff {border-radius: 100%; padding: 10px; font-size: 8px; background-color: #707070;} </style> </head> <body> <script> function openNav() { document.getElementById(\"mySidenav\").style.width = \"150px\"; } function closeNav() { document.getElementById(\"mySidenav\").style.width = \"0\"; } </script>";
String webHead="<html> <head> <meta name='viewport' content='width=device-width, initial-scale=1.0'/> <meta http-equiv='Content-Type' content='text/html;charset=utf-8' /> <style> body { background: #eab0dc; font-family: \"Lato\", sans-serif; } .button { border: none; border-color:black; color: white; padding: 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .buttonMenu { padding: 5px 24px; margin-left:20%; background-color:black; border: none; border-color:black; color:white; text-align: left; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .sidenav { height: 100%; width: 0; position: fixed; z-index: 1; top: 0; left: 0; background-color: #111; overflow-x: hidden; transition: 0.5s; padding-top: 60px; } .sidenav a { padding: 8px 8px 8px 32px; text-decoration: none; font-size: 18px; color: #818181; display: block; transition: 0.3s; } .sidenav a:hover { color: #f1f1f1; } .sidenav .closebtn { position: absolute; top: 0; right: 25px; font-size: 36px; margin-left: 50px; } .button-on {border-radius: 100%; background-color: #4CAF50;} .button-off {border-radius: 100%;background-color: #707070;} .button-ledon {border-radius: 100%; padding: 10px; font-size: 8px; margin: 0px 0px; background-color: #ff4500;} .button-ledoff {border-radius: 100%; padding: 10px; font-size: 8px; background-color: #707070;} </style> </head> <body> <script> function openNav() { document.getElementById(\"mySidenav\").style.width = \"150px\"; } function closeNav() { document.getElementById(\"mySidenav\").style.width = \"0\"; } </script>";
String webTail="</body> </html>";

String webMenu="";
String webHtml="";

void handleRoot() {
  makeHtml();
  if(monit==1)
    server.send(200, "text/html", webHeadMonit+webHtml+webTail);
  else
    server.send(200, "text/html", webHead+webHtml+webTail);
}

void makeHtml() {
  String s=""; 

  s+="<h3 style='color:SteelBlue;'>&emsp;김동일유튜브 <a href='http://i2r.link' style='color:SteelBlue;'>http://i2r.link</a> </h3>";

  s+="모니터링 ";
  s+="<form action='/on'>";
  s+="<input type='hidden' name='act' value='1'>";
  s+="<input type='hidden' name='no' value='0'>";
  if(monit==1) 
      s+="<th><button type='submit' name='value' value='0' class='button button-on' ></button></a></th>";
  else
      s+="<th><button type='submit' name='value' value='1' class='button button-off' ></button></a></th>";    
  s+="</form>";

  s+="<br>입력<table style='width:100%'><br>";
  s+="<table>";
  s+="<tr>";
  s+="<th>00</th>";
  s+="<th>01</th>";
  s+="<th>02</th>";
  s+="<th>03</th>";
  s+="<th>04</th>";
  s+="<th>05</th>";
  s+="<th>06</th>";
  s+="<th>07</th>";
  s+="</tr>";

  s+="<tr>";
  for(int i=0;i<8;i++) {
    s+="<th>";
    if(In[i]==1) 
      s+="<button class='button button-ledon' ></button></a>"; //off
    else 
      s+="<button class='button button-ledoff' ></button></a>"; //on
    s+="</th>";
  }
  s+="<tr>";
  s+="</table>";

  s+="출력<br>";
  s+="<table>";
  s+="<tr>";
  s+="<th>00</th>";
  s+="<th>01</th>";
  s+="<th>02</th>";
  s+="<th>03</th>";
  s+="<th>04</th>";
  s+="<th>05</th>";
  s+="</tr>";
  s+="<tr>";
  for(i=0;i<6;i++) {
  s+="<form action='/on'>";
  s+="<input type='hidden' name='act' value='2'>";
  s+="<input type='hidden' name='no' value='"+(String)i+"'>";
  if(Out[i]==1) 
      s+="<th><button type='submit' name='value' value='0' class='button button-on' ></button></a></th>";
  else
      s+="<th><button type='submit' name='value' value='1' class='button button-off' ></button></a></th>";    
  s+="</form>";
  }
  s+="</tr>";
  s+="</table>";

  s+="<br><br>AP & IP :&emsp;"+sChipId+"&emsp;"+WiFi.localIP().toString();
  webHtml=s;
}

// act 1=monitoring on/off  2=출력
void handleOn() {
  act=server.arg("act").toInt();
  int no=server.arg("no").toInt();
  int value=server.arg("value").toInt();

  Serial.println("----------------------------");
  Serial.println(act);
  Serial.println(no);
  Serial.println(value);

  if(act==1) {
    monit=value;
  }
  else if(act==2) {
    Out[no]=value;
    crd16Rtu();
  }

  GoHome();
}

void GoHome() {
  String s;
  s="<meta http-equiv='refresh' content=\"0;url='http://"+WiFi.localIP().toString()+"/'\">";
  server.send(200, "text/html", s);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send ( 404, "text/plain", message );
}
