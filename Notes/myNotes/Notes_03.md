# Chapter 3 Notes
## P.5~9 protected & private
+ Class is used to encapsulate data.
+ Inheritance is used to expand class, to reuse the same base, ex. vehicle (engine, years ...), different types of vehicle could reuse the same base and then define their own data, truck (is a vehicle, weight), Bus (is a vehicle, capacity).
+ Protected is used to share data between base and derived class.
+ Polymorphism is used to provide a single interface for derived class to share, avoid the naming complexity. We could all use "start" to start a car and a plane, even though the staring procedure may differ.
+ Virtual is a keyword used to define the single interface in polymorphism and is effective when used with polymorphism.

## P.12 virtual function is effective only with polymorphism
+ common usage:
```
Base *p = new Derived;
p->virtualFunction();
```
```
f(Base &r){ r.virtualFunction(); }
Derived d;
f(d);
```
## P.27 Summary #1 keyword: virtual
+ Explicitly add virtual whenever applicable (readability)
+ The function definition in the inherited class can be omitted if base-class function is to be called.

## P.29 virtual destructor
+ without virtual destructor, Derive::~Derive will not be called when delete b1:
```C++=
#include <iostream>
using namespace std;

class Base{
public:
	Base(){ cout << "construct base\n"; }
	~Base(){ cout << "destruct base\n"; }
};


class Derive: public Base{
public:
	Derive(){ cout << "construct derive\n"; }
	~Derive(){ cout << "destruct derive\n"; }
};


int main()
{
	Base *b1 = new Derive;	// construct base, construct derive
	Base *b2 = new Base;	// construct base
	Derive *d = new Derive;	// construct base, construct derive

	delete b1;				// destruct base
	delete b2;				// destruct base
	delete d;				// destruct derive, destruct base
	return 0;
}
```
+ with virtual destructor
```C++=
#include <iostream>
using namespace std;

class Base{
public:
	Base(){ cout << "construct base\n"; }
	virtual ~Base(){ cout << "destruct base\n"; }
};


class Derive: public Base{
public:
	Derive(){ cout << "construct derive\n"; }
	~Derive(){ cout << "destruct derive\n"; }
};


int main()
{
	Base *b1 = new Derive;	// construct base, construct derive
	Base *b2 = new Base;	// construct base
	Derive *d = new Derive;	// construct base, construct derive

	delete b1;				// destruct derive, destruct base
	delete b2;				// destruct base
	delete d;				// destruct derive, destruct base
	return 0;
}
```
+ Base constructor will be called when creating derived instance is because derived instance will have inherited property of base class. The only way base class member can be properly initialized is through base constructor.
###### reference: [order of constructor call](https://www.studytonight.com/cpp/order-of-constructor-call.php)

## P.31~32 calling base constructor
```C++=
#include <iostream>
using namespace std;

class base{
public:
	base(int){}
	virtual ~base(){}
};

class derive : public base{
public:
	derive(int i):base(i){} // !!
	~derive(){}
};


int main()
{
	base *b1 = new base(10);
	base *b2 = new derive(20);
	delete b1;
	delete b2;
	return 0;
}
```
+ summary: Explicitly call base constructor, define virtual base destructor

## P.34~36 casting base class pointer to derived class

## P.37 access specifier in derived class
###### reference: [protected & privated inheritance](https://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance)

## P.38 struct in C++
+ A class that is intended to be publicly used

## function overloading
+ function overloading: different function prototype
+ polymorphism: identical function prototype, different namespace

## P.46 Function prototype when overloading operator
###### reference: [list of operator](https://en.cppreference.com/w/cpp/language/operators), [wiki](https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B), [overloading member access operators](https://stackoverflow.com/questions/8777845/overloading-member-access-operators-c)

## P.47
+ Return reference is useful when returning a class or struct object, could avoid unnecessary copy
+ Const object can only use const member function, but const member function could also be called by non-const object.

## P.53~54
+ "ostream& operator >>(ostream &)" is a member function of class ostream, thus we cannot make it a member function of our class.
+ we are able to overload it as a global function, "friend" it for access permission to the private data.

## Overloading resolution
###### reference: [why overloading is not ambiguous](https://www.geeksforgeeks.org/why-overriding-both-the-global-new-operator-and-the-class-specific-operator-is-not-ambiguous/), [overloading resolution](https://www.geeksforgeeks.org/why-overriding-both-the-global-new-operator-and-the-class-specific-operator-is-not-ambiguous/), [priority](https://stackoverflow.com/questions/25862633/c-why-member-function-has-priority-over-global-function), [why const reference](https://stackoverflow.com/questions/21485366/why-we-use-reference-return-in-assignment-operator-overloading-and-not-at-plus-m)

## P. 56~61 type casting operator overloading
```c++=
// ways to type-cast
int a = 69;
char c = a; // type-casting
cout << c << endl;	// E

cout << (char)a << endl;	// type-casting	// E
cout << char(a) << endl;	// type-casting	// E
see practice3-6
```
+ while(cin >> input)	// type casting
+ no return type because that would have another meaning than type cast operator
```
bool operator () (int, int) {}	// overload ()
operator bool () {}				// overload type-cast operator
these are different
```
###### reference: [user-defined conversion](https://en.cppreference.com/w/cpp/language/cast_operator), [type cast const vs non-const](https://stackoverflow.com/questions/2325121/casting-operator-const-vs-non-const), [overloading type-cast](https://www.learncpp.com/cpp-tutorial/910-overloading-typecasts/) 

## P.69~73 functional object
+ see practice 3-8
