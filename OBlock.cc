#include "OBlock.h"

void OBlock::setPos(int o){
	pos[0][0] = 0;
	pos[0][1] = 2;
	pos[1][0] = 0;
	pos[1][1] = 3;
	pos[2][0] = 1;
	pos[2][1] = 2;
	pos[3][0] = 1;
	pos[3][1] = 3;

/*
	pos[0][0] = 0;
	pos[0][1] = 0;
	pos[1][0] = 0;
	pos[1][1] = 1;
	pos[2][0] = 1;
	pos[2][1] = 0;
	pos[3][0] = 1;
	pos[3][1] = 1;
	// {{0,0},{0,1},{1,0},{1,1}}
*/
}

OBlock::OBlock(){
	x=0;
	y=0;
	o=0;
	c='O';
	setPos(o);
}
