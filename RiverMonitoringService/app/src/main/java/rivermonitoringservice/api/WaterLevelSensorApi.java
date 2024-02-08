package rivermonitoringservice.api;

import rivermonitoringservice.WaterLevelState;

public interface WaterLevelSensorApi {
    void updateWaterLevel(int waterLevel) throws Exception;
    WaterLevelState getState();
}
