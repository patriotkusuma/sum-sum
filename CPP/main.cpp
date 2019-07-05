#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void login();
void Tittle();
void draw();
void gotoxy(int x, int y);
void gotoxy(int x, int y, std::string text);
void ManageData();
void MenuAwal();
void Exit();
void ShowData(); //belum selesai
void SearchData();

int main() {
    system("cls");
    login();
    MenuAwal();
    return 0;
}

void MenuAwal(){
    int a;
    system("cls");
    draw();
    gotoxy(31,3); std::cout << "SUM-SUM DEALER";
    gotoxy(4,6); std::cout << "SELAMAT DATANG";
    gotoxy(4,7); std::cout << "Silakan pilih menu yang diinginkan";
    gotoxy(5,10); std::cout << "1. Manage Data";
    gotoxy(5,11); std::cout << "2. Show Data";
    gotoxy(5,12); std::cout << "3. Search Data";
    gotoxy(5,13); std::cout << "4. Transaction";
    gotoxy(5,14); std::cout << "9. EXIT";
    gotoxy(4,20); std::cout << "Masukkan pilihan anda :";
    gotoxy(4,22); std::cout << "> "; std::cin>>a;
    switch(a){
        case 1:
            ManageData();
            break;
        case 2:
            ShowData();
            break;
        case 3:
            SearchData();
            break;
        case 9:
            Exit();
            break;
    }
}

void Tittle(){
    gotoxy(31,3); std::cout << "SUM-SUM DEALER";
}

void SearchData(){
    while(1){
        system("cls");
        std::string ID;
        draw();
        Tittle();
        gotoxy(4,6); std::cout << "MENU SEARCH DATA";
        gotoxy(4,7); std::cout << "Harap Masukkan ID yang ingin dicari";
        gotoxy(4,20); std::cout << "Masukkan ID dibawah ini :";
        gotoxy(4,22); std::cin >> ID;
        gotoxy(4,8); std::cout << ID.length();
        if(ID.length()>5){
            gotoxy(4,8); std::cout << "Harap memasukkan 5 karakter";
        } else if (ID.length()<5){
            gotoxy(4,8); std::cout << "Harap memasukkan 5 karakter";
        }
        gotoxy(4,22); system("pause");
    }
}

void ShowData(){
    system("cls");
    draw();
}
void Exit(){
    system("cls");
    draw();
    char a;
    gotoxy(31,3); std::cout << "SUM-SUM DEALER";
    gotoxy(4,6); std::cout << "GOOD BYE";
    gotoxy(4,20); std::cout << "APAKAH YAKIN INGIN KELUAR (Y/T)";
    gotoxy(4,22); std::cout << "> "; std::cin >>a;
    // if(a=='y'||a=='Y'){
        
    // }
    if(a=='t'||a=='T'){
        MenuAwal();
    }
}

void ManageData(){
    system("cls");
    int a;
    draw();
    gotoxy(31,3); std::cout << "SUM-SUM DEALER";
    gotoxy(4,6); std::cout <<"MANAGE DATA";
    gotoxy(4,7); std::cout <<"Silakan Pilih Menu yang diinginkan";
    gotoxy(5,10); std::cout << "1. Tambah Data";
    gotoxy(5,11); std::cout << "2. Lihat Data";
    gotoxy(5,12); std::cout << "3. Update Data";
    gotoxy(5,13); std::cout << "4. Delete Data";
    gotoxy(5,14); std::cout << "5. Kembali";
    gotoxy(4,20); std::cout << "Masukkan pilihan anda : ";
    gotoxy(4,22); std::cout << "> "; std::cin>>a;
    switch (a)
    {
    case 5:
        MenuAwal();
        break;
    
    default:
        break;
    }
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