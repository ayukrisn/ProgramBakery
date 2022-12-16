/*
==================================================
    Header file "variabel.h" berisi deklarasi
    dari variabel-variabel yang akan digunakan
    pada program ini
==================================================
*/

/*
    IFNDEF, DEFINE, DAN ENDIF
    Header guard yang digunakan untuk mencegah
    double inclusion saat menangani include directive
*/
#ifndef VARIABEL_H
#define VARIABEL_H


/*
    Struct untuk data pengguna
    yang akan disimpan selama
    program dijalankan
*/
typedef struct {
    char username[20];
    char password[20];
    char nama[30];
} daftarData;
extern daftarData dataKaryawan;
extern daftarData dataPemilik;
extern daftarData dataMembership;

/*
    Union yang akan digunakan saat berurusan dengan file
    write: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    read:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
*/
typedef union {
    daftarData membership;
    daftarData karyawan;
    daftarData pemilik;
} tipeData;
extern tipeData writeUser;
extern tipeData readUser; //note: menghapus variabel struct 'data'

/*
    Struct yang digunakan untuk menyimpan
    data menu makanan dan saat berurusan dengan file
    writeMenu: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    readMenu:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
    dataMenu:  variabel yang digunakan untuk menyimpan data
           selama program dijalankan
*/
typedef struct {
    char jenisMakanan[10];
    char kodeMakanan[5];
    char namaMakanan[20];
    char deskripsiMakanan[100];
    float hargaMakanan;
    int jamJadwalStockPagi;
    int jamJadwalStockSiang;
    int jamJadwalStockSore;
    int stock;
} dataMenu;
extern dataMenu simpanMenu[50];
extern dataMenu writeMenu;
extern dataMenu readMenu;

typedef struct {
    int pagi;
    int siang;
    int sore;
} restock;
extern restock jamRestock;

/*
    Struct yang digunakan pada saat
    berurusan dengan stock makanan
*/
typedef struct {
    char waktuRestock[30]; //nanti pake asctime
    char namaKaryawan[20]; //nanti strcpy("dataKaryawan.nama", "logRestock.namaKaryawan")
    int stockLama; //stock sebelum restock
    int jumlahRestock; //banyaknya restock
    int stockSkrg; //stock setelah restock
} logRestock;
extern logRestock writeStock;
extern logRestock readStock;

typedef struct {
    char namaMakanan;
    char kodeMakanan;
    float hargaSatuan;
    int banyakPembelian;
    float hargaTotal;
} detailTransaksi;
extern detailTransaksi DTransaksi[12];

typedef struct {
    char kodeTransaksi;
    char usernameM[20]; //strcpy dari dataMembership.username, klo pelanggan biasa strcpy "GuestCostumer"
    char namaPelanggan[30]; //nama mungkin bisa dari dataMembership.nama atau variabel char nama buat pelanggan biasa
    char namaKaryawan[30];
    char usernameK[20];
    char waktuTransaksi[30];
    int totalPembelian;
    float hargaTotal;
} dataTransaksi;
extern dataTransaksi Transaksi;

/*
    Bool untuk memastikan apakah restock sudah
    dilakukan atau belum
*/
extern bool updateStockPagi;
extern bool updateStockSiang;
extern bool updateStockSore;
#endif // VARIABEL_H
