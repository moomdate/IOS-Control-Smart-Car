#include <ESP8266WiFi.h>
const char* ssid = "iPhone";
const char* password = "GGG19022539";
#define Relay1 D1
#define Relay2 D2

WiFiServer server(80);
void setup() {
  Serial.begin(74880);
  delay(10);
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
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/data") != -1)
  {
    // Serial.println("cccc");
  }
  else if (req.indexOf("/") != -1)
  {
    client.flush();
    String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    web += "<html>\r\n";
    web += "<head>\r\n";
    web += "<meta charset='utf-8'>";
    web += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" crossorigin=\"anonymous\">";
    web += "<script>\r\n";
    web += "var ajax = null;\r\n";
    web += "if (window.XMLHttpRequest)\r\n";
    web += "{ajax =new XMLHttpRequest();}\r\n";
    web += "else\r\n";
    web += "{ajax=new ActiveXObject(\"Microsoft.XMLHTTP\");}\r\n";
    web += "function ajaxLoad(method ,URL,displayElementId,sendData)\r\n";
    web += "{\r\n";
    web += "if(!ajax){alert(\"not support\");return;}\r\n";
    web += "ajax.open(method,URL,true);\r\n";
    web += "ajax.onreadystatechange = function()\r\n";
    web += "{\r\n";
    web += "if(ajax.readyState == 4 && ajax.status==200)\r\n";
    web += "{\r\n";
    web += "var ajax_result = ajax.responseText;\r\n";
    web += "var el = document.getElementById(displayElementId);\r\n";
    web += "el.innerHTML = ajax_result;\r\n";
    web += "}\r\n";
    web += "}\r\n";
    web += "ajax.send(sendData);\r\n";
    web += "}\r\n";
    web += "function update_temp_humi()\r\n";
    web += "{\r\n";
    web += " window.ondevicemotion = function(event) {\r\n";
    web += "x = Math.ceil(event.accelerationIncludingGravity.x)*20;\r\n";
    web += "y = Math.ceil(event.accelerationIncludingGravity.y)*20;}\r\n";
    web += "var rand = Math.random();\r\n";
    web += "var URL =  x + \"=\" + y;\r\n";
    web += "ajaxLoad(\"GET\",URL,\'temp_humi\',null);\r\n";
    web += "}\r\n";
    web += "</script>\r\n";
    web += "</head>";
    web += "<body>";
    web += "</br>";
    web += "<div class=\"panel panel-primary\"> <div class=\"panel-heading\"> <h3 class=\"panel-title\"><h1><Center>Let's GO</Center></h1></h3> </div> <div class=\"panel-body\"> <div class=\"alert alert-danger\" role=\"alert\"><center><h2>เอียง to บังคับรถ</h2><center></div> </div> </div>";
    web += "<script>";
    web += "function Relay(state){ajaxLoad(\"GET\",state+\'.html\',null,null);}";
    web += "setInterval(\"update_temp_humi()\",120);";
    web += "</script>";
    web += "</body>";
    web += "</html>";
    client.print(web);

    return;
  }
}

