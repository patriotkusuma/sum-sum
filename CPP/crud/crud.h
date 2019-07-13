#include <fstream>

namespace crud {

    struct node{
        std::string ID;
        std::string Nama;
        std::string Brand;
        int Tahun;
        double Harga;
        struct node *next;
        struct node *prev;
    }*start, *last;
    int counter = 0;


    void Empty();
    void InsertTop();
    void Display();
    void DeleteAny();
    void Search();
    void update();
    void Sort();
    node* CreateNode();
    
}