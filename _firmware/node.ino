#include <ESP8266WiFi.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <PubSubClient.h>
#include <Servo.h>



unsigned long timeCurr, timePrev; 

const char *ssid = "iPhone"; 
const char *pass = "123123123";

// cloudMQTT
const char *mqttServer = "m24.cloudmqtt.com";
const int mqttPort = 12472;
const char *mqttUser = "dusmflea";
const char *mqttPassword = "POk8KVBfLmsu";


WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);

  // WiFi connect
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // MQTT Connet
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);


  timePrev = millis();

  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe("esp/kick");

  Wire.begin(D1, D2); 
}


// MQTT callback
void callback(char *topic, byte *payload, unsigned int length)
{
  
  char receivedChar[length];
  memcpy(receivedChar, payload, length);
  receivedChar[length] = '\0';

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    receivedChar[i] = (char)payload[i];
  }

  Serial.println();
  Serial.println("-----------------------");

  // -----------------------------------------
  if (strcmp(receivedChar, "am") == 0)
  {
    Wire.beginTransmission(8);
    Wire.write("a");
    Wire.endTransmission(); 
  }
  if (strcmp(receivedChar, "bm") == 0)
  {
    Wire.beginTransmission(8);
    Wire.write("b");
    Wire.endTransmission(); 
  }
  if (strcmp(receivedChar, "x") == 0)
  {
    Wire.beginTransmission(8);
    Wire.write("x");
    Wire.endTransmission(); 
  }  
  if (strcmp(receivedChar, "X") == 0)
  {
    Wire.beginTransmission(8);
    Wire.write("X");
    Wire.endTransmission(); 
  }  
  if (strcmp(receivedChar, "y") == 0)
  {
    Wire.beginTransmission(8);
    Wire.write("y");
    Wire.endTransmission(); 
  }  
  if (strcmp(receivedChar, "Y") == 0)
  {
    Wire.beginTransmission(8);
    Wire.write("Y");
    Wire.endTransmission(); 
  }  
  // ------------------------------------------

}

void loop()
{
  client.loop();
}