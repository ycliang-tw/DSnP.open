# Chapter 2 Notes
## P.28 "Mutable"
###### reference: [c++ mutable](https://liam.page/2017/05/25/the-mutable-keyword-in-Cxx/)

## P.31 The address of array
```c++=
int arr[5] = {};
int *p = new int[5];
cout << arr << endl;		// 0x7ffd0edbe080
cout << &arr << endl;		// 0x7ffd0edbe080
cout << &arr[0] << endl;	// 0x7ffd0edbe080
cout << p << endl;			// 0x1f88010
cout << &p << endl;			// 0x7ffd0edbe078	
cout << &p[0] << endl;		// 0x1f88010
```
retrospect: memory layout:
                                      example of the above code:
	--------------- high address       |-------stack--------|
	|             |                    | ( 10 * sizeof(int) |
	|    stack    |                    | 0x7ffd0edbe080 (a) |
	|-------------| stack top          | 0x7ffd0edbe078 (p) |--
	|             |                    |--------------------| |
	|             |                    |                    | |
	|-------------|                    |--------------------| |
	|             |                    |       p array      |<-
	|    heap     |                    |                    |
	|-------------|                    |--------------------|
	|             |                    |                    |
	|             |                    |                    |
	|-------------| low address        |--------------------|

## P.40 When is "return by reference" useful?
return by reference can be useful when return a struct or object,
it will save the time of copying if return by value is used.
+ Why not "Array<int> arr2 = arr;"
> this will invoke copy constructor which isn't explicit defined in this example, thus result in shallow copy.
> when there's pointer type or dynamically  allocated space in class member, shallow copy will cause all kinds of trouble.
###### reference: [when does a function have to return a reference](https://stackoverflow.com/questions/18064371/when-does-a-function-have-to-return-a-reference-in-c)

## P.63 Anonymous union
```c++=
#include <iostream>
using namespace std;

// ananymous union 
class A{
private:
	union {
		int _a;
		char _b;
	};

	int _i;
	int _j;
public:
	A(int a = 10, char b = 'b'){
		_i = a;
		_b = b;
	}

	int getA() const { return _a; }
	char getB() const{ return _b; }
	int getI() const { return _i; }
};

/*	named union
// have to create an instance
class A{
private:
	union B{
		int _a;
		char _b;
	}B;

	int _i;
	int _j;
public:
	A(int a = 10, char b = 'b'){
		_i = a;
		B._b = b;
	}

	int getA() const { return B._a; }
	char getB() const{ return B._b; }
	int getI() const { return _i; }
};
*/
int main()
{
	A a;
	cout << a.getB() << endl;
	cout << a.getI() << endl;
	return 0;
}
```
###### reference: [named union](https://stackoverflow.com/questions/19222914/why-does-named-union-inside-struct-overwriting-other-struct-members)


## P.64 Memory alignment
Memory alignment is to increase memory transaction throughput!
To achieve aligned memory layout, there could be padding added between class or struct members in compile time.
This can be examined by code below:
```c++=
// 64-bit machine
class A{	
	char a; // 1 byte, 3 padded byte
	int b;	// 4 byte
	char c;	// 1 byte, 3 padded byte
	int d;	// 4 byte
};
// sizeof() is a built-in operator
int main(){cout << sizeof(A) << endl;}

$> g++ -c test.cpp -o test.o
$> objdump -d test.o | less
the exact numeric form: 16 byte(0x10) of memory size of class A will show in assembly code.
```
The amount of padding added is determined by the largest data type.
```c++=
// sizeof(A) == 1
class A {
	char a;	// 1 byte
};		
// sizeof(B) == 8
class B {
	char a; // 1 byte, 3 padded byte (due to "sizeof(int) == 4")
	int b;	// 4 byte
};
// sizeof(C) == 16
class C {
	char a;	// 1 byte, 7 padded byte (sizeof(pointer) == 8)
	int *b;	// 8 byte
};
// sizeof(D) == 24
class D {
	char a;	// 1 byte, 7 padded byte (sizeof(pointer) == 8)
	char *b;// 8 byte
	bool c;	// 1 byte, 7 paaded byte (sizeof(pointer) == 8)
};
// sizeof(E) == 16
class E {
	char a;	// 1 byte
	bool b;	// 1 byte
			// 6 padded byte (sizeof(pointer) == 8)
	bool*c;	// 8 byte
};
```
There are also "Bit field" & "pragma(pack)" to manipulate the size of a object type.
#### reference:
+ [memory alignment](https://hackmd.io/@sysprog/c-memory?type=view)
+ [Bit Field](https://en.cppreference.com/w/cpp/language/bit_field)

## P.72 will not produce 'compile error' on my machine.

