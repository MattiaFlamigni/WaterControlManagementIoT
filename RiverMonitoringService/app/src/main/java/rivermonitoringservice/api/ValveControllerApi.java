package rivermonitoringservice.api;

import rivermonitoringservice.WaterLevelState;

public interface ValveControllerApi {
    String adjustValve(WaterLevelState state);
}
