#include <iostream>
#include "crud.h"
#include "functions/pos.h"
#include "functions/drawing.h"


crud::node* CreateNode(){
    crud::counter++;
    struct crud::node *temp;
    temp = new(struct crud::node);
    temp->ID 
}

void crud::Display(){
    system("cls");
    std::string ID, Name, Brand, Tahun, Harga;
    dr::draw();
    ps::gotoxy(5,8); std::cout << "ID       : ";
    ps::gotoxy(5,9); std::cout << "Nama     : ";
    ps::gotoxy(5,10); std::cout << "Brand    : ";
    ps::gotoxy(5,11); std::cout << "Tahun    : ";
    ps::gotoxy(5,12); std::cout << "Harga    : ";
    struct crud::node *temp;
    temp = new node;
    
}