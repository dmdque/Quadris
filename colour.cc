int colourBlock(char c){
    int colour;
    if(c==' '){ colour=1; }
    else if(c=='I'){ colour=2; }
    else if(c=='J'){ colour=3; }
    else if(c=='L'){ colour=4; }
    else if(c=='O'){ colour=6; }
    else if(c=='T'){ colour=7; }
    else if(c=='S'){ colour=8; }
    else if(c=='Z'){ colour=9; }
    return colour;
}
