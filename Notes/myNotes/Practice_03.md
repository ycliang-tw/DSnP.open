# Practice_03
## Practice 1
```c++=
#include <iostream>
using namespace std;

class Base{
public:
	virtual void f(){cout << "base f\n";}
	void g(){cout << "base g\n";}
};
/*
class Base{
public:
	void f(){cout << "base f\n";}
	void g(){cout << "base g\n";}
};
*/
class Derive : public Base{
public:
	void f(){cout << "derived f\n";}
	void g(){cout << "derived g\n";}
};
/*
class Derive{
public:
	void f(){cout << "derived f\n";}
	void g(){cout << "derived g\n";}
};
*/
int main()
{
	Base a;
	Derive b;
	a.f();	// base f
	a.g();	// base g
	b.f();	// derived f
	b.g();	// derived g
	return 0;
}
```
+ virtual does nothing and the outputs of every combination are the same.

## Practice 2
```c++=
#include <iostream>
using namespace std;

class Base{
public:
	virtual void f(){cout << "base f\n";}
	void g(){cout << "base g\n";}
	virtual void h(){cout << "base h\n";}
};

class Derive:public Base{
public:
	void f(){cout << "derived f\n";}
	void g(){cout << "derived g\n";}
//	void h(){cout << "derived h\n";}
};

int main()
{
	Base *b = new Base;
	Base *bd = new Derive;
	Derive *d = new Derive;
//	Derive *db = new Base;	// compilation error

	b->f();	// base f
	b->g();	// base g
	b->h();	// base h
	
	bd->f();// derived f
	bd->g();// base g
	bd->h();// base h
	
	d->f();	// derived f
	d->g();	// derived g
	d->h();	// base h

	return 0;
}
```

## Practice 4
```c++=
#include <iostream>
using namespace std;

class A{
	int real, imag;
public:
	A(int r, int i):real(r), imag(i){}
	
	A operator + (const A& a) const;
	A operator - (const A& a) { this->real -= a.real; this->imag -= a.imag; return *this; }
	A operator * (const A& a) { 
		this->real = this->real*a.real - this->imag*a.imag; 
		this->imag = this->imag*a.real + this->real*a.imag; 
		return *this; 
	}

	A& operator = (const A& a) { this->real - a.real; this->imag - a.imag; return *this; }

	A& operator [] (int i) { return *this; }



	friend ostream& operator << (ostream&, const A&);
};

A A::operator + (const A &a) const 
{
/*
	this->real += a.real;
	this->imag += a.imag;
	return *this;
*/
/*
	A b(this->real, this->imag);
	b.real += a.real;
	b.imag += a.imag;
	return b;
*/
	return A(real+a.real, imag+a.imag);
}

ostream& operator<<(ostream& os, const A& a)
{
	os << "real: " << a.real << ", imag: " << a.imag << endl;
	return os;
}

int main()
{
	A a(10, 10), b(20, 20), c(30, 30);
	cout << a << b << c;
	cout << a+b+c << a-b*c;
	a = c;
	cout << a;
	cout << a[0];
//	cout << ~a << a&b << a | c;
//	cout << a+=b << a-=c << a*=b;
//	cout << a == b << a != c << a <=c;
//	cout << a++ << ++a << ++a * c;
	return 0;
}
```

## Practice 5 
```c++=
#include <iostream>
using namespace std;

template<class T> class Array{
	T *_data;
public:
	Array(size_t i = 0) { _data = new T[i]; }
	T& operator [] (size_t i) { return _data[i]; }
	const T& operator [] (size_t i) const{ return _data[i]; }
};

template<class T>
void f(const Array<T>& arr)
{
	//arr[1] = 20;
	int a = arr[0];
	a = 20;
}

int main()
{
	const Array<int> arr(10);
	cout << arr[0] << endl;
	Array<int> arr1(10);
	f(arr1);
//	arr[1] = 20;
	return 0;
}
```

## Practice 6
```c++=
#include <iostream>
using namespace std;


class B{
	int *ptr;
public:
	B(int *p): ptr(p){}
};

class A{
	mutable int _data;
public:
	A(int i =0): _data(i){}
	operator int () const { return _data; }
	operator bool() const { return _data!=0; }
	operator B() const { return &_data; }
};



int main()
{
	A a(20);
	cout << static_cast<int>(a) << endl;
	cout << bool(a) << endl;
	B b(B(a));
	return 0;
}
```

## Practice 7
```c++=
#include <iostream>
using namespace std;

class A{
public:
	int a;
	A(int i = 0):a(i) {}
	A operator + (const A& x){
		cout << "A::+\n";
		return A(a+x.a);
	}

	friend ostream& operator <<(ostream &os, const A& x){
		os << x.a << endl;
		return os;
	}
};

A operator + (const A &x, const A &b)
{	
	cout << "global+\n";
	return A(x.a+b.a);
}

int main()
{
	A a(10), b(20);
	cout << a+b;
	cout << ::operator+(a,b);
	return 0;
}
```
+ change the behavior of operator "+" to "-" produce no error. Be intuitive when overloading operators to avoid unexpected or run-time error.

## Practice 8
+ compilation error is because Compare is pure virtual, so the sort inside f would not have a match for "sort( , , compare cmp)"
```c++=
#include <iostream>
#include <algorithm>
using namespace std;

struct Compare{
	virtual bool operator () (int, int) const = 0;
//	virtual bool operator () (int i, int j){ return i < j;}// const = 0;
};

struct Less : public Compare{
	bool operator () (int i, int j) const { return (i < j); }
};

struct Greater: public Compare{
	bool operator () (int i, int j) const { return (i > j); }
};

void f(const Compare &c)
{
	int arr[10] = {4,2,6,7,1,3,5,9,8,0};
	::sort<int*>(arr+0, arr+10, c);
	for(int i = 0; i < 10; i++){
		cout << arr[i] << endl;
	}
}

int main()
{	
	f(Less());
	f(Greater());
	return 0;
}

// compilation error: no matching sort(int [10], int*, Compare)
// could compile if modify the pure virtual function but not as expected.
// because f would cast sent obj to Compare and thus do the Compare::().
```
