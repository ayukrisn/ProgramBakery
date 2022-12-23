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
#include "pendukung.h"
#include "daftarMenuRev.h"
#include "restock.h"
#include "transaksi.h"

/*
    Bool untuk memastikan apakah restock sudah
    dilakukan atau belum
*/
bool updateStockPagi; bool updateStockSiang; bool updateStockSore;
restock jamRestock;
/*
    Struct yang digunakan pada saat
    berurusan dengan stock makanan
*/
logRestock writeStock; logRestock readStock;

    /*//Menambahkan jam jadwal restock
    printf("\t\t Input jadwal jam restock (Format: 24 jam. Contoh: 16)\n\n");
    printf("\t\t Batas jam restock pagi: Jam 7-10\n");
    printf("\t\t Jam restock pagi:");
    pilihanUser(&writeMenu.jamJadwalStockPagi, 7, 10);

    printf("\n\t\t Batas jam restock pagi: Jam 11-15\n");
    printf("\t\t Jam restock siang: ");
    pilihanUser(&writeMenu.jamJadwalStockSiang, 11, 15);

    printf("\n\t\t Batas jam restock pagi: Jam 17-19\n");
    printf("\t\t Jam restock sore: ");
    pilihanUser(&writeMenu.jamJadwalStockSore, 17, 19);
    printf("\t\t _____________________________________________________________________________\n"); */

/*
=================================================================
 M A N A G E  S T O K
=================================================================
*/

/*
    Mengatur jadwal restock berdasarkan
    jadwal yang sudah diset pemilik sebelumnya
*/
void setJamRestock()
{
    FILE *jadwalRestock;
    jadwalRestock = fopen("jadwalRestock.txt", "r");
    fscanf(jadwalRestock, "%d;%d;%d;", &jamRestock.pagi, &jamRestock.siang, &jamRestock.sore);
    fclose(jadwalRestock);
}

/*
    Melihat stock yang ada pada saat ini
*/
void lihatStock()
{
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

	printf("\t\t _________________________________________________________\n");
    printf("\t\t|                    DAFTAR STOCK                         |\n");
    printf("\t\t| ________________________________________________________|\n");
    printf("\t\t| NO | KODE |  NAMA MAKANAN                | JUMLAH STOCK |\n");
    printf("\t\t| --------------------------------------------------------|\n");

    int nomor = 1;
    while(!feof(fileDaftarMenu))
    {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, &readMenu.hargaMakanan, &readMenu.stock);
        printf("\t\t| %-2d | %-4s | %-28s | %-12d |\n", nomor, readMenu.kodeMakanan, readMenu.namaMakanan, readMenu.stock); 
        nomor++;
    }
    printf("\t\t|_________________________________________________________|\n");
    fclose(fileDaftarMenu);

    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

/*
    Melihat riwayat penambahan stock
*/
void riwayatRestock()
{
    char text[200];
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                  R I W A Y A T  S T O C K             |\n");
    printf("\t\t|_______________________________________________________|\n");

    FILE *fileRestock;
    fileRestock = fopen("logRestock.txt", "r");
    if(fileRestock == NULL)
    {
        printf("\t\t Belum ada riwayat stock atau file tidak dapat dibuka.\n");
        systemPause();
        systemCLS();
        manageStockP();
    }

    while(fgets(text, sizeof(text), fileRestock)) {
        printf("%s", text);
    }

    fclose(fileRestock);
    systemPause();
    systemCLS();
    manageStockP();
}

/*
    Prosedur di mana pemilik dapat mengatur jadwal restock
*/
void aturJadwalRestock() 
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|           A T U R  J A D W A L  R E S T O C K         |\n");
    printf("\t\t|_______________________________________________________|\n");

    printf("\t\t Input jadwal jam restock (Format: 24 jam. Contoh: 16)\n\n");
    printf("\t\t Batas jam restock pagi: Jam 9-10\n");
    printf("\t\t Jam restock pagi:");
    pilihanUser(&jamRestock.pagi, 9, 10);
    printf("\t\t _____________________________________________________________________________\n"); 

    printf("\n\t\t Batas jam restock siang: Jam 11-15\n");
    printf("\t\t Jam restock siang: ");
    pilihanUser(&jamRestock.siang, 11, 15);
    printf("\t\t _____________________________________________________________________________\n"); 

    printf("\n\t\t Batas jam restock sore: Jam 17-19\n");
    printf("\t\t Jam restock sore: ");
    pilihanUser(&jamRestock.sore, 17, 19);
    printf("\t\t _____________________________________________________________________________\n");

    // Memasukkan jadwal yang sudah diatur ke dalam file sehingga dapat digunakan
    // pada saat aplikasi dibuka kembali
    FILE *jadwalRestock;
    jadwalRestock = fopen("jadwalRestock.txt", "w");
    fprintf(jadwalRestock, "%d;%d;%d;\n", jamRestock.pagi, jamRestock.siang, jamRestock.sore);
    fclose(jadwalRestock);

    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|   J A D W A L  R E S T O C K  S U D A H  D I A T U R  |\n");
    printf("\t\t|_______________________________________________________|\n");
    systemPause();
    systemCLS();
    manageStockP();
}

/*
    Melihat status restock saat ini
*/
void statusRestock()
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|               S T A T U S  R E S T O C K              |\n");
    printf("\t\t|_______________________________________________________|\n");
    time_t waktu = time(NULL);
    struct tm *waktuLokal = localtime(&waktu);
    printf("\t\t| > Status restock pagi:                                |\n");
    if((!updateStockPagi) && (waktuLokal->tm_hour > jamRestock.pagi)) 
        printf("\t\t| > BELUM DIUPDATE - MELEWATI JADWAL                    |\n");
    if((!updateStockPagi) && (waktuLokal->tm_hour < jamRestock.pagi)) 
        printf("\t\t| > BELUM DIUPDATE                                      |\n");
    if(updateStockPagi)
        printf("\t\t| > SUDAH DIUPDATE                                      |\n");
    printf("\t\t| > Status restock siang:                               |\n");
    if((!updateStockSiang) && (waktuLokal->tm_hour > jamRestock.siang)) 
        printf("\t\t| > BELUM DIUPDATE - MELEWATI JADWAL                    |\n");
    if((!updateStockSiang) && (waktuLokal->tm_hour < jamRestock.siang)) 
        printf("\t\t| > BELUM DIUPDATE                                      |\n");
    if(updateStockSiang)
        printf("\t\t| > SUDAH DIUPDATE                                      |\n");
    printf("\t\t| > Status restock sore:                                |\n");
    if((!updateStockSore) && (waktuLokal->tm_hour > jamRestock.sore)) 
        printf("\t\t| > BELUM DIUPDATE - MELEWATI JADWAL                    |\n");
    if((!updateStockSore) && (waktuLokal->tm_hour < jamRestock.sore)) 
        printf("\t\t| > BELUM DIUPDATE                                      |\n");
    if(updateStockSore)
        printf("\t\t| > SUDAH DIUPDATE                                      |\n");
    printf("\t\t|_______________________________________________________|\n");
    
    systemPause();
    systemCLS();
    manageStockP();
}

/*
    PROSEDUR UNTUK MELAKUKAN RESTOCK
*/
void restockJadwalPagi()
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                  R E S T O C K  P A G I               |\n");
    printf("\t\t|_______________________________________________________|\n");

    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        manageStockK();
    }
    resetStock();
    int restockPagi;
    prosesRestock(&restockPagi);
    updateStockPagi = true;

    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

void restockJadwalSiang()
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 R E S T O C K  S I A N G              |\n");
    printf("\t\t|_______________________________________________________|\n");

    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        manageStockK();
    }
    if (!updateStockPagi) resetStock();
    int restockSiang;
    prosesRestock(&restockSiang);
    updateStockSiang = true;

    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

void restockJadwalSore()
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 R E S T O C K  S O R E                |\n");
    printf("\t\t|_______________________________________________________|\n");

    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        manageStockK();
    }
    if (!updateStockPagi && !updateStockSiang) resetStock();
    int restockSore;
    prosesRestock(&restockSore);
    updateStockSore = true;

    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

/*
    Mendapatkan catatan waktu dilaksanakan restock
*/
void waktuRestock (FILE *pfileLog)
{
    time_t waktu = time(NULL);
    struct tm *waktuLokal = localtime(&waktu);
    strcpy(writeStock.waktuRestock, asctime(waktuLokal));
    printf("\t\t Waktu Restock: %s", writeStock.waktuRestock);
}

/*
    Proses melakukan restock
*/
void prosesRestock (int *restock)
{
    /*
        Buka tiga file
        > dataDaftarMenu.txt dan tempDaftarMenu.txt untuk mengubah
          data menu agar sesuai dengan restock
        > logRestock.txt untuk menambahkan riwayat restock baru
    */
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

    FILE *logRestock;
    logRestock = fopen("logRestock.txt", "a");

    FILE *tempDaftarMenu;
    tempDaftarMenu = fopen("tempDaftarMenu.txt", "w");

    // Mendapatkan waktu restock
    waktuRestock(logRestock);
    // Menentukan siapa yang melakukan restock
    if (isPemilik)
    strcpy(writeStock.namaYgRestock, dataPemilik.nama);
    if (isKaryawan)
    strcpy(writeStock.namaYgRestock, dataKaryawan.nama);

    fprintf(logRestock, "\t\t   __________________________________________________________________________\n");
    fprintf(logRestock, "\t\t ||                                                                          ||\n");
    fprintf(logRestock, "\t\t ||                              L O G  R E S T O C K                        ||\n");
    fprintf(logRestock, "\t\t ||                                                                          ||\n");
    fprintf(logRestock, "\t\t ||==========================================================================||\n");
    fprintf(logRestock, "\t\t    > Waktu Restock: %-37s\n", writeStock.waktuRestock);
    if (isPemilik)
    fprintf(logRestock, "\t\t || > Nama Pemilik : %-56s||\n", writeStock.namaYgRestock);
    if (isKaryawan)
    fprintf(logRestock, "\t\t || > Nama Karyawan: %-56s||\n", writeStock.namaYgRestock);
    fprintf(logRestock, "\t\t ||==========================================================================||\n");
    
    // Loop untuk melakukan restock makanan
    int elemenDaftarMenu = 0;
    do {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, &readMenu.hargaMakanan, &readMenu.stock);

        printf("\t\t Nama makanan: %s\n", readMenu.namaMakanan);
        printf("\t\t Kode makanan: %s\n", readMenu.kodeMakanan);
        printf("\t\t Input jumlah restock: ");
        inputInteger(restock);
        printf("\t\t _________________________________________________________\n");

        if(*restock != 0) {
            writeStock.stockLama = readMenu.stock;
            writeStock.jumlahRestock = *restock;
            readMenu.stock += *restock;
            writeStock.stockSkrg = readMenu.stock;
            fprintf(logRestock, "\t\t || > Nama Makanan : %-30s | > Stock Lama   : %-6d||\n", readMenu.namaMakanan, writeStock.stockLama);
            fprintf(logRestock, "\t\t || > Kode Makanan : %-30s | > Restock      : %-6d||\n", readMenu.kodeMakanan, *restock);
            fprintf(logRestock, "\t\t ||                                                 | > Stock Baru   : %-6d||\n", writeStock.stockSkrg);
            fprintf(logRestock, "\t\t ||--------------------------------------------------------------------------||\n");
        }
        fprintf(tempDaftarMenu, "%s;%s;%s;%s;%.2f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, readMenu.hargaMakanan, readMenu.stock);
    } while (!feof(fileDaftarMenu));
    fprintf(logRestock, "\t\t ||__________________________________________________________________________||\n");

    fclose(logRestock);
    fclose(fileDaftarMenu);
    fclose(tempDaftarMenu);
    // tempDaftarMenu.txt menggantikan dataDaftarMenu.txt
    remove("dataDaftarMenu.txt");
    rename("tempDaftarMenu.txt","dataDaftarMenu.txt");

    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 Stock sudah ditambahkan               |\n");
    printf("\t\t|_______________________________________________________|\n");
}

/*
    Mereset stock menjadi 0
*/
void resetStock()
{
    /*
        > dataDaftarMenu.txt dan tempDaftarMenu.txt untuk mengubah
          data menu agar sesuai dengan restock
    */
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

    FILE *tempDaftarMenu;
    tempDaftarMenu = fopen("tempDaftarMenu.txt", "w");
    do {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, &readMenu.hargaMakanan, &readMenu.stock);

        readMenu.stock = 0;

        fprintf(tempDaftarMenu, "%s;%s;%s;%s;%.2f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, readMenu.hargaMakanan, readMenu.stock);
    } while (!feof(fileDaftarMenu));

    fclose(fileDaftarMenu);
    fclose(tempDaftarMenu);
    // tempDaftarMenu.txt menggantikan dataDaftarMenu.txt
    remove("dataDaftarMenu.txt");
    rename("tempDaftarMenu.txt","dataDaftarMenu.txt");
}