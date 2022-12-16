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
#include <time.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesAdmin.h"
#include "pendukung.h"
#include "daftarMenuRev.h"
#include "restock.h"

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
    printf("\t\t| [1] Manage akun karyawan                              |\n");
    printf("\t\t| [2] Manage akun membership                            |\n");
    printf("\t\t| [3] Manage daftar menu                                |\n");
    printf("\t\t| [4] Manage sistem stock                               |\n");
    printf("\t\t| [5] Manage riwayat transaksi                          |\n");
    printf("\t\t| [6] Sign out dan kembali ke menu awal                 |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-6) :        \n");
    pilihanUser(&pilihan, 1, 6);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        manageKaryawan();
        } else if (pilihan == 2) {
            systemCLS();
            //manageMembership();
        } else if (pilihan == 3 ) {
            systemCLS();
            manageDaftarMenu();
        } else if (pilihan == 4 ) {
            systemCLS();
            manageStockP();
        } else if (pilihan == 5) {
            systemCLS();
            //riwayatTransaksi();
        } else if (pilihan == 6) {
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
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|         L I S T  D A F T A R  K A R Y A W A N         |\n");
	    printf("\t\t|_______________________________________________________|\n");

        int print = 1;
        while(!feof(fileKaryawan))
        // while ((fscanf(fileKaryawan, "%s %s %s\n", readUser.karyawan.username, readUser.karyawan.password, readUser.karyawan.nama)!=0))
        {
            fscanf(fileKaryawan, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
            printf("\t\t No : %d \n", print);
            printf("\t\t Nama : %s \n", readUser.karyawan.nama);
            printf("\t\t Username : %s \n", readUser.karyawan.username);
            printf("\t\t Password : %s \n", readUser.karyawan.password);
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
    scanf("%[^\n]", writeUser.karyawan.username);
    getchar();

    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");

    int cari=0;
     do {
        fscanf(fileKaryawan, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
        // printf("Data dari file : %s\n", readUser.karyawan.username);
        // printf("Data dari input : %s\n", writeUser.karyawan.username);
        if(strcmp(readUser.karyawan.username, writeUser.karyawan.username)== 0){
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
        fscanf(fileKaryawan, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
        if(strcmp(readUser.karyawan.username, writeUser.karyawan.username)!= 0){
           fprintf(tempKaryawan, "%s;%s;%s;\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
        } 
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
	printf("\t\t| [4] Kembali ke akses pemilik                          |\n");
	printf("\t\t|_______________________________________________________|\n");
	printf("\t\t  Ketikkan pilihan anda (1-4) :                          \n");
    pilihanUser(&pilihan, 1, 4);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        lihatDaftarMenuP();
        } else if (pilihan == 2) {
            systemCLS();
            tambahDaftarMenu();
        } else if (pilihan == 3 ) {
            systemCLS();
            hapusDaftarMenu();
        } else if (pilihan == 4) {
            systemCLS();
            menuAwalPemilik();
        }
}

/*
    Menu Manage Stock
    Prosedur dapat dilihat di restock.c
*/
void manageStockP() {
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 M A N A G E  S T O C K                |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t| Silahkan pilih menu yang diinginkan.                  |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Lihat stock saat ini                              |\n");
    printf("\t\t| [2] Atur jadwal restock                               |\n");
    printf("\t\t| [3] Lihat riwayat stock                               |\n");
    printf("\t\t| [4] Lihat status stock                                |\n");
    printf("\t\t| [5] Kembali ke menu pemilik                           |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-5) :        \n");
    pilihanUser(&pilihan, 1, 5);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        lihatStockP();
        } else if (pilihan == 2) {
            systemCLS();
            aturJadwalRestock();
        } else if (pilihan == 3 ) {
            systemCLS();
            riwayatRestock();
        } else if (pilihan == 4 ) {
            systemCLS();
            statusRestock();
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
    printf("\t\t| [2] Manage stock makanan                              |\n");
    printf("\t\t| [3] Lihat daftar menu                                 |\n");
    printf("\t\t| [4] Lihat riwayat transaksi                           |\n");
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
            manageStockK();
        } else if (pilihan == 3 ) {
            systemCLS();
            lihatDaftarMenuK();
        } else if (pilihan == 4 ) {
            systemCLS();
            //lihatRiwayatTransaksi();
        } else if (pilihan == 5) {
            systemCLS();
            menuPertama();
        }
}

/*
    Prosedur menu manage stock
*/
void manageStockK()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                  M A N A G E  S T O C K               |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t|           Silahkan pilih menu yang diinginkan.        |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Tambahkan stock jadwal pagi                       |\n");
    printf("\t\t| [2] Tambahkan stock jadwal siang                      |\n");
    printf("\t\t| [3] Tambahkan stock jadwal sore                       |\n");
    printf("\t\t| [4] Lihat jumlah stock                                |\n");
    printf("\t\t| [5] Kembali ke menu karyawan                          |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-5) :        \n");
    pilihanUser(&pilihan, 1, 5);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        restockJadwalPagi();
        } else if (pilihan == 2) {
            systemCLS();
            restockJadwalSiang();
        } else if (pilihan == 3 ) {
            systemCLS();
            restockJadwalSore();
        } else if (pilihan == 4 ) {
            systemCLS();
            lihatStockK();
        } else if (pilihan == 5) {
            systemCLS();
            menuAwalKaryawan();
        }
}