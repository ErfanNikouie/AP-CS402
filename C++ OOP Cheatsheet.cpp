#include <iostream>
#include <vector>
using namespace std;

// Defining a class named 'Animal'
class Animal
{
private:

	/*
	* These variables cannot be public, because we do not want other classes to change these features of our animals.
	* We create getters and setters for these fields to prevent unfiltered access. 
	* This is called 'Encapsulation'. Our fields are 'encapsulated' in the class and only accessible through their getters and setters.
	*/

	string name; // The 'name' string of our animal.
	int hunger; // The 'hunger' integer of our animal.

public:

	#pragma region Constructors and Destructors

	/*
	* A constructor is "like" a function. It is called whenever the object is created. 
	* Its job is to set the default or desired values of our variables. It can also call other functions.
	*/ 

	// This is a default constructor.
	Animal() = default;

	// Another way to implement the default constructor. Using the 'default' keyword is shorter and more comprehensible.
	/* Animal() {} */ // IMPORTANT: This one should be commented out because we already have a default constructor.

	// Simple constructor with parameters.
	/* Animal(string const& name, int hunger) // IMPORTANT: This one should be commented out because we already have a constructor for these two parameters using initializer section (see below).
	{
		// Note: 'this' keyword is a pointer to the current object.
		this->name = name;
		this->hunger = hunger;
	}*/

	// This constructor uses an 'initializer section'. It sets the 'name' to 'name' and 'hunger' to 'hunger'. It needs an empty body ('{}') since we are intializing every variable.
	Animal(string const& name, int hunger) : name(name), hunger(hunger) {}

	// We can pass constructors to other constructors. Here we want to initialize our animal only by 'name' so we pass the default value for 'hunger' (0) to the other constructor.
	Animal(string const& name) : Animal(name, 0) {}


	/*
	* Destructors are like constructors, but they only get called when the object is getting destroyed.
	* One of its uses is to ensure every pointer created inside the class is deleted. (Arrays, dynamic arrays, ...)
	*/

	// We have not created any pointers in this class, so we just print something to the console.
	~Animal()
	{
		cout << "Animal('" << name << "') is deleted." << endl; // Example: "Animal('Cat') is deleted.";
	}

	#pragma endregion

	#pragma region Getters and Setters

	// This setter function updates the 'name' according to the new value.
	// Note 1: Using '&' is a pass-by-reference, it is faster to pass a reference of an 'string' object because 'string' is a big object.
	// Note 2: Using 'const' for 'value' means that it can never change in the function. 
	//         (Since we are passing a reference, if it does change in the function, it changes outside of it as well, so it can introduce bugs.)
	void setName(string const& value)
	{
		name = value;
	}


	// This getter function returns the 'name' of our animal.
	// Note: Using 'const' in front of a function means that the function cannot change any value of the object. 
	//		 For example, if we wanted to change the 'name' of our animal inside this function, it would produce an error.
	string getName() const
	{
		return name;
	}


	// This setter function changes the value of 'hunger' if the new value is valid.
	void setHunger(int value)
	{
		//Filtering the new value: (Checking if the new value is valid.)
		if (value < 0) // We do not want our hunger to be set to negative.
			return;

		hunger = value;
	}


	// If hunger is over 30, our animal is hungry.
	bool isHungry()
	{
		return hunger > 30;
	}

	#pragma endregion

	// Every time our animal eats, its hunger is reduced by 'value'.
	void eat(int value)
	{
		if (!isHungry())
		{
			cout << "Animal('" << name << "') is not hungry." << endl; // Example: "Animal('Cat') is not hungry.";
		}

		cout << "Animal('" << name << "') is eating." << endl; // Example: "Animal('Cat') is eating."
		hunger -= value; // Reduce hunger by 'value'.

		if (hunger < 0) // We don't want our hunger value to be negative.
			hunger = 0;
	}
};



/*
* We use inheritance when we have a common behaviour between classes. 
* For example, 'Cat' is a kind of 'Animal', so it makes sense for 'Cat' to inherit all the features (variables and functions) of 'Animal'.
* Note 1: 'public' inheritance does not change the accessibility of our attributes, meaning, our 'protected' attributes stay 'protected', and our 'public' attributes stay 'public'.
* Note 2: 'private' attributes are never accessible (but still exist) in derived classes (classes that inherit from another class).
*		  For Example: 'Cat' has 'name' and 'hunger' but cannot directly access them.
*/

class Cat : public Animal
{

	// 'protected' is like 'private', not accessible from outside, but derived classes can directly access these attributes.
protected:
	string race;

public:
	void setRace(string const& race)
	{
		this->race = race;
	}

	string getRace() const
	{
		return race;
	}
	
	/*
	* Overriding and redefining are different.
	* In overriding when we have a pointer to a base class type, calling a virtual function, automatically calls the overridden function in the lowest derived class.
	* Redefining, on the other hand, when we have a pointer to a base class, by calling the function, the function on the base class gets called.
	* 
	* For example:
	* Imagine we have an object of the type 'Cat'. We create an 'Animal*' and set it to the address of our object.
	* Now, if we call 'eat(int)' on the 'Animal*', it calls the 'eat(int)' function on 'Animal', because the function is not virtual.
	* But if it were marked as 'virtual' and it was overridden in 'Cat', it would have called 'eat(int)' on 'Cat'.
	*/

	// Here we are redefining eat. Because the 'eat(int)' function in 'Animal' is not a virtual function, when we define eat again, it does not count as an override.
	void eat(int value)
	{
		// We use '::' (called the scope resolution operator) to determine the scope. For example, the line below calls 'eat(value)' on 'Animal'.
		Animal::eat(value);
		cout << "Cat('" << getName() << "') has finished eating." << endl;
	}

	// 'vitrual' functions can be overriden in derived classes.
	virtual void Meow()
	{
		// Note: we cannot directly access name, so we use its public getter.
		cout << "Cat('" << getName() << "') says meow." << endl;
	}
};

int main()
{
	// Creating objects:

	// Using default constructor:
	Animal defaultAnimal1;
	Animal defaultAnimal2 = Animal();
	Animal* defaultAnimalPtr = new Animal(); // Note: we use 'new' to create pointers of objects.

	// Using a constructor with parameters:
	Animal animal1 = Animal("Cat", 0);

	// Using a constructor with only one parameter:
	Animal animal2 = Animal("Cat");
	

	// When an object goes out of scope, it gets destroyed automatically (unless it is a pointer) and its destructor is called. Nevertheless we can manually call destructors like this:
	Animal animal("Cat", 0);
	animal.~Animal();


	// Calling functions on objects:
	animal.setName("My Cat"); // Set 'name' to 'My Cat'.

	animal.eat(10); // Output: "Animal('My Cat') is not hungry." 
	animal.setHunger(50); // Set 'hunger' to '50'
	animal.eat(10); // Output: "Animal('My Cat') is eating." 


	return 0;
}