#include <cstdlib>
#include <sstream> // for appending int to string
#include "field.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "OBlock.h"
using namespace std;

// constructor
Field::Field() : MAXROW(15), MAXCOL(10), level(0), score(0), highScore(0), filename("sequence.txt"), graphicDisplay(true){
	file.open(filename.c_str());
	file>>next;
	changeBlock(next);
	nextBlock();
	seed(-1);
	for (int row = 0; row < MAXROW; row++){
		for (int col = 0; col < MAXCOL ; col++){
			grid[row][col] = ' ';
		}
	}
}

// deconstructor
Field::~Field(){
    for (int row=0; row<MAXROW; row++){
        delete [] grid[row];
    }
    delete [] grid;
    activeBlock->~Tetromino();
    delete activeBlock;
    if(graphicDisplay){ w.~Xwindow(); }
    file.close();
}

// move left
void Field::left(){
	if (activeBlock->getx() > 0){ // check left wall boundary
		if (!checkConflict(activeBlock->getx() - 1, activeBlock->gety())){ // check for conflicts
			activeBlock->left();
		}
	}
}

// move right
void Field::right(){
	if (activeBlock->getx() < MAXCOL){ // check for right wall boundary
		if (!checkConflict(activeBlock->getx() + 1, activeBlock->gety())){ // check for conflicts
			activeBlock->right();
		}
	}
}

// move down
void Field::down(){
	if (activeBlock->gety() < MAXROW){ // check for bottom boundary
		if (!checkConflict(activeBlock->getx(), activeBlock->gety() + 1)){ // check for conflicts
			activeBlock->down();
		}
	}
}

// rotate clockwise
void Field::clockwise(){
	activeBlock->rotatecw();
	if (checkConflict(activeBlock->getx(), activeBlock->gety())){ // if there is a conflict
		activeBlock->rotateccw(); // undo rotation
	}
}

// rotate counter-clockwise
void Field::counterClockwise(){
	activeBlock->rotateccw();
	if (checkConflict(activeBlock->getx(), activeBlock->gety())){ // if there is a conflict
		activeBlock->rotatecw(); // undo rotation
	}
}

// drop block
void Field::drop(){
	// move down until a conflict is found
	while (!checkConflict(activeBlock->getx(), activeBlock->gety())){
		activeBlock->down();
	}
	activeBlock->up(); // check if top first
	for (int i = 0; i < 4; i++){ // write activeBlock->to grid
		grid[activeBlock->gety() + activeBlock->pos[i][1]][activeBlock->getx() + activeBlock->pos[i][0]] = activeBlock->getC();
        }
	changeBlock(next); // get next block
	nextBlock(); // determine next block 
}

// levelup
void Field::levelUp(){
	if(level<3) { level++; }
}

// leveldown
void Field::levelDown(){
	if(level>0) { level--; }
}

// start at level n
void Field::startLevel(int n){
	if(n>=0 && n<=3) { level=n; }
}

// change sequence file
void Field::scriptFile(string name){
	ifstream newfile;
	newfile.open(name.c_str());
	if(newfile){
		file.close();
		filename=name;
	}
	newfile.close();
}

// restart game
void Field::restart(){
	clearBoard();
	file.close();
	file.open(filename.c_str());
	char ch;
	file>>ch;
	changeBlock(ch);
	nextBlock();
}

// clear line
void Field::clearLine(int rowd){
	for (int row = rowd; row > 0; row --){
		for (int col = 0; col < MAXCOL; col++){
			grid[row][col] = grid[row - 1][col];
		}
	} 
}

// number of cleared lines
int Field::completeLines(){
	int numCleared= 0;
	for (int row = 0; row < MAXROW; row++){
		bool cl = true; // complete line
		for (int col = 0; col < MAXCOL && cl; col++){
			if (grid[row][col] == ' ')
				cl = false; 
		}
		if (cl){
			clearLine(row); // clear lien
			numCleared++;
		}
	}
	return numCleared; // returns the number of lines cleared
}

// change current block
void Field::changeBlock(char type){ // *remember to check for memory leaks
    if(type=='I') activeBlock = new IBlock(); // depending on whether activeBlock->is a pointer... "new"
    else if(type=='J') activeBlock = new JBlock();
    else if(type=='L') activeBlock = new LBlock();
    else if(type=='O') activeBlock = new OBlock();
    else if(type=='S') activeBlock = new SBlock();
    else if(type=='Z') activeBlock = new ZBlock();
    else if(type=='T') activeBlock = new TBlock();
}

// clear gameboard
void Field::clearBoard(){
	score=0;
	level=0;
	// reset grid to empty
	for (int row = 0; row < MAXROW; row++){
		for (int col = 0; col < MAXCOL ; col++){
			grid[row][col] = ' ';
		}
	}
}

// score update
void Field::updateScore(int numLine){
	if(numLine==0) return; // if no lines cleared
	score+=(level + numLine)*(level + numLine);
	if (score > highScore){
		highScore = score; 
	}
}

// check if game over
bool Field::checkLoss(){
	return checkConflict(0,0);
}

bool Field::checkConflict(int x, int y){ // returns true if there is a conflict
	for (int i = 0; i < 4; i++){
		int positionX = x + activeBlock->pos[i][0];
		int positionY = y + activeBlock->pos[i][1];
		if (grid[positionY][positionX] != ' ')
			return true;
		// right wall boundary
		if (positionX >= MAXCOL) 
			return true;
	}
	return false;
} // *todo: check for out of bounds of grid cases

bool Field::activeBlockCheck(int row, int col) const{ // checks if activeBlock is present at given position
        for (int i = 0; i < 4; i++){
                if (col == activeBlock->getx() + activeBlock->pos[i][0] && row == activeBlock->gety() + activeBlock->pos[i][1])
                        return true;
        }
        return false;
}

// determine next block depending on level
void Field::nextBlock(){
	if(level == 0){ 	
		if(!file.good()){ // if file cannot open (end of file)
			file.close(); 
			file.open (filename.c_str()); 
		} 
		file>>next;
	}
	else {
		int n;
		if(level == 1){
			n=rand()%6; // probability of 1/6
			if(n==0){
				n=rand()%2; // probability of 1/2
			}
			else { 
				n=rand()%6+2; 
			}
		}
		else if(level == 2){
			n=rand()%7; // probability of 1/7 (equal probability)
		}
		else if(level == 3){
			n=rand()%9; // probability of 1/9
			if(n<=1) { n=0; }
			else if(n<=3) { n=1; }
			else if(n==7) { n=2; }
			else if(n==8) { n=3; }
		}	
		if(n==0){ next='S'; }
		else if(n==1){ next='Z'; }
		else if(n==2){ next='I'; }
		else if(n==3){ next='L'; }
		else if(n==4){ next='J'; }
		else if(n==5){ next='O'; }	
		else if(n==6){ next='T'; }
	}
}

// random number generator's seed
void Field::seed(int n){
	if(n<0) { srand(time(NULL)); }
	else { srand(n); }
}

// display game
ostream &operator<<(ostream &out, Field &f){ 
	if(f.graphicDisplay) { f.w.fillRectangle(0,0,240,510,0); }
	int colour=1;
	ostringstream levelSS;
	ostringstream scoreSS;
	ostringstream highScoreSS;
	levelSS << "Level: " << f.level;
	scoreSS << "Score: " << f.score;
	highScoreSS << "Highscore: " << f.highScore;
	if(f.graphicDisplay){
		f.w.drawString(20,30,levelSS.str());
		f.w.drawString(20,50,scoreSS.str());
		f.w.drawString(20,70,highScoreSS.str());
		f.w.fillRectangle(20,90,200,300);    	
	}
	out<< levelSS.str() << endl; // "Level: "<<f.level<<endl;
    	out<< scoreSS.str() << endl; // "Score: "<<f.score<<endl;
    	out<< highScoreSS.str() << endl; // "Highscore: "<<f.highScore<<endl;
	out<<"----------"<<endl;
	for (int row = 0; row < f.MAXROW; row++){
		for (int col = 0; col < f.MAXCOL; col++){
			char c;
			if (f.activeBlockCheck(row, col)){
				c = f.activeBlock->getC();
				out << c;
				colour = colourBlock(c);
			}
			else{
				c = f.grid[row][col];
				out << c;
				colour = colourBlock(c);
			}
			if(f.graphicDisplay){
				f.w.fillRectangle(20+col*20,90+row*20,20,20,colour);
			}
		}
		out << endl;
	}
	out<<"----------"<<endl;
	out<<"Next:"<<endl;
	// draw the next block
	if(f.graphicDisplay) { f.w.drawString(20,430,"Next:"); }
	char next=f.next;
	colour = colourBlock(next);
	if(next=='L'){ 
		if(f.graphicDisplay){
			f.w.fillRectangle(60,450,20,20,colour);
			f.w.fillRectangle(20,470,60,20,colour);
		}
		out<<"  L"<<endl<<"LLL"<<endl; 
	}
	else if(next=='J'){ 
		if(f.graphicDisplay){
			f.w.fillRectangle(20,450,20,20,colour);
			f.w.fillRectangle(20,470,60,20,colour);
		}
		out<<"J"<<endl<<"JJJ"<<endl; 
	}
	else if(next=='O'){	
		if(f.graphicDisplay){
			f.w.fillRectangle(20,450,40,20,colour);
			f.w.fillRectangle(20,470,40,20,colour);
		}
		out<<"OO"<<endl<<"OO"<<endl; 
	}
	else if(next=='T'){
		if(f.graphicDisplay){
			f.w.fillRectangle(20,450,60,20,colour);
			f.w.fillRectangle(40,470,20,20,colour);
		}
		out<<"TTT"<<endl<<" T"<<endl; 
	}
	else if(next=='S'){ 
		if(f.graphicDisplay){
			f.w.fillRectangle(40,450,40,20,colour);
			f.w.fillRectangle(20,470,40,20,colourBlock(next));
		}
		out<<" SS"<<endl<<"SS"<<endl; 
	}
	else if(next=='Z'){ 
		if(f.graphicDisplay){
			f.w.fillRectangle(20,450,40,20,colourBlock(next));
			f.w.fillRectangle(40,470,40,20,colourBlock(next));
		}
		out<<"ZZ"<<endl<<" ZZ"<<endl; 
	}
	else if(next=='I'){ 
		if(f.graphicDisplay){
			f.w.fillRectangle(20,450,80,20,colourBlock(next));
		}
			out<<"IIII"<<endl; 
	}
	if(f.graphicDisplay && f.checkLoss()){
		f.w.drawString(95,200,"GAME OVER!",0);
	}
	return out;
}
