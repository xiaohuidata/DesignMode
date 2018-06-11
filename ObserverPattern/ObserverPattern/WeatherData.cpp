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
	virtual void Display() = 0;
};
typedef shared_ptr<Observer> ObserverPtr;

class Subject
{
public:
	virtual ~Subject(){};
	virtual void RegisterObserver(const string &strObserverName, Observer *o) = 0;
	virtual void RemoveObserver(const string &strObserverName) = 0;
	virtual void NotifyObservers() = 0;
	virtual void SetMeasurements(float tmperature, float humidity, float pressure) = 0;
};
typedef shared_ptr<Subject> SubjectPtr;

class WeatherData : public Subject
{
public:
	WeatherData();
	~WeatherData();
	void RegisterObserver(const string &strObserverName, Observer *o);
	void RemoveObserver(const string &strObserverName);
	void NotifyObservers();
	void MeasurementsChanged();
	void SetMeasurements(float tmperature, float humidity, float pressure);

private:
	map<string, Observer *> observers;
	float m_Temperature;
	float m_Humidity;
	float m_Pressure;
};

WeatherData::WeatherData() {};

WeatherData::~WeatherData()
{
	for (auto it = observers.begin(); it != observers.end();)
	{
		auto o = it;
		Observer *ptr = it->second;
		cout << "destructor observer " << it->first << endl;
		it++;
		observers.erase(o);
		delete(ptr);
		ptr = nullptr;
	}
}

void WeatherData::RegisterObserver(const string &strObserverName, Observer *o)
{
	observers[strObserverName] = o;
}

void WeatherData::RemoveObserver(const string &strObserverName)
{
	auto o = observers.find(strObserverName);
	Observer *ptr = o->second;
	observers.erase(o);
	delete(ptr);
	ptr = nullptr;
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

class CurrentConditionsDisplay : public Observer
{
public:
	CurrentConditionsDisplay(const SubjectPtr &weatherData);
	void Update(float temperature, float humidity, float pressure);
	void Display();
private:
	float m_Temperature;
	float m_Humidity;
	const SubjectPtr &m_WeatherData;
};

CurrentConditionsDisplay::CurrentConditionsDisplay(const SubjectPtr &weatherData) : m_WeatherData(weatherData)
{
	string strName = "CurrentConditionsDisplay";

	weatherData->RegisterObserver("CurrentConditionsDisplay", this);
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

class StatisticsDisplay : public Observer
{
public:
	StatisticsDisplay(const SubjectPtr &weatherData);
	void Update(float temperature, float humidity, float pressure);
	void Display();
private:
	float maxTemp;
	float minTemp;
	float tempSum;
	int numReadings;
	const SubjectPtr &m_WeatherData;
};

StatisticsDisplay::StatisticsDisplay(const SubjectPtr &weatherData) : m_WeatherData(weatherData)
{
	string strName = "StatisticsDisplay";

	weatherData->RegisterObserver("StatisticsDisplay", this);
}

void StatisticsDisplay::Update(float temperature, float humidity, float pressure)
{
	tempSum += temperature;
	numReadings++;

	if (temperature > maxTemp)
	{
		maxTemp = temperature;
	}

	if (temperature < minTemp)
	{
		minTemp = temperature;
	}

	Display();
}

void StatisticsDisplay::Display()
{
	cout << "Avg/Max/Min temperature = " << (tempSum / numReadings) << "/" << maxTemp << "/" << minTemp << endl;
}

class ForecastDisplay : public Observer
{
public:
	ForecastDisplay(const SubjectPtr &weatherData);
	void Update(float temperatue, float humidity, float pressure);
	void Display();
private:
	float currentPressure;
	float lastPressure;
	const SubjectPtr &m_WeatherData;
};

ForecastDisplay::ForecastDisplay(const SubjectPtr &weatherData): m_WeatherData(weatherData)
{
	string strName = "ForecastDisplay";

	weatherData->RegisterObserver("ForecastDisplay", this);
}

void ForecastDisplay::Update(float temperatur, float humidity, float pressure)
{
	lastPressure = currentPressure;
	currentPressure = pressure;
	Display();
}

void ForecastDisplay::Display()
{
	cout << "Forecast: ";
	if (currentPressure > lastPressure)
	{
		cout << "Improving weather on the way!" << endl;
	}
	else if(currentPressure == lastPressure)
	{
		cout << "More of the same" << endl;
	}
	else
	{
		cout << "Watch out for cooler, rainy weather" << endl;
	}
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
	const SubjectPtr &m_WeatherData;
};

HeatIndex::HeatIndex(const SubjectPtr &weatherData) : m_WeatherData(weatherData)
{
	string strName = "HeatIndexDisplay";

	weatherData->RegisterObserver("HeatIndexDisplay", this);
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

	cout << setprecision(20) << "heatindex = " << heatindex << endl;
}

void test()
{
	SubjectPtr weatherData(new WeatherData());
	Observer *currentDisplay = new CurrentConditionsDisplay(weatherData);
	Observer *statisticsDisplay = new StatisticsDisplay(weatherData);
	Observer *forecastDisplay = new ForecastDisplay(weatherData);
	Observer *heatIndex = new HeatIndex(weatherData);

	weatherData->SetMeasurements(80, 65, 30.4f);
	weatherData->SetMeasurements(82, 70, 29.2f);
	weatherData->SetMeasurements(78, 90, 29.2f);
}

int main(int argc, char *argv[])
{
	test();
	return 0;
}


//#include <iostream>
//#include <memory>
//#include <map>
//#include <string>
//#include <iomanip>
//
//using namespace std;
//
//class Observer
//{
//public:
//	virtual void Update(float temp, float humidity, float pressure) = 0;
//	virtual void Display() = 0;
//};
//typedef shared_ptr<Observer> ObserverPtr;
//
//class Subject
//{
//public:
//	virtual ~Subject(){};
//	virtual void RegisterObserver(const string &strObserverName, Observer *o) = 0;
//	virtual void RemoveObserver(const string &strObserverName) = 0;
//	virtual void NotifyObservers() = 0;
//	virtual void SetMeasurements(float tmperature, float humidity, float pressure) = 0;
//};
//typedef shared_ptr<Subject> SubjectPtr;
//
//class WeatherData : public Subject
//{
//public:
//	WeatherData();
//	~WeatherData();
//	void RegisterObserver(const string &strObserverName, Observer *o);
//	void RemoveObserver(const string &strObserverName);
//	void NotifyObservers();
//	void MeasurementsChanged();
//	void SetMeasurements(float tmperature, float humidity, float pressure);
//
//private:
//	map<string, Observer *> observers;
//	float m_Temperature;
//	float m_Humidity;
//	float m_Pressure;
//};
//
//WeatherData::WeatherData() {};
//
//void WeatherData::RegisterObserver(const string &strObserverName, Observer *o)
//{
//	observers[strObserverName] = o;
//}
//
//WeatherData::~WeatherData()
//{
//	for (auto it = observers.begin(); it != observers.end();)
//	{
//		auto o = it;
//		Observer *ptr = it->second;
//		cout << "destructor observer " << it->first << endl;
//		it++;
//		observers.erase(o);
//		delete(ptr);
//		ptr = nullptr;
//	}
//}
//
//void WeatherData::RemoveObserver(const string &strObserverName)
//{
//	auto o = observers.find(strObserverName);
//	Observer *ptr = o->second;
//	observers.erase(o);
//	delete(ptr);
//	ptr = nullptr;
//}
//
//void WeatherData::NotifyObservers()
//{
//	for (auto it = observers.cbegin(); it != observers.cend(); it++)
//	{
//		it->second->Update(m_Temperature, m_Humidity, m_Pressure);
//	}
//}
//
//void WeatherData::MeasurementsChanged()
//{
//	NotifyObservers();
//}
//
//void WeatherData::SetMeasurements(float temperature, float humidity, float pressure)
//{
//	this->m_Temperature = temperature;
//	this->m_Humidity = humidity;
//	this->m_Pressure = pressure;
//	MeasurementsChanged();
//}
//
//class CurrentConditionsDisplay : public Observer
//{
//public:
//	CurrentConditionsDisplay(Subject *weatherData);
//	void Update(float temperature, float humidity, float pressure);
//	void Display();
//private:
//	float m_Temperature;
//	float m_Humidity;
//	Subject *m_WeatherData;
//};
//
//CurrentConditionsDisplay::CurrentConditionsDisplay(Subject *weatherData) : m_WeatherData(weatherData)
//{
//	string strName = "CurrentConditionsDisplay";
//
//	weatherData->RegisterObserver("CurrentConditionsDisplay", this);
//}
//
//void CurrentConditionsDisplay::Update(float temperature, float humidity, float pressure)
//{
//	this->m_Temperature = temperature;
//	this->m_Humidity = humidity;
//	Display();
//}
//
//void CurrentConditionsDisplay::Display()
//{
//	cout << "Current conditions: " << m_Temperature << "F degrees and " << m_Humidity << "% humidity" << endl;
//}
//
//class StatisticsDisplay : public Observer
//{
//public:
//	StatisticsDisplay(Subject *weatherData);
//	void Update(float temperature, float humidity, float pressure);
//	void Display();
//private:
//	float maxTemp;
//	float minTemp;
//	float tempSum;
//	int numReadings;
//	Subject *m_WeatherData;
//};
//
//StatisticsDisplay::StatisticsDisplay(Subject *weatherData) : m_WeatherData(weatherData)
//{
//	string strName = "StatisticsDisplay";
//
//	weatherData->RegisterObserver("StatisticsDisplay", this);
//}
//
//void StatisticsDisplay::Update(float temperature, float humidity, float pressure)
//{
//	tempSum += temperature;
//	numReadings++;
//
//	if (temperature > maxTemp)
//	{
//		maxTemp = temperature;
//	}
//
//	if (temperature < minTemp)
//	{
//		minTemp = temperature;
//	}
//
//	Display();
//}
//
//void StatisticsDisplay::Display()
//{
//	cout << "Avg/Max/Min temperature = " << (tempSum / numReadings) << "/" << maxTemp << "/" << minTemp << endl;
//}
//
//class ForecastDisplay : public Observer
//{
//public:
//	ForecastDisplay(Subject *weatherData);
//	void Update(float temperatue, float humidity, float pressure);
//	void Display();
//private:
//	float currentPressure;
//	float lastPressure;
//	Subject *m_WeatherData;
//};
//
//ForecastDisplay::ForecastDisplay(Subject *weatherData) : m_WeatherData(weatherData)
//{
//	string strName = "ForecastDisplay";
//
//	weatherData->RegisterObserver("ForecastDisplay", this);
//}
//
//void ForecastDisplay::Update(float temperatur, float humidity, float pressure)
//{
//	lastPressure = currentPressure;
//	currentPressure = pressure;
//	Display();
//}
//
//void ForecastDisplay::Display()
//{
//	cout << "Forecast: ";
//	if (currentPressure > lastPressure)
//	{
//		cout << "Improving weather on the way!" << endl;
//	}
//	else if (currentPressure == lastPressure)
//	{
//		cout << "More of the same" << endl;
//	}
//	else
//	{
//		cout << "Watch out for cooler, rainy weather" << endl;
//	}
//}
//
//class HeatIndex : public Observer
//{
//public:
//	HeatIndex(Subject *weatherData);
//	void Update(float temperature, float humidity, float pressure);
//	void Display();
//private:
//	float m_Temperature;
//	float m_Humidity;
//	Subject *m_WeatherData;
//};
//
//HeatIndex::HeatIndex(Subject *weatherData) : m_WeatherData(weatherData)
//{
//	string strName = "HeatIndexDisplay";
//
//	weatherData->RegisterObserver("HeatIndexDisplay", this);
//}
//
//void HeatIndex::Update(float temperature, float humidity, float pressure)
//{
//	this->m_Temperature = temperature;
//	this->m_Humidity = humidity;
//	Display();
//}
//
//void HeatIndex::Display()
//{
//	double heatindex = 16.923 + 1.85212 * 0.1 * m_Temperature + 5.37941 * m_Humidity - 1.00255 * 0.1 * m_Temperature * m_Humidity
//		+ 9.41695 * 0.001 * m_Temperature * m_Temperature + 7.28898 * 0.001 * m_Humidity * m_Humidity + 3.45372 * 0.0001 * m_Temperature * m_Temperature * m_Humidity
//		- 8.14871 * 0.0001 * m_Temperature * m_Humidity * m_Humidity + 1.02102 * 0.00001 * m_Temperature * m_Temperature * m_Humidity * m_Humidity - 3.8646 * 0.00001 * m_Temperature * m_Temperature * m_Temperature
//		+ 2.91583 * 0.00001 * m_Humidity * m_Humidity * m_Humidity + 1.42721 * 0.000001 * m_Temperature * m_Temperature * m_Temperature * m_Humidity + 1.97483 * 0.0000001 * m_Temperature * m_Humidity * m_Humidity * m_Humidity
//		- 2.18429 * 0.00000001 * m_Temperature * m_Temperature * m_Temperature * m_Humidity * m_Humidity + 8.4396 * 0.0000000001 * m_Temperature * m_Temperature * m_Humidity * m_Humidity * m_Humidity - 4.81975 * 0.000000000001 * m_Temperature * m_Temperature * m_Temperature * m_Humidity * m_Humidity * m_Humidity;
//
//	cout << setprecision(20) << "heatindex = " << heatindex << endl;
//}
//
//void test()
//{
//	Subject *weatherData = new WeatherData();
//	Observer *currentDisplay = new CurrentConditionsDisplay(weatherData);
//	Observer *statisticsDisplay = new StatisticsDisplay(weatherData);
//	Observer *forecastDisplay = new ForecastDisplay(weatherData);
//	Observer *heatIndex = new HeatIndex(weatherData);
//
//	weatherData->SetMeasurements(80, 65, 30.4f);
//	weatherData->SetMeasurements(82, 70, 29.2f);
//	weatherData->SetMeasurements(78, 90, 29.2f);
//
//	delete weatherData;
//	weatherData = nullptr;
//}
//
//int main(int argc, char *argv[])
//{
//	test();
//	return 0;
//}

//#include <iostream>
//#include <memory>
//using namespace std;
//class A
//{
//public:
//	virtual ~A() {};
//};
//class B : public A
//{
//public:
//	B()
//	{
//		cout << "B" << endl;
//	}
//	~B()
//	{
//		cout << "~B" << endl;
//	}
//};
//
//void test()
//{
//	shared_ptr<A> ptr(new B);
//}
//
//int main(int argc, char *argv[])
//{
//	test();
//
//	return 0;
//}