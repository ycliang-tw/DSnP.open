# Chapter 1 Notes
## P.29 Share vs. Alias
My opinion is that reference(alias) is created for syntax tidiness,
with referece we will not ever need to deal with dereference and pointer to manipulate data; (for example, a swap function ...etc.)
otherwise we would need a whole lot of these operators to have the same effect.
That makes the code more intuitive and clean.

With that being said, it has its limit as well, so we cannot rely everything on referece.
Below are some differeces listed between pointer and reference:
1. A reference must be initialized; A pointer doesn\'t
2. A reference cannot be reassigned; A pointer can
3. A reference cannot be NULL; A pointer can
... etc.

+ [reference pointer differences stackoverflow](https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in)
+ [reference pointer differences](https://www.educba.com/c-plus-plus-reference-vs-pointer/)

```c++=
// swap with pointer
void swap_with_pointer(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_with_referece(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int a = 10, b = 20
	swap_with_pointer(&a, &b);
	swap_with_reference(a, b);
	return 0;
}
```

## P.39 Customized Copy Constructors

```
// test.cpp
class B{
public:
	B(){a = 10;}
	B(const B &b){
		a = b.a + 10;
	}
	int a;
};

class A{
public:
	A(){}
	A(const A &a){}
	B _b;
};


int main()
{
	B b1;
	cout << b1.a << endl;	// 10
	B b2 = b1;
	cout << b2.a << endl;	// 20
	
	A a1;
	cout << a1._b.a << endl;//10
	A a2 = a1;
	cout << a2._b.a << endl;//10
	return 0;
}
```
+ No, the copy constructor for B will not be executed when A's copy constructor is called. (see the above example test.cpp)
+ Didn't think of any elegant solution right now. All I can think of is something like below
```
class B{
	copy(const B &b)
};
class A{
public:
	A(const A &a){
		B c = a._b;
		_b.copy(c);
	}
};
```

## P.42 Careful with pointer data member 
```
class A {
	B _b;
	C *_c;
	A(){ ...; _c = new C; ...}
	~A(){ ...; delete _c; ...}
}
A a1, a2;
// do something on a1
a2 = a1; // copy a1 to a2
```
+ The program will crash when exits because there will be a double free on the memory allocated in a1.
+ The memory leak will happen in the allocated memory in a2 which will not be freed when program exits.

## P.44 Calling Constructors
+ When constructor of a class object is called, the constructors of its data members will be recusively called.
```
class A{};
class B{};
class C{
	A _a;
	B _b;
};
C c1; // before C's constructor is called, A and B's constructors will be called first.
```

## P.45 Memory and constructor
+ `new` will allocate memory and then call the constructor while `malloc`(..etc) will only allocate memory, so constructor is not called.
	+ [What happens to class members when malloc is used instead of new?](https://stackoverflow.com/questions/2914209/what-happens-to-class-members-when-malloc-is-used-instead-of-new)
		+ This discussion concludes that malloc is still valid with class in c++ in some situation, only that there is something else should be done. (have not tested it myself, think I will just stay with new and delete until the situation that needs malloc pops up)

## P.53 See how constructors/destructors are called
+ problem 2: I think there is no difference. (p.46 has some reference)

## P.58~60 "friends" between classes
```
class MyClass{
	friend class OtherClass;
	// this line indicates that OtherClass can access MyClass' private data member.
	// "friendship is granted, not taken"
}
```


