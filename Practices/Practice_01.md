# Practice_01
## 9. Initialization List
```
#include <iostream>
using namespace std;

class B{
public:
	B(int val = 10){cout << "constructor B\n"; _bd = val;}
	int getB(){return _bd;}
private:
	int _bd;
};

class A{
public:
	A(int val = 20, int valB = 10):_b(valB){cout << "constructor A\n"; _ad = val;}
	int getA(){return _ad;}
	int getB(){return _b.getB();}
private:
	int _ad;
	B	_b;
};

int main()
{
	A a(30,40);
	cout << a.getB() << endl;
	cout << a.getA() << endl;
	return 0;
}
```
