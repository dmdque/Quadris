#ifndef __FIELD_H__
#define __FIELD_H__

#include <iostream>
#include <fstream>
#include "tetromino.h"
#include "window.h"
#include "colour.h"

class Field{
  int MAXROW;
  int MAXCOL;
  int level;
  int score, highScore;
  std::string filename;
  std::ifstream file;
  char next;
  char grid[15][10];

  public:
	Xwindow w;
	bool graphicDisplay;

	Tetromino *activeBlock; 

	Field();
	~Field();

	// command methods
	void left();
	void right();
	void down();
	void clockwise();
	void counterClockwise();
	void drop();
	void levelUp();
	void levelDown();
	void startLevel(int n);
	void scriptFile(std::string name);
	void restart();

	int completeLines();
	void clearLine(int rowd);
	void changeBlock(char type);
	void clearBoard();
	void nextBlock();
	void updateScore(int numLine);
	bool checkLoss();
	bool checkConflict(int x, int y);
	bool activeBlockCheck(int row, int col) const;

	void seed(int n);

	friend std::ostream &operator<<(std::ostream &out, Field &f);
};

#endif
