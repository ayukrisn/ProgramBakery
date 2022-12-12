/*
==================================================
    Source code "aksesAdmin.c" berisi definisi dari
    fungsi/prosedur yang dapat dijalankan
    oleh pemilik dan karyawan
    Contoh: membuka program untuk pelanggan, 
            manage akun karyawan
            manage daftar menu
            manage status penjualan
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
    ===========================================================================
    B A G I A N  A K S E S  P E M I L I K
    ===========================================================================
*/

/*
    Prosedur menu awal setelah melakukan sign in pemilik
*/
void menuAwalPemilik()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|               A K S E S  P E M I L I K                |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t| Silahkan pilih menu yang diinginkan.                  |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Buka program untuk pelanggan                      |\n");
    printf("\t\t| [2] Manage akun karyawan                              |\n");
    printf("\t\t| [3] Manage daftar menu                                |\n");
    printf("\t\t| [4] Lihat status penjualan                            |\n");
    printf("\t\t| [5] Sign out dan kembali ke menu awal                 |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-5) :        \n");
    pilihanUser(&pilihan, 1, 5);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        //menuMasukPelanggan();
        } else if (pilihan == 2) {
            systemCLS();
            manageKaryawan();
        } else if (pilihan == 3 ) {
            systemCLS();
            manageDaftarMenu();
        } else if (pilihan == 4 ) {
            systemCLS();
            //manageStatusPenjualan();
        } else if (pilihan == 5) {
            systemCLS();
            menuPertama();
        }
}

/*
    Menunjukkan menu untuk memanage akun karyawan
*/

void manageKaryawan()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|        M A N A G E  A K U N   K A R Y A W A N         |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t| Silahkan pilih menu yang diinginkan.                  |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Lihat daftar akun karyawan                        |\n");
    printf("\t\t| [2] Tambah akun karyawan                              |\n");
    printf("\t\t| [3] Hapus akun karyawan                               |\n");
    printf("\t\t| [4] Kembali ke akses pemilik                          |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-4) :        \n");
    pilihanUser(&pilihan, 1, 4);
    fflush(stdin);
        if (pilihan == 1) {
            systemCLS();
            listKaryawan();
        } else if (pilihan == 2 ) {
            systemCLS();
            signUpKaryawan();
        } else if (pilihan == 3 ) {
            systemCLS();
            hapusKaryawan();
        } else if (pilihan == 4) {
            systemCLS();
            menuAwalPemilik();
        }
}

/*
    Melihat daftar karyawan
*/

void listKaryawan()
{
    showListKaryawan();
    int pilihan;
    printf("\t\t _______________________________________________________ \n");    
    printf("\t\t|           Ingin kembali ke menu sebelumnya?           |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Ya, kembali ke menu manage karyawan               |\n");
    printf("\t\t| [2] Tidak, kembali ke menu awal                       |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2):         \n");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1){
        systemCLS();
        manageKaryawan();
    } else if (pilihan ==2){
        systemCLS();
        menuAwalPemilik();
    }
}


void showListKaryawan()
{
    //Membuka file dataKaryawan.txt dan membacanya

    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");

    //Melihat apakah ada data atau tidak
    if (fileKaryawan == NULL) {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|             Belum ada data yang tersimpan.            |\n");
	    printf("\t\t|-------------------------------------------------------|\n");
    	printf("\t\t|   Silahkan tambahkan akun karyawan terlebih dahulu.   |\n");
    	printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageKaryawan();
    } else {
        // fread(&dataKaryawan, sizeof(dataKaryawan), 1, fileKaryawan);)
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|         L I S T  D A F T A R  K A R Y A W A N         |\n");
	    printf("\t\t|_______________________________________________________|\n");

        int print = 1;
        while(!feof(fileKaryawan))
        // while ((fscanf(fileKaryawan, "%s %s %s\n", read.karyawan.username, read.karyawan.password, read.karyawan.nama)!=0))
        {
            fscanf(fileKaryawan, "%[^,],%[^,],%[^,],\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
            printf("\t\t No : %d \n", print);
            printf("\t\t Nama : %s \n", read.karyawan.nama);
            printf("\t\t Username : %s \n", read.karyawan.username);
            printf("\t\t Password : %s \n", read.karyawan.password);
            print++;
        }
    }
    fclose(fileKaryawan);
}


void hapusKaryawan() 
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|          H A P U S  D A T A  K A R Y A W A N          |\n");
    printf("\t\t|_______________________________________________________|\n");
    showListKaryawan();

    printf("\t\t  Ketik username karyawan yang ingin dihapus : ");
    scanf("%[^\n]", write.karyawan.username);
    getchar();

    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");

    int cari=0;
     do {
        fscanf(fileKaryawan, "%[^,],%[^,],%[^,],\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        // printf("Data dari file : %s\n", read.karyawan.username);
        // printf("Data dari input : %s\n", write.karyawan.username);
        if(strcmp(read.karyawan.username, write.karyawan.username)== 0){
            printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|                 Data telah ditemukan.                 |\n");
	    printf("\t\t|_______________________________________________________|\n");
            cari=1;
            break;
        }
    } while (!feof(fileKaryawan));

    if(cari==0) {
        printf("\t\t _______________________________________________________ \n");
	printf("\t\t|                 Data tidak ditemukan.                 |\n");
	printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageKaryawan();
    } else {

    FILE *tempKaryawan;
	tempKaryawan=fopen("tempKaryawan.txt","w+");
	rewind(fileKaryawan);
    while(!feof(fileKaryawan)) {
        fscanf(fileKaryawan, "%[^,],%[^,],%[^,],\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        if(strcmp(read.karyawan.username, write.karyawan.username)!= 0){
           fprintf(tempKaryawan, "%s,%s,%s,\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        } // else continue;
    }
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|             Data telah dihapus dari file.             |\n");
    printf("\t\t|_______________________________________________________|\n");
    fclose(fileKaryawan);
    fclose(tempKaryawan);
    remove("dataKaryawan.txt");
    rename("tempKaryawan.txt","dataKaryawan.txt");
    systemPause();
    systemCLS();
    manageKaryawan();
    }
}

/*
    Menu Manage Daftar Menu
    Prosedur dapat dilihat di daftarMenu.c
*/
void manageDaftarMenu() 
{
    int pilihan;
	printf("\t\t _______________________________________________________ \n");
	printf("\t\t|           M A N A G E  D A F T A R  M E N U           |\n");
	printf("\t\t|-------------------------------------------------------|\n");
	printf("\t\t| Silahkan pilih opsi dibawah ini                       |\n");
	printf("\t\t|-------------------------------------------------------|\n");
	printf("\t\t| [1] Lihat Daftar Menu                                 |\n");
	printf("\t\t| [2] Tambah Daftar Menu                                |\n");
	printf("\t\t| [3] Hapus Daftar Menu                                 |\n");
	printf("\t\t| [4] Edit Daftar Menu                                  |\n");
	printf("\t\t| [5] Kembali ke akses pemilik                          |\n");
	printf("\t\t|_______________________________________________________|\n");
	printf("\t\t  Ketikkan pilihan anda (1-5) :                          \n");
    pilihanUser(&pilihan, 1, 5);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        //lihatDaftarMenu();
        } else if (pilihan == 2) {
            systemCLS();
            //tambahDaftarMenu();
        } else if (pilihan == 3 ) {
            systemCLS();
            //editDaftarMenu();
        } else if (pilihan == 4 ) {
            systemCLS();
            //hapusDaftarMenu();
        } else if (pilihan == 5) {
            systemCLS();
            menuAwalPemilik();
        }
}


/*
    ===========================================================================
    B A G I A N  A K S E S  K A R Y A W A N
    ===========================================================================
*/

/*
    Prosedur menu awal untuk karyawan
*/
void menuAwalKaryawan()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|               A K S E S  K A R Y A W A N              |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t| Silahkan pilih menu yang diinginkan.                  |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Buka program untuk pelanggan                      |\n");
    printf("\t\t| [2] Manage stok dagang                                |\n");
    printf("\t\t| [3] Lihat daftar menu                                 |\n");
    printf("\t\t| [4] Lihat status penjualan                            |\n");
    printf("\t\t| [5] Sign out dan kembali ke menu awal                 |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-5) :        \n");
    pilihanUser(&pilihan, 1, 5);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        //menuMasukPelanggan();
        } else if (pilihan == 2) {
            systemCLS();
            //manageStok();
        } else if (pilihan == 3 ) {
            systemCLS();
            //lihatDaftarMenu();
        } else if (pilihan == 4 ) {
            systemCLS();
            //lihatStatusPenjualan();
        } else if (pilihan == 5) {
            systemCLS();
            menuPertama();
        }
}