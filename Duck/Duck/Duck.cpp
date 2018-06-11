#include <iostream>

using namespace std;

class FlyBehavior
{
public:
	virtual void Fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
	virtual void Fly();
};

void FlyWithWings::Fly()
{
	cout << "we are Fly!" << endl;
}

class FlyNoWay : public FlyBehavior
{
public:
	virtual void Fly();
};

void FlyNoWay::Fly()
{
	cout << "I can't fly!" << endl;
}

class FlyRocketPowered : public FlyBehavior
{
public:
	virtual void Fly();
};

void FlyRocketPowered::Fly()
{
	cout << "I'm Flying whith a rocket!" << endl;
}

class QuackBehavior
{
public:
	virtual void Quack() = 0;
};

class Qquack : public QuackBehavior
{
public:
	virtual void Quack();
};

void Qquack::Quack()
{
	cout << "gua gua quack!" << endl;
}

class Squeak : public QuackBehavior
{
public:
	virtual void Quack();
};

void Squeak::Quack()
{
	cout << "zhi zhi quack!" << endl;
}

class MuteQuack : public QuackBehavior
{
public:
	virtual void Quack();
};

void MuteQuack::Quack()
{
	cout << "can't quack!" << endl;
}

class Duck
{
public:
	Duck() {};
	virtual ~Duck()
	{
		delete flyBehavior;
		delete quackBehavior;
		cout << "~Duck" << endl;
	};
	virtual void Swim();
	void DisPlay();
	void PerformQuack();
	void PerformFly();
	void SetFlyBehavior(FlyBehavior *fb);
	void SetQuackBehavior(QuackBehavior *qb);
	void DeletePtr();

protected:
	FlyBehavior *flyBehavior;
	QuackBehavior *quackBehavior;
};

void Duck::Swim()
{
	cout << "I can Swimming." << endl;
}

void Duck::DisPlay()
{
	cout << "I'm a fun Duck." << endl;
}

void Duck::PerformQuack()
{
	quackBehavior->Quack();
}

void Duck::PerformFly()
{
	flyBehavior->Fly();
}

void Duck::SetFlyBehavior(FlyBehavior *fb)
{
	flyBehavior = fb;
}

void Duck::SetQuackBehavior(QuackBehavior *qb)
{
	quackBehavior = qb;
}

void Duck::DeletePtr()
{
	cout << "~" << endl;
}

class MallardDuck : public Duck
{
public:
	MallardDuck();
	~MallardDuck()
	{
		DeletePtr();
	};

	virtual void DisPlay();
};

MallardDuck::MallardDuck()
{
	quackBehavior = new Qquack();
	flyBehavior = new FlyWithWings();
}

void MallardDuck::DisPlay()
{
	cout << "I'm a real Mallard duck" << endl;
}

class ModelDuck : public Duck
{
public:
	ModelDuck();
	~ModelDuck()
	{
		DeletePtr();
	};

	virtual void DisPlay();
};

ModelDuck::ModelDuck()
{
	flyBehavior = new FlyNoWay();
	quackBehavior = new Qquack();
}

void ModelDuck::DisPlay()
{
	cout << "I'm amodel duck!" << endl;
}

void duck()
{
	Duck *mallard = new MallardDuck();
	mallard->PerformQuack();
	mallard->PerformFly();

	Duck *model = new ModelDuck();
	model->PerformFly();
	model->SetFlyBehavior(new FlyRocketPowered());
	model->PerformFly();

	delete mallard;
	delete model;

	MallardDuck mal;
	mal.PerformFly();
}

int main(int argc, char *argv[])
{
	duck();

	return 0;
}