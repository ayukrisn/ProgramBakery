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
=================================================================
 M E L I H A T  D A F T A R  M E N U
=================================================================
*/

/*
    Lihat daftar menu untuk pemilik
*/ 
void lihatDaftarMenuP()
{
    // Memeriksa apakah file dataDaftarMenu.txt ada atau tidak
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

     if (fileDaftarMenu == NULL) {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|             Belum ada data yang tersimpan.            |\n");
	    printf("\t\t|-------------------------------------------------------|\n");
    	printf("\t\t|         Silahkan tambahkan menu terlebih dahulu.      |\n");
    	printf("\t\t|_______________________________________________________|\n");
        fclose(fileDaftarMenu);
        systemPause();
        systemCLS();
        manageDaftarMenu();
     }
     fclose(fileDaftarMenu);
    
    lihatDaftarMenu();

    int pilihan;
    printf("\t\t _______________________________________________________ \n");    
    printf("\t\t|           Ingin kembali ke menu sebelumnya?           |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Ya, kembali ke menu manage daftar menu            |\n");
    printf("\t\t| [2] Tidak, kembali ke menu awal                       |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2): ");
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


/*
    Lihat daftar menu untuk karyawan
*/ 
void lihatDaftarMenuK()
{
    // Memeriksa apakah file dataDaftarMenu.txt ada atau tidak
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

    if (fileDaftarMenu == NULL) {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|             Belum ada data yang tersimpan.            |\n");
	    printf("\t\t|-------------------------------------------------------|\n");
    	printf("\t\t|         Silahkan tambahkan menu terlebih dahulu.      |\n");
    	printf("\t\t|_______________________________________________________|\n");
        fclose(fileDaftarMenu);
        systemPause();
        systemCLS();
        menuAwalKaryawan();
     }
    fclose(fileDaftarMenu);

    lihatDaftarMenu();
    systemPause();
    systemCLS();
    menuAwalKaryawan();
}

/*
    Memilih daftar menu yang diinginkan
*/
void lihatDaftarMenu()
{
    int pilihan;
    printf("\t\t _________________________________________________________________ \n");    
    printf("\t\t|                        D A F T A R  M E N U                     |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|            Pilih jenis makanan yang ingin ditampilkan           |\n");
	printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t| [1] Semua    [2] Bread    [3] Cookies     [4] Cake    [5] Toast |\n");
    printf("\t\t|-----------------------------------------------------------------|\n");
    printf("\t\t|                  [6] Kembali ke menu sebelumnya                 |\n");
	printf("\t\t|_________________________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-6): ");
    pilihanUser(&pilihan, 1, 6);
    fflush(stdin);
    // Bila pilih semua, panggil prosedur show semua daftar
    if (pilihan == 1) {
        systemCLS();
        showDaftarMenuAll();
    //Bila pilih satu jenis, assign ke variabel dan show sesuai jenis
    } else if (pilihan >= 2 && pilihan <= 5) {
        if (pilihan == 2) strcpy (writeMenu.jenisMakanan, "Bread");
        if (pilihan == 3) strcpy (writeMenu.jenisMakanan, "Cookies");
        if (pilihan == 4) strcpy (writeMenu.jenisMakanan, "Cake");
        if (pilihan == 5) strcpy (writeMenu.jenisMakanan, "Toast");
        systemCLS();
        showDaftarMenuJenis();
    //Bila pilih kembali
    } else if (pilihan == 6) {
        systemCLS();
        menuAwalPemilik();
    }
}


/*
    Melihat daftar menu menurut jenis
*/
void showDaftarMenuJenis()
{
    //Membuka file dataDaftarMenu.txt dan membacanya

    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

	printf("\t\t __________________________________________________________________________________________________\n");
	printf("\t\t|                                    D A F T A R  M E N U                                          |\n");
    printf("\t\t|                                     CAKE ME OUT BAKERY                                           |\n");
    printf("\t\t|                                  Jenis Makanan: %-10s                                         |\n", writeMenu.jenisMakanan);
    printf("\t\t| _________________________________________________________________________________________________|\n");
    printf("\t\t| NO | KODE |  NAMA MAKANAN   |                         DESKRIPSI                        |  HARGA  |\n");
    printf("\t\t| ------------------------------------------------------------------------------------------------ |\n");

    int nomor = 1;
    while(!feof(fileDaftarMenu)) {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, readMenu.deskripsiMakanan, &readMenu.hargaMakanan);
        if(strcmp(writeMenu.jenisMakanan, readMenu.jenisMakanan)==0) {
            printf("\t\t No : %d \n", nomor);
            printf("\t\t Kode Makanan : %s \n", readMenu.kodeMakanan);
            printf("\t\t Nama makanan : %s \n", readMenu.namaMakanan);
            printf("\t\t Deskripsi : %s \n", readMenu.deskripsiMakanan);
            printf("\t\t Harga : %.2f \n", readMenu.hargaMakanan);
            nomor++;
        }
    }
    fclose(fileDaftarMenu);
}

/*
    Melihat seluruh daftar menu
*/
void showDaftarMenuAll()
{
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

	printf("\t\t __________________________________________________________________________________________________\n");
    printf("\t\t|                                    D A F T A R  M E N U                                          |\n");
    printf("\t\t|                                     CAKE ME OUT BAKERY                                           |\n");
    printf("\t\t| _________________________________________________________________________________________________|\n");
    printf("\t\t| NO | KODE |  NAMA MAKANAN   |                         DESKRIPSI                        |  HARGA  |\n");
    printf("\t\t| ------------------------------------------------------------------------------------------------ |\n");

    int nomor = 1;
    while(!feof(fileDaftarMenu))
    {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, readMenu.deskripsiMakanan, &readMenu.hargaMakanan);
        printf("\t\t No : %d \n", nomor);
        printf("\t\t Kode Makanan : %s \n", readMenu.kodeMakanan);
        printf("\t\t Nama makanan : %s \n", readMenu.namaMakanan);
        printf("\t\t Deskripsi : %s \n", readMenu.deskripsiMakanan);
        printf("\t\t Harga : %.2f \n", readMenu.hargaMakanan);
        nomor++;
    }
    fclose(fileDaftarMenu);
}
    

/*
=================================================================
 M E N A M B A H  D A F T A R  M E N U
=================================================================
*/
void tambahDaftarMenu()
{
    int pilihanJenis;
    // Mendapatkan input jenis makanan dari user
    printf("\t\t _________________________________________________________ \n");
	printf("\t\t|                    TAMBAH DAFTAR MENU                   |\n");
	printf("\t\t|---------------------------------------------------------|\n");
 	printf("\t\t|         Pilih jenis makanan yang ingin ditambahkan      |\n");
  	printf("\t\t|         [1] Bread  [2] Cookies [3] Cake [4] Toast       |\n");
    printf("\t\t|---------------------------------------------------------|\n");
    printf("\t\t|             [5] Kembali ke menu sebelumnya              |\n");
	printf("\t\t|_________________________________________________________|\n");
    pilihanUser(&pilihanJenis, 1, 5);
    if (pilihanJenis == 1) strcpy(writeMenu.jenisMakanan, "Bread");
    else if (pilihanJenis == 2) strcpy(writeMenu.jenisMakanan, "Cookies");
    else if (pilihanJenis == 3) strcpy(writeMenu.jenisMakanan, "Cake");
    else if (pilihanJenis == 4) strcpy(writeMenu.jenisMakanan, "Toast");
    else if (pilihanJenis == 5) {
        systemPause();
        systemCLS();
        manageDaftarMenu();
    }

    printf("\t\t _________________________________________________________ \n");
	printf("\t\t|                    TAMBAH DAFTAR MENU                   |\n");
	printf("\t\t|---------------------------------------------------------|\n");
 	printf("\t\t|              Mohon masukkan daftar menu baru            |\n");
  	printf("\t\t|< Kode, Nama makanan, deskripsi makanan, harga makanan > |\n");
	printf("\t\t|_________________________________________________________|\n");

    //Menambahkan kode makanan (perlu validasi)
    printf("\t\t Format kode makanan: 4 huruf (2 huruf mewakili jenis, 2 huruf mewakili nama)");
    printf("\t\t Kode makanan: ");
    scanf("%[^\n]", writeMenu.kodeMakanan);
    getchar();
    //Menambahkan nama makanan
    inputNama(writeMenu.namaMakanan);
    //Menambahkan deskripsi makanan
    printf("\t\t Deskripsi makanan: ");
    scanf("%[^\n]", writeMenu.deskripsiMakanan);
    getchar();
    //Menambahkan harga makanan
    printf("\t\t Harga makanan: ");
    scanf("%f", &writeMenu.hargaMakanan);
    getchar();

    // printf("Data dari user: %s\n%s\n%.2f\n", writeMenu.namaMakanan, writeMenu.deskripsiMakanan, writeMenu.hargaMakanan);
    // Pemeriksaan apakah nama makanan sudah terdaftar
    FILE *fileDaftarMenu;
    fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");
    if(fileDaftarMenu != NULL){
     do {
        fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, readMenu.deskripsiMakanan, &readMenu.hargaMakanan);
        if(strcmp(readMenu.namaMakanan, writeMenu.namaMakanan)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|       Nama sudah terdaftar. Mohon masukkan nama yang berbeda.       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            tambahDaftarMenu();
            break;
        } else if(strcmp(readMenu.kodeMakanan, writeMenu.kodeMakanan)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|   Kode makanan sudah terdaftar. Mohon masukkan kode yang berbeda.   |\n");
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

    fprintf(fileWriteMenu, "%s;%s;%s;%s;%.2f;\n", writeMenu.jenisMakanan, writeMenu.kodeMakanan, writeMenu.namaMakanan, writeMenu.deskripsiMakanan, writeMenu.hargaMakanan);
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
