#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Dough
{

};

class ThinCrustDough : public Dough
{

};

class Sauce
{

};

class MarinaraSauce : public Sauce
{

};

class Cheese
{

};

class ReggianoCheese : public Cheese
{

};

class Veggies
{

};

class Garlic : public Veggies
{

};

class Onion : public Veggies
{

};

class Mushroom : public Veggies
{

};

class RedPepper : public Veggies
{

};

class Pepperoni
{

};

class SlicedPepperoni : public Pepperoni
{

};

class Clams
{

};

class FreshClams : public Clams
{

};

class PizzaIngredientFactory
{
public:
	virtual Dough* CreateDough() = 0;
	virtual Sauce* CreateSauce() = 0;
	virtual Cheese* CreateCheese() = 0;
	virtual vector<Veggies*> CreateVeggies() = 0;
	virtual Pepperoni* CreatePepperoni() = 0;
	virtual Clams* CreateClam() = 0;
};


class NYPizzaIngredientFactor : public PizzaIngredientFactory
{
public:

	Dough* CreateDough()
	{

		return new ThinCrustDough();
	}

	Sauce* CreateSauce()
	{
		return new MarinaraSauce();
	}

	Cheese* CreateCheese()
	{
		return new ReggianoCheese();
	}

	vector<Veggies *> CreateVeggies()
	{
		vector<Veggies*> vec = { new Garlic(), new Onion(), new Mushroom(), new RedPepper() };
		return vec;
	}

	Pepperoni* CreatePepperoni()
	{
		return new SlicedPepperoni();
	}

	Clams* CreateClam()
	{
		return new FreshClams;
	}
};

class Pizza
{
public:

	~Pizza()
	{
		delete m_dough;
		delete m_sauce;
		for (auto it : m_veggies)
			delete it;
		delete m_cheese;
		delete m_pepperoni;
		delete m_clams;
	}

	virtual void Prepare() = 0;

	virtual void Bake()
	{
		cout << "Bake for 25 minutes at 350" << endl;
	}

	virtual void Cut()
	{
		cout << "Cutting the pizza into diagonal slices" << endl;
	}

	virtual void Box()
	{
		cout << "Place pizza in official PizzaStore box" << endl;
	}

	void SetName(string name)
	{
		m_name = name;
	}

	string GetName()
	{
		return m_name;
	}

	string ToString()
	{
		string str = "Pizza name is " + m_name;
		cout << "Pizza name is " << m_name << endl;
		return str;
	}

protected:
	string m_name;
	Dough* m_dough;
	Sauce* m_sauce;
	vector<Veggies*> m_veggies;
	Cheese* m_cheese;
	Pepperoni* m_pepperoni;
	Clams* m_clams;

};

class CheesePizza : public Pizza
{
public:
	CheesePizza(PizzaIngredientFactory * ingredientFactor)
	{
		m_ingredientFactory = ingredientFactor;
	}

	void Prepare()
	{
		cout << "Preparing " << m_name << endl;
		m_dough = m_ingredientFactory->CreateDough();
		m_sauce = m_ingredientFactory->CreateSauce();
		m_cheese = m_ingredientFactory->CreateCheese();
	}

private:
	PizzaIngredientFactory* m_ingredientFactory;
};

class ClamPizza : public Pizza
{
public:
	ClamPizza(PizzaIngredientFactory * ingredientFactor)
	{
		m_ingredientFactory = ingredientFactor;
	}

	void Prepare()
	{
		cout << "Preparing " << m_name << endl;
		m_dough = m_ingredientFactory->CreateDough();
		m_sauce = m_ingredientFactory->CreateSauce();
		m_cheese = m_ingredientFactory->CreateCheese();
	}

private:
	PizzaIngredientFactory* m_ingredientFactory;
};

class PizzaStore
{

public:
	virtual Pizza* CreatePizza(string item) = 0;
};

class NYPizzaStore : public PizzaStore
{

public:
	Pizza* CreatePizza(string item)
	{
		Pizza* pizza = NULL;
		PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactor();

		if (item == "cheese")
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->SetName("New York Style Cheese Pizza");
		}
		else if (item == "veggie")
		{

		}
		else if (item == "clam")
		{
			pizza = new ClamPizza(ingredientFactory);
			pizza->SetName("New York Style Clam Pizza");
		}
		else if (item == "pepperoni")
		{

		}
		return pizza;
	}
};