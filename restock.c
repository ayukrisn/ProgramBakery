/*
==================================================
    Source code "restock.c" berisi definisi dari
    fungsi/prosedur untuk manajemen restock
    - Set jam restock, atur jam restock, lihat
        status restock, lihat jumlah stock, dsb
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
#include "daftarMenu.h"
#include "restock.h"
#include "transaksi.h"

/*
    Bool untuk memastikan apakah restock sudah
    dilakukan atau belum. Bila sudah diupdate,
    variabel akan diset ke true
*/
bool updateStockPagi; bool updateStockSiang; bool updateStockSore;
restock jamRestock;

/*
    Struct yang digunakan pada saat
    berurusan dengan stock makanan
*/
logRestock writeStock; logRestock readStock;


/*
=================================================================
 M A N A G E  S T O K
=================================================================
*/

/*  ------------------------------------------
    SET JAM RESTOCK
    Mengatur jadwal restock berdasarkan
    jadwal yang sudah diset pemilik sebelumnya
    ------------------------------------------
*/
void setJamRestock()
{
    // Membuka file
    FILE *jadwalRestock;
    jadwalRestock = fopen("jadwalRestock.txt", "r");

    // Membaca jam restock yang sudah diset sebelumnya
    fscanf(jadwalRestock, "%d;%d;%d;", &jamRestock.pagi, &jamRestock.siang, &jamRestock.sore);

    // Menutup file
    fclose(jadwalRestock);
}

/*  =====================================
    LIHAT STOCK
    Melihat stock yang ada pada saat ini
    =====================================
*/
void lihatStock()
{
    // Membuka file
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

    // Output header
	printf("\t\t _________________________________________________________\n");
    printf("\t\t|                    DAFTAR STOCK                         |\n");
    printf("\t\t|_________________________________________________________|\n");
    printf("\t\t| NO | KODE |  NAMA MAKANAN                | JUMLAH STOCK |\n");
    printf("\t\t|---------------------------------------------------------|\n");

    //Deklarasi dan define nomor = 1 untuk urutan tabel
    int nomor = 1;
    /*
        Selama file belum menyentuh akhir, scan tiap baris pada file
        dan tampilkan ke layar. Nomor increment
    */
    while(!feof(fileDaftarMenu))
    {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, &readMenu.hargaMakanan, &readMenu.stock);
        printf("\t\t| %-2d | %-4s | %-28s | %-12d |\n", nomor, readMenu.kodeMakanan, readMenu.namaMakanan, readMenu.stock); 
        nomor++;
    }
    printf("\t\t|_________________________________________________________|\n");

    // Tutup file
    fclose(fileDaftarMenu);

    systemPause();
    systemCLS();
    // Jika pemilik, kembali ke menu pemilik. Jika karyawan, kembali ke menu karyawan
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

/*  ==================================
    RIWAYAT RESTOCK
    Melihat riwayat penambahan stock
    ==================================
*/
void riwayatRestock()
{
    // Menampilkan header
    printf("\t\t   __________________________________________________________________________ \n");
    printf("\t\t ||                                                                          ||\n");
    printf("\t\t ||                       R I W A Y A T  R E S T O C K                       ||\n");
    printf("\t\t ||__________________________________________________________________________||\n");

    // Membuka file dan memeriksa apakah file ada atau tidak
    FILE *fileRestock;
    fileRestock = fopen("logRestock.txt", "r");
    if(fileRestock == NULL)
    {
        // Bila tidak ada, tampilkan info dan kembali ke menu manage stock
        printf("\t\t Belum ada riwayat stock atau file tidak dapat dibuka.\n");
        systemPause();
        systemCLS();
        manageStockP();
    }

    // Menampilkan setiap karakter pada file hingga file habis
    char c;
    while((c=fgetc(fileRestock))!=EOF){
        printf("%c", c);
    }

    // Tutup file dan kembali ke menu manage stock
    fclose(fileRestock);
    systemPause();
    systemCLS();
    manageStockP();
}

/*  ======================================================
    ATUR JADWAL RESTOCK
    Prosedur di mana pemilik dapat mengatur jadwal restock
    ======================================================
*/
void aturJadwalRestock() 
{
    // Menampilkan header
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|           A T U R  J A D W A L  R E S T O C K         |\n");
    printf("\t\t|_______________________________________________________|\n");

    // Instruksi untuk input masing2 jadwal
    printf("\t\t Input jadwal jam restock (Format : 24 jam. Contoh : 16)\n\n");
    printf("\t\t Batas jam restock pagi : Jam 9-10\n");
    printf("\t\t Jam restock pagi :");
    pilihanUser(&jamRestock.pagi, 9, 10);
    printf("\t\t _____________________________________________________________________________\n"); 

    printf("\n\t\t Batas jam restock siang : Jam 11-15\n");
    printf("\t\t Jam restock siang : ");
    pilihanUser(&jamRestock.siang, 11, 15);
    printf("\t\t _____________________________________________________________________________\n"); 

    printf("\n\t\t Batas jam restock sore : Jam 17-19\n");
    printf("\t\t Jam restock sore : ");
    pilihanUser(&jamRestock.sore, 17, 19);
    printf("\t\t _____________________________________________________________________________\n");

    // Memasukkan jadwal yang sudah diatur ke dalam file sehingga dapat digunakan
    // pada saat aplikasi dibuka kembali
    FILE *jadwalRestock;
    jadwalRestock = fopen("jadwalRestock.txt", "w");
    fprintf(jadwalRestock, "%d;%d;%d;\n", jamRestock.pagi, jamRestock.siang, jamRestock.sore);
    fclose(jadwalRestock);

    // Menampilkan instruksi dan kembali ke menu manage stock pemilik
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|   J A D W A L  R E S T O C K  S U D A H  D I A T U R  |\n");
    printf("\t\t|_______________________________________________________|\n");
    systemPause();
    systemCLS();
    manageStockP();
}

/*  ===============================
    STATUS RESTOCK
    Melihat status restock saat ini
    ===============================
*/
void statusRestock()
{
    // Menampilkan header
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|               S T A T U S  R E S T O C K              |\n");
    printf("\t\t|_______________________________________________________|\n");

    // Mengambil waktu lokal dan memasukkan ke dalam struct
    time_t waktu = time(NULL);
    struct tm *waktuLokal = localtime(&waktu);

    /*
        Memeriksa status restock pagi dengan boolean
        dibandingkan dengan jam saat ini
    */
    printf("\t\t| > Status restock pagi:                                |\n");
    if((!updateStockPagi) && (waktuLokal->tm_hour > jamRestock.pagi)) 
        printf("\t\t| > BELUM DIUPDATE - MELEWATI JADWAL                    |\n");
    else if((!updateStockPagi) && (waktuLokal->tm_hour < jamRestock.pagi)) 
        printf("\t\t| > BELUM DIUPDATE                                      |\n");
    else if(updateStockPagi)
        printf("\t\t| > SUDAH DIUPDATE                                      |\n");

    /*
        Memeriksa status restock siang dengan boolean
        dibandingkan dengan jam saat ini
    */
    printf("\t\t| > Status restock siang:                               |\n");
    if((!updateStockSiang) && (waktuLokal->tm_hour > jamRestock.siang)) 
        printf("\t\t| > BELUM DIUPDATE - MELEWATI JADWAL                    |\n");
    else if((!updateStockSiang) && (waktuLokal->tm_hour < jamRestock.siang)) 
        printf("\t\t| > BELUM DIUPDATE                                      |\n");
    else if(updateStockSiang)
        printf("\t\t| > SUDAH DIUPDATE                                      |\n");

    /*
        Memeriksa status restock sore dengan boolean
        dibandingkan dengan jam saat ini
    */
    printf("\t\t| > Status restock sore:                                |\n");
    if((!updateStockSore) && (waktuLokal->tm_hour > jamRestock.sore)) 
        printf("\t\t| > BELUM DIUPDATE - MELEWATI JADWAL                    |\n");
    else if((!updateStockSore) && (waktuLokal->tm_hour < jamRestock.sore)) 
        printf("\t\t| > BELUM DIUPDATE                                      |\n");
    else if(updateStockSore)
        printf("\t\t| > SUDAH DIUPDATE                                      |\n");
    printf("\t\t|_______________________________________________________|\n");
    
    // Kembali ke menu manage stock pemilik
    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    else if (isKaryawan) manageStockK();
}

/*
    ===========================================================
    PROSEDUR UNTUK MELAKUKAN RESTOCK
    - restock jadwal pagi/siang/sore, waktu restock, dan proses restock
    ===========================================================
*/

/*  -----------------------
    RESTOCK JADWAL PAGI
    Melakukan restock pagi
    -----------------------
*/
void restockJadwalPagi()
{
    // Menampilkan header
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                  R E S T O C K  P A G I               |\n");
    printf("\t\t|_______________________________________________________|\n");

    // Memeriksa apakah daftar menu ada atau tidak
    if (!cekFileDaftarMenu()) {
        // Bila tidak, kembali ke menu manage stock
        systemPause();
        systemCLS();
        // Menentukan ke menu karyawan atau pemilik
        if (isKaryawan) manageStockK();
        else if (isPemilik) manageStockP();
    }

    // Memanggil prosedur untuk mereset stock
    resetStock();

    // Variabel restock pagi
    int restockPagi;
    // Memanggil prosedur untuk melakukan restock
    prosesRestock(&restockPagi);

    // Stock pagi sudah dilakukan
    updateStockPagi = true;

    // Kembali ke menu manage stock
    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

/*  -----------------------
    RESTOCK JADWAL SIANG
    Melakukan restock siang
    -----------------------
*/
void restockJadwalSiang()
{
    // Menampilkan header
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 R E S T O C K  S I A N G              |\n");
    printf("\t\t|_______________________________________________________|\n");

     // Memeriksa apakah daftar menu ada atau tidak
    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        // Menentukan ke menu karyawan atau pemilik
        if (isKaryawan) manageStockK();
        else if (isPemilik) manageStockP();
    }

    // Memeriksa apakah update pagi dilakukan atau tidak
    // Jika belum, reset stock kemarin
    if (!updateStockPagi) resetStock();

    // Variabel restock siang
    int restockSiang;

    // Memanggil prosedur untuk melakukan restock
    prosesRestock(&restockSiang);

    // Stock siang sudah dilakukan
    updateStockSiang = true;

    // Kembali ke menu manage stock
    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

/*  -----------------------
    RESTOCK JADWAL SORE
    Melakukan restock sore
    -----------------------
*/
void restockJadwalSore()
{
    // Menampilkan header
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 R E S T O C K  S O R E                |\n");
    printf("\t\t|_______________________________________________________|\n");

    // Memeriksa apakah file daftar menu ada atau tidak
    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        // Menentukan ke menu karyawan atau pemilik
        if (isKaryawan) manageStockK();
        else if (isPemilik) manageStockP();
    }

    // Bila update pagi dan siang tidak dilakukan, reset stock kemarin
    if (!updateStockPagi && !updateStockSiang) resetStock();

    // Variabel stock sore
    int restockSore;

    // Memanggil prosedur proses restock
    prosesRestock(&restockSore);

    // Stock sore sudah dilakukan
    updateStockSore = true;

    // Kembali ke menu manage stock
    systemPause();
    systemCLS();
    if (isPemilik) manageStockP();
    if (isKaryawan) manageStockK();
}

/*  -----------------------------------------------
    WAKTU RESTOCK
    Mendapatkan catatan waktu pelaksanaan restock
    -----------------------------------------------
*/
void waktuRestock (FILE *pfileLog)
{
    time_t waktu = time(NULL);
    struct tm *waktuLokal = localtime(&waktu);
    strcpy(writeStock.waktuRestock, asctime(waktuLokal));
    printf("\t\t Waktu Restock: %s", writeStock.waktuRestock);
}

/*  ----------------------------------------------
    PROSES RESTOCK
    Proses melakukan restock, dipanggil di setiap
    prosedur update restock
    ----------------------------------------------
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
    fprintf(logRestock, "\t\t ||                           L O G  R E S T O C K                           ||\n");
    fprintf(logRestock, "\t\t ||                                                                          ||\n");
    fprintf(logRestock, "\t\t ||==========================================================================||\n");
    fprintf(logRestock, "\t\t || > Waktu Restock : %-36s||\n", writeStock.waktuRestock);
    if (isPemilik)
    fprintf(logRestock, "\t\t || > Nama Pemilik  : %-55s||\n", writeStock.namaYgRestock);
    if (isKaryawan)
    fprintf(logRestock, "\t\t || > Nama Karyawan : %-55s||\n", writeStock.namaYgRestock);
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

/*  ------------------------
    RESET STOCK
    Mereset stock menjadi 0
    ------------------------
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