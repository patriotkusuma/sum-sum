#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#define MAX 50

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

typedef struct{
    char data[MAX][30];
    int head, tail;
}queue;
queue antrian;

// typedef struct data{
//     int ID;
//     std::string Nama;
//     std::string Brand;
//     int Tahun;
//     double Harga;
// };

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
void TambahData();
void ManageAntrian();

void init(){
    antrian.head = antrian.tail = -1;
}

int isFull(){
    if(antrian.tail == MAX-1){
        return 1;
    } else {
        return 0;
    }
}

int isEmpty(){
    if(antrian.tail == -1){
        antrian.head = -1;
        return 1;
    } else {
        return 0;
    }
}

void inQueue(char d[MAX]){
    antrian.head = 0;
    antrian.tail ++;
    strcpy(antrian.data[antrian.tail],d);
}

void deQueue(){
    gotoxy(5,10); std::cout << "Data Diambil" << " "<<antrian.data[antrian.head];
    for(int i = antrian.head; i < antrian.tail; i++){
        strcpy(antrian.data[i],antrian.data[i+1]);
        antrian.tail--;
    }
}

void clear(){
    antrian.head=antrian.tail =-1;
    gotoxy(5,10); std::cout << "Semua Dat Sudah Terhapus";
}

void print(){
    for(int i=0; i<=antrian.tail; i++){
        gotoxy(5,10 + i);std::cout <<"Antrian ke - " << i+1;
        gotoxy(18,10 +i); std::cout <<antrian.data[i]; 
    }
}


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
    gotoxy(5,10); std::cout << "1. Manage Antrian";
    gotoxy(5,11); std::cout << "2. Manage Data";
    gotoxy(5,12); std::cout << "3. Show Data";
    gotoxy(5,13); std::cout << "4. Search Data";
    gotoxy(5,14); std::cout << "5. Transaction";
    gotoxy(5,15); std::cout << "9. EXIT";
    gotoxy(4,20); std::cout << "Masukkan pilihan anda :";
    gotoxy(4,22); std::cout << "> "; std::cin>>a;
    switch(a){
        case 1:
            ManageAntrian();
        case 2:
            ManageData();
            break;
        case 3:
            ShowData();
            break;
        case 4:
            SearchData();
            break;
        case 9:
            Exit();
            break;
    }
}


void ManageAntrian(){
    int pilihan;
    char value[30];
    char kembali;
    ManageAntrianAwal:
    system("cls");
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MANAGE ANTRIAN";
    gotoxy(4,7); std::cout << "Silakan pilih menu yang diinginkan";
    do{
        gotoxy(5,10); std::cout << "1. Registrasi Antrian";
        gotoxy(5,11); std::cout << "2. Panggil Antrian";
        gotoxy(5,12); std::cout << "3. Lihat Antrian";
        gotoxy(5,13); std::cout << "4. Hapus Antrian";
        gotoxy(5,14); std::cout << "5. Kembali";
        gotoxy(4,22); std::cout << "> ";std::cin >> pilihan;
        switch (pilihan)
        {
        case 1: 
            if(isFull() !=1){
                system("cls");
                draw();
                Tittle();
                gotoxy(4,6); std::cout << "Registrasi Antrian";
                gotoxy(4,7); std::cout << "Silakan Masukkan Data";
                gotoxy(5,10); std::cout << "Nama : "; std::cin >> value;
                inQueue(value);
            } else {
                system("cls");
                draw();
                Tittle();
                gotoxy(4,6); std::cout << "Registrasi Antrian";
                gotoxy(4,7); std::cout << "Silakan Masukkan Data";
                gotoxy(4,10); std::cout << "Data Sudah Penuh";
                
            }
                gotoxy(4,19); std::cout << "Data Antrian Sudah Tersimpan";
                gotoxy(4,20); std::cout << "Masukan b/B untuk kembali";
                gotoxy(4,22); std::cout << "> "; std::cin >> kembali;
                if(kembali == 'b' || 'B'){
                    goto ManageAntrianAwal;
                } else {
                    MenuAwal();
                }
            break;
        case 2:
        
        case 3: 
            if(isEmpty() != 1){
                system("cls");
                draw();
                Tittle();
                gotoxy(4,6); "Daftar Antrian";
                gotoxy(5,7);
                print();
            } else {
                system("cls");
            }
            gotoxy(4,20); std::cout << "Masukan b/B untuk Kembali";
            gotoxy(4,22); std::cout << "> "; std::cin >> kembali;
            if(kembali == 'b' || 'B'){
                goto ManageAntrianAwal;
            } else {
                MenuAwal();
            }
        case 5: 
            MenuAwal();
        default:
            break;
        }
    } while(pilihan !=1);
    getchar();
}


void TambahData(){
    awal:
    system("cls");
    std::string ID,Nama,Brand,TahunTerbit, Harga;
    char pilihan;
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU TAMBAH DATA";
    gotoxy(4,7); std::cout << "Masukkan Data sesuai Ketentuan di Bawah ini.";
    gotoxy(6,9); std::cout << "ID            : "; 
    gotoxy(6,10); std::cout << "Nama          : "; 
    gotoxy(6,11); std::cout << "Brand         : "; 
    gotoxy(6,12); std::cout << "Tahun Terbit  : "; 
    gotoxy(6,13); std::cout << "Harga         : "; 
    gotoxy(22,9); std::cin>>ID;
        if(ID==""){
            gotoxy(6,10); std::cout << "Harap Masukkan ID";
            goto awal;
        } 
    gotoxy(22,10); std::cin >> Nama;
        if(Nama==""){
            gotoxy(6,11); std::cout << "Harap Masukkan Nama";
            goto awal;
        }
    gotoxy(22,11); std::cin>> Brand;
        if(Brand==""){
            std::cout << "Harap Masukkan Brand";
        }
    gotoxy(22,12); std::cin >> TahunTerbit;
        if(TahunTerbit==""){
            std::cout << "Harap Masukkan Tahun Terbit";
        }
    gotoxy(22,13); std::cin >> Harga;
        if(Harga==""){
            std::cout << "Harap Masukkan Harga";
        }
    gotoxy(4,20); std::cout << "Apakah anda yakin ingin menyimpan?(Y/T)";
    gotoxy(4,22);std::cin >> pilihan;
    if(pilihan=='t'||'T'){
        ManageData();
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
        gotoxy(4,19); std::cout << "Masukkan ID dibawah ini :";
        gotoxy(4,20); std::cout << "masukkan b/B untuk kembali";
        gotoxy(4,22); std::cin >> ID;
        gotoxy(4,8); std::cout << ID.length();
        if(ID.length()>5){
            gotoxy(4,8); std::cout << "Harap memasukkan 5 karakter";
        } 
        // else if (ID.length()<5){
        //     gotoxy(4,8); std::cout << "Harap memasukkan 5 karakter";
        // }
         else if (ID == "B" || ID == "b"){
            MenuAwal();
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
    Tittle();
    gotoxy(4,6); std::cout << "GOOD BYE";
    gotoxy(4,20); std::cout << "APAKAH YAKIN INGIN KELUAR (Y/T)";
    gotoxy(4,22); std::cout << "> "; std::cin >>a;
    // if(a=='y'||a=='Y'){
    //     goto keluar
    // }
    if(a=='t'||a=='T'){
        MenuAwal();
    }

    // keluar:
}

void ManageData(){
    system("cls");
    int a;
    draw();
    Tittle();
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
    case 1:
        TambahData();
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