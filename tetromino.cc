#include <iostream>
#include "tetromino.h"
using namespace std;

Tetromino::~Tetromino(){
	for(int i = 0; i < 4; i++){
    		delete [] pos[i];
  	}
	delete [] pos;
}

char Tetromino::getC(){
    return c;
}

int Tetromino::getx(){
    return x;
}

int Tetromino::gety(){
    return y;
}

void Tetromino::rotatecw(){
    o = (o + 1) % 4;
    setPos(o);
}

void Tetromino::rotateccw(){
    o = (o + 3) % 4;
    setPos(o);
}

void Tetromino::right(){
    if (x < 10)
        x++;
}

void Tetromino::left(){
    if (x > 0)
        x--;
}

void Tetromino::down(){
    if (y < 15)
        y++;
}

void Tetromino::up(){
    if (y > 0)
	y--;
}

