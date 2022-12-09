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
    Struct untuk data membership
    yang akan disimpan selama
    program dijalankan
*/
typedef struct {
    char username[10];
    char password[20];
    char email[30];
    char noTelp[20];
    char nama[30];
    char tipeMembership[10];
} daftarDataMembership;
extern daftarDataMembership dataMembership;

/*
    Union yang digunakan untuk menyimpan
    data pembeli (membership/tidak)
*/
typedef union {
    daftarDataMembership dataMembership;
    char guest[20];
} tipePembeli;

/*
    Struct untuk data pekerja
    yang akan disimpan selama
    program dijalankan
*/
typedef struct {
    char username[10];
    char password[20];
    char email[30];
    char noTelp[20];
    char nama[30];
    char jabatan[20];
} daftarDataPekerja;
extern daftarDataPekerja dataKaryawan;
extern daftarDataPekerja dataPemilik;

/*
    Union yang akan digunakan saat berurusan dengan file
    write: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    read:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
*/
typedef union {
    daftarDataMembership membership;
    daftarDataPekerja karyawan;
    daftarDataPekerja pemilik;
} tipeData;
extern tipeData write;
extern tipeData read; //note: menghapus variabel struct 'data'

#endif // VARIABEL_H
