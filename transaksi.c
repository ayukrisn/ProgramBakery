/*
==================================================
    Source code "restock.c" berisi definisi dari
    fungsi/prosedur untuk manajemen restock
    Contoh: update dan lihat restock
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
#include "daftarMenuRev.h"
#include "restock.h"
#include "transaksi.h"

/*
    =============================
    FUNGSI UNTUK MENCETAK STRUK
    =============================
*/

/*
    Melakukan cetak struk
*/
void cetakStruk(FILE *pfileStruk, int urutan) 
{
    int dt = 0;
        fprintf(pfileStruk, "\t\t _________________________________________________________________ \n"); 
        fprintf(pfileStruk, "\t\t|                  C A K E  M E  O U T  B A K E R Y               | \n");   
        fprintf(pfileStruk, "\t\t|                   S T R U K  P E M B A Y A R A N                |\n");
	    fprintf(pfileStruk, "\t\t|=================================================================|\n");
        fprintf(pfileStruk, "\t\t  Waktu Pembayaran: %s", transaksi.waktuTransaksi);
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
        fclose(pfileStruk);
}


void simpanStrukPelanggan(int urutan)
{
    FILE *riwayatStrukPelanggan;
    if (isMember) {
        char namaFile[40];
        strcpy(namaFile, dataMembership.username);
        strcat(namaFile, ".txt");
        riwayatStrukPelanggan = fopen(namaFile, "a");
        cetakStruk(riwayatStrukPelanggan, urutan);
    }
    
}

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

void readFileStruk(FILE *pfileStruk)
{
    char c;
    while((c=fgetc(pfileStruk))!=EOF){
        printf("%c", c);
    }
}


void lihatRiwayatTransaksi()
{
    printf("\t\t ______________________________________________________ \n");
    printf("\t\t|                                                      |\n");
    printf("\t\t|            R I W A Y A T  T R A N S A K S I          |\n");
    printf("\t\t|______________________________________________________|\n");

    FILE *riwayatTransaksi;
    riwayatTransaksi = fopen("dataTransaksi.txt", "r");
    readFileStruk(riwayatTransaksi);
    fclose(riwayatTransaksi);
    systemPause();
    systemCLS();
    menuAwalPemilik();
}

void riwayatTransaksiMember()
{
    printf("\t\t ______________________________________________________ \n");
    printf("\t\t|                                                      |\n");
    printf("\t\t|            R I W A Y A T  T R A N S A K S I          |\n");
    printf("\t\t|______________________________________________________|\n");
    
    FILE *riwayatTransaksi;
    
    char namaFile[40];
    strcpy(namaFile, dataMembership.username);
    strcat(namaFile, ".txt");
    riwayatTransaksi = fopen(namaFile, "r");

    readFileStruk(riwayatTransaksi);
    fclose(riwayatTransaksi);

    systemPause();
    systemCLS();
    menuAwalPelanggan();
}