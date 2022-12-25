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
extern char namaGuest[20]; //bila pengguna bukan member

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
extern dataMenu writeMenu;
extern dataMenu readMenu;

/*
    Struct yang digunakan pada saat
    berurusan dengan jadwal restock
*/
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
    char waktuRestock[30]; //menggunakan asctime
    char namaYgRestock[20]; //nama org yg melakukan restock
    int stockLama; //stock sebelum restock
    int jumlahRestock; //banyaknya restock
    int stockSkrg; //stock setelah restock
} logRestock;
extern logRestock writeStock;
extern logRestock readStock;

/*
    Struct untuk menyimpan data detail
    transaksi
*/
typedef struct {
    char namaMakanan[20];
    char kodeMakanan[5];
    float hargaSatuan;
    int banyakPembelian;
    float hargaTotal;
} detailTransaksi;
extern detailTransaksi DTransaksi[12];

/*
    Struct untuk menyimpan data transaksi
*/
typedef struct {
    char namaPelanggan[30]; 
    char namaKaryawan[30];
    char waktuTransaksi[30];
    int totalPembelian;
    float hargaSblmDiskon;
    float totalDiskon;
    float hargaTotal;
    float jumlahPembayaran;
    float jumlahKembalian;
} dataTransaksi;
extern dataTransaksi transaksi;

/*
    Struct untuk menyimpan tipe diskon
    untuk membership
*/
typedef struct {
    float d50k;
    float d100k;
    float d200k;
} tipeDiskon;
extern tipeDiskon nominalDiskon;


/*
    Bool untuk memastikan apakah restock sudah
    dilakukan atau belum. Bila sudah diupdate,
    variabel akan diset ke true
*/
extern bool updateStockPagi;
extern bool updateStockSiang;
extern bool updateStockSore;

/*
    Bool untuk memastikan apakah pelanggan yang masuk merupakan 
    pelanggan dengan membership atau tidak
*/
extern bool isPelanggan;
extern bool isMember;

/*
    Bool untuk memastikan apakah yang masuk merupakan
    karyawan atau pemilik
*/
extern bool isKaryawan;
extern bool isPemilik;

#endif // VARIABEL_H
