#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void login();
void draw();
void gotoxy(int x, int y);
void gotoxy(int x, int y, std::string text);

int main() {
    system("cls");
    int a;
    login();
    system("cls");
    draw();
    gotoxy(31,3); std::cout << "SUM-SUM STORE";
    gotoxy(4,6); std::cout << "SELAMAT DATANG";
    gotoxy(4,7); std::cout << "Silakan pilih menu yang diinginkan";
    gotoxy(5,10); std::cout << "1. Manage Data";
    gotoxy(5,11); std::cout << "2. Show Data";
    gotoxy(5,12); std::cout << "3. Transaction";
    gotoxy(5,13); std::cout << "9. EXIT";
    gotoxy(4,20); std::cout << "Masukkan pilihan anda :";
    gotoxy(4,22); std::cout << "> "; std::cin>>a;
    return 0;
}

void login(){
    system("cls");
    std::string username;
    std::string password;
    char ch;
    while(true){
        system("cls");
        password="";
        gotoxy(10,10); std::cout << "Enter Username : ";
        std::cin >> username;
        if(username == "")
            break;
        
        gotoxy(10,11); std::cout << "Enter Password : ";
        ch=_getch();
        while(ch != 13){
            password.push_back(ch);
            std::cout << "*";
            ch=_getch();
        }

        if(username == "admin" && password == "admin"){
            gotoxy(10, 14); std::cout << "Access Granted :P";
            gotoxy(10,15); std::cout << "Press Enter to continue.....";
            getch();
            break;
        } else {
            gotoxy(10,14); std::cout << "Access Aborted, Please Try Again";
            getch();
        }
    }
}

void gotoxy(int x, int y){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
}

void gotoxy(int x, int y, std::string text){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
    std::cout << text;
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

    // std::cout << "top - left         : " << tl << std::endl << std::endl;
    // std::cout << "top - right        : " << tr << std::endl << std::endl;
    // std::cout << "bottom - left      : " << bl << std::endl << std::endl;
    // std::cout << "bottom - right     : " << br << std::endl << std::endl;
    // std::cout << "vertical - line    : " << ver << std::endl << std::endl;
    // std::cout << "horizontal - line  : " << hor << std::endl << std::endl;
    // std::cout << "connector - top    : " << ct << std::endl << std::endl;
    // std::cout << "connector - bottom : " << cb << std::endl << std::endl;
    // std::cout << "connector - left   : " << cl << std::endl << std::endl;
    // std::cout << "connector - right  : " << cr << std::endl << std::endl;
    // std::cout << "cross              : " << c << std::endl << std::endl;

    std::string line(74, hor);

    gotoxy(2,1);
    std::cout << tl << line << tr; //for the top line
    //vertical-line in the left and right of the box
    for(a=1; a<22; a++){
        gotoxy(2,a+1);
        std::cout << ver;
        gotoxy(77, a+1);
        std::cout << ver;
    }

    gotoxy(2,23);
    std::cout << bl << line << br; //for the bottom line
    gotoxy(2,5);
    std::cout << cl << line << cr;
    gotoxy(2,21);
    std::cout << cl << line << cr;

    // gotoxy(2,3);
    // std::cout << cl << line << cr;
    // //
    // // gotoxy(9,3);
    // std::cout << ct;
    // gotoxy(9,4);
    // std::cout << ver;
    // gotoxy(9,5);
    // std::cout << cb;
    // //
    // gotoxy(42, 3);
    // std::cout << ct;
    // gotoxy(42, 4);
    // std::cout << ver;
    // gotoxy(42, 5);
    // std::cout << cb;

    // //
    // gotoxy()



}