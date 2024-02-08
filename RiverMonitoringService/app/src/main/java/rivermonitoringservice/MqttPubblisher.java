package rivermonitoringservice;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MqttPubblisher {

    private String broker;
    private String clientId;
    private String topic;

    public MqttPubblisher(String broker, String clientId, String topic){
        this.broker = broker;
        this.clientId = clientId;
        this.topic = topic;
    }

    public void sendMsg(String msg) throws Exception {

        try {
            MqttClient client = new MqttClient(broker, clientId);
            MqttConnectOptions options = new MqttConnectOptions();
            options.setCleanSession(true);

            client.connect(options);

            MqttMessage message = new MqttMessage();
            message.setPayload(msg.getBytes());

            client.publish(topic, message);
            System.out.println("Message published : " + message);

            client.disconnect();

        } catch (MqttException e) {
            e.printStackTrace();
        }
    }


}
