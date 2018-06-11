#include <iostream>

using namespace std;

class Pizza
{
public:
	virtual void Prepare() = 0;
	virtual void Bake() = 0;
	virtual void Cut() = 0;
	virtual void Box() = 0;

private:

};

class CheesePizza : public Pizza
{
public:
	virtual void Prepare()
	{

	}

	virtual void Bake()
	{

	}

	virtual void Cut()
	{

	}

	virtual void Box()
	{

	}

};

class VeggiePizza : public Pizza
{
public:
	virtual void Prepare()
	{

	}

	virtual void Bake()
	{

	}

	virtual void Cut()
	{

	}

	virtual void Box()
	{

	}

};

class ClamPizza : public Pizza
{
public:
	virtual void Prepare()
	{

	}

	virtual void Bake()
	{

	}

	virtual void Cut()
	{

	}

	virtual void Box()
	{

	}
};

class PepperoniPizza : public Pizza
{
	virtual void Prepare()
	{

	}

	virtual void Bake()
	{

	}

	virtual void Cut()
	{

	}

	virtual void Box()
	{

	}
};

class SimplePizzaFactory
{
public:
	Pizza* CreatePizza(const string type);
};

Pizza* SimplePizzaFactory::CreatePizza(const string type)
{
	Pizza* pizza;
	if (type == "cheese")
	{
		pizza = new CheesePizza();
	}
	else if (type == "pepperoni")
	{
		pizza = new PepperoniPizza();
	}
	else if (type == "clam")
	{
		pizza = new ClamPizza();
	}
	else if (type == "veggie")
	{
		pizza = new VeggiePizza();
	}
	
	return pizza;
}

class PizzaStore
{
public:
	PizzaStore(SimplePizzaFactory factory) : m_Factory(factory)
	{}
	virtual Pizza* CreatePizza() = 0;
	virtual Pizza* OrderPizza(const string type);

private:
	SimplePizzaFactory m_Factory;
};

Pizza* PizzaStore::OrderPizza(const string type)
{
	Pizza *pizza;
	pizza = m_Factory.CreatePizza(type);
	pizza->Prepare();
	pizza->Bake();
	pizza->Cut();
	pizza->Box();
	return pizza;
}

class NYStylePizzaStore : public PizzaStore
{
public:
	Pizza* CreatePizza(const string type);
};

/*
Pizza* NYStylePizzaStore::CreatePizza(const string type)
{
	Pizza *pizza;
	if (type == "cheese")
	{
		pizza = new NyStypleCheesePize();
	}
	else if (type == "pepperoni")
	{
		pizza = new NyStyplePepperoniPizza();
	}
	else if (type == "clam")
	{
		pizza = new NYStyleclamPizza();
	}
	else if (type == "veggie")
	{
		pizza = new NYStyleVeggiePizza();
	}
}


class ChicagoStyplePizzaStore : public PizzaStore
{
	Pizza* CreatePizza(const string type);
};
Pizza* ChicagoSyplePizzaStore::CreatePizza(const string type)
{
	if (type == "cheese")
	{
		pizza = new ChicagoStyleCheesePizza();
	}
	else if (type == "pepperoni")
	{
		pizza = new ChicagoStyplePepperoniPizza();
	}
	else if (type == "clam")
	{
		pizza = new ChicagoStyleClamPizza();
	}
	else if (type == "veggie")
	{
		pizza = new ChicagoStyleVeggiePizza();
	}
}
*/