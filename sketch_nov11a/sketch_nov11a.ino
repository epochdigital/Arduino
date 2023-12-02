#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 
const char* ssid = "Dina"; 
const char* password = "dindinhoon08";

ESP8266WebServer server(80);

uint8_t pinLED = D5;
bool statusLED = LOW;

void setup() {
  Serial.begin(115200);
  delay(100); 
  pinMode(pinLED, OUTPUT);

  Serial.println("Menghubungi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi tersambung..!");
  Serial.print("Nomor IP: ");  Serial.println(WiFi.localIP());

  
  server.on("/", tersambung);
  server.on("/ledmenyala", LED_menyala);
  server.on("/ledmati", LED_mati);
  server.onNotFound(tidak_ditemukan);
  server.begin();
  Serial.println("Memulai HTTP server");
}


void tersambung() {
  statusLED = LOW;
  server.send(200, "text/html", kirimHTML(statusLED)); 
}

void LED_menyala() {
  statusLED = HIGH;
  server.send(200, "text/html", kirimHTML(statusLED)); 
}

void LED_mati() {
  statusLED = LOW;
  server.send(200, "text/html", kirimHTML(statusLED)); 
}

void tidak_ditemukan(){
  server.send(404, "text/plain", "Halaman tidak ditemukan");
}


String kirimHTML(uint8_t statusLED) {
  String htmlContent = "<!DOCTYPE html>\n";
  htmlContent += "<html lang=\"en\">\n";
  htmlContent += "<head>\n";
  htmlContent += "<meta charset=\"UTF-8\">\n";
  htmlContent += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  htmlContent += "<title>Document</title>\n";
  htmlContent += "</head>\n";
  htmlContent += "<style>\n";
  htmlContent += "body{\n";
  htmlContent += "  margin: 0;\n";
  htmlContent += "  padding: 0;\n";
  htmlContent += "  background: #000007;\n";
  htmlContent += "  -webkit-tap-highlight-color: rgba(0, 0, 0, 0);\n";
  htmlContent += "}\n";
  htmlContent += ".lamp{\n";
  htmlContent += "  display: block;\n";
  htmlContent += "  position: absolute;\n";
  htmlContent += "  left: 50%;\n";
  htmlContent += "  transform: translateX(-50%);\n";
  htmlContent += "  height: 35vh;\n";
  htmlContent += "  opacity: 0.9;\n";
  htmlContent += "  z-index: 5;\n";
  htmlContent += "}\n";
  htmlContent += ".light{\n";
  htmlContent += "  width: 50%;\n";
  htmlContent += "  height: 80vh;\n";
  htmlContent += "  position: absolute;\n";
  htmlContent += "  left: 50%;\n";
  htmlContent += "  transform: translate(-50%,-10%);\n";
  htmlContent += "  background-image: radial-gradient(circle, #ffffff, #d19a00, #c04e24, #d19a00,#000007,#000007,#000007);\n";
  htmlContent += "  border-radius: 50%;\n";
  htmlContent += "  clip-path: polygon(45% 33%, 55% 33%, 100% 100%, 0% 100%);\n";
  htmlContent += "  transition: 0.5s;\n";
  htmlContent += "}\n";
  htmlContent += ".button{\n";
  htmlContent += "  width: 120px;\n";
  htmlContent += "  height: 40px;\n";
  htmlContent += "  display: flex;\n";
  htmlContent += "  align-items: center;\n";
  htmlContent += "  justify-content: center;\n";
  htmlContent += "  background: transparent;\n";
  htmlContent += "  border: 1px solid #ffffff;\n";
  htmlContent += "  color: #fff;\n";
  htmlContent += "  margin: 20px;\n";
  htmlContent += "  outline: none;\n";
  htmlContent += "}\n";
  htmlContent += ".a{\n";
  htmlContent += "  position: absolute;\n";
  htmlContent += "  top: 50px;\n";
  htmlContent += "}\n";
  htmlContent += ".b{\n";
  htmlContent += "  position: absolute;\n";
  htmlContent += "  top: 100px;\n";
  htmlContent += "}\n";
  htmlContent += "</style>\n";
  htmlContent += "<body>\n";
  htmlContent += "  <img  id=\"lamp\" class=\"lamp\" src=\"https://www.freepngimg.com/thumb/lamp/7-2-lamp-picture.png\" alt=\"\">\n";
  if(statusLED){
    htmlContent += "  <div id=\"div\" class=\"light\"></div>\n";
  }else{
     htmlContent += "  <div id=\"div\" class=\"\"></div>\n";
  }
  htmlContent += "  <input id=\"b\" type=\"button\" onclick=\"night()\" class=\"button b\" value=\"off\">\n";
  htmlContent += "  <input id=\"a\" type=\"button\" onclick=\"day()\" class=\"button a\" value=\"on\">\n";
  htmlContent += "  <script>\n";
  htmlContent += "    function day() {\n";
   htmlContent += "     window.location.href=\"/ledmenyala\"\n";
  htmlContent += "      let day = document.getElementById(\"div\");\n";
  htmlContent += "      day.style.opacity = \"1\";\n";
  htmlContent += "      let lamp = document.getElementById(\"lamp\");\n";
  htmlContent += "      lamp.style.opacity = \"0.9\";\n";
  htmlContent += "      let a = document.getElementById(\"a\");\n";
  htmlContent += "      a.style.border = \"1px solid yellow\";\n";
  htmlContent += "      let b = document.getElementById(\"b\");\n";
  htmlContent += "      b.style.border = \"1px solid #fff\";\n";
  htmlContent += "    }\n";
  htmlContent += "    function night() {\n";
  htmlContent += "     window.location.href=\"/ledmati\"\n";
  htmlContent += "      let day = document.getElementById(\"div\");\n";
  htmlContent += "      day.style.opacity = \"0\";\n";
  htmlContent += "      let lamp = document.getElementById(\"lamp\");\n";
  htmlContent += "      lamp.style.opacity = \"0.5\";\n";
  htmlContent += "      let a = document.getElementById(\"a\");\n";
  htmlContent += "      a.style.border = \"1px solid #fff\";\n";
  htmlContent += "      let b = document.getElementById(\"b\");\n";
  htmlContent += "      b.style.border = \"1px solid yellow\";\n";
  htmlContent += "    }\n";
  htmlContent += "  </script>\n";
  htmlContent += "</body>\n";
  htmlContent += "</html>\n";

  return htmlContent;
}

void loop() {
  server.handleClient();
  if(statusLED)
  {
    digitalWrite(pinLED, HIGH);
  } else {
    digitalWrite(pinLED, LOW);
  }
}
