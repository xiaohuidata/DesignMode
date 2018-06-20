#include <iostream>
#include <thread>
#include <mutex>

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (uniqueInstance == nullptr)
		{
			uniqueInstance = new Singleton();
		}
		return uniqueInstance;
	}
private:
	Singleton() {}
	static Singleton* uniqueInstance;
};

/*
class StaticSingleton 
{
public:

	static StaticSingleton* uniqueInstance = new StaticSingleton();

	static StaticSingleton* getInstance() {
		return uniqueInstance;
	}
private:
	StaticSingleton();
};
*/

class SingletonS
{
public:
	static SingletonS* GetInstance()
	{
		if (uniqueInstance == nullptr)
		{
			mt.lock();
			if (uniqueInstance == nullptr)
			{
				uniqueInstance = new SingletonS();
			}
			mt.unlock();
		}
		return uniqueInstance;
	}

private:
	static std::mutex mt;
	static SingletonS* uniqueInstance;

	SingletonS();
};