#include "mqtt_pub.h"
#include "config.h"

MQTT_Pub::MQTT_Pub(const char* ssid, const char* password, const char* mqtt_server, const char* topic)
    : client(espClient), ssid(ssid), password(password), mqtt_server(mqtt_server), topic(topic) {
   
}

void MQTT_Pub::setup() {
    Serial.begin(115200);
    setup_wifi();
    randomSeed(micros());
    client.setServer(mqtt_server, 1883);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
}

void MQTT_Pub::loop() {

    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    /*
    unsigned long now = millis();
    if (now - lastMsgTime > 10000) {
        lastMsgTime = now;
        value++;

        // Creating a message in the buffer
        snprintf(msg, sizeof(msg), "hello world #%ld", value);

        Serial.println(String("Publishing message: ") + msg);

        // Publishing the message
        client.publish(topic, msg);
    }*/

    





   

    
}

void MQTT_Pub::setup_wifi() {
    delay(10);
    Serial.println(String("Connecting to ") + ssid);
    WiFi.mode(WIFI_STA);
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

void MQTT_Pub::callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(String("Message arrived on [") + topic + "] len: " + length);

    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    
    /*converte messa in numero e assegna a frequenza*/
    frequenza = message.toInt();
    Serial.println(frequenza);

}

void MQTT_Pub::reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = String("esiot-2122-client-") + String(random(0xffff), HEX);

        // Attempt to connect
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            // client.publish("outTopic", "hello world");
            // ... and resubscribe
            client.subscribe(topic);

        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
