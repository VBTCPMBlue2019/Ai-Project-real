// Ai Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <memory>
using namespace std;

//part 1
class Pizza
{
public:
	void setDough(const string& dough) // setting all the details about the pizza and making them constant strings
	{
		m_dough = dough;
	}
	void setSauce(const string& sauce)
	{
		m_sauce = sauce;
	}
	void setTopping(const string& topping)
	{
		m_topping = topping;
	}
	void open() const
	{
		cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and "
			<< m_topping << " topping. " << endl;
	}
private:

	string m_dough;
	string m_sauce;
	string m_topping;
};


class PizzaBuilder
{
public:
	virtual ~PizzaBuilder() {}; // setting a function member used for an object and execute other class's version of the function

	Pizza* getPizza()
	{
		return m_pizza.release();
	}
	void createNewPizzaProduct()
	{
		m_pizza = make_unique<Pizza>();
	}
	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTopping() = 0;
protected:
	unique_ptr<Pizza> m_pizza;
};

//----------------------------------------------------------------

//Part 2
class ClassicPizzaBuilder : public PizzaBuilder
{
public:
	virtual ~ClassicPizzaBuilder() {}; //You can change this and the ingredients if you want in the code. But regardless its a normal pizza

	virtual void buildDough()
	{
		m_pizza->setDough("pan baked");
	}
	virtual void buildSauce()
	{
		m_pizza->setSauce("tomato");
	}
	virtual void buildTopping()
	{
		m_pizza->setTopping("pepperoni");
	}
};

class YourPizzaBuilder : public PizzaBuilder
{
public:
	virtual ~YourPizzaBuilder() {};

	//Add questions to ask in the console and after all questions are answered make the pizza based off the questions.
	//This is the AI ^


	virtual void buildDough()
	{
		m_pizza->setDough("");
	}
	virtual void buildSauce()
	{
		m_pizza->setSauce("");
	}
	virtual void buildTopping()
	{
		m_pizza->setTopping("");
	}
};

//----------------------------------------------------------------
 // this next part is where it inserts all the info you put into the console and output it all
// Part 3
class Cook
{
public:
	void openPizza()
	{
		m_pizzaBuilder->getPizza()->open();
	}
	void makePizza(PizzaBuilder* pb)
	{
		m_pizzaBuilder = pb;
		m_pizzaBuilder->createNewPizzaProduct();
		m_pizzaBuilder->buildDough();
		m_pizzaBuilder->buildSauce();
		m_pizzaBuilder->buildTopping();
	}
private:
	PizzaBuilder* m_pizzaBuilder;
};

int main()
{
	Cook cook;
	ClassicPizzaBuilder ClassicPizzaBuilder;
	YourPizzaBuilder  YourPizzaBuilder;

	cook.makePizza(&ClassicPizzaBuilder);
	cook.openPizza();

	cook.makePizza(&YourPizzaBuilder);
	cook.openPizza();
}