/*
==================================================
    Source code "transaksi.c" berisi definisi dari
    fungsi/prosedur untuk mmencetak dan melihat
    struk

    Kontributor: I Gusti Ayu Krisna Kusuma Dewi
                 (2205551072)
    Merapikan kode dan memeriksa bug:
                 Ni Kadek Ari Lestari
                (2205551069)
    Informasi lengkap dapat dilihat pada history
    commit GitHub
==================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesAdmin.h"
#include "aksesPelanggan.h"
#include "pendukung.h"
#include "daftarMenu.h"
#include "restock.h"
#include "transaksi.h"

/*
    =============================
    FUNGSI UNTUK MENCETAK STRUK
    =============================
*/

dataRiwayatTransaksi writeLogTransaksi;
dataRiwayatTransaksi readLogTransaksi;

/* -----------------------------
    Mendapatkan waktu saat ini
    (tanggal, bulan, dan tahun)
   -----------------------------
*/
void waktuSaatIni()
{
    time_t waktu = time(NULL);
    struct tm *waktuLokal = localtime(&waktu);
    writeLogTransaksi.tahunTransaksi = waktuLokal->tm_year + 1900;
    writeLogTransaksi.bulanTransaksi = waktuLokal->tm_mon + 1;
    writeLogTransaksi.tanggalTransaksi = waktuLokal->tm_mday;
}

/* ----------------------------------------------
    Mendapatkan detail untuk riwayat transaksi
    agar dapat dipanggil sesuai dengan keinginan
    ---------------------------------------------
*/
void infoStruk()
{
    waktuSaatIni();
    if(isMember) {
        strcpy(writeLogTransaksi.usernamePelanggan, dataMembership.username);
    } else {
        strcpy(writeLogTransaksi.usernamePelanggan, "guest");
    }
    if(isKaryawan) {
        strcpy(writeLogTransaksi.usernameKaryawan, dataKaryawan.username);
    } else if (isPemilik) {
        strcpy(writeLogTransaksi.usernameKaryawan, dataPemilik.username);
    }
}

/*  -----------------------------
    Melakukan cetak struk
    -----------------------------
*/
void cetakStruk(FILE *pfileStruk, int urutan) 
{
        infoStruk();
        fprintf(pfileStruk, "%d;%d;%d;%s;%s;", writeLogTransaksi.tanggalTransaksi, writeLogTransaksi.bulanTransaksi, writeLogTransaksi.tahunTransaksi, writeLogTransaksi.usernamePelanggan, writeLogTransaksi.usernameKaryawan);
    int dt = 0;
        fprintf(pfileStruk, "\n\t\t _________________________________________________________________ \n"); 
        fprintf(pfileStruk, "\t\t|                  C A K E  M E  O U T  B A K E R Y               | \n");   
        fprintf(pfileStruk, "\t\t|                   S T R U K  P E M B A Y A R A N                |\n");
	    fprintf(pfileStruk, "\t\t|=================================================================|\n");
        fprintf(pfileStruk, "\t\t  > Waktu Pembayaran : %s", transaksi.waktuTransaksi);
        fprintf(pfileStruk, "\t\t| > Nama Pegawai     : %-43s|\n", transaksi.namaKaryawan);
        fprintf(pfileStruk, "\t\t| > Nama Pelanggan   : %-43s|\n", transaksi.namaPelanggan);
        fprintf(pfileStruk, "\t\t|_________________________________________________________________|\n");
    while (dt < urutan) {
        fprintf(pfileStruk, "\t\t| Pesanan ke-%-2d                                                   |\n", dt+1);
        fprintf(pfileStruk, "\t\t| > Nama Pesanan     : %-43s|\n", DTransaksi[dt].namaMakanan);
        fprintf(pfileStruk, "\t\t| > Harga Satuan     : Rp%-41.2f|\n", DTransaksi[dt].hargaSatuan);
        fprintf(pfileStruk, "\t\t| > Pembelian        : %-43d|\n", DTransaksi[dt].banyakPembelian);
	    fprintf(pfileStruk, "\t\t| > Harga Total      : Rp%-41.2f|\n", DTransaksi[dt].hargaTotal);
        fprintf(pfileStruk, "\t\t|_________________________________________________________________|\n");
        dt++;
    }   
        fprintf(pfileStruk, "\t\t| > Total Pembelian  : %-43d|\n", transaksi.totalPembelian);
        fprintf(pfileStruk, "\t\t| > Sub Total        : Rp%-41.2f|\n", transaksi.hargaSblmDiskon);
        fprintf(pfileStruk, "\t\t| > Total Diskon     : Rp%-41.2f|\n", transaksi.totalDiskon);
	    fprintf(pfileStruk, "\t\t| > Harga Total      : Rp%-41.2f|\n", transaksi.hargaTotal);
        fprintf(pfileStruk, "\t\t|_________________________________________________________________|\n");
        fprintf(pfileStruk, "\t\t| > Total Pembayaran : Rp%-41.2f|\n", transaksi.jumlahPembayaran);
	    fprintf(pfileStruk, "\t\t| > Kembalian        : Rp%-41.2f|\n", transaksi.jumlahKembalian);
        fprintf(pfileStruk, "\t\t _________________________________________________________________ \n");
        fprintf(pfileStruk, ";\n");
        fclose(pfileStruk);
}

/*  --------------------------------------------
    Fungsi yang dipanggil untuk menyimpan
    riwayat transaksi ke file dataTransaksi.txt
    --------------------------------------------
*/
void simpanRiwayatTransaksi(int urutan)
{
    FILE *riwayatStruk;
    riwayatStruk = fopen("dataTransaksi.txt", "a");
    cetakStruk(riwayatStruk, urutan);
}

/*
    =============================
    FUNGSI UNTUK MELIHAT STRUK
    =============================
*/

/*  --------------------------------------------
    Fungsi yang digunakan untuk memeriksa
    ketersediaan file dataTransaksi.txt
    --------------------------------------------
*/
void cekFileStruk()
{
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");
    if(riwayatTransaksi == NULL) {
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                                                                 |\n");
        printf("\t\t|            File data riwayat transaksi tidak ditemukan          |\n");
        printf("\t\t|_________________________________________________________________|\n");
        fclose(riwayatTransaksi);
        systemPause();
        systemCLS();
        if (isPelanggan) menuAwalPelanggan();
        else if (isKaryawan) menuAwalKaryawan();
        else if (isPemilik) menuAwalPemilik();
    }
    fclose(riwayatTransaksi);
}

/*  --------------------------------------------
    Menunjukkan menu riwayat transaksi
    dan memberikan opsi filter yang diinginkan
    --------------------------------------------
*/
void menulihatRiwayatTransaksi()
{
    cekFileStruk();
    int pilihan;
    printf("\t\t _________________________________________________________________ \n");    
    printf("\t\t|              M E N U  R I W A Y A T  T R A N S A K S I          |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|          Pilih filter riwayat transaksi yang ingin dilihat      |\n");
	printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t| [1] Tampilkan semua riwayat transaksi                           |\n");
    printf("\t\t| [2] Cari sesuai karyawan                                        |\n");
    printf("\t\t| [3] Cari sesuai pelanggan                                       |\n");
    printf("\t\t| [4] Cari sesuai waktu transaksi                                 |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                  [5] Kembali ke menu sebelumnya                 |\n");
	printf("\t\t|_________________________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-5) : ");
    pilihanUser(&pilihan, 1, 5);
    if (pilihan == 1) {
        systemCLS();
        showRiwayatTransaksiAll();
    } else if (pilihan == 2) {
        systemCLS();
        showRiwayatTransaksiK();
    } else if (pilihan == 3) {
        systemCLS();
        showRiwayatTransaksiP();
    } else if (pilihan == 4) {
        systemCLS();
        menuCariRiwayatWaktu();
    } else if (pilihan == 5) {
        systemCLS();
        if (isPemilik) menuAwalPemilik();
        else if (isKaryawan) menuAwalKaryawan();
    }
}

/*  -------------------------------------------------
    Memberikan output dari seluruh riwayat transaksi
    -------------------------------------------------
*/
void showRiwayatTransaksiAll()
{
    
    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                 R I W A Y A T  T R A N S A K S I                |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|               Cari berdasarkan: Seluruh Transaksi               |\n");
    printf("\t\t|_________________________________________________________________|\n\n");

    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    int nomor = 1;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        printf("\t\t =================================================================\n");
        printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
        printf("\t\t =================================================================");
        printf("%s\n", readLogTransaksi.dataTransaksi);
        nomor++;
   } while (!feof(riwayatTransaksi));
   fclose(riwayatTransaksi);

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();
}

/*  ------------------------------------------
    Memberikan output dari riwayat transaksi
    berdasarkan karyawan yang dipilih
    ------------------------------------------
*/
void showRiwayatTransaksiK()
{
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                 R I W A Y A T  T R A N S A K S I                |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                    Cari berdasarkan: Karyawan                   |\n");
    printf("\t\t|_________________________________________________________________|\n");

    printf("\t\t Masukkan username karyawan/pemilik pada transaksi: ");
    scanf("%19s", writeLogTransaksi.usernameKaryawan);
    getchar();

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if(strcmp(writeLogTransaksi.usernameKaryawan, readLogTransaksi.usernameKaryawan)==0) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();
}

/*  ------------------------------------------------
    Memberikan output dari seluruh riwayat transaksi
    berdasarkan username pelanggan
    ------------------------------------------------
*/
void showRiwayatTransaksiP()
{
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                 R I W A Y A T  T R A N S A K S I                |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                    Cari berdasarkan: Pelanggan                  |\n");
    printf("\t\t|  Username untuk membership dan \"guest\"untuk non-membership      |\n");
    printf("\t\t|_________________________________________________________________|\n\n");

    printf("\t\t Masukkan username pelanggan pada transaksi: ");
    scanf("%19s", writeLogTransaksi.usernamePelanggan);
    getchar();
    printf("\n");

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if(strcmp(writeLogTransaksi.usernamePelanggan, readLogTransaksi.usernamePelanggan)==0) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();
}

/*  ------------------------------------------------
    Menu untuk memilih filter riwayat transaksi
    berdasarkan waktu
    ------------------------------------------------
*/
void menuCariRiwayatWaktu()
{
    int pilihan;
    printf("\t\t _________________________________________________________________ \n");    
    printf("\t\t|              M E N U  R I W A Y A T  T R A N S A K S I          |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|          Pilih filter riwayat transaksi yang ingin dilihat      |\n");
	printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t| [1] Riwayat transaksi hari ini                                  |\n");
    printf("\t\t| [2] Riwayat transaksi kemarin                                   |\n");
    printf("\t\t| [3] Riwayat transaksi bulan ini                                 |\n");
    printf("\t\t| [4] Riwayat transaksi bulan lalu                                |\n");
    printf("\t\t| [5] Cari berdasarkan tanggal, bulan, dan tahun spesifik         |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                  [6] Kembali ke menu sebelumnya                 |\n");
	printf("\t\t|_________________________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-6) : ");
    pilihanUser(&pilihan, 1, 6);
    if (pilihan == 1) {
        systemCLS();
        showRiwayatTransaksiHariIni();
    } else if (pilihan == 2) {
        systemCLS();
        showRiwayatTransaksiKemarin();
    } else if (pilihan == 3) {
        systemCLS();
        showRiwayatTransaksiBulanIni();
    } else if (pilihan == 4) {
        systemCLS();
        showRiwayatTransaksiBulanLalu();
    } else if (pilihan == 5) {
        systemCLS();
        showRiwayatTransaksiTanggal();
    } else if (pilihan == 6) {
        systemCLS();
        menulihatRiwayatTransaksi();
    }
}

/*  ------------------------------------------------
    Memberikan output dari seluruh riwayat
    transaksi hari ini
    ------------------------------------------------
*/
void showRiwayatTransaksiHariIni()
{
    waktuSaatIni();
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                  R I W A Y A T  T R A N S A K S I               |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|               Cari berdasarkan: Hari Ini (%-2d-%-2d-%4d)           |\n", writeLogTransaksi.tanggalTransaksi, writeLogTransaksi.bulanTransaksi, writeLogTransaksi.tahunTransaksi);
    printf("\t\t|_________________________________________________________________|\n\n");

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if((writeLogTransaksi.tanggalTransaksi == readLogTransaksi.tanggalTransaksi) && (writeLogTransaksi.bulanTransaksi == readLogTransaksi.bulanTransaksi) && (writeLogTransaksi.tahunTransaksi == readLogTransaksi.tahunTransaksi)) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();

}

/*  ---------------------------------------
    Memberikan output dari seluruh riwayat 
    transaksi kemarin
    ---------------------------------------
*/
void showRiwayatTransaksiKemarin()
{
    waktuSaatIni();
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                  R I W A Y A T  T R A N S A K S I               |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|               Cari berdasarkan: Kemarin (%-2d-%-2d-%4d)            |\n", writeLogTransaksi.tanggalTransaksi-1, writeLogTransaksi.bulanTransaksi, writeLogTransaksi.tahunTransaksi);
    printf("\t\t|_________________________________________________________________|\n\n");

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if((writeLogTransaksi.tanggalTransaksi-1 == readLogTransaksi.tanggalTransaksi) && (writeLogTransaksi.bulanTransaksi == readLogTransaksi.bulanTransaksi) && (writeLogTransaksi.tahunTransaksi == readLogTransaksi.tahunTransaksi)) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();
}

/*  -----------------------------------------
    Memberikan output dari seluruh riwayat 
    transaksi bulan ini
    -----------------------------------------
*/
void showRiwayatTransaksiBulanIni()
{
    waktuSaatIni();
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                  R I W A Y A T  T R A N S A K S I               |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|               Cari berdasarkan: Bulan Ini (%-2d-%4d)             |\n", writeLogTransaksi.bulanTransaksi, writeLogTransaksi.tahunTransaksi);
    printf("\t\t|_________________________________________________________________|\n\n");

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if((writeLogTransaksi.bulanTransaksi == readLogTransaksi.bulanTransaksi) && (writeLogTransaksi.tahunTransaksi == readLogTransaksi.tahunTransaksi)) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();
}

/*  ----------------------------------------
    Memberikan output dari seluruh riwayat 
    transaksi bulan lalu
    -----------------------------------------
*/
void showRiwayatTransaksiBulanLalu()
{
    waktuSaatIni();
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                  R I W A Y A T  T R A N S A K S I               |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|               Cari berdasarkan: Bulan Lalu (%-2d-%4d)            |\n", writeLogTransaksi.bulanTransaksi-1, writeLogTransaksi.tahunTransaksi);
    printf("\t\t|_________________________________________________________________|\n\n");

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if((writeLogTransaksi.bulanTransaksi-1 == readLogTransaksi.bulanTransaksi) && (writeLogTransaksi.tahunTransaksi == readLogTransaksi.tahunTransaksi)) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    menulihatRiwayatTransaksi();
}

/*  ------------------------------------------------
    Memberikan output dari seluruh riwayat 
    transaksi berdasarkan tanggal yang diberikan
    ------------------------------------------------
*/
void showRiwayatTransaksiTanggal()
{
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                  R I W A Y A T  T R A N S A K S I               |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                     Cari berdasarkan: Tanggal                   |\n");
    printf("\t\t|_________________________________________________________________|\n\n");

    printf("\t\t Masukkan tahun: ");
    pilihanUser(&writeLogTransaksi.tahunTransaksi, 1900, 3000);

    printf("\t\t Masukkan bulan: ");
    pilihanUser(&writeLogTransaksi.bulanTransaksi, 1, 12);

    if(writeLogTransaksi.bulanTransaksi == 1 || writeLogTransaksi.bulanTransaksi == 3 || writeLogTransaksi.bulanTransaksi == 5 || writeLogTransaksi.bulanTransaksi == 7 || writeLogTransaksi.bulanTransaksi == 8 || writeLogTransaksi.bulanTransaksi == 10 || writeLogTransaksi.bulanTransaksi == 12) {
        printf("\t\t Masukkan hari: ");
        pilihanUser(&writeLogTransaksi.tanggalTransaksi, 1, 31);
    } else if(writeLogTransaksi.bulanTransaksi == 4 || writeLogTransaksi.bulanTransaksi == 6 || writeLogTransaksi.bulanTransaksi == 9 || writeLogTransaksi.bulanTransaksi == 11) { 
        printf("\t\t Masukkan hari: ");
        pilihanUser(&writeLogTransaksi.tanggalTransaksi, 1, 30);
    } else if(writeLogTransaksi.bulanTransaksi == 2 && writeLogTransaksi.tahunTransaksi % 4 == 0) {
        printf("\t\t Masukkan hari: ");
        pilihanUser(&writeLogTransaksi.tanggalTransaksi, 1, 29);
    } else if(writeLogTransaksi.bulanTransaksi == 2 && writeLogTransaksi.tahunTransaksi % 4 != 0) {
        printf("\t\t Masukkan hari: ");
        pilihanUser(&writeLogTransaksi.tanggalTransaksi, 1, 28);
    }

    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if((writeLogTransaksi.tanggalTransaksi == readLogTransaksi.tanggalTransaksi) && (writeLogTransaksi.bulanTransaksi == readLogTransaksi.bulanTransaksi) && (writeLogTransaksi.tahunTransaksi == readLogTransaksi.tahunTransaksi)) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|                        Data tidak ditemukan                     |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menulihatRiwayatTransaksi();
}

/*  -----------------------------------------
    Memberikan output dari seluruh riwayat 
    transaksi pada masing-masing member
    -----------------------------------------
*/
void showRiwayatTransaksiMember()
{
    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");

    printf("\t\t _________________________________________________________________ \n");
    printf("\t\t|                 R I W A Y A T  T R A N S A K S I                |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                   Riwayat Transaksi Membership                  |\n");
    printf("\t\t|_________________________________________________________________|\n\n");

    strcpy(writeLogTransaksi.usernamePelanggan, dataMembership.username);
    int nomor = 1;
    bool ketemu = false;
    do {
        fscanf(riwayatTransaksi, "%d;%d;%d;%[^;];%[^;];%[^;];\n", &readLogTransaksi.tanggalTransaksi, &readLogTransaksi.bulanTransaksi, &readLogTransaksi.tahunTransaksi, 
        readLogTransaksi.usernamePelanggan, readLogTransaksi.usernameKaryawan, readLogTransaksi.dataTransaksi);
        if(strcmp(writeLogTransaksi.usernamePelanggan, readLogTransaksi.usernamePelanggan)==0) {
            printf("\t\t =================================================================\n");
            printf("\t\t|                       Transaksi Ke-%-5d                        |\n", nomor);
            printf("\t\t =================================================================");
            printf("%s\n", readLogTransaksi.dataTransaksi);
            nomor++;
            ketemu = true;
        }
    } while (!feof(riwayatTransaksi));
    fclose(riwayatTransaksi);

    if(!ketemu){
        printf("\t\t _________________________________________________________________ \n");
        printf("\t\t|       Anda belum melakukan transaksi. Ayo pesan sekarang!       |\n");
        printf("\t\t|_________________________________________________________________|\n");
    }

    systemPause();
    systemCLS();
    menuAwalPelanggan();
}