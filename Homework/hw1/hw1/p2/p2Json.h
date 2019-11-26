/****************************************************************************
  FileName     [ p2Json.h]
  PackageName  [ p2 ]
  Synopsis     [ Header file for class Json JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#ifndef P2_JSON_H
#define P2_JSON_H

#include <vector>
#include <string>
#include <unordered_set>
#include <map>
#include <climits>

using namespace std;

class JsonElem
{
public:
   // TODO: define constructor & member functions on your own
   JsonElem() {}
   JsonElem(const string& k, int v): _key(k), _value(v) {}
   int getval(){ return _value; }

   friend ostream& operator << (ostream&, const JsonElem&);

private:
   string  _key;   // DO NOT change this definition. Use it to store key.
   int     _value; // DO NOT change this definition. Use it to store value.
};

class Json
{
public:
   // TODO: define constructor & member functions on your own
   bool read(const string&);
   void exec(const string&);
   void add(const string&, const int&);

private:
   vector<JsonElem>       _obj;  // DO NOT change this definition.
                                 // Use it to store JSON elements.
								 //
	void err(){ cerr << "Error: No element fount!!\n"; }
	void print(){
		int size = _obj.size();
		cout << "{\n";
		for(int i = 0; i < size; i++){
			cout << "  " << _obj[i];
			if(i != size-1)	cout << ",";
			cout << "\n";
		}
		cout << "}\n";
	}

	void sum(){
		if(_obj.empty()){ err(); return; }
		int val = 0;
		for(auto it: _obj){
			val += it.getval();
		}
		cout << "The summation of the values is: ";
		cout << val;
		cout << ".\n";
	}

	void ave(){
		if(_obj.empty()){ err(); return; }
		float val = 0.0;
		for(auto it: _obj){
			val+=it.getval();
		}
		cout << "The average of the values is:";
		cout << float(val/_obj.size());
		cout << ".\n";
	}

	void max(){
		if(_obj.empty()){ err(); return; }
		unsigned int idx = 0;
		int val = INT_MIN;
		for(; idx < _obj.size(); idx++){
			if(_obj[idx].getval() > val)
				val = _obj[idx].getval();
		}
		cout << "The maximum of the values is: { ";
		cout << _obj[idx];
		cout << " }.\n";
	}

	void min(){
		if(_obj.empty()){ err(); return; }
		unsigned int idx = 0;
		int val = INT_MAX;
		for(; idx < _obj.size(); idx++){
			if(_obj[idx].getval() < val)
				val = _obj[idx].getval();
		}
		cout << "The minimum of the values is: { ";
		cout << _obj[idx];
		cout << " }.\n";
	}
};

#endif // P2_TABLE_H
