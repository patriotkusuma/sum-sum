#include "functions/libs.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct data{
    std::string ID;
    std::string Nama;
    std::string Brand;
    int Tahun;
    double Harga;
};


struct queue{
    int kode[MAX], head, tail;
    std::string nama[MAX], alamat[MAX];
}antrian;

data Mobil[SIZE];
std::vector<data> datas;


struct DetailTransaction{
    data item;
    double qty;
    double pay;
};

struct pembeli{
    DetailTransaction detail;
    std::string Nama;
    std::string Alamat;
};

void login();
void Tittle();
void draw();
void LoadData();
void gotoxy(int x, int y);
void gotoxy(int x, int y, std::string text);
void ManageData();
void MenuAwal();
void Exit();
void SaveTransaction(std::vector<pembeli> buyers);
void PrintBill(std::vector<DetailTransaction> details);
void ShowData(); //belum selesai
void SearchData();
void TambahData();
void ManageAntrian();
void DrawForSort();
void DrawForm();
void InputForm();
void TransactionFromQueue();
void UpdateData();
void doTransaction();
void DeleteData();
data find_data(std::string id);
// bool CompareInterval(Interval i1, Interval2);
void SortingData();
bool acompare(data lhs, data rhs){
    return lhs.Nama < rhs.Nama;
}

//queue
void init();
bool isFull();
bool isEmpty();
void inQueue();
void deQueue();
void print();
void clear();


int main() {
    system("cls");
    login();
    MenuAwal();
    return 0;
}

void SaveTransaction(std::vector<pembeli> buyers){
    std::fstream os;
    os.open("transactions.txt", std::ios::app);
    DetailTransaction bayar;
    for(auto i : buyers){
        os  << i.Nama<<"," << i.Alamat <<","
        << i.detail.item.ID << ","<<i.detail.item.Nama<<","
        << i.detail.qty << std::endl;; 
    }

}

void PrintBill(std::vector<DetailTransaction> details){
    std::ofstream os("bill.txt");
    DetailTransaction bayar;

    os << "(|********************************************|)" << std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|    +                                  +    |)" << std::endl;
	os << "(|    +	  ------ Delaer  Yu-Sum ------   +    |)" << std::endl;
	os << "(|    +	  -------- YOGYAKARTA --------   +    |)" << std::endl;
	os << "(|    +                                  +    |)" << std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	
	double total = 0;
	for(DetailTransaction d : details)
	{
		double sub = d.qty * d.item.Harga;
		total += sub;
		os <<"(|  " <<std::setiosflags(std::ios::left) << std::setw(42) << d.item.Nama;
		os << "|)";
		os << std::endl;
		os << "(|  "<<std::setiosflags(std::ios::right)<< std::setw(3) << d.qty;
		os <<std::setw(3) << "x";
		os << std::setw(11) << d.item.Harga;
		os << std::setw(22) << sub;
		os << "   |)";
		os << std::resetiosflags(std::ios::right)<<std::endl;
	}
	os << "(|--------------------------------------------|)" << std::endl;
	os << std::setiosflags(std::ios::left) << std::setw(19) << "(|";
	os << std::setw(14) << "Total Harga :";
	os <<std::setiosflags(std::ios::right)<< std::setw(10) << total << "   |)"<< std::endl <<std::resetiosflags(std::ios::right);
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|  Instagram : @YUSUM_FRUITS                 |)" << std::endl;
	os << "(|  Phone     : 0879837213475                 |)" <<std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|    $--- Terima Kasih  Telah Mampir ---$    |)" << std::endl;
	os << "(|       $--- TIDAK MENERIMA RETUR ---$       |)" << std::endl;
	os << "(|********************************************|)" << std::endl;

	
	os.close();
	
	system("start /min notepad /p bill.txt");
}

//queue
void inQueue(){
    system("cls");
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU REGISTRASI ANTRIAN";
    std::string nama;
    std::string alamat;
    if(!isFull()){
            std::cin.ignore();
            gotoxy(4,7); std::cout << "Masukan Data di bawah ini:";
            gotoxy(5,8); std::cout << "Nama      :"; std::getline(std::cin, nama);
            antrian.nama[antrian.tail] = nama;
            gotoxy(5,9); std::cout << "Alamat    :"; std::getline(std::cin, alamat);
            antrian.alamat[antrian.tail] = alamat;
            gotoxy(4,19); std::cout << "Data berhasil ditambahkan ke dalam antrian ^_^";
            antrian.tail++;
    
    }else{
        gotoxy(5,10); std::cout << "Data sudah penuh";
    }
    gotoxy(4,22);
    getch();
    ManageAntrian();

}
void clear(){
    antrian.head=-1;
    antrian.tail=-1;
    ManageAntrian();
}
void deQueue(){
    system("cls");
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU PANGGIL ANTRIAN";
    gotoxy(4,7); std::cout << "ANTRIAN NO : ";
    gotoxy(5,8); std::cout << "Nama       : ";
    gotoxy(5,9); std::cout << "Alamat     : ";
    if(!isEmpty()){
            gotoxy(19,7); std::cout << antrian.head + 1;
            gotoxy(19,8); std::cout << antrian.nama[antrian.head];
            gotoxy(19,9); std::cout << antrian.alamat[antrian.head];
            gotoxy(4,22);
            getchar(); 

        for(int i=antrian.head;i<antrian.tail;i++){
            antrian.nama[i]=antrian.nama[i+1];
            antrian.alamat[i]=antrian.alamat[i+1];
        }
        antrian.tail--;
    }else{
        gotoxy(5,10); std::cout << "Data sudah penuh";
    }
    gotoxy(4,22);
    getch();
    ManageAntrian();
}
bool isFull(){
    if(antrian.tail==MAX)
        return true;
    else return false;
}

bool isEmpty(){
    if(antrian.tail==0)
        return true;
    else return false;
}

void init(){
    antrian.head=0;
    antrian.tail=0;
}
void print(){
    char hor,cl,cr;//border
    cl  = '\xCC' ; //connector-left
    cr  = '\xB9' ; //connector-right

    std::string line(74, hor);
    system("cls");
    draw();
    gotoxy(2,8); std::cout << cl << line << cr;
    Tittle();
    gotoxy(4,6);std::cout << "DAFTAR ANTRIAN";
    int j=0;
    if(!isEmpty()){
        gotoxy(5,7); std::cout << "NO";
        gotoxy(12,7);std::cout << "Nama";
        gotoxy(42,7); std::cout << "Alamat";
        for(int i=antrian.head; i<=antrian.tail-1;i++){
            gotoxy(5,9+j); std::cout << i + 1;
            gotoxy(12,9+j); std::cout <<antrian.nama[i];
            gotoxy(42,9+j); std::cout << antrian.alamat[i];
            j++;
        }
    }
    getchar();
    gotoxy(4,22); std::cout << ">"; getchar();
    ManageAntrian();
}

//Manage Data
void LoadData(){
    std::fstream is("items.txt");

    std::string item;
    while(std::getline(is, item)){
        int begin = 0;
        int pos = item.find(",");
        std::string id = item.substr(begin, pos);
        
        begin = pos + 1;
        pos = item.find(",",begin);
        std::string barang = item.substr(begin, pos - begin);

        begin = pos + 1;
        pos = item.find(",", begin);        
        std::string merek = item.substr(begin, pos - begin);
        
        begin = pos + 1;
        pos = item.find(",", begin);        
        std::string year = item.substr(begin, pos - begin);
        
        begin = pos + 1;
        std::string price = item.substr(begin);

        datas.push_back({id,barang,merek,stoi(year),stod(price)});
    }

    is.close();
}

void UpdateData(){
    // datas.clear();
    system("cls");
    // LoadData();
    draw();
    Tittle();
    std::ifstream is("items.txt");
    std::string item;
    int i=0;
    int temp;
    temp = 0;
    while(std::getline(is, item)){
        temp;
        int begin = 0;
        int pos = item.find(",");
        std::string id = item.substr(begin, pos);
        Mobil[i].ID = id;

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string barang = item.substr(begin, pos - begin);
        Mobil[i].Nama = barang; 

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string merek = item.substr(begin, pos - begin);
        Mobil[i].Brand = merek;

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string year = item.substr(begin, pos - begin);
        Mobil[i].Tahun = stoi(year);

        begin = pos + 1;
        std::string price = item.substr(begin);
        Mobil[i].Harga = stod(price);   
        temp++;
        i++;
    }
    is.close();
    std::string id,kode, barang, merek;
    int tahun;
    double harga;
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU UPDATE DATA";
    gotoxy(4,7); std::cout << "Harap Masukkan ID yang ingin diubah";
    gotoxy(4,19); std::cout << "Masukkan ID dibawah ini :";
    gotoxy(4,20); std::cout << "masukkan b/B untuk kembali";
    gotoxy(4,22); std::cin >> id;
    for(int i = 0; i!=temp; i++){
        if(Mobil[i].ID == id){
            gotoxy(5,8); std::cout << "ID      : "; std::cout << Mobil[i].ID;
            gotoxy(5,9); std::cout << "Nama    : "; std::cout << Mobil[i].Nama;
            gotoxy(5,10); std::cout << "Merek   : "; std::cout << Mobil[i].Brand;
            gotoxy(5,11); std::cout << "Tahun   : "; std::cout << Mobil[i].Tahun;
            gotoxy(5,12); std::cout << "Harga   : "; std::cout << Mobil[i].Harga;
            getchar();
            gotoxy(4,22);
            system("pause");
            system("cls");
            draw();
            Tittle();
            gotoxy(4,6); std::cout << "MENU UPDATE DATA";
            gotoxy(4,7); std::cout << "Harap Masukkan data dibawah ini : "; 
            gotoxy(5,8); std::cout << "ID      : "; std::cin >> Mobil[i].ID; std::cin.ignore();
            gotoxy(5,9); std::cout << "Nama    : "; std::getline(std::cin,Mobil[i].Nama);
            gotoxy(5,10); std::cout << "Merek   : "; std::getline(std::cin,Mobil[i].Brand);
            gotoxy(5,11); std::cout << "Tahun   : "; std::cin >> Mobil[i].Tahun;
            gotoxy(5,12); std::cout << "Harga   : "; std::cin >> Mobil[i].Harga;
        }

    }
    getchar();
    system("cls");
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU UPDATE DATA";
    gotoxy(4,7); std::cout << "Harap Masukkan ID yang ingin dicari";
    gotoxy(4,19); std::cout << "Data Sudah Tersimpan dengan Baik :";
    gotoxy(4,20); std::cout << "Tekan Enter untuk Kembali";
    gotoxy(4,22);
    std::cin.ignore();
    std::ofstream os("temp.txt");
    for(int i = 0; i != temp; i++){
        os << Mobil[i].ID << "," << Mobil[i].Nama 
        << "," << Mobil[i].Brand << "," << Mobil[i].Tahun 
        << "," << Mobil[i].Harga << std::endl;
    }
    os.close();
    remove("items.txt");
    rename("temp.txt", "items.txt");
    ManageData();
    
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
    gotoxy(5,12); std::cout << "3. Sort Data by Name";
    gotoxy(5,13); std::cout << "4. Search Data";
    gotoxy(5,14); std::cout << "5. Transaction";
    gotoxy(5,15); std::cout << "9. EXIT";
    gotoxy(4,20); std::cout << "Masukkan pilihan anda :";
    gotoxy(4,22); std::cout << "> "; std::cin>>a;
    switch(a){
        case 1:
            ManageAntrian();
            break;
        case 2:
            ManageData();
            break;
        case 3:
            SortingData();
            break;
        case 4:
            SearchData();
            break;
        case 5:
            doTransaction();
        case 9:
            Exit();
            break;
    }
}
bool repeat= true;

void doTransaction(){
    while(repeat)
        InputForm();
    system("cls");
}

void ManageAntrian(){
    int pilihan;
    int penuh, kosong;
    char value[30];
    char kembali;
    int n;
    n=1;
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
            inQueue();
            break;
        case 2: //Panggil Antrian 
            deQueue();
            break;
        case 3: //Daftar Antrian
            print();
            break;
        case 4:
            clear(); 
            break;
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
    std::fstream stud;
    stud.open("items.txt", std::ios::app);
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
    std::cin.ignore();
    gotoxy(22,9); std::getline(std::cin, ID);
        if(ID==""){
            gotoxy(22,9); std::cout << "Harap Masukkan ID";
            gotoxy(4,22); system("pause");
            goto awal;
        } 

    gotoxy(22,10); std::getline(std::cin, Nama);
        if(Nama==""){
            gotoxy(22,10); std::cout << "Harap Masukkan Nama";
            gotoxy(4,22); system("pause");
            goto awal;
        }
    gotoxy(22,11); std::getline(std::cin, Brand);
        if(Brand==""){
            gotoxy(22,11);std::cout << "Harap Masukkan Brand";
            gotoxy(4,22); system("pause");
            goto awal;
        }
    gotoxy(22,12); std::getline(std::cin, TahunTerbit);
        if(TahunTerbit==""){
            gotoxy(22,12);std::cout << "Harap Masukkan Tahun Terbit";
            gotoxy(4,22); system("pause");
            goto awal;
        }
    gotoxy(22,13); std::getline(std::cin, Harga);
        if(Harga==""){
            gotoxy(22,13);std::cout << "Harap Masukkan Harga";
            gotoxy(4,22); system("pause");
            goto awal;
        }
    gotoxy(4,20); std::cout << "Apakah anda yakin ingin menyimpan?(Y/T)";
    gotoxy(4,22);std::cin >> pilihan;
    if(pilihan=='y'||'Y'){
        stud<<ID<<","<<Nama<<","<<Brand<<","<<TahunTerbit<<","<<Harga<<'\n';
        stud.close();
        ManageData();
    }
    if(pilihan=='t'||'T'){
        ManageData();
    }
}

void Tittle(){
    gotoxy(31,3); std::cout << "SUM-SUM DEALER";
}

data find_data(std::string id){
    for(auto i : datas)
        if(i.ID == id)
            return i;

    return data{"", "", "", 0, 0};
}

void SearchData(){
    std::ifstream is("items.txt");
    std::string item;
    int i=0;
    int temp;
    temp = 0;
    while(std::getline(is, item)){
        temp;
        int begin = 0;
        int pos = item.find(",");
        std::string id = item.substr(begin, pos);
        Mobil[i].ID = id;

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string barang = item.substr(begin, pos - begin);
        Mobil[i].Nama = barang; 

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string merek = item.substr(begin, pos - begin);
        Mobil[i].Brand = merek;

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string year = item.substr(begin, pos - begin);
        Mobil[i].Tahun = stoi(year);

        begin = pos + 1;
        std::string price = item.substr(begin);
        Mobil[i].Harga = stod(price);   
        temp++;
        i++;
    }
    is.close();
    system("cls");

    std::string id;
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU SEARCH DATA";
    gotoxy(4,7); std::cout << "Harap Masukkan ID yang ingin dicari";
    gotoxy(4,19); std::cout << "Masukkan ID dibawah ini :";
    gotoxy(4,20); std::cout << "masukkan b/B untuk kembali";
    gotoxy(4,22); std::cin >> id;
    for(int i = 0; i< temp; i++){
        if(Mobil[i].ID == id){
            gotoxy(5,8); std::cout << "ID      : "; std::cout << Mobil[i].ID;
            gotoxy(5,9); std::cout << "Nama    : "; std::cout << Mobil[i].Nama;
            gotoxy(5,10); std::cout << "Merek   : "; std::cout << Mobil[i].Brand;
            gotoxy(5,11); std::cout << "Tahun   : "; std::cout << Mobil[i].Tahun;
            gotoxy(5,12); std::cout << "Harga   : "; std::cout << Mobil[i].Harga;
            
            gotoxy(4,22); system("pause");
            MenuAwal();
            break;
        }
        // if(Mobil[i].ID != id){
        //     gotoxy(5,10); std::cout << "Maaf data dengan ID" << id << "tidak ditemukan";
        // }
    }
    gotoxy(4,22); system("pause");
    MenuAwal();
   }

void SortingData(){
    
    std::ifstream is("items.txt");
    std::string item;
    int i=0;
    int temp;
    temp = 0;
    while(std::getline(is, item)){
        temp;
        int begin = 0;
        int pos = item.find(",");
        std::string id = item.substr(begin, pos);
        Mobil[i].ID = id;

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string barang = item.substr(begin, pos - begin);
        Mobil[i].Nama = barang; 

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string merek = item.substr(begin, pos - begin);
        Mobil[i].Brand = merek;

        begin = pos + 1;
        pos = item.find(",", begin);
        std::string year = item.substr(begin, pos - begin);
        Mobil[i].Tahun = stoi(year);

        begin = pos + 1;
        std::string price = item.substr(begin);
        Mobil[i].Harga = stod(price);   
        temp++;
        i++;
    }
    is.close();
    
    system("cls");
    char cl,cr,hor; //border
    hor = '\xCD' ; //horizontal-line
    cl  = '\xCC' ; //connector-left
    cr  = '\xB9' ; //connector-right
    
    std::string line(74, hor);
    // int j, k, temp;
    datas.clear();
    
    DrawForSort();
    gotoxy(31,3); std::cout << "Daftar Harga";
    gotoxy(4,6); std::cout << "NO";
    gotoxy(10,6); std::cout << "ID";
    gotoxy(19,6); std::cout << "NAMA";
    gotoxy(40,6); std::cout << "MEREK";
    gotoxy(52,6); std::cout << "TAHUN";
    gotoxy(64,6); std::cout << "HARGA";
    
    // std::sort(Mobil, Mobil + SIZE, acompare);
    int   m, n;
    data swap;
    for(n = 0; n<temp-1 ;n++ ){
        for(m=0; m<temp -1; m++){
            if(Mobil[m].Brand > Mobil[m+1].Brand){
                swap = Mobil[m];
                Mobil[m]=Mobil[m+1];
                Mobil[m+1] = swap;
            }
        }
    }

    for(int i = 0; i <= temp; i++){
        gotoxy(4,8 + i);std::cout<< i+1 ;
        gotoxy(10,8 + i); std::cout <<Mobil[i].ID;
        gotoxy(19,8 + i); std::cout << Mobil[i].Nama;
        gotoxy(40,8 + i); std::cout << Mobil[i].Brand;
        gotoxy(52,8 + i); std::cout << Mobil[i].Tahun;
        gotoxy(64,8 + i); std::cout << Mobil[i].Harga << "000";
    }
    getchar();
    gotoxy(4,49); std::cout << "> "; getchar();
    ManageData();
    // std::string id = item.substr
    
}
void ShowData(){
    char cl,cr,hor; //border
    hor = '\xCD' ; //horizontal-line
    cl  = '\xCC' ; //connector-left
    cr  = '\xB9' ; //connector-right
    
    std::string line(74, hor);
    
    system("cls");
    int j = 0;
    datas.clear();
    LoadData();
    DrawForSort();
    gotoxy(31,3); std::cout << "Daftar Harga";
    gotoxy(4,6); std::cout << "NO";
    gotoxy(10,6); std::cout << "ID";
    gotoxy(19,6); std::cout << "NAMA";
    gotoxy(40,6); std::cout << "MEREK";
    gotoxy(52,6); std::cout << "TAHUN";
    gotoxy(64,6); std::cout << "HARGA";
    gotoxy(2,7); std::cout << cl << line << cr;
    for(auto i : datas){
        gotoxy(4,8 + j);std::cout << j+1;
        gotoxy(10,8 + j); std::cout <<i.ID;
        gotoxy(19,8 + j); std::cout << i.Nama;
        gotoxy(40,8 + j); std::cout << i.Brand;
        gotoxy(52,8 + j); std::cout << i.Tahun;
        gotoxy(64,8 + j); std::cout << i.Harga << "000";
        j++;
    }
    
    gotoxy(4,47); std::cout << "Tekan Enter Untuk kembali";
    getchar();
    gotoxy(4,49); std::cout << "> "; getchar();
    ManageData();
}



void DeleteData(){
    datas.clear();
    system("cls");
    LoadData();
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU DELETE DATA";
    gotoxy(4,7); std::cout << "Data keberapa yang akan dihapus";
    gotoxy(4,19); std::cout << "Masukkan pada kolom di bawah ini :";
    gotoxy(4,20); std::cout << "masukkan b/B untuk kembali";
    
    std::vector<std::string> records;
    std::string line;
    std::ifstream records_input("items.txt");
    while(std::getline(records_input,line)){
        records.push_back(line);
    }
    records_input.close();

    size_t recno = records.size();
    size_t recno1;
    std::string nomor;
    int re;
    recno = re - 1;
    gotoxy(4,22); std::cin>>nomor;
    if(nomor=="b"){
        ManageData();
    }
    recno1 = stoi(nomor);   
    recno1--;
    records.erase(records.begin() + recno1);
    recno = records.size();
    std::ofstream os("temp.txt");
    for(size_t i = 0; i != recno; i++){
        os << records[i] << std:: endl;
    }
    os.close();
    remove("items.txt");
    rename("temp.txt", "items.txt");
    system("cls");
    draw();
    Tittle();
    gotoxy(4,6); std::cout << "MENU DELETE DATA";
    gotoxy(4,7); std::cout << "Data sudah terhapus";
    gotoxy(4,20); std::cout << "Tekan Enter untuk kembali";
    gotoxy(4,22); system("pause");
    
    ManageData();
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
    gotoxy(5,12); std::cout << "3. Sorting Data by Name";
    gotoxy(5,13); std::cout << "4. Update Data";
    gotoxy(5,14); std::cout << "5. Delete Data";
    gotoxy(5,15); std::cout << "6. Kembali";
    gotoxy(4,20); std::cout << "Masukkan pilihan anda : ";
    gotoxy(4,22); std::cout << "> "; std::cin>>a;
    switch (a)
    {
    case 1:
        TambahData();
        break;
    case 2: 
        ShowData();
        break;
    case 3:
        SortingData();
        break;
    case 4:
        UpdateData();
        break;
    case 5:
        DeleteData();
        break;
    case 6:
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

void TransactionFromQueue(){
    LoadData();
    system("cls");
    DrawForm();
    std::string nama;
    std::string alamat;
    double sub = 0;
    double total = 0;
    std::vector<DetailTransaction> details;
    std::vector<pembeli> buyers;
    int j =0;
    gotoxy(45, 2); std::cout << "NAMA   : ";
    gotoxy(45, 3); std::cout << "Alamat : ";
    std::cin.ignore();
    gotoxy(53, 2); std::getline(std::cin, nama);
    gotoxy(53, 3); std::getline(std::cin, alamat);
    int i=0;
    while(true){
        for(auto d:details){
            gotoxy(4,8 + i); std::cout << d.item.ID;
            gotoxy(14,8 + i); std::cout << d.item.Nama;
            gotoxy(45, 8 + i); std::cout << d.item.Harga;
            gotoxy(56,8 + i); std::cout << d.qty;
            sub = d.item.Harga * d.qty;
            gotoxy(66, 8 + i); std::cout << sub;
            i++;
        }
        total += sub;
        gotoxy(56,30); std::cout << total;

        form:
        gotoxy(4,8 + j); std::string id;
        std::getline(std::cin, id);
        if(id == "!")
            return;

        if(id == "#"){
            repeat = false;
            return;
        }

        if(id == "")
            break;
        
        data i = find_data(id);
        if(id != i.ID)
            {
                goto form;
            }

        if(i.ID == "")
            continue;

        double qty = 1;
        gotoxy(14, 8 +j); std::cout << i.Nama;
        gotoxy(45, 8 + j); std::cout << i.Harga;
        gotoxy(56, 8 + j); std::cout << qty;

        std::string in_qty;
        std::cin.ignore();
        gotoxy(56, 8); std::getline(std::cin, in_qty);
        if(in_qty != "")
            qty = stod(in_qty);
        
        details.push_back({{i.ID, i.Nama, i.Brand, i.Tahun, i.Harga}, qty});
        buyers.push_back({{{i.ID, i.Nama,i.Brand,i.Tahun,i.Harga}, qty,}, nama, alamat});
        j++;
    }

    gotoxy(56,29); std::string in_pay;
    std::getline(std::cin, in_pay);

    if(in_pay == "!")
        return;
    
    DetailTransaction bayar;
    double pay;
    bayar.pay = stod(in_pay);
    gotoxy(56,31); std::cout << bayar.pay;
    gotoxy(56,31); std::cout << bayar.pay - total;

    gotoxy(4,34); std::cout << "> ";

    // std::fstream trs;
    // trs.open("transaksi.txt", std::ios::app);
    // for(auto i : details){
    //     trs <<"," << i.pay << "," << i.qty <<std::endl;
    // }
    // trs.close();
    std::cin.get();
    MenuAwal();
}

void gotoxy(int x, int y, std::string text){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
    std::cout << text;
}

void DrawForSort(){
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
    for(a=1; a<50; a++){
        gotoxy(2,a+1);
        std::cout << ver;
        gotoxy(77, a+1);
        std::cout << ver;
    }
    gotoxy(2,7); std::cout << cl << line << cr;
    gotoxy(2,50);
    std::cout << bl << line << br; //for the bottom line
    gotoxy(2,5);
    std::cout << cl << line << cr;
    gotoxy(2,48);
    std::cout << cl << line << cr;
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

    
}

void InputForm(){
    LoadData();
    system("cls");
    DrawForm();
    std::string nama;
    std::string alamat;
    double sub = 0;
    double total = 0;
    std::vector<DetailTransaction> details;
    std::vector<pembeli> buyers;
    int j =0;
    gotoxy(45, 2); std::cout << "NAMA   : ";
    gotoxy(45, 3); std::cout << "Alamat : ";
    std::cin.ignore();
    gotoxy(53, 2); std::getline(std::cin, nama);
    gotoxy(53, 3); std::getline(std::cin, alamat);
    int i=0;
    while(true){
        for(auto d:details){
            gotoxy(4,8 + i); std::cout << d.item.ID;
            gotoxy(14,8 + i); std::cout << d.item.Nama;
            gotoxy(45, 8 + i); std::cout << d.item.Harga;
            gotoxy(56,8 + i); std::cout << d.qty;
            sub = d.item.Harga * d.qty;
            gotoxy(66, 8 + i); std::cout << sub;
            i++;
        }
        total += sub;
        gotoxy(56,30); std::cout << total;

        form:
        gotoxy(4,8 + j); std::string id;
        std::getline(std::cin, id);
        if(id == "!")
            return;

        if(id == "#"){
            repeat = false;
            return;
        }

        if(id == "")
            break;
        
        data i = find_data(id);
        if(id != i.ID)
            {
                goto form;
            }

        if(i.ID == "")
            continue;

        double qty = 1;
        gotoxy(14, 8 +j); std::cout << i.Nama;
        gotoxy(45, 8 + j); std::cout << i.Harga;
        gotoxy(56, 8 + j); std::cout << qty;

        std::string in_qty;
        std::cin.ignore();
        gotoxy(56, 8); std::getline(std::cin, in_qty);
        if(in_qty != "")
            qty = stod(in_qty);
        
        details.push_back({{i.ID, i.Nama, i.Brand, i.Tahun, i.Harga}, qty});
        buyers.push_back({{{i.ID, i.Nama,i.Brand,i.Tahun,i.Harga}, qty,}, nama, alamat});
        j++;
    }

    gotoxy(56,29); std::string in_pay;
    std::getline(std::cin, in_pay);

    if(in_pay == "!")
        return;
    
    DetailTransaction bayar;
    double pay;
    bayar.pay = stod(in_pay);
    gotoxy(56,31); std::cout << bayar.pay;
    gotoxy(56,31); std::cout << bayar.pay - total;
    PrintBill(details);
    SaveTransaction(buyers);
    gotoxy(4,34); std::cout << "> ";

    // std::fstream trs;
    // trs.open("transaksi.txt", std::ios::app);
    // for(auto i : details){
    //     trs <<"," << i.pay << "," << i.qty <<std::endl;
    // }
    // trs.close();
    std::cin.get();
    MenuAwal();
}

void DrawForm(){
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

    gotoxy(4,2); std::cout << "SUM-SUM DEALER";
    std::string line(74, hor);
    gotoxy(2,1);
    std::cout << tl << line << tr; //for the top line
    //vertical-line in the left and right of the box
    for(a=1; a<35; a++){
        gotoxy(2,a+1);
        std::cout << ver;
        gotoxy(77, a+1);
        std::cout << ver;
    }

    gotoxy(2,35);
    std::cout << bl << line << br; //for the bottom line
    gotoxy(2,5);
    std::cout << cl << line << cr;
    gotoxy(2,28);std::cout << cl << line << cr;
    gotoxy(2,7);std::cout << cl << line << cr;
    gotoxy(2, 33);  std::cout << cl << line << cr;
    gotoxy(45,29); std::cout << "Bayar   :";
    gotoxy(45,30); std::cout << "Total   :";
    gotoxy(45,31); std::cout << "Kembali :";
    gotoxy(4,6); std::cout << "ID";
    gotoxy(14,6); std::cout << "Nama";
    gotoxy(45,6);std::cout << "Price";
    gotoxy(56,6); std::cout << "QTY";
    gotoxy(66,6); std::cout << "Sub";
    
}


void Exit(){
    system("cls");
    draw();
    char a;
    Tittle();
    gotoxy(4,6); std::cout << "GOOD BYE";
    gotoxy(5,8); std::cout << "Aplikasi ini dibuat oleh : ";
    gotoxy(5,10); std::cout << "[1] Patriot Kusuma Sejati";
    gotoxy(62,10); std::cout << "[18.11.1819]";
    gotoxy(5,11); std::cout << "[2] Vito Nur Ariyanto";
    gotoxy(62,11); std::cout << "[18.11.1830]";
    gotoxy(5,12); std::cout << "[3] Anselmus Rusdiatmaja";
    gotoxy(62,12); std::cout << "[18.11.1856]";
    gotoxy(5,13); std::cout << "[4] Sidiq Agung Maridia";
    gotoxy(62,13); std::cout << "[18.11.1871]";
    gotoxy(5,14); std::cout << "[5] Yesica Jacinda Asmara Devi";
    gotoxy(62,14); std::cout << "[18.11.1853]";
    gotoxy(5,15); std::cout << "[6] Marsha Recha Hapsari";
    gotoxy(62,15); std::cout << "[18.11.1814]";
    gotoxy(5,16); std::cout << "[7] Sumiyati";
    gotoxy(62,16); std::cout << "[18.11.1810]";
    gotoxy(4,20); std::cout << "APAKAH YAKIN INGIN KELUAR (Y/T)";
    gotoxy(4,22); std::cout << "> "; std::cin >>a;
    if(a=='y'||a=='Y'){
        system("cls");
        exit(1);
    }
    if(a=='t'||a=='T'){
        MenuAwal();
    }
    
}