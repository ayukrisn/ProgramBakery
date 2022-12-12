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
    Union yang digunakan untuk menyimpan
    data pembeli (membership/tidak)
*/
typedef union {
    daftarData dataMembership;
    char guest[20];
} tipePembeli;

/*
    Struct yang digunakan untuk menyimpan
    data menu dan sat berurusan dengan file
    writeMenu: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    readMenu:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
    dataMenu:  variabel yang digunakan untuk menyimpan data
           selama program dijalankan
*/

typedef struct
{
    char namaMakanan[20];
    char deskripsiMakanan[100];
    float hargaMakanan;
} dataMenu;
extern dataMenu simpanMenu;
extern dataMenu writeMenu;
extern dataMenu readMenu;
#endif // VARIABEL_H
