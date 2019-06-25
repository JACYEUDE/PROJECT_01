#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <ArduinoJson.h>
int x, y, z;


const char* ssid = "Millennium Falcon";
const char* password = "19072008";

ESP8266WebServer server(4444);


void setupADXL345(){
  Wire.beginTransmission(0x53);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(0x53);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(0x53);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  
  delay(500);
  
}
/*String createJsonResponse() {
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& object = jsonBuffer.createObject();
  JsonObject& data = object.createNestedObject("data");
   
  JsonObject& accel = data.createNestedObject("accel");

  JsonObject& gyro = data.createNestedObject("gyro");
   
  JsonObject& accelXl = accel.createNestedObject("accelX");
  JsonObject& accelYl = accel.createNestedObject("accelY");
  JsonObject& accelZl = accel.createNestedObject("accelZ");
 
  JsonObject& gyroXl = gyro.createNestedObject("gyroX");
  JsonObject& gyroYl = gyro.createNestedObject("gyroY");
  JsonObject& gyroZl = gyro.createNestedObject("gyroZ");

  object["nodeID"] = "mcu1";
 
  accel["accelX"] = accelX;
  accel["accelY"] = accelY;
  accel["accelZ"] = accelZ;
  gyro["gyroX"] = gyroX;
  gyro["gyroY"] = gyroY;
  gyro["gyroZ"] = gyroZ;

  String json;
  object.prettyPrintTo(json);
  return json;
} */

void readADXL345() {    
  Wire.beginTransmission(0x53);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.requestFrom(0x53, 6);
  while(Wire.available() < 6);
  x = Wire.read()<<8|Wire.read(); 
  y = Wire.read()<<8|Wire.read(); 
  z = Wire.read()<<8|Wire.read(); 
  
  delay(500);
    
}


void handleRoot() {
 

  String textoHTML;

  textoHTML = "<center>RAW DATA FROM MPU6050 REGISTERS</center>";
  textoHTML += "<html><head><style>table, th, td {border: 1px solid black;}</style></head><body><table><tr><th>Modulo</th><th>Eixo X</th>  <th>Eixo Y</th>  <th>Eixo Z</th>   </tr>    <td>Acelerometro</td>    <td><script></script></td>    <td>accelY</td>    <td>accelZ</td>  </tr>  <tr>    <td>Giroscopio</td>    <td>gyroX</td>    <td>gyroY</td>    <td>gyroZ</td></tr></table></body></html>";
  textoHTML +=  "<html><body><p><a href=https://youtu.be/5y19QMU2GS0>LINKAO</a></p>"; 
  textoHTML +=  "<html><body><p><a href=http://127.0.0.1:5500/nodejs-server/public/index.html>LINKAO</a></p>";
  textoHTML +=  Serial.println(x);
   
  server.send(200, "text/html", textoHTML);
 
}

void handleNotFound(){
 
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
 
}

void setup(void){

  Serial.begin(115200);
  Wire.begin();
  setupADXL345();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){

readADXL345();
delay(100);
Serial.println(x);

  delay(500);
  
   server.handleClient(); 
}
