#include "functions.h"
#include <string>

void draw();

int main() {
    draw();
    return 0;
}

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

    std::cout << "top - left         : " << tl << std::endl << std::endl;
    std::cout << "top - right        : " << tr << std::endl << std::endl;
    std::cout << "bottom - left      : " << bl << std::endl << std::endl;
    std::cout << "bottom - right     : " << br << std::endl << std::endl;
    std::cout << "vertical - line    : " << ver << std::endl << std::endl;
    std::cout << "horizontal - line  : " << hor << std::endl << std::endl;
    std::cout << "connector - top    : " << ct << std::endl << std::endl;
    std::cout << "connector - bottom : " << cb << std::endl << std::endl;
    std::cout << "connector - left   : " << cl << std::endl << std::endl;
    std::cout << "connector - right  : " << cr << std::endl << std::endl;
    std::cout << "cross              : " << c << std::endl << std::endl;

    
}