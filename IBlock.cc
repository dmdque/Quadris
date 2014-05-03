#include "IBlock.h"

void IBlock::setPos(int o){
    if (o == 0 || o == 2){
		pos[0][0] = 0;
		pos[0][1] = 3;
		pos[1][0] = 1;
		pos[1][1] = 3;
		pos[2][0] = 2;
		pos[2][1] = 3;
		pos[3][0] = 3;
		pos[3][1] = 3;
    }
    else if (o == 1 || o == 3){
		pos[0][0] = 0;
		pos[0][1] = 0;
		pos[1][0] = 0;
		pos[1][1] = 1;
		pos[2][0] = 0;
		pos[2][1] = 2;
		pos[3][0] = 0;
		pos[3][1] = 3;
    }
}

IBlock::IBlock(){
	x=0;
	y=0;
	o=0;
	c='I';
	setPos(o);
}

