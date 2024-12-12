#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// WiFi and MQTT credentials
const char* ssid = "iPhone (4)";
const char* password = "p27v4kxs9abqn";
const char* mqtt_server = "26153c839e864d51b805827602b1df8e.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "alrochman23";
const char* mqtt_password = "Malivice$23";

const char* topic_publish = "home/esp2/button";
const char* topic_subscribe = "home/esp1/button";
const char* topic_potentiometer = "home/potentiometer/esp2";

WiFiClientSecure espClient;
PubSubClient client(espClient);

// Pins
const int buttonPin = D1;
const int ledPin = D3;
const int potPin = A0;

bool ledState = false;
unsigned long lastPotPublish = 0;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.printf("Message received on topic %s: %s\n", topic, message.c_str());
  if (String(topic) == topic_subscribe) {
    if (message == "1") {
      digitalWrite(ledPin, HIGH);
    } else if (message == "0") {
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP1", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(topic_subscribe);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  setup_wifi();
  espClient.setInsecure(); // Use for HiveMQ Cloud without CA certificate
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Button Logic
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed");
    client.publish(topic_publish, "1");
    delay(5000);
    client.publish(topic_publish, "0");
  }

  // Potentiometer Logic
  if (millis() - lastPotPublish > 15000) {
    lastPotPublish = millis();
    int potValue = analogRead(potPin);
    float voltage = potValue * (3.3 / 1023.0);
    char potStr[8];
    dtostrf(voltage, 4, 2, potStr);
    client.publish(topic_potentiometer, potStr);
    Serial.printf("Potentiometer value sent: %s\n", potStr);
  }
}