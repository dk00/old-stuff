package hw09.b96902120;

public class WeatherStation {

    public static void main(String[] args) {
        WeatherMeasurement wm = new WeatherMeasurement();
        new HeatIndexDisplay(wm);
        wm.setMeasurements(80, 65);
        wm.setMeasurements(82, 70);
        wm.setMeasurements(78, 90);
    }
}
