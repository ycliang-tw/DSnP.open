/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "p2Json.h"

using namespace std;

bool
Json::read(const string& jsonFile)
{
	ifstream fp(jsonFile);
	if(!fp)	return false;

	string parse;
	getline(fp, parse);	// {
	while(getline(fp, parse)){
		if(parse == "}" || parse.empty())
			break;
	
		stringstream ss(parse);
		string key, colon;
		int value;	
		ss >> key >> colon >> value;

		_obj.push_back( JsonElem(key, value) );
	}
	/*
	for(auto it:_obj){
		cout << it << endl;
	}
	*/
	return true;
}

void 
Json::exec(const string& command)
{
	int size = _obj.size();
	int sum = 0, min = INT_MAX, max = INT_MIN;
	int minid = 0, maxid = 0;
	float ave = 0.0;
	for(int idx = 0; idx < size; idx++){
		int tmp = _obj[idx].getval();
		if(tmp > max){ max = tmp; maxid = idx; }
		if(tmp < min){ min = tmp; minid = idx; }
		sum += tmp;
	}
	ave = float(sum) / float(size);
	
	if(command == "PRINT"){
		cout << "{\n";
		for(int i = 0; i < size; i++){
			cout << "  " << _obj[i];
			if(i != size -1) cout << ",";
			cout << "\n";
		}
		cout << "}\n";
	}else if(size == 0){
		cerr << "Error: No element found!\n";
	}else if(command == "SUM"){
		cout << "The summation of the values is: " << sum << ".\n";
	}else if(command == "AVE"){
		cout << "The average of the values is: " << fixed << setprecision(1) << ave << ".\n";
	}else if(command == "MAX"){
		cout << "The maximum of the values is: { " << _obj[maxid] << " }.\n";
	}else if(command == "MIN"){
		cout << "The minimum of the values is: { " << _obj[minid] << " }.\n";
	}
}

void 
Json::add(const string& key, const int& value)
{
	_obj.push_back(JsonElem(key, value));
}

ostream&
operator << (ostream& os, const JsonElem& j)
{
   return (os << "\"" << j._key << "\" : " << j._value);
}

