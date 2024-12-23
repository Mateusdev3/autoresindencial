#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>
#include <DFRobot_DHT11.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define DHT11_PIN 4




const char* ssid = "Starlink2.4";
const char* password = "messias314";
const char* servidorIP = "http://192.168.1.44";
const char* servidorIP1 = "http://192.168.1.137";
const unsigned char monroe [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
0x00, 0x60, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x4f, 0xff, 0x83, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xc7, 0xe7, 0xff, 0xd1, 0x80, 0x18, 0xc1, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x1f, 0xf3, 0xff, 0xc8, 0xc0, 0x33, 0xce, 0x30, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x06, 0x3f, 0xf9, 0x7f, 0x00, 0x60, 0x33, 0x9e, 0x20, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x0c, 0x7f, 0xf0, 0xff, 0xf0, 0x30, 0x13, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x7f, 0xfc, 0xfd, 0xbf, 0x30, 0x13, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x31, 0x0f, 0xff, 0x78, 0x01, 0x18, 0x23, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x87, 0xff, 0x00, 0x01, 0x86, 0x4e, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x0f, 0x80, 0x00, 0x00, 0xe3, 0x9c, 0x20, 0x00, 0x00, 0x06, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x0c, 0x1c, 0x00, 0x78, 0x01, 0xe1, 0x30, 0xc9, 0x80, 0x00, 0xc0, 0xb0, 0x00, 
0x00, 0x00, 0x80, 0x06, 0x10, 0x00, 0xc7, 0xff, 0xc3, 0x21, 0x34, 0x80, 0x18, 0x03, 0x90, 0x00, 
0x00, 0x0e, 0x3c, 0x01, 0x88, 0x01, 0xc0, 0xe0, 0x42, 0x46, 0x0c, 0x03, 0x01, 0xe1, 0xc8, 0x00, 
0x00, 0x30, 0x03, 0x00, 0xc4, 0x06, 0xc0, 0x78, 0x04, 0x08, 0x00, 0x60, 0x7e, 0x71, 0xe4, 0x00, 
0x00, 0x23, 0xf9, 0x80, 0x8f, 0xf8, 0xc7, 0xf8, 0x0c, 0x10, 0x08, 0x09, 0xfc, 0x3c, 0xe2, 0x00, 
0x00, 0x60, 0x3c, 0xe0, 0xc7, 0xe0, 0xfd, 0xfe, 0x04, 0x21, 0x01, 0xfc, 0xf0, 0x1e, 0x71, 0x00, 
0x00, 0x47, 0xc7, 0x00, 0xe0, 0x20, 0x7f, 0xf0, 0x00, 0x00, 0x03, 0xf0, 0x78, 0x07, 0x79, 0x00, 
0x00, 0xc7, 0x91, 0xfc, 0x18, 0x00, 0x7e, 0x26, 0x00, 0x07, 0xf9, 0xe0, 0x3d, 0xc3, 0xf8, 0x00, 
0x00, 0x60, 0x00, 0x07, 0xc3, 0x80, 0x63, 0x30, 0x00, 0x1f, 0xfc, 0xf0, 0x1f, 0xe0, 0xfc, 0x00, 
0x00, 0x0e, 0x1e, 0x00, 0x00, 0x20, 0x12, 0x00, 0x3f, 0xc7, 0x1e, 0x7b, 0x8f, 0x80, 0x7e, 0x00, 
0x00, 0x00, 0xc0, 0x0f, 0x80, 0x10, 0x00, 0x04, 0x7f, 0xe7, 0x8f, 0x3f, 0x87, 0x80, 0x1e, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0xf3, 0xc7, 0x9e, 0x03, 0xc0, 0x0f, 0x80, 
0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x0f, 0x1e, 0x3c, 0x01, 0xe3, 0xcf, 0x01, 0xe7, 0x07, 0x00, 
0x00, 0x00, 0xf2, 0x40, 0x00, 0x03, 0xe7, 0x8f, 0x1e, 0x00, 0xf1, 0xe7, 0x80, 0xff, 0x80, 0x00, 
0x00, 0x00, 0x79, 0x00, 0x00, 0x3f, 0xe3, 0xc7, 0x8f, 0xfc, 0x78, 0xe3, 0xce, 0x7c, 0x00, 0x00, 
0x00, 0x00, 0x40, 0x00, 0x07, 0x9e, 0x01, 0xe3, 0xc0, 0x7e, 0x3c, 0x71, 0xff, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0xff, 0x8f, 0x00, 0xf1, 0xe0, 0x0f, 0x1c, 0x78, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x39, 0xfe, 0x07, 0x08, 0x70, 0xf0, 0x47, 0x8f, 0xf8, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x07, 0xf8, 0x8e, 0x07, 0xf8, 0x78, 0x71, 0xe3, 0xcf, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x87, 0xfc, 0x0f, 0x03, 0xf8, 0x3c, 0x78, 0xff, 0xc4, 0x00, 0x00, 0x40, 0x00, 0x00, 
0x00, 0x07, 0xc3, 0x9e, 0x07, 0x81, 0xe0, 0x1e, 0x3c, 0x7f, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 
0x02, 0x07, 0xc3, 0xcf, 0x03, 0x80, 0xf0, 0x0f, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x1f, 0x07, 0xe1, 0xc7, 0x03, 0xc0, 0xf0, 0x0f, 0xfc, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0x83, 0xf1, 0xe7, 0x81, 0xe0, 0x79, 0xe1, 0xf0, 0x00, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x00, 
0x07, 0xe3, 0xf0, 0xe7, 0xc0, 0xe0, 0x3f, 0xf1, 0x00, 0x00, 0xb2, 0x18, 0x00, 0x00, 0x00, 0x00, 
0x07, 0xf3, 0xf8, 0xff, 0xe0, 0xf0, 0x1f, 0x04, 0xdf, 0x10, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0xfb, 0xbc, 0x78, 0xf0, 0x78, 0x10, 0x09, 0xef, 0x88, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0xdf, 0xbc, 0x78, 0xf0, 0x3c, 0x00, 0x08, 0xf6, 0x25, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0xef, 0x9e, 0x38, 0x7c, 0x00, 0x21, 0x08, 0x84, 0x12, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xe7, 0xce, 0x3c, 0x30, 0x00, 0x4e, 0x84, 0x0d, 0xf2, 0xc3, 0x40, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x73, 0xcf, 0x3c, 0x00, 0x00, 0x45, 0xc2, 0x90, 0x40, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x78, 0xc7, 0x80, 0x00, 0x00, 0x10, 0x00, 0x27, 0xe0, 0x02, 0x90, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x38, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc2, 0x00, 0x20, 0x00, 0x00, 0x01, 0xc0, 
0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 
0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xf8, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xef, 0xf8, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf7, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

DFRobot_DHT11 DHT;
WebServer server(80);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pino do ESP32 conectado ao relé
const int relePin = 13;
const int relePin2 = 12;
const int relePin3 = 14;
const int relePin4 = 27;
const int led = 2;

int temp = 0;
int humi = 0;

int r1 = 0;
int r2 = 0;
int r3 = 0;
int r4 = 0;
int r5 = 0;


void setup() {
  ini();
  pinMode(relePin, OUTPUT);
  pinMode(relePin2, OUTPUT);
  pinMode(relePin3, OUTPUT);
  pinMode(relePin4, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(relePin, HIGH);   // invertido (rele aterrado)
  digitalWrite(relePin2, HIGH);  // invertido (rele aterrado)
  digitalWrite(relePin3, HIGH);  // invertido (rele aterrado)
  digitalWrite(relePin4, HIGH);   // invertido (rele aterrado)
  digitalWrite(led, LOW);

  // Wifi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado!");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  digitalWrite(led, HIGH);
  

  // Rotas HTTP
  server.on("/", handleRoot);
  server.on("/ligar1", handleLigar);
  server.on("/desligar1", handleDesligar);
  server.on("/ligar2", handleLigar2);
  server.on("/desligar2", handleDesligar2);
  server.on("/ligar3", handleLigar3);
  server.on("/desligar3", handleDesligar3);
  server.on("/ligar4", handleLigar4);
  server.on("/desligar4", handleDesligar4);
  server.on("/ligarRele5", handleLigarRelex1);
  server.on("/desligarRele5", handleDesligarRelex1);
  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  server.handleClient();
  Oled();
  Temp();
  delay(250);
}
void handleRoot() {

  String pagina = "<!DOCTYPE html>";
pagina += "<html lang='pt'>";
pagina += "<head><meta charset='UTF-8'>";
pagina += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
pagina += "<title>Automação 📱</title></head>";
pagina += "<body>";
pagina += "<div class='fundo'></div>";
pagina += "<div class='main'>";
pagina += "<div class='txt1'><h1>Automação</h1>";
pagina += "<div class='graus'><span>🌡️" + String(temp) + "°C </span><span> 💧" + String(humi) + "% </span></div></div>";
pagina += "<div class='button-container'>";
pagina += "<button id='meubt1' class='b b-1' onclick='toggleRele1()'>Luz 1</button>";
pagina += "<button id='meubt2' class='b b-2' onclick='toggleRele2()'>Luz 2</button>";
pagina += "<button id='meubt3' class='b b-3' onclick='toggleRele3()'>Luz 3</button>";
pagina += "<button id='meubt4' class='b b-4' onclick='toggleRele4()'>Ventilador</button>";
pagina += "<button id='meubt5' class='b b-5' onclick='toggleRele5()'>Bomba</button>";
pagina += "<button id='meubt6' class='b b-6' onclick='Camera1()'>Camera</button>";
pagina += "<button id='meubt7' class='b b-7' onclick='toggleRele7()'>TV</button>";
pagina += "<button id='meubt8' class='b b-8' onclick='toggleRele8()'>Microtik</button>";
pagina += "<button id='meubt9' class='b b-9' onclick='toggleRele9()'>Tomada</button>";
pagina += "</div></div>";

pagina += "<script>";
pagina += "let isRele1On = false;";
pagina += "let isRele2On = false;";
pagina += "let isRele3On = false;";
pagina += "let isRele4On = false;";
pagina += "let isRele5On = false;";

pagina += "function toggleRele1() { isRele1On = !isRele1On; const button1 = document.getElementById('meubt1');";
pagina += "if (isRele1On) { button1.classList.add('on'); button1.classList.remove('off'); ligarRele1();";
pagina += "} else { button1.classList.add('off'); button1.classList.remove('on'); desligarRele1(); } }";

pagina += "function toggleRele2() { isRele2On = !isRele2On; const button2 = document.getElementById('meubt2');";
pagina += "if (isRele2On) { button2.classList.add('on'); button2.classList.remove('off'); ligarRele2();";
pagina += "} else { button2.classList.add('off'); button2.classList.remove('on'); desligarRele2(); } }";

pagina += "function toggleRele3() { isRele3On = !isRele3On; const button3 = document.getElementById('meubt3');";
pagina += "if (isRele3On) { button3.classList.add('on'); button3.classList.remove('off'); ligarRele3();";
pagina += "} else { button3.classList.add('off'); button3.classList.remove('on'); desligarRele3(); } }";

pagina += "function toggleRele4() { isRele4On = !isRele4On; const button4 = document.getElementById('meubt4');";
pagina += "if (isRele4On) { button4.classList.add('on'); button4.classList.remove('off'); ligarRele4();";
pagina += "} else { button4.classList.add('off'); button4.classList.remove('on'); desligarRele4(); } }";

pagina += "function toggleRele5() { isRele5On = !isRele5On; const button5 = document.getElementById('meubt5');";
pagina += "if (isRele5On) { button5.classList.add('on'); button5.classList.remove('off'); ligarRele5();";
pagina += "} else { button5.classList.add('off'); button5.classList.remove('on'); desligarRele5(); } }";

pagina += "function ligarRele1() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/ligar1', true); rqr.send(); }";
pagina += "function desligarRele1() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/desligar1', true); rqr.send(); }";
pagina += "function ligarRele2() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/ligar2', true); rqr.send(); }";
pagina += "function desligarRele2() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/desligar2', true); rqr.send(); }";
pagina += "function ligarRele3() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/ligar3', true); rqr.send(); }";
pagina += "function desligarRele3() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/desligar3', true); rqr.send(); }";
pagina += "function ligarRele4() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/ligar4', true); rqr.send(); }";
pagina += "function desligarRele4() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/desligar4', true); rqr.send(); }";
pagina += "function ligarRele5() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/ligarRele5', true); rqr.send(); }";
pagina += "function desligarRele5() { var rqr = new XMLHttpRequest(); rqr.open('GET', '/desligarRele5', true); rqr.send(); }";
pagina += "function Camera1() { window.open('http://192.168.1.161', '_blank'); }";
pagina += "</script>";

pagina += "<style>";
pagina += "body { text-align: center; }";
pagina += ".graus span { font-family: Arial, Helvetica, sans-serif; font-size: 40px; text-shadow: 6px 6px 9px black; margin-left: 30px; margin-right: 30px; }";
pagina += ".fundo { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/fundo%20site.png);";
pagina += "background-size: cover; background-repeat: no-repeat; height: 100vh; width: 100vw; position: fixed; top: 0; left: 0;";
pagina += "z-index: -1; opacity: 0.855; background-color: rgba(0, 0, 0, 0.507); }";
pagina += ".main { display: flex; flex-direction: column; justify-content: center; align-items: center; background-color: rgba(0, 0, 0, 0.507); }";
pagina += ".txt1 { color: rgb(245, 237, 237); text-align: center; font-size: 30px; text-shadow: 2px 2px 10px rgba(0, 0, 0, 0.7); }";
pagina += ".button-container { display: flex; justify-content: center; align-items: center; flex-wrap: wrap; }";
pagina += ".b { padding: 60px 90px; min-width: 150px; max-width: 150px; max-height: 100px; background-color: rgb(239, 247, 255); opacity: 0.9;";
pagina += "border-radius: 30px; color: rgb(0, 0, 0); cursor: pointer; font-size: 18px; margin: 10px; text-align: center;";
pagina += "display: flex; justify-content: center; align-items: center; }";
pagina += ".b-1 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/lapadag2.png);";
pagina += "background-position: center; background-size: cover; }";
pagina += ".b-2 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/lampadag4.png); background-position: center; background-size: cover; }";
pagina += ".b-3 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/lampadag4.png); background-position: center; background-size: cover; }";
pagina += ".b-4 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/ventilador.png); background-position: center; background-size: cover; }";
pagina += ".b-5 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/bombag1.png); background-position: center; background-size: cover; }";
pagina += ".b-6 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/camera.png); background-position: center; background-size: cover; }";
pagina += ".b-7 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/tv.png); background-position: center; background-size: cover; }";
pagina += ".b-8 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/microtik.png); background-position: center; background-size: cover; }";
pagina += ".b-9 { background-image: url(https://raw.githubusercontent.com/Mateusdev3/autoresindencial/refs/heads/main/images/tomada.png); background-position: center; background-size: cover; }";
pagina += ".on { border-color: rgb(0, 255, 0); }";
pagina += "</style></body></html>";
 server.send(200, "text/html", pagina);
}
// Funções
void ini(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.drawBitmap(0, 0,  monroe, 128, 64, WHITE);
  display.display();
}
void Temp() {
  DHT.read(DHT11_PIN);
  int t = DHT.temperature;
  int h = DHT.humidity;
  temp = t;
  humi = h;
}  
void Oled(){
  display.clearDisplay();
  display.setTextSize(1);  
  display.setTextColor(SSD1306_WHITE); 
  display.setTextSize(3);
  display.setCursor(0, 40);
  display.print(temp);
  display.print("C");
  display.drawLine(0, 33, 128, 33, SSD1306_WHITE);
  display.drawLine(62, 64, 62, 33, SSD1306_WHITE);
  // humidade
  display.setTextSize(3);
  display.setCursor(74, 40);
  display.print(humi);
  display.print("%");
  if (r1 == 1){
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 5);
    display.println("Luz 1");
  }
  if (r2 == 1){
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(40, 5);
    display.println("Luz 2");
  }
  if (r3 == 1){
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 25);
    display.println("Luz 3");
  }
  if (r4 == 1){
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(85, 35);
    display.println("Luz 4");
  }
  if (r5 == 1){
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(80, 5);
    display.println("Bomba");
  }
  display.display();
  
}

void handleLigar() {
  HTTPClient http;
  String url = String(servidorIP1) + "/ligar";
  http.begin(url);
  int codigohttp = http.GET();
  if(codigohttp > 0){
     Serial.printf("Requisição GET bem-sucedida, código de status: %d\n", );
     server.send(200, "text/plain", "Rele Luz do quarto");
  }else {
    Serial.printf("Erro na requisição GET: %s\n", http.errorToString(codigohttp).c_str());
  }
  http.end();
}

void handleDesligar() {
  HTTPClient http;
  String url = String(servidorIP1) + "/desligar";
  http.begin(url);
  int codigohttp = http.GET();
  if(codigohttp > 0){
     Serial.printf("Requisição GET bem-sucedida, código de status: %d\n", codigohttp);
     server.send(200, "text/plain", "Rele Luz do quarto");
  }else {
    Serial.printf("Erro na requisição GET: %s\n", http.errorToString(codigohttp).c_str());
  }
  http.end();
}

void handleLigar2() {
  digitalWrite(relePin2, LOW);
  server.send(200, "text/plain", "Relé 2 ligado");
  r2 = 1;
  
}

void handleDesligar2() {
  digitalWrite(relePin2, HIGH);
  server.send(200, "text/plain", "Relé 2 desligado");
  r2 = 0;
}
void handleLigar3(){
  digitalWrite(relePin3, LOW);
  server.send(200, "text/plain", "Relé 3 ligado");
  r3 = 1;

}
void handleDesligar3(){
  digitalWrite(relePin3, HIGH);
  server.send(200, "text/plain", "Rele 3 desligado");
  r3 = 0;
}
void handleLigar4(){
  digitalWrite(relePin4, LOW);
  server.send(200, "text/plain", "Rele 4 Ligado");
  r4 = 1;
}
void handleDesligar4(){
    digitalWrite(relePin4, HIGH);
  server.send(200, "text/plain", "Rele 4 desligado");
  r4 = 0;
}
void handleLigarRelex1() {
  HTTPClient http;
  String url = String(servidorIP) + "/ligar";
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("Requisição GET bem-sucedida, código de status: %d\n", httpCode);
     server.send(200, "text/plain", "Rele bomba ligado");
     r5 = 1;
   
  } else {
    Serial.printf("Erro na requisição GET: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
void handleDesligarRelex1() {
  HTTPClient http;
  String url = String(servidorIP) + "/desligar";
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("Requisição GET bem-sucedida, código de status: %d\n", httpCode);
     server.send(200, "text/plain", "Rele bomba desligado");
     r5 = 0;
  } else {
    Serial.printf("Erro na requisição GET: %s\n", http.errorToString(httpCode).c_str());  
  }
  http.end();
}