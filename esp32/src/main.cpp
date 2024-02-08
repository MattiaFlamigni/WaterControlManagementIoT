#include <Arduino.h>
#include "mqtt_client.h"
#include "mqtt_pub.h"
#include "config.h"
#include "components/Sonar.h"
#include "components/Led.h"

// Setup MQTT client
const char* ssid = "Wind3 HUB-E99111";
const char* password = "29190210";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topic = "WaterLevel";
//Sonar* sonar;
MQTT_Client mqtt_client(ssid, password, mqtt_server, topic);
MQTT_Pub mqtt_pub(ssid, password, mqtt_server, "frequency");

void setup() {
    mqtt_client.setup();
    mqtt_pub.setup();
    


    //Serial.begin(9600);
    //sonar = new Sonar(ECHO_PIN, TRIG_PIN, SONAR_TIME);
}

void loop() {
    mqtt_client.loop();
    mqtt_pub.loop();



    
    //Serial.println(String("Distance: ") + sonar->getDistance());
    delay(1000);

}
