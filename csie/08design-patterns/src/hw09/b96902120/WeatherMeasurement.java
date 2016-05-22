package hw09.b96902120;

import java.util.Observer;

public class WeatherMeasurement extends WeatherData {
    ObservableHelper sub=new ObservableHelper();
    public void setMeasurements(float temperature, float humidity) {
        this.temperature = temperature;
        this.humidity = humidity;
        measurementsChanged();
    }
    void addObserver(Observer o) {
        
        sub.addObserver(o);
    }
    public void measurementsChanged(){
        sub.setChanged();
        sub.notifyObservers(this);
    }
}
 