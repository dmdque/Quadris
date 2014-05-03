#ifndef __IBLOCK_H__
#define __IBLOCK_H__

#include "tetromino.h"

class IBlock : public Tetromino{
public:
	void setPos(int o);
	IBlock();
};
#endif
