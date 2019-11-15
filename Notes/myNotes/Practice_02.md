# Practice_02
## 3.
```
#include <iostream>
using namespace std;

class A{
public:
	A(int val = 10){_d = val;}
	A f(){ this->_d = this->_d+10; return (*this);}
	void p() const {cout << _d << endl;}
private:
	int _d;
};

int main()
{
	const A a(10);
	//a.f();
	A(a).f().p();
	a.p();
	(const_cast<A *>(&a)->f()).p();
	a.p();
	return 0;
}
```
## 5. Include Guard
```
a.
#if !defined(<header>)
#define (<header>)
#endif

b. (depends on compiler)
#pragma once
```

## 6.
something like this:
```
#include <iostream>
using namespace std;

class N{
public:
	N(void *p): _p(p){}
	void setMark(){
		_p = (void*)((uintptr_t)_p | 0x1);
	}
	bool checkMark() const{
		return (uintptr_t)_p & 0x1;
	}
	void unset(){
		_p = (void*)((uintptr_t)_p & 0x0);
	}
private:
	void *_p;
};

int main()
{
	int arr[10] = {1, 2, 3, 4, 5,
				   6, 7, 8, 9, 10};
	N n1(&arr[5]);
	n1.setMark();
	cout << n1.checkMark() << endl;
	n1.unset();
	cout << n1.checkMark() << endl;
	

	return 0;
}
```

## 8.
something like this (?
```
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#define MAX_DEPTH	5
#define maxRef	999999
using namespace std;

class N_;
class N {
	N_ *_n;
public:
	N():_n(0) {}
	void gen();
	void statistics() const;
};

class N_ {
	friend class N;
	size_t		_d[1<<17];	// 1MB
	unsigned 	_refCnt;
	N			_child1;
	N			_child2;
	N_(): _refCnt(0) {}
};

N_* nList[1<<MAX_DEPTH] = {0};

void N::gen()
{
	assert(_n == 0);
	int i = rand()%(1<<MAX_DEPTH);
	if(nList[i] == 0){
		N_ *tmp = new N_;
		tmp->_refCnt++;
		nList[i] = tmp;
		tmp = 0;
		nList[i]->_child1.gen();
		nList[i]->_child2.gen();
	}else{
		_n = nList[i];
		_n->_refCnt++;
	}
}

void N::statistics() const 
{
	for(int i = 0 ; i < maxRef; i++){
		for(int j = 0; j < (1<<MAX_DEPTH); j++){
			if(nList[j] == 0)continue;
			if(nList[j]->_refCnt == i){
				cout << "Ref[" << j << "] = " << nList[j]->_refCnt << endl;
			}
		}
	}
}

int main()
{
	srand(getpid());
	N root;
	root.gen();
	root.statistics();
	return 0;
}
```
