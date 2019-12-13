/****************************************************************************
  FileName     [ p2Main.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define main() function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include "p2Json.h"

using namespace std;

int main()
{
   Json json;

   string jsonFile;
   cout << "Please enter the file name: ";
   cin >> jsonFile;
   if (json.read(jsonFile))
      cout << "File \"" << jsonFile << "\" was read in successfully." << endl;
   else {
      cerr << "Failed to read in file \"" << jsonFile << "\"!" << endl;
      exit(-1); // jsonFile does not exist.
   }

   // TODO read and execute commands
   string command;
   while (true) {
		cout << "Enter command: ";
		cin >> command;
		if(command == "EXIT" || cin.eof()){
			break;
		}else if(command == "ADD"){
			string key;
			int value;
			cin >> key >> value;
			json.add(key, value);
		}else{
			json.exec(command);
		}
   }
   return 0;
}
//	commands = {"PRINT", "SUM", "AVE", "MAX", "MIN", "ADD", "EXIT"};
