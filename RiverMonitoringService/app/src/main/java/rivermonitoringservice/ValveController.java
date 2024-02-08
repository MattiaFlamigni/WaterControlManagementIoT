package rivermonitoringservice;

import rivermonitoringservice.api.ValveControllerApi;

public class ValveController implements ValveControllerApi {
    public String adjustValve(WaterLevelState state) {
        String valveOpeningLevel = "0";
        switch (state) {
            case TOO_LOW:
                valveOpeningLevel = "0";
                break;
            case NORMAL:
                valveOpeningLevel = "25";
                break;
            case PREE_TOO_HIGH:
                valveOpeningLevel = "25";
                break;
            case TOO_HIGH:
                valveOpeningLevel = "50";
                break;
            case TOO_HIGH_CRITICAL:
                valveOpeningLevel = "100";
                break;
        }

        return valveOpeningLevel;
    }
}
