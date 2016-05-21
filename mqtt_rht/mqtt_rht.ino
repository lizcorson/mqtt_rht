/* mqtt_rht
 *  Publish temperature/humidity sensor data with MQTT. Based on ESP8266 MQTT example.
 *
 * Liz Corson
 * 21 May 2016
 */

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SparkFunHTU21D.h"

// Update these with values suitable for your network.

const char* ssid = "***";
const char* password = "***";
const char* mqtt_server = "xxx.xxx.xxx.xxx";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
const int msgDelay = 5000; //how often to send data
char msg_rh[50];
char msg_t[50];
HTU21D myHumidity;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  myHumidity.begin();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if ((unsigned long)(millis() - lastMsg) >= msgDelay) {
    lastMsg = millis();

    float temp = myHumidity.readTemperature()*1.8+32; //convert to F
    float rh = myHumidity.readHumidity();

    Serial.println(temp);
    Serial.println(rh);

    String rh_str = String(rh);
    rh_str.toCharArray(msg_rh, rh_str.length() + 1);
    Serial.print("Publish message: ");
    Serial.println(msg_rh);
    client.publish("office/rh", msg_rh);

    String temp_str = String(temp);
    temp_str.toCharArray(msg_t, temp_str.length() + 1);
    Serial.print("Publish message: ");
    Serial.println(msg_t);
    client.publish("office/temp", msg_t);

    //Thanks to this post: http://forum.arduino.cc/index.php?topic=241222.0
  }
}
