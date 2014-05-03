#include <iostream>
#include <string>
#include <sstream>
#include "field.h"
#include "command.h"
#include "window.h"
using namespace std;

int main(){
 	// declare and initialize variable
	string input;
	Field f;
 	cout << f; // display gameboard
	cout<<"Please enter a command: ";
  while(cin>>input){
		bool invalid=false;
		string temp="\0";
		temp+=input[0];
		istringstream s(temp);
		int n;
		if(s>>n){ // determine if first char of input is a number
			if(input.length() == 1) { cin>>input; } // if there is a space between number and command
			else{
				int length=input.length();
				for(int i = 0; i < length - 1; i++){ // remove first char and get rest as string
					input[i]=input[i+1];
				}
				input.erase(length - 1);
			}
		}
		else n=1;
		for(int i=0; i<n; i++){
			if(input[0]=='-') { interface(input, f); break; } // if user inputs a command interface
			else { interpreter(input, f, invalid); } // command interpreter
		}
		if(invalid==true){ cout<<"Invalid Command"<<endl; }
		else cout<<f;
		if(f.checkLoss()){ // determine if game over
			cout<<endl<<"Game Over"<<endl;
			cout<<"Would you like to start a new game? (type anything to continue or 'exit' to quit)"<<endl;
			cin>>input;
		    	if(input=="exit"){ break; } // exit game
		    	f.restart(); // restart game
			cout << f;
       		}
		cout<<endl<<"Please enter a command: ";
    	}
	f.~Field();
}
