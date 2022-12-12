/*
==================================================
    Source code "daftarMenuRev.c" berisi definisi 
    dari fungsi/prosedur untuk manage menu
    Contoh: show menu, edit menu, dsb
==================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesAdmin.h"
#include "pendukung.h"
#include "daftarMenuRev.h"

/*
    Struct yang digunakan untuk menyimpan
    data menu dan sat berurusan dengan file
    writeMenu: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    readMenu:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
    simpanMenu:  variabel yang digunakan untuk menyimpan data
           selama program dijalankan
*/
dataMenu simpanMenu; dataMenu writeMenu; dataMenu readMenu;

/*
    Melihat daftar menu
*/
void showDaftarMenu()
{
        //Membuka file dataKaryawan.txt dan membacanya

    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

    //Melihat apakah ada data atau tidak
    if (fileDaftarMenu == NULL) {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|             Belum ada data yang tersimpan.            |\n");
	    printf("\t\t|-------------------------------------------------------|\n");
    	printf("\t\t|         Silahkan tambahkan menu terlebih dahulu.      |\n");
    	printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageDaftarMenu();
    } else {
	    printf("\t\t ____________________________________________________________________________________________\n");
	    printf("\t\t|                                    D A F T A R  M E N U                                    |\n");
        printf("\t\t|                                     CAKE ME OUT BAKERY                                     |\n");
        printf("\t\t| __________________________________________________________________________________________ |\n");
        printf("\t\t|  NO |  NAMA MAKANAN   |                         DESKRIPSI                        |  HARGA  |\n");
        printf("\t\t| ------------------------------------------------------------------------------------------ |\n");

        int nomor = 1;
        while(!feof(fileDaftarMenu))
        {
            fscanf(fileDaftarMenu, "%[^;];%[^;];%f;\n", readMenu.namaMakanan, readMenu.deskripsiMakanan, &readMenu.hargaMakanan);
            printf("\t\t No : %d \n", nomor);
            printf("\t\t Nama makanan : %s \n", readMenu.namaMakanan);
            printf("\t\t Deskripsi : %s \n", readMenu.deskripsiMakanan);
            printf("\t\t Harga : %.2f \n", readMenu.hargaMakanan);
            nomor++;
        }
    }
    fclose(fileDaftarMenu);
}

// Akses untuk pemilik
void lihatDaftarMenu()
{
    showDaftarMenu();
    int pilihan;
    printf("\t\t _______________________________________________________ \n");    
    printf("\t\t|           Ingin kembali ke menu sebelumnya?           |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Ya, kembali ke menu manage daftar menu            |\n");
    printf("\t\t| [2] Tidak, kembali ke menu awal                       |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2):         \n");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1){
        systemCLS();
        manageDaftarMenu();
    } else if (pilihan ==2){
        systemCLS();
        menuAwalPemilik();
    }
}

// Akses untuk pegawai
void lihatDaftarMenuP()
{
    showDaftarMenu();
    systemPause();
    systemCLS();
    menuAwalKaryawan();
}




/*
    Menambah daftar menu
*/
void tambahDaftarMenu()
{
    printf("\t\t _________________________________________________________ \n");
	printf("\t\t|                    TAMBAH DAFTAR MENU                   |\n");
	printf("\t\t|---------------------------------------------------------|\n");
 	printf("\t\t|              Mohon masukkan daftar menu baru            |\n");
  	printf("\t\t|    < Nama makanan, deskripsi makanan, harga makanan >   |\n");
	printf("\t\t|_________________________________________________________|\n");

    //Menambahkan nama makanan
    inputNama(writeMenu.namaMakanan);
    //Menambahkan deskripsi makanan
    printf("\t\t Deskripsi makanan: ");
    scanf("%[^\n]", writeMenu.deskripsiMakanan);
    getchar();
    //Menambahkan harga makanan MASIH EROR: STACKDUMP
    printf("\t\t Harga makanan: ");
    scanf("%f", &writeMenu.hargaMakanan);
    getchar();

    printf("Data dari user: %s\n%s\n%.2f\n", writeMenu.namaMakanan, writeMenu.deskripsiMakanan, writeMenu.hargaMakanan);
    // Pemeriksaan apakah nama makanan sudah terdaftar
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");
    if(fileDaftarMenu != NULL){
     do {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%f;\n", readMenu.namaMakanan, readMenu.deskripsiMakanan, &readMenu.hargaMakanan);
        if(strcmp(readMenu.namaMakanan, writeMenu.namaMakanan)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|       Nama sudah terdaftar. Mohon masukkan nama yang berbeda.       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            tambahDaftarMenu();
            break;
        } 
    } while (!feof(fileDaftarMenu));
    }
    fclose(fileDaftarMenu);

    //Membuka file dataDaftarMenu.txt untuk memasukkan data tadi
    FILE *fileWriteMenu;
    fileWriteMenu = fopen("dataDaftarMenu.txt", "a");

    fprintf(fileWriteMenu, "%s;%s;%.2f;\n", writeMenu.namaMakanan, writeMenu.deskripsiMakanan, writeMenu.hargaMakanan);
    fclose(fileWriteMenu);

    //Memeriksa apakah fprintf berhasil
    if(fprintf != 0) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|              Tambah Daftar Menu berhasil.             |\n");
        printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageDaftarMenu();
    } else {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|      Terjadi error pada proses Tambah Daftar Menu     |\n");
        printf("\t\t|_______________________________________________________|\n");
        exit(1);
    }
}
