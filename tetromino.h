#ifndef __TETROMINO_H__
#define __TETROMINO_H__

class Tetromino{
  protected:
    int x; // x position of the {0,0} square
    int y;
    int o; // orientation, has values from 0-3
    char c; // char to be printed in field
  public:
    int pos[4][2];
    virtual void setPos(int o)=0;
    ~Tetromino();	

    char getC();

    int getx();
    int gety();

    void rotatecw();
    void rotateccw();

    void right();
    void left();
    void down();
    void up();
};

#endif
