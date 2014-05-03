#include <iostream>
#include <string>
#include "command.h"
using namespace std;

void interpreter(string input, Field &f, bool &invalid){
	string interpret[9]={"left","right","down","clockwise","counterclockwise",
			     "drop","levelup","leveldown","restart"}; // input interpreters
	bool same[9];
	int numCommands=9;
	string command;
	int length=input.length();
	// set all interpreters to true
	for(int j=0; j<9; j++){
	   same[j]=true;
	}
	// determine what input implies
	for(int a=0; a<length; a++){
	   char ch=input[a];
	   for(int b=0; b<9; b++){
	      if(ch!=interpret[b][a] && same[b]==true){
	         same[b]=false;
	         numCommands--;}
	   }
	}
	if(numCommands==1){ // determine if there is 1 similar command
	   for(int i=0; i<9; i++){
	      if(same[i]==true){
		 command = interpret[i]; 
		 break;}
	   }
	}
	// actions according to command
	if (command == "left"){
		f.left();}
	else if (command == "right"){
		f.right();}
	else if (command == "down"){
		f.down();}
	else if (command == "clockwise"){
		f.clockwise();}
	else if (command == "counterclockwise"){
		f.counterClockwise();}
	else if (command == "drop"){
		f.drop();}
	else if (command == "levelup"){
		f.levelUp();}
	else if (command == "leveldown"){
		f.levelDown();}
	else if (command == "restart"){
		f.restart();}
	else { 
		invalid=true;
		return; 
	}
	int linesCleared = f.completeLines(); // int linesCleared is for scoring
	f.updateScore(linesCleared);
}

void interface(string input, Field &f){	// command-line interface
	int n;
	string filename;
	if(input=="-text"){
		f.graphicDisplay=false;
		f.w.~Xwindow();
	}
	else if(input=="-seed") { 
		cin>>n;
		f.seed(n); 
	}
	else if(input=="-scriptfile") { 
		cin>>filename;
		f.scriptFile(filename); 
	}
	else if(input=="-startlevel") { 
		cin>>n;
		f.startLevel(n); 
		cout<<f; 
	}
	else {
	   	cout<<"Invalid Command"<<endl;
	}
}
