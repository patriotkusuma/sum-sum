#include <iostream>
#include "pos.h"

namespace dr{

    void draw(){
        int a;
        char tl,tr,bl,br,ver,hor,ct,cb,cl,cr,c; //border
        tl  = '\xC9' ; //top-left
        tr  = '\xBB' ; //top-right
        bl  = '\xC8' ; //bottom-left
        br  = '\xBC' ; //bottom-right
        ver = '\xBA' ; //vertical-line
        hor = '\xCD' ; //horizontal-line
        ct  = '\xCB' ; //connector-top
        cb  = '\xCA' ; //connector-bottom
        cl  = '\xCC' ; //connector-left
        cr  = '\xB9' ; //connector-right
        c   = '\xCE' ; //cross

        std::string line(74, hor);
        ps::gotoxy(2,1);
        std::cout << tl << line << tr; //for the top line
        //vertical-line in the left and right of the box
        for(a=1; a<22; a++){
            ps::gotoxy(2,a+1);
            std::cout << ver;
            ps::gotoxy(77, a+1);
            std::cout << ver;
        }

        ps::gotoxy(2,23);
        std::cout << bl << line << br; //for the bottom line
        ps::gotoxy(2,5);
        std::cout << cl << line << cr;
        ps::gotoxy(2,21);
        std::cout << cl << line << cr;   
    }
}