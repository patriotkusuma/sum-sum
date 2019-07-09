#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <ctype.h>
#include <iostream>
#include <iomanip>
#define SIZE 500

using namespace std;

typedef struct
{
        int tgl, bln, thn;
} data_tgl;
typedef struct
{
        long int NIM;
        char nama[25];
        char sex;
        char tempat[20];
        data_tgl tgl_lahir;
        char jurusan[15];
        char fakultas[15];
        char alamat[40];
        char kabupaten[20];
        char propinsi[20];
} data_mhs;


int Menu_Utama(void);
void Menu_Daftar(void);
void Menu_Cari(void);
void Entry_Data(void);
void Menu_Hapus(void);
void urut_NIM(data_mhs mahasiswa[], int n);
void urut_nama(data_mhs mahasiswa[], int n);
void cari_NIM(data_mhs mahasiswa[], int n);
void cari_nama(data_mhs mahasiswa[], int n);
void hapus_NIM(data_mhs mahasiswa[], int n);
void hapus_data(void);
void sort_NIM(data_mhs mahasiswa[], int n);
void print_record_header(void);
void print_record(data_mhs mahasiswa[], int n);
void print_record2(data_mhs mahasiswa[], int n);
void tukar(data_mhs *mahasiswa, int a, int b);
int valid_date(const int dd, const int mm, const int yyyy);
int valid_sex(const char sex);
int valid_char(char *ch);
void convert_to_upper_array(char *ch);
void convert_to_upper_char(char *ch);
void check_line_printed(int *line_printed, int max_line);
void garis1(int n);
void garis2(int n);
void header(void);
void keluar(void);

int main(void)
{

     int choice = 0;
     header();
   while((choice = Menu_Utama()) != 0)
     {
                   switch(choice)
                   {
                                 case 1: Entry_Data(); break;
                                 case 2: Menu_Daftar(); break;
                                 case 3: Menu_Cari(); break;
         case 4: Menu_Hapus(); break;
                                 case 5: keluar();
         default: printf("Pilihan Salah!!\n\n");
          getch();
          Menu_Utama(); break;
                   }
     }
     return 0;
}

int Menu_Utama(void)
{
    int choice;

 system("cls");
 garis1(79);
 cout << setw(53) << "+-------------------------+" << endl;
 cout << setw(53) << "|  ###   MENU UTAMA  ###  |" << endl;
 cout << setw(53) << "+-------------------------+" << endl;
 cout << setw(53) << "| 1. Entry Data Mahasiswa |" << endl;
 cout << setw(53) << "| 2. Daftar Mahasiswa     |" << endl;
 cout << setw(53) << "| 3. Cari Data Mahasiswa  |" << endl;
 cout << setw(53) << "| 4. Hapus Data Mahasiswa |" << endl;
 cout << setw(53) << "| 5. Keluar               |" << endl;
 cout << setw(53) << "+-------------------------+" << endl << endl;
 garis1(79);
 cout << setw(47) << "Masukkan pilihan : ";
 cin >> choice;
   
 return choice;
}

void Menu_Daftar(void)
{
     int choice;
     data_mhs mahasiswa[SIZE];
     FILE *file_ptr;
     int i=0;
     file_ptr = fopen("dbase.dat", "rb");
     if(file_ptr == NULL)
     {
   printf("Data tidak ditemukan!!\nSilahkan entry data dulu!!\n");
   getch();
   keluar();
     }
     while(!feof(file_ptr))
     {
                           fread(&mahasiswa[i], sizeof(data_mhs), 1, file_ptr);
                           i++;
     }
     fclose(file_ptr);

  system("cls");
     do
     {
   garis2(80);
   pil :
   cout << setw(55) << "+-----------------------------+" << endl;
   cout << setw(55) << "|  **  DAFTAR MAHASISWA  **   |" << endl;
   cout << setw(55) << "+-----------------------------+" << endl;
   cout << setw(55) << "| 1. Urutkan Berdasarkan NIM  |" << endl;
   cout << setw(55) << "| 2. Urutkan Berdasarkan Nama |" << endl;
   cout << setw(55) << "| 3. Kembali ke Menu Utama    |" << endl;
   cout << setw(55) << "+-----------------------------+" << endl << endl;
   garis2(80);
   cout << setw(50) << "Masukkan pilihan : ";
   cin >> choice;

              switch(choice)
              {
                            case 1: urut_NIM(mahasiswa, i-1); break;
                            case 2: urut_nama(mahasiswa, i-1); break;
                            case 3: break;
                            default: printf("Pilihan Salah!!\n"); getch(); system("cls"); goto pil; break;
              }
     }
     while(choice != 3);
}

void Menu_Cari(void)
{
     int choice;
     data_mhs mahasiswa[SIZE];
     FILE *file_ptr;
     int i=0;
    
     file_ptr = fopen("dbase.dat", "rb");
     if(file_ptr == NULL)
     {
   printf("Data tidak ditemukan!!\nSilahkan entry data dulu!!\n");
   getch();
   keluar();
     }
     while(!feof(file_ptr))
     {
                           fread(&mahasiswa[i], sizeof(data_mhs), 1, file_ptr);
                           i++;
     }
     fclose(file_ptr);

  system("cls");
     do
     {
   garis2(80);
   pil :
   cout << setw(55) << "+-----------------------------+" << endl;
   cout << setw(55) << "|  **   PENCARIAN DATA   **   |" << endl;
   cout << setw(55) << "+-----------------------------+" << endl;
   cout << setw(55) << "| 1. Berdasarkan NIM          |" << endl;
   cout << setw(55) << "| 2. Berdasarkan Nama         |" << endl;
   cout << setw(55) << "| 3. Kembali ke Menu Utama    |" << endl;
   cout << setw(55) << "+-----------------------------+" << endl << endl;
   garis2(80);
   cout << setw(50) << "Masukkan pilihan : ";
   cin >> choice;
  
              switch(choice)
              {
                            case 1: cari_NIM(mahasiswa, i-1); break;
                            case 2: cari_nama(mahasiswa, i-1); break;
                            case 3: break;
                            default: printf("Pilihan Salah!!\n"); getch(); system("cls"); goto pil; break;
              }
     }
     while(choice != 3);
}

void Menu_Hapus(void)
{
 data_mhs mahasiswa[SIZE];
    FILE *file_ptr;
    int i=0;
    
    file_ptr = fopen("dbase.dat", "rb");
    if(file_ptr == NULL)
    {
   printf("Data tidak ditemukan!!\nSilahkan entry data dulu!!\n");
   getch();
   keluar();
    }
    while(!feof(file_ptr))
    {
                         fread(&mahasiswa[i], sizeof(data_mhs), 1, file_ptr);
                         i++;
    }
    fclose(file_ptr);

 hapus_data();
}

void Entry_Data(void)
{
     FILE *file_ptr;
     char lagi;
     char str[10];
     char temp[8];
     data_mhs mahasiswa;

  system("cls");
     do
     {
              printf("NIM \t\t\t: 0"); fflush(stdin);
     gets(temp); sscanf(temp, "%li", &mahasiswa.NIM);
     do
     {
      printf("Nama \t\t\t: "); fflush(stdin);
      gets(mahasiswa.nama);
      convert_to_upper_array(mahasiswa.nama);
     }
     while(valid_char(mahasiswa.nama));
              do
              {
                 printf("Jenis Kelamin[L/P] \t: "); fflush(stdin);
                 scanf("%c", &mahasiswa.sex);
                 convert_to_upper_char(&mahasiswa.sex);
              }
              while(valid_sex(mahasiswa.sex));
     do
     {
      printf("Tempat Lahir \t\t: "); fflush(stdin);
      gets(mahasiswa.tempat);
      convert_to_upper_array(mahasiswa.tempat);
     }
     while(valid_char(mahasiswa.tempat));
              do
              {
                 printf("Tgl Lahir [hh/bb/tttt]\t: "); fflush(stdin);
                 scanf("%2d%[    -/.,\n]%2d%[     -/.,\n]%4d", &mahasiswa.tgl_lahir.tgl, str, &mahasiswa.tgl_lahir.bln, str, &mahasiswa.tgl_lahir.thn);
              }
              while(valid_date(mahasiswa.tgl_lahir.tgl, mahasiswa.tgl_lahir.bln, mahasiswa.tgl_lahir.thn));
     do
     {
      printf("Jurusan \t\t: "); fflush(stdin);
      gets(mahasiswa.jurusan);
      convert_to_upper_array(mahasiswa.jurusan);
     }
     while(valid_char(mahasiswa.jurusan));
     do
     {
      printf("Fakultas \t\t: "); fflush(stdin);
      gets(mahasiswa.fakultas);
      convert_to_upper_array(mahasiswa.fakultas);
     }
     while(valid_char(mahasiswa.fakultas));
     printf("Alamat \t\t\t: "); fflush(stdin);
     gets(mahasiswa.alamat);
     convert_to_upper_array(mahasiswa.alamat);
              do
     {
      printf("Kota/Kabupaten \t\t: "); fflush(stdin);
      gets(mahasiswa.kabupaten);
      convert_to_upper_array(mahasiswa.kabupaten);
     }
     while(valid_char(mahasiswa.kabupaten));
     do
     {
      printf("Propinsi \t\t: "); fflush(stdin);
      gets(mahasiswa.propinsi);
      convert_to_upper_array(mahasiswa.propinsi);
     }
     while(valid_char(mahasiswa.propinsi));
             
              file_ptr = fopen("dbase.dat", "ab");
              fwrite(&mahasiswa, sizeof(data_mhs), 1, file_ptr);
              fclose(file_ptr);
              printf("\nEntry Data Mahasiswa lagi [Y/T]?"); fflush(stdin);
              scanf("%c", &lagi);
     }
     while(lagi == 'y' || lagi == 'Y');
}


void urut_NIM(data_mhs mahasiswa[], int n)
{
     int j, line_printed = 0;
     sort_NIM(mahasiswa, n);
  system("cls");
  cout << endl << endl;
  garis2(79);
  cout << endl;
  cout << setw(55) << "DAFTAR MAHASISWA DIURUTKAN BERDASARKAN NIM"<< endl;
  cout << endl;
  cout << endl;
     print_record_header();
     for(j=0; j<n; j++)
     {
              print_record(mahasiswa, j);
              line_printed++;
              check_line_printed(&line_printed, 22);
     }
     printf("\nMaaf! karena terbatasnya layar, sebagian data tidak ditampilkan");
     printf("\nUntuk menampilkan data lengkap silahkan masuk ke menu pencarian");
     printf("\nTekan sembarang tombol...\n");
     getch();
  system("cls");
}

void urut_nama(data_mhs mahasiswa[], int n)
{
     int j, k, line_printed = 0;
     for(j=0; j<n; j++)
     {
              for(k=n-1; k>j; k--)
              {
                         if(strcmp(mahasiswa[k].nama, mahasiswa[k-1].nama) < 0)
                         tukar(mahasiswa, k, k-1);
              }
     }
  system("cls");
  cout << endl << endl;
  garis2(79);
  cout << endl;
  cout << setw(60) << "DAFTAR MAHASISWA DIURUTKAN BERDASARKAN NAMA"<< endl;
  cout << endl;
  print_record_header();
     for(j=0; j<n; j++)
     {
              print_record(mahasiswa, j);
              line_printed++;
              check_line_printed(&line_printed, 22);
     }
     printf("\nMaaf! karena terbatasnya layar, sebagian data tidak ditampilkan");
     printf("\nUntuk menampilkan data lengkap silahkan masuk ke menu pencarian");
     printf("\nTekan Sembarang Tombol...\n");
  getch();
  system("cls");
}

void cari_NIM(data_mhs mahasiswa[], int n)
{
     int j;
     long int id_num=0;
     printf("\n\nMasukkan NIM yang akan dicari : 0");
     scanf("%li", &id_num);
     for(j=0; j<n; j++)
     {
              if(mahasiswa[j].NIM == id_num)
              {
      printf("\nHasil pencarian\n");
                  printf("===============\n\n");
                  print_record2(mahasiswa, j);
                  break;
              }
              if(j == n-1 && mahasiswa[j].NIM != id_num)
                   printf("Data tidak ditemukan!!\n");
     }
  printf("\nTekan Sembarang Tombol..\n");
  getch();
  system("cls");
}

void cari_nama(data_mhs mahasiswa[], int n)
{
     int j;
     char name[20];
     printf("\n\nMasukkan nama yang dicari : "); fflush(stdin);
     gets ( name);
     convert_to_upper_array(name);
     for(j=0; j<n; j++)
     {
   if(!strcmp(mahasiswa[j].nama, name))
         {
    printf("\nHasil pencarian\n");
             printf("===============\n\n");
    print_record2(mahasiswa, j);
    break;
   }
   if(j == n-1 && mahasiswa[j].nama != name)
    printf("Data tidak ditemukan!!\n");
  }
  printf("\nTekan Sembarang Tombol...\n");
  getch();
  system("cls");
}

void sort_NIM(data_mhs mahasiswa[], int n)
{
 int j, k;
 for(j=0; j<n; j++)
 {
  for(k=n-1; k>j; k--)
  {
   if(mahasiswa[k].NIM < mahasiswa[k-1].NIM)
    tukar(mahasiswa, k, k-1);
  }
 }
}

void hapus_data(void)
{
 char yes;
 system("cls");
 cout << endl << endl << endl << endl;
 cout << setw(65) << "Apakah anda yakin akan menghapus seluruh database? [Y/T]";
 cin >> yes;
 if(yes == 'y' || yes == 'Y')
 {
  system("del dbase.dat");
  cout << endl << endl << endl;
  cout << setw(60) << "Seluruh database telah dihapus dengan sukses" << endl;
 }
 getch();
 system("cls");
}


void print_record_header(void)
{
 printf("===============================================================================\n");
 printf("   NIM    |      NAMA      |JK | TGL LAHIR  |   JURUSAN   | FAKULTAS | ALAMAT  \n");
 printf("----------+----------------+---+------------+-------------+----------+---------\n");
}

void print_record(data_mhs mahasiswa[], int j)
{
 printf("0%-8li | %-14s | %c | %2d/%2d/%4d | %-10s | %-8s | %-10s\n", mahasiswa[j].NIM, mahasiswa[j].nama, mahasiswa[j].sex, mahasiswa[j].tgl_lahir.tgl, mahasiswa[j].tgl_lahir.bln, mahasiswa[j].tgl_lahir.thn, mahasiswa[j].jurusan, mahasiswa[j].fakultas, mahasiswa[j].kabupaten);
}

void print_record2(data_mhs mahasiswa[], int j)
{
 printf("%-15s : 0%li\n", "NIM", mahasiswa[j].NIM);
 printf("%-15s : %s\n", "Nama", mahasiswa[j].nama);
 printf("%-15s : %c\n", "Jenis Kelamin", mahasiswa[j].sex);
 printf("%-15s : %s\n", "Tempat lahir", mahasiswa[j].tempat);
 printf("%-15s : %2d/%2d/%2d\n", "Tanggal lahir", mahasiswa[j].tgl_lahir.tgl, mahasiswa[j].tgl_lahir.bln, mahasiswa[j].tgl_lahir.thn);
 printf("%-15s : %s\n", "Jurusan", mahasiswa[j].jurusan);
 printf("%-15s : %s\n", "Fakultas", mahasiswa[j].fakultas);
 printf("%-15s : %s\n", "Alamat", mahasiswa[j].alamat);
 printf("%-15s : %s\n", "Kabupaten", mahasiswa[j].kabupaten);
 printf("%-15s : %s\n", "Propinsi", mahasiswa[j].propinsi);
}

void tukar(data_mhs *mahasiswa, int a, int b)
{
 data_mhs temp;
 temp = mahasiswa[a];
 mahasiswa[a] = mahasiswa[b];
 mahasiswa[b] = temp;
}

int valid_date(const int dd, const int mm, const int yyyy)
{
 int tgl_of_bulan[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
 int i, error = 0;

 if(mm < 12)
 {
          for(i=1; i<12; i++)
          {
                   if(mm == i)
                   {
                         error = 0; break;
                   }
          }
          if(i == 12 && mm != i)
               error = 1;
 }
 
   if(dd > 31 || dd < 1 || dd > tgl_of_bulan[mm - 1])
  error = 1;

 if(1900 <= yyyy && yyyy <= 9999)
 {
          if(mm == 2)
          {
                if(!(yyyy % 4) && (yyyy % 100) || !(yyyy % 400))
                          if(dd == 29)
                    error = 0;
          }
 }
 else
     error = 1;
 if(error == 1)
 {
  printf("Upss!! Format tanggal salah!\n");
 }
 getch();
 return error;
}

int valid_sex(const char sex)
{
 if(sex != 'L' && sex != 'P')
 {
  printf("Kode salah --> %c\n", sex);
  getch();
  return 1;
 }
 return 0;
}

int valid_char(char *ch)
{
 if((*ch >= 'A' || *ch >= 'a') && (*ch <= 'Z' || *ch <= 'z'))
 {
  return 0;
 }
 else
 {
  cout << "Isi dengan huruf!!" << endl;
  return 1;
 }
}

void convert_to_upper_array(char *ch)
{
 while(*ch != '\0')
 {
  if(islower(*ch))
   *ch = toupper(*ch);
  ++ch;
 }
}

void convert_to_upper_char(char *ch)
{
 if(islower(*ch))
  *ch = toupper(*ch);
}

void check_line_printed(int *line_printed, int max_line)
{
 if(*line_printed >= max_line)
 {
  printf("Tekan sembarang tombol..");
  getch();
  printf("\n");
  *line_printed = 0;
 }
}

void garis1(int n)
{
 for(int i=0; i<n; i++)
 {
  cout << "*";
 }
 cout << "\n";
}

void garis2(int n)
{
 for(int i=0; i<n; i++)
 {
  cout << "#";
 }
 cout << "\n";
}

void header(void)
{
 cout << endl << endl << endl << endl << endl << endl << endl;
    garis2(80);
 cout << setw(65) << "D3 Informatika - Universitas Negeri Surabaya\n\n";
 cout << setw(43) << "2007\n\n";
 garis2(80);
 cout << endl << endl << endl;
 cout << setw(54) << "press any key to continue...";
 getch();
}

void keluar(void)
{
 system("cls");
 cout << "\n\n\n\n\n\n\n\n";
 cout << setw(70) << "Terima kasih telah menggunakan program ini\n\n\n\n\n\n\n\n";
 getch();
 exit(1);
}