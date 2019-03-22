// Ai Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

// Toppings
string pep = "pepperoni";
string hamburg = "hamburger";
string shrcheese = "shredded cheese";

//None
string none = "no";

// Sauce
string tom = "tomato";
string cheese = "cheese";

//Dough
string pbak = "pan baked";
string stufcrus = "stuffed crust";

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
	 ~ClassicPizzaBuilder() {}; //You can change this and the ingredients if you want in the code. But regardless its a normal pizza

	void buildDough()
	{
		m_pizza->setDough(pbak);
	}
	void buildSauce()
	{
		m_pizza->setSauce(tom);
	}
	void buildTopping()
	{
		m_pizza->setTopping(pep);
	}
};

int q1response;
int q2response;
int q3response;

int PizzaQs() {
	cout << "Do you want a regular pizza? (yes = 0 / no = 1)" << endl; // Q1
	cin >> q1response;
	if (q1response == 1) {
		cout << "Do you want sauce? (1 = tomato/ 2 = cheese / none = 0)" << endl; // Q2
		cin >> q2response;
		cout << "What type of dough would you want? (1 - pan baked / 2 - stuffed crust)" << endl; // Q3
		cin >> q3response;
	}
	else {
		cout << "You got it..." << endl;
	}
	
	return 0;
}

class YourPizzaBuilder : public PizzaBuilder
{
public:
	virtual ~YourPizzaBuilder() {};

	void buildDough() {
		if (q1response == 0) {
			m_pizza->setDough(pbak);
		}
		else if (q1response == 1) {
			m_pizza->setDough(stufcrus);
		}
	}

	void buildSauce() {
		if (q1response == 0) {
			m_pizza->setSauce(tom);
		}
		else if (q1response == 1) {
			if (q2response == 0) {
				m_pizza->setSauce(none);
			}
			else if (q2response == 1) {
				m_pizza->setSauce(tom);
			}
			else if (q2response == 2) {
				m_pizza->setSauce(cheese);
			}
		}
	}

	void buildTopping() {
		if (q1response == 0) {
			m_pizza->setTopping(pep);
		}
		else if (q1response == 1) {
			m_pizza->setTopping(shrcheese);
		}
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
	YourPizzaBuilder YourPizzaBuilder;

	cook.makePizza(&ClassicPizzaBuilder);
	cook.openPizza();
	PizzaQs();
	cook.makePizza(&YourPizzaBuilder);
	cook.openPizza();
}