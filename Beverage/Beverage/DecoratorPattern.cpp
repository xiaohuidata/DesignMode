//#include <iostream>
//#include <string>
//#include <memory>
//
//using namespace std;
//
//class Beverage
//{
//public:
//	Beverage()
//	{
//		this->m_strDescription = "Unknown Beverage";
//	}
//	virtual string GetDescription();
//	virtual double Cost() = 0;
//protected:
//	string m_strDescription;
//};
//typedef shared_ptr<Beverage> BeveragePtr;
//
//string Beverage::GetDescription()
//{
//	return m_strDescription;
//}
//
///*class CondimentDecorator : public Beverage
//{
//public:
//	virtual string GetDescription();
//};
//string CondimentDecorator::GetDescription()
//{
//	return m_strDescription;
//}*/
//
//class Espresso : public Beverage
//{
//public:
//	Espresso()
//	{
//		m_strDescription = "Espresso";
//	}
//
//	double Cost();
//};
//
//double Espresso::Cost()
//{
//	return 1.99;
//}
//
//class HouseBlend : public Beverage
//{
//public:
//	HouseBlend()
//	{
//		m_strDescription = "Hose Blend Coffee";
//	}
//
//	double Cost();
//};
//
//double HouseBlend::Cost()
//{
//	return .89;
//}
//
//class DarkRoast : public Beverage
//{
//public:
//	DarkRoast()
//	{
//		m_strDescription = "Dark Roast Coffee";
//	}
//
//	double Cost();
//};
//
//double DarkRoast::Cost()
//{
//	return .99;
//}
//
//class Soy : public Beverage
//{
//public:
//	Soy(BeveragePtr beverage);
//	string GetDescription();
//	double Cost();
//private:
//	BeveragePtr m_ptrBeverage;
//};
//
//Soy::Soy(BeveragePtr beverage)
//{
//	this->m_ptrBeverage = beverage;
//}
//
//string Soy::GetDescription()
//{
//	return m_ptrBeverage->GetDescription() + ", Soy";
//}
//
//double Soy::Cost()
//{
//	return .15 + m_ptrBeverage->Cost();
//}
//
//class Mocha : public Beverage
//{
//public:
//	Mocha(BeveragePtr beverage);
//	string GetDescription();
//	double Cost();
//
//private:
//	BeveragePtr m_ptrBeverage;
//};
//
//Mocha::Mocha(BeveragePtr beverage)
//{
//	this->m_ptrBeverage = beverage;
//}
//
//string Mocha::GetDescription()
//{
//	return m_ptrBeverage->GetDescription() + ", Mocha";
//}
//
//double Mocha::Cost()
//{
//	return .20 + m_ptrBeverage->Cost();
//}
//
//class Whip : public Beverage
//{
//public:
//	Whip(BeveragePtr beverage);
//	string GetDescription();
//	double Cost();
//private:
//	BeveragePtr m_ptrBeverage;
//};
//
//Whip::Whip(BeveragePtr beverage)
//{
//	this->m_ptrBeverage = beverage;
//}
//
//string Whip::GetDescription()
//{
//	return m_ptrBeverage->GetDescription() + ", Whip";
//}
//
//double Whip::Cost()
//{
//	return .10 + m_ptrBeverage->Cost();
//}
//
//int main(int argc, char *argv[])
//{
//	BeveragePtr firstBeverage(new Espresso());
//	cout << firstBeverage->GetDescription() << " $" << firstBeverage->Cost() << endl;
//	
//	BeveragePtr secondBeverage(new DarkRoast());
//	BeveragePtr secondMocha(new Mocha(secondBeverage));
//	BeveragePtr secondWhip(new Whip(secondMocha));
//	cout << secondWhip->GetDescription() << " $" << secondWhip->Cost() << endl;
//
//	BeveragePtr thirdBeverage(new HouseBlend);
//	BeveragePtr soy(new Soy(thirdBeverage));
//	BeveragePtr mocha(new Mocha(soy));
//	BeveragePtr whip(new Whip(mocha));
//
//	cout << whip->GetDescription() << " $" << whip->Cost() << endl;
//	
//	return 0;
//}

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Beverage
{
public:
	Beverage()
	{
		this->m_strDescription = "Unknown Beverage";
	}
	virtual string GetDescription();
	virtual double Cost() = 0;
protected:
	string m_strDescription;
};
typedef shared_ptr<Beverage> BeveragePtr;

string Beverage::GetDescription()
{
	return m_strDescription;
}

class Espresso : public Beverage
{
public:
	Espresso()
	{
		m_strDescription = "Espresso";
	}

	double Cost();
};

double Espresso::Cost()
{
	return 1.99;
}

class HouseBlend : public Beverage
{
public:
	HouseBlend()
	{
		m_strDescription = "Hose Blend Coffee";
	}

	double Cost();
};

double HouseBlend::Cost()
{
	return .89;
}

class DarkRoast : public Beverage
{
public:
	DarkRoast()
	{
		m_strDescription = "Dark Roast Coffee";
	}

	double Cost();
};

double DarkRoast::Cost()
{
	return .99;
}

class Soy : public Beverage
{
public:
	Soy(Beverage *beverage);
	string GetDescription();
	double Cost();
private:
	Beverage *m_ptrBeverage;
};

Soy::Soy(Beverage *beverage)
{
	m_ptrBeverage = beverage;
}

string Soy::GetDescription()
{
	return m_ptrBeverage->GetDescription() + ", Soy";
}

double Soy::Cost()
{
	return .15 + m_ptrBeverage->Cost();
}

class Mocha : public Beverage
{
public:
	Mocha(Beverage *beverage);
	string GetDescription();
	double Cost();

private:
	Beverage *m_ptrBeverage;
};

Mocha::Mocha(Beverage *beverage)
{
	m_ptrBeverage = beverage;
}

string Mocha::GetDescription()
{
	return m_ptrBeverage->GetDescription() + ", Mocha";
}

double Mocha::Cost()
{
	return .20 + m_ptrBeverage->Cost();
}

class Whip : public Beverage
{
public:
	Whip(Beverage *beverage);
	string GetDescription();
	double Cost();
private:
	Beverage *m_ptrBeverage;
};

Whip::Whip(Beverage *beverage)
{
	m_ptrBeverage = beverage;
}

string Whip::GetDescription()
{
	return m_ptrBeverage->GetDescription() + ", Whip";
}

double Whip::Cost()
{
	return .10 + m_ptrBeverage->Cost();
}

int main(int argc, char *argv[])
{
	Beverage *firstBeverage = new Espresso();
	cout << firstBeverage->GetDescription() << " $" << firstBeverage->Cost() << endl;

	Beverage *secondBeverage = new DarkRoast();
	secondBeverage = new Mocha(secondBeverage);
	secondBeverage = new Whip(secondBeverage);
	cout << secondBeverage->GetDescription() << " $" << secondBeverage->Cost() << endl;

	Beverage *thirdBeverage = new HouseBlend();
	thirdBeverage = new Soy(thirdBeverage);
	thirdBeverage = new Mocha(thirdBeverage);
	thirdBeverage = new Whip(thirdBeverage);
	cout << thirdBeverage->GetDescription() << " $" << thirdBeverage->Cost() << endl;

	delete(firstBeverage);
	delete(secondBeverage);
	delete(thirdBeverage);

	return 0;
}