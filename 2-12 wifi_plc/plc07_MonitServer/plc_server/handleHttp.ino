// html->string 변환사이트
// http://davidjwatts.com/youtube/esp8266/esp-convertHTM.html#
// https://tomeko.net/online_tools/cpp_text_escape.php?lang=en
String webHead="<html> <head> <meta name='viewport' content='width=device-width, initial-scale=1.0'/> <meta http-equiv='Content-Type' content='text/html;charset=utf-8' /> <style> body { background: #eab0dc; font-family: \"Lato\", sans-serif; } .button { border: none; border-color:black; color: white; padding: 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .buttonMenu { padding: 5px 24px; margin-left:20%; background-color:black; border: none; border-color:black; color:white; text-align: left; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .sidenav { height: 100%; width: 0; position: fixed; z-index: 1; top: 0; left: 0; background-color: #111; overflow-x: hidden; transition: 0.5s; padding-top: 60px; } .sidenav a { padding: 8px 8px 8px 32px; text-decoration: none; font-size: 18px; color: #818181; display: block; transition: 0.3s; } .sidenav a:hover { color: #f1f1f1; } .sidenav .closebtn { position: absolute; top: 0; right: 25px; font-size: 36px; margin-left: 50px; } .button-on {border-radius: 100%; background-color: #4CAF50;} .button-off {border-radius: 100%;background-color: #707070;} .button-ledon {border-radius: 100%; padding: 10px; font-size: 8px; margin: 0px 0px; background-color: #ff4500;} .button-ledoff {border-radius: 100%; padding: 10px; font-size: 8px; background-color: #707070;} </style> </head> <body> <script> function openNav() { document.getElementById(\"mySidenav\").style.width = \"150px\"; } function closeNav() { document.getElementById(\"mySidenav\").style.width = \"0\"; } </script>";
String webTail="<p><a href='/wifi'>네트웍공유기변경-누른후 와이파설정부터 다시하세요</a></p> &emsp;&emsp;<a href='scanwifi'> <button >기기찿기</button></a> </body> </html>";
String webHeadM="<html> <head> <meta http-equiv='refresh' content='5'/> <meta name='viewport' content='width=device-width, initial-scale=1.0'/> <meta http-equiv='Content-Type' content='text/html;charset=utf-8' /> <style> body { background: #eab0dc; font-family: \"Lato\", sans-serif; } .button { border: none; border-color:black; color: white; padding: 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .buttonMenu { padding: 5px 24px; margin-left:20%; background-color:black; border: none; border-color:black; color:white; text-align: left; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; } .sidenav { height: 100%; width: 0; position: fixed; z-index: 1; top: 0; left: 0; background-color: #111; overflow-x: hidden; transition: 0.5s; padding-top: 60px; } .sidenav a { padding: 8px 8px 8px 32px; text-decoration: none; font-size: 18px; color: #818181; display: block; transition: 0.3s; } .sidenav a:hover { color: #f1f1f1; } .sidenav .closebtn { position: absolute; top: 0; right: 25px; font-size: 36px; margin-left: 50px; } .button-on {border-radius: 100%; background-color: #4CAF50;} .button-off {border-radius: 100%;background-color: #707070;} .button-ledon {border-radius: 100%; padding: 10px; font-size: 8px; margin: 0px 0px; background-color: #ff4500;} .button-ledoff {border-radius: 100%; padding: 10px; font-size: 8px; background-color: #707070;} </style> </head> <body> <script> function openNav() { document.getElementById(\"mySidenav\").style.width = \"150px\"; } function closeNav() { document.getElementById(\"mySidenav\").style.width = \"0\"; } </script>";

String webMenu="";
String webHtml="";

void handleRoot() {
  makeHtml();
  if(monit==1)
    server.send(200, "text/html", webHeadM+webMenu+webHtml+webTail);
  else
    server.send(200, "text/html", webHead+webMenu+webHtml+webTail);
}

void makeHtml() {
  String s=""; 

  s+="<h3 style='color:SteelBlue;'>&emsp;김동일유튜브 <a href='http://i2r.link' style='color:SteelBlue;'>http://i2r.link</a> </h3>";
  s+=s1;
  s+=(String)ipNo+"  PLC";

  s+="<br>출력<table style='width:100%'>";
  for(int i=0;i<4;i++) {
    s+="<tr>";
    s+="<form action='/on'>";
    s+="<input type='hidden' name='act' value='"+(String)i+"'>";
    if(p4[i]==1) 
      s+="<button type='submit' name='value' value='0' class='button button-on' >4"+(String)i+"</button></a>"; //off
    else 
      s+="<button type='submit' name='value' value='1' class='button button-off' >4"+(String)i+"</button></a>"; //on
    s+="</form>";
    s+="</tr>";
  }
  s+="</table>";

  String sm="";
  //sm+="<div style='background-color:LightSalmon;width: 300px;'>";
  s+="입력";
  for(int i=0;i<8;i++) {
    //Serial.println(p0[i]);
    if(p0[i]==1) 
      s+="<button class='button button-ledon' >"+(String)i+"</button></a>"; 
    else 
      s+="<button class='button button-ledoff' >"+(String)i+"</button></a>"; 
  }
  //s+="</div>";

  s+="<br><form action='/on'>모니터링";
  s+="<input type='hidden' name='act' value='4'>";
  if(monit==1) 
    s+="<button type='submit' name='value' value='0' class='button button-on' >on</button></a>"; //off
  else 
    s+="<button type='submit' name='value' value='1' class='button button-off' >off</button></a>"; //on
  s+="</form>";

  s+="통신에러";
  if(errorPlc==1) 
    s+="<button class='button button-ledon' ></button></a>";
  else 
    s+="<button class='button button-ledoff' ></button></a>"; 

  s+="<br><br>AP & IP :&emsp;"+sChipId+"&emsp;"+WiFi.localIP().toString();
  //s=s+"&emsp;&emsp;<a href='/scanwifi'> <button >기기찿기</button></a>";
  webHtml=s;
}
void makeMenu() {
  int no;
  webMenu="";
  webMenu+="<div id='mySidenav' class='sidenav'>";
  webMenu+="<a href='javascript:void(0)' class='closebtn' onclick='closeNav()'>&times;</a>";
  for(int i=0;i<countScaned;i++) {
    no=actIp[i];
    webMenu+="<form action='/menu'>";
    webMenu+="<input type='hidden' name='ipNo' value='"+(String)no+"'>";
    webMenu+="<button type='submit' name='blindNo' value='0' style='margin-left:20%;background-color:black;border-color:black;color:white;font-size:18px;'>"+(String)no+"</button>";
    webMenu+="<br>";
    webMenu+="</form>";
  }
  webMenu+="</div>";
  webMenu+="<span style='font-size:30px;cursor:pointer' onclick='openNav()'>&#9776;</span>";
  webMenu+="메뉴열기";
}

void handleMenu() {
  ipNo=server.arg("ipNo").toInt();
  int blindNo=server.arg("blindNo").toInt();
  makeHtml();
  GoHome();
}

// actNo 1=up 2=stop 3=down 4=auto 5=lightSet 6=setOpen
void handleOn() {
  int act=server.arg("act").toInt();
  int value=server.arg("value").toInt();

  Serial.println("----------------------------");
  Serial.println(ipNo);
  Serial.println(act);

  if(act<4) 
    p4[act]=value;
  else if(act==4) 
    monit=value;

  String s=s1+String(ipNo);
  s+="/on?act="+(String)act+"&value="+value;
  httpSend(s);
  GoHome();
}

void httpSend(String s) {
  Serial.println(s);
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, s)) {
    http.setTimeout(500);
    int httpCode = http.GET();
    Serial.println(httpCode);
    http.end();
  }
  makeHtml();
}

void handleMonit() {
  if(monit==1)
    monit=0;
  else
    monit=1;
  String s=s1+String(ipNo);
  s+="/on?act=4";
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

void handleScan() {
  wifiScan();
  GoHome();
  //String s;
  //s="{\"chipId\":\""+sChipId+"\",\"ip\":\""+WiFi.localIP().toString()+"\", server}";
  //server.send(200, "text/plain", s);
}
