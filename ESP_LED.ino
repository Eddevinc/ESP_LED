
#include <SPI.h>
#include <ESP8266WiFi.h>

//Wifi Details Starts from Here

const char* ssid = "ManjCell";
const char* password = "welcome@123";

const char* host = "smartgatedemo.azurewebsites.net";
const int httpsPort = 80; 
String userName = "Team-B"; //This needs to be changed according to the teams. 
//http://smartgatedemo.azurewebsites.net/SampleIoT/LEDSwitch?userName=Team-A

WiFiClient client;
//Wifi Details Ends Here

int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long customtime = 0;         // the last time the output pin was toggled
long debounce = 200; 

#define led 13 //GPIO13 is connected to + of LED (long leg), GND of ESP8266 is connected to - of LED (short leg)

void setup() {
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    
  // Connect to wifi Starts From Here
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Connect to wifi Starts Ends Here
}

void loop()
{
     String url = "/api/SampleIoTServices/GetSwitchStatus?userName=" + userName;
}
            
//Call api and send data.
String PostDataToEndPoint(String Url)
{
   // Use WiFiClientSecure class to create TLS connection
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  Serial.println("Port is :");
  Serial.println(httpsPort);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
  }
  Serial.println("requesting URL: ");
      Serial.println(Url);
    
      client.print(String("GET ") + Url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "User-Agent: BuildFailureDetectorESP8266\r\n" +
                   "Connection: close\r\n\r\n");
    
      Serial.println("request sent");
      while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
          Serial.println("headers received");
          break;
        }
      }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("Response is:");
  Serial.println("----***-----");
  Serial.println(line);
  Serial.println("----***-----");
  Serial.println("closing connection");

  //If response is true or car is authenticated rotate the motor to open the gate.
  if(line == "1") 
  {
    Serial.println("Glow Led");
    digitalWrite(led,HIGH); 
  }
  else
  {
    Serial.println("Switch Off");
    }

 delay(2000);
  return "\r";
}




