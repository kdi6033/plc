/** Handle root or redirect to captive portal */
void handleRoot() {
  //Serial.println("Server Html");
  //Serial.println ( WiFi.localIP() );
  String s; 
  String s1= String(ssid);
  s="<meta name='viewport' content='width=device-width, initial-scale=1.0'/>";
  s=s+"<meta http-equiv='refresh' content='5'/>";
  s=s+"<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />";
  s=s+"<h1>PLC 웹서버 i2r</h1>";
   s=s+"<br>김동일교수 idea to real<br>";
  s=s+"<br>출력버튼<br>";
  if(p4[0]==1)
    s=s+"<a href=\"p40\"><button style='background-color:Lime; color:blue;'>p40 on</button></a>";
  else 
    s=s+"<a href=\"p40\"><button style='background-color:DarkGreen; color:white;'>p40 off</button></a>";
  s=s+"&nbsp&nbsp";
  if(p4[1]==1) 
    s=s+"<a href=\"p41\"><button style='background-color:Lime; color:blue;'>p41 on</button></a>";
  else 
    s=s+"<a href=\"p41\"><button style='background-color:DarkGreen; color:white;'>p41 off</button></a>";
  s=s+"&nbsp&nbsp";
  if(p4[2]==1) 
    s=s+"<a href=\"p42\"><button style='background-color:Lime; color:blue;'>p42 on</button></a>";
  else 
    s=s+"<a href=\"p42\"><button style='background-color:DarkGreen; color:white;'>p42 off</button></a>";
   s=s+"&nbsp&nbsp";
  if(p4[3]==1) 
    s=s+"<a href=\"p43\"><button style='background-color:Lime; color:blue;'>p43 on</button></a>";
  else 
    s=s+"<a href=\"p43\"><button style='background-color:DarkGreen; color:white;'>p43 off</button></a>";
  s=s+"&nbsp&nbsp";  
  s=s+"<a href=\"send\"><button style='background-color:Orange; color:blue;'>보내기</button></a>";
  s=s+"<br><br>";

  s=s+"입력 Led<br>";
  if(p0[0]==1) 
    s=s+"<button style='background-color:Lime; color:blue;'>p00</button>";
  else 
    s=s+"<button style='background-color:DarkGreen; color:white;'>p00</button>";
  s=s+"&nbsp&nbsp";
  if(p0[1]==1) 
    s=s+"<button style='background-color:Lime; color:blue;'>p01</button>";
  else 
    s=s+"<button style='background-color:DarkGreen; color:white;'>p01</button>";
  s=s+"&nbsp&nbsp";
  if(p0[2]==1) 
    s=s+"<button style='background-color:Lime; color:blue;'>p02</button>";
  else 
    s=s+"<button style='background-color:DarkGreen; color:white;'>p02</button>";
  s=s+"&nbsp&nbsp";
  if(p0[3]==1) 
    s=s+"<button style='background-color:Lime; color:blue;'>p03</button>";
  else 
    s=s+"<button style='background-color:DarkGreen; color:white;'>p03</button>";
  s=s+"&nbsp&nbsp";
  if(p0[4]==1) 
    s=s+"<button style='background-color:Lime; color:blue;'>p04</button>";
  else 
    s=s+"<button style='background-color:DarkGreen; color:white;'>p04</button>";
  s=s+"&nbsp&nbsp";
  if(p0[5]==1) 
    s=s+"<button style='background-color:Lime; color:blue;'>p05</button>";
  else 
    s=s+"<button style='background-color:DarkGreen; color:white;'>p05</button>";
  s=s+"<br><br>";
      
  s=s+"아래 공유기 이름과 주소가 연결되었으면 주소를 선택한 후에 설정에서 사용 하시는 인터넷 공유기를 선택하세요. <br>";
  s=s+"연결된 AP 이름과 IP : "+sAP_ssid+"  "+String(ssid)+"  "+"<p><a href='http://"+WiFi.localIP().toString()+"'/>"+WiFi.localIP().toString()+"</a></p>";
  s=s+"<p><a href='/wifi'>공유기를 바꾸려면 누르세요.</a></p>";
  server.send(200, "text/html", s); // Empty content inhibits Content-length header so we have to close the socket ourselves.
}

void handleSend() {
  Serial.println("Send");
  handleRoot();
}

void handleP40() {
  Serial.println("P40");
  if(p4[0]==1) 
    p4[0]=0;
  else
    p4[0]=1;
  handleRoot();
}

void handleP41() {
  if(p4[1]==1) 
    p4[1]=0;
  else
    p4[1]=1;
  handleRoot();
}

void handleP42() {
  if(p4[2]==1) 
    p4[2]=0;
  else
    p4[2]=1;
  handleRoot();
}

void handleP43() {
  if(p4[3]==1) 
    p4[3]=0;
  else
    p4[3]=1;
  handleRoot();
}

void handleScan() {
  String s="";
  s="{\"chipid\":\""+sChipID+"\","+"\"ip\":\""+WiFi.localIP().toString()+","+"\"class\":\"plc-ls-k120s\""+","
      +"\"p00\":"+p0[0]+","+"\"p01\":"+p0[1]+","+"\"p02\":"+p0[2]+","+"\"p03\":"+p0[3]+","
      +"\"p04\":"+p0[4]+","+"\"p05\":"+p0[5]+","+"\"p06\":"+p0[6]+","+"\"p07\":"+p0[7]+","
      +"\"p40\":"+p4[0]+","+"\"p41\":"+p4[1]+","+"\"p42\":"+p4[2]+","+"\"p43\":"+p4[3]
      +"}";
  server.send(200, "text/plain", s);
}

void handleOn() {
  handleRoot();
  delay(1000);
}

void handleOff() {
  handleRoot();
  delay(1000);
}

void handleWifi() {
  String s; 
  String s1= String(ssid);
  //s="<meta name=\"viewport\" content=\"width=device-width, user-scalable=no\", meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\", meta http-equiv='refresh' content='5'/>";
  s="<meta name=\"viewport\" content=\"width=device-width, user-scalable=no\", meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />";
  //s=s+"<meta http-equiv='refresh' content='5'/>";
  s=s+"<h1>Wifi 사양</h1>";
  if (server.client().localIP() == apIP) {
    Serial.println(String(softAP_ssid));
    s=s+String("<p>연결된 AP: ") + sAP_ssid + "</p>";
  } else {
    s=s+"<p>연결된 와이파이 " + String(ssid) + "</p>";
  }
  s=s+"<table><tr><th align='left'>SoftAP 사양</th></tr>";
  s=s+"<tr><td>SSID " + String(softAP_ssid) + "</td></tr>";
  s=s+"<tr><td>IP   " + toStringIp(WiFi.softAPIP()) + "</td></tr>"+"</table>";
  s=s+"<br /><table><tr><th align='left'>WLAN 사양</th></tr>";
  s=s+"<tr><td>SSID " + String(ssid) + "</td></tr>";
  s=s+"<tr><td>IP   " + toStringIp(WiFi.localIP()) + "</td></tr>"+"</table>";
  
  s=s+"<br /><table><tr><th align='left'>검색된 와이파이 </th></tr>";
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      s=s+"\r\n<tr><td>SSID " + WiFi.SSID(i) + String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":" *") + " (" + WiFi.RSSI(i) + ")</td></tr>";
    }
  } else {
    s=s+"<tr><td>No WLAN found</td></tr>";
  }
  s=s+"</table>";
  s=s+"<p><a href='/wifi'>와이파이가 없으면 다시 검색하세요.</a></p>";
  
  s=s+"<form method='POST' action='wifisave'><h4>연결하려는 와이파이 입력</h4>"
    +"<input type='text' placeholder='와이파이 이름' name='n'/>"
    +"<br /><input type='password' placeholder='비밀번호' name='p'/>"
    +"<br /><input type='submit' value='      저    장      '/></form>"
    +"<p><a href='/'>메인 홈페이지로 가기</a>.</p>";
  server.send(200, "text/html", s);
}

/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave() {
  Serial.println("wifi save");
  server.arg("n").toCharArray(ssid, sizeof(ssid) - 1);
  server.arg("p").toCharArray(password, sizeof(password) - 1);
  server.sendHeader("Location", "wifi", true);
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.client().stop(); // Stop is needed because we sent no content length
  saveCredentials();
  connect = strlen(ssid) > 0; // Request WLAN connect with new credentials if there is a SSID
}

/** Redirect to captive portal if we got a request for another domain. Return true in that case so the page handler do not try to handle the request again. */
boolean captivePortal() {
  if (!isIp(server.hostHeader()) && server.hostHeader() != (String(myHostname)+".local")) {
    Serial.print("Request redirected to captive portal");
    server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send ( 302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
    return true;
  }
  return false;
}

void handleNotFound() {
  if (captivePortal()) { // If caprive portal redirect instead of displaying the error page.
    return;
  }
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
