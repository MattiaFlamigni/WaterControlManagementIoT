#include "mqtt_client.h"
#include "config.h"
#include "components/Led.h"


MQTT_Client::MQTT_Client(const char* ssid, const char* password, const char* mqtt_server, const char* topic)
    : client(espClient), ssid(ssid), password(password), mqtt_server(mqtt_server), topic(topic) {
        
        


   
}

void MQTT_Client::setup() {


    greenLed = new Led(GREEN_LED_PIN);
    redLed = new Led(RED_LED_PIN);
    

    redLed->switchOn();
    redLed->switchOff();
    
    
    this->sonar = new Sonar(ECHO_PIN, TRIG_PIN, SONAR_TIME);
    Serial.begin(115200);
    setup_wifi();
    randomSeed(micros());
    client.setServer(mqtt_server, 1883);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
}

void MQTT_Client::loop() {
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


   


    // Reading the distance from the sensor with frequency F

    //legge la variabile frequenza e a ogni frequenza legge la distanza


    unsigned long now = millis();
    if (now - lastMsgTime > frequenza) {
        lastMsgTime = now;


        int distance = sonar->getDistance()*100;
    Serial.println(String("Distance: ") + distance);

    // Creating a message in the buffer
    snprintf(msg, sizeof(msg), "%d", distance);

    Serial.println(String("Publishing message: ") + msg);

    // Publishing the message
    client.publish(topic, msg);
        
    }















    



   

    
}

void MQTT_Client::setup_wifi() {
    delay(10);
    Serial.println(String("Connecting to ") + ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    redLed->switchOn();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    greenLed->switchOn();
    redLed->switchOff();
}

void MQTT_Client::callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(String("Message arrived on [") + topic + "] len: " + length);
    greenLed->switchOn();
}

void MQTT_Client::reconnect() {
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


            greenLed->switchOn();
            
            greenLed->switchOff();
            

        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);


            redLed->switchOn();
            redLed->switchOff();

        }
    }
}
