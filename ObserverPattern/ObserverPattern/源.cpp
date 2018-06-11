#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class Observer
{
public:
	virtual void Update(float temp, float humidity, float pressure) = 0;
};
typedef shared_ptr<Observer> ObserverPtr;

class Subject
{
public:
	virtual void RegisterObserver(const string &strObserverName, const ObserverPtr &o) = 0;
	virtual void RemoveObserver(const string &strObserverName) = 0;
	virtual void NotifyObservers() = 0;
	virtual void SetMeasurements(float tmperature, float humidity, float pressure) = 0;
};
typedef shared_ptr<Subject> SubjectPtr;

class DisplayElement
{
public:
	virtual void Display() = 0;
};

class WeatherData : public Subject
{
public:
	WeatherData();
	void RegisterObserver(const string &strObserverName, const ObserverPtr &o);
	void RemoveObserver(const string &strObserverName);
	void NotifyObservers();
	void MeasurementsChanged();
	void SetMeasurements(float tmperature, float humidity, float pressure);

private:
	map<string, ObserverPtr> observers;
	float m_Temperature;
	float m_Humidity;
	float m_Pressure;
};

WeatherData::WeatherData() {};

void WeatherData::RegisterObserver(const string &strObserverName, const ObserverPtr &o)
{
	observers[strObserverName] = o;
}

void WeatherData::RemoveObserver(const string &strObserverName)
{
	auto o = observers.find(strObserverName);
	observers.erase(o);
}

void WeatherData::NotifyObservers()
{
	for (auto it = observers.cbegin(); it != observers.cend(); it++)
	{
		it->second->Update(m_Temperature, m_Humidity, m_Pressure);
	}
}

void WeatherData::MeasurementsChanged()
{
	NotifyObservers();
}

void WeatherData::SetMeasurements(float temperature, float humidity, float pressure)
{
	this->m_Temperature = temperature;
	this->m_Humidity = humidity;
	this->m_Pressure = pressure;
	MeasurementsChanged();
}

class CurrentConditionsDisplay : public Observer, DisplayElement
{
public:
	CurrentConditionsDisplay(const SubjectPtr &weatherData);
	void Update(float temperature, float humidity, float pressure);
	void Display();
private:
	float m_Temperature;
	float m_Humidity;
	SubjectPtr m_WeatherData;
};

CurrentConditionsDisplay::CurrentConditionsDisplay(const SubjectPtr &weatherData)
{
	this->m_WeatherData = weatherData;
	string strName = "CurrentConditionsDisplay";

	ObserverPtr ptr(this);
	weatherData->RegisterObserver("CurrentConditionsDisplay", ptr);
}

void CurrentConditionsDisplay::Update(float temperature, float humidity, float pressure)
{
	this->m_Temperature = temperature;
	this->m_Humidity = humidity;
	Display();
}

void CurrentConditionsDisplay::Display()
{
	cout << "Current conditions: " << m_Temperature << "F degrees and " << m_Humidity << "% humidity" << endl;
}

class HeatIndex : public Observer
{
public:
	HeatIndex(const SubjectPtr &weatherData);
	void Update(float temperature, float humidity, float pressure);
	void Display();
private:
	float m_Temperature;
	float m_Humidity;
	SubjectPtr m_WeatherData;
};

HeatIndex::HeatIndex(const SubjectPtr &weatherData)
{
	this->m_WeatherData = weatherData;
	string strName = "HeatIndexDisplay";

	ObserverPtr ptr(this);
	weatherData->RegisterObserver("HeatIndexDisplay", ptr);
}

void HeatIndex::Update(float temperature, float humidity, float pressure)
{
	this->m_Temperature = temperature;
	this->m_Humidity = humidity;
	Display();
}

void HeatIndex::Display()
{
	double heatindex = 16.923 + 1.85212 * 0.1 * m_Temperature + 5.37941 * m_Humidity - 1.00255 * 0.1 * m_Temperature * m_Humidity
		+ 9.41695 * 0.001 * m_Temperature * m_Temperature + 7.28898 * 0.001 * m_Humidity * m_Humidity + 3.45372 * 0.0001 * m_Temperature * m_Temperature * m_Humidity
		- 8.14871 * 0.0001 * m_Temperature * m_Humidity * m_Humidity + 1.02102 * 0.00001 * m_Temperature * m_Temperature * m_Humidity * m_Humidity - 3.8646 * 0.00001 * m_Temperature * m_Temperature * m_Temperature
		+ 2.91583 * 0.00001 * m_Humidity * m_Humidity * m_Humidity + 1.42721 * 0.000001 * m_Temperature * m_Temperature * m_Temperature * m_Humidity + 1.97483 * 0.0000001 * m_Temperature * m_Humidity * m_Humidity * m_Humidity
		- 2.18429 * 0.00000001 * m_Temperature * m_Temperature * m_Temperature * m_Humidity * m_Humidity + 8.4396 * 0.0000000001 * m_Temperature * m_Temperature * m_Humidity * m_Humidity * m_Humidity - 4.81975 * 0.000000000001 * m_Temperature * m_Temperature * m_Temperature * m_Humidity * m_Humidity * m_Humidity;
	cout.setf(ios::fixed);
	cout << setprecision(20) << "heatindex = " << heatindex << endl;
}

int main(int argc, char *argv[])
{
	SubjectPtr weatherData(new WeatherData());

	ObserverPtr currentDisplay(new CurrentConditionsDisplay(weatherData));
	ObserverPtr heatIndex(new HeatIndex(weatherData));
	//	weatherData->RegisterObserver("CurrentConditions", currentDisplay);
	//	weatherData->RegisterObserver("HeatIndex", heatIndex);
	weatherData->SetMeasurements(80, 65, 30.4f);
	return 0;
}