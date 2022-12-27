/*
==================================================
    Source code "aksesAdmin.c" berisi definisi dari
    fungsi/prosedur yang dapat dijalankan
    oleh pemilik dan karyawan
    Contoh: membuka program untuk pelanggan, 
            manage akun karyawan dan membership
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
#include "daftarMenu.h"
#include "restock.h"
#include "transaksi.h"
#include "aksesPelanggan.h"

/*
    Bool untuk menandakan apakah yang melakukan log in
    merupakan pemilik atau karyawan
*/
bool isPemilik = false; bool isKaryawan = false;
/*
    ===========================================================================
    B A G I A N  A K S E S  P E M I L I K
    ===========================================================================
*/

/*
    Menu awal setelah melakukan sign in pemilik
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
    printf("\t\t| [3] Manage akun membership                            |\n");
    printf("\t\t| [4] Manage daftar menu                                |\n");
    printf("\t\t| [5] Manage sistem stock                               |\n");
    printf("\t\t| [6] Lihat riwayat transaksi                           |\n");
    printf("\t\t| [7] Sign out dan kembali ke menu awal                 |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-7) : ");
    pilihanUser(&pilihan, 1, 7);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        konfirmasiBuka();
    } else if (pilihan == 2) {
        systemCLS();
        manageKaryawan();
    } else if (pilihan == 3) {
        systemCLS();
        manageAkunMembership();
    } else if (pilihan == 4 ) {
        systemCLS();
        manageDaftarMenu();
    } else if (pilihan == 5 ) {
        systemCLS();
        manageStockP();
    } else if (pilihan == 6 ) {
        systemCLS();
        menulihatRiwayatTransaksi();
    } else if (pilihan == 7 ) {
        isPemilik = false;
        systemCLS();
        menuPertama();
    }
}

/*
    Menunjukkan menu untuk memanage akun membership
*/

void manageAkunMembership()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|       M A N A G E  A K U N  M E M B E R S H I P       |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t| Silahkan pilih menu yang diinginkan.                  |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Lihat daftar akun membership                      |\n");
    printf("\t\t| [2] Hapus akun membership                             |\n");
    printf("\t\t| [3] Kembali ke akses pemilik                          |\n");
    printf("\t\t| [4] Sign out dan kembali ke menu awal                 |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-4) : ");
    pilihanUser(&pilihan, 1, 4);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        listMembership();
    } else if (pilihan == 2 ) {
        systemCLS();
        hapusMembership();
    } else if (pilihan == 3 ) {
        systemCLS();
        menuAwalPemilik();
    } else if (pilihan == 4) {
        systemCLS();
        menuPertama();
    }
}

/*
    Melihat daftar akun membership
*/
void listMembership()
{
    showListMembership();
    int pilihan;
    printf("\t\t _______________________________________________________ \n");    
    printf("\t\t|           Ingin kembali ke menu sebelumnya?           |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Ya, kembali ke menu manage akun membership        |\n");
    printf("\t\t| [2] Tidak, kembali ke menu awal                       |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) : ");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1){
        systemCLS();
        manageAkunMembership();
    } else if (pilihan ==2){
        systemCLS();
        menuAwalPemilik();
    }
}


void showListMembership()
{
    //Membuka file dataMembership.txt dan membacanya

    FILE *fileMember;
    fileMember = fopen("dataMembership.txt", "r");

    //Melihat apakah ada data atau tidak
    if (fileMember == NULL) {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|             Belum ada data yang tersimpan.            |\n");
	    printf("\t\t|-------------------------------------------------------|\n");
    	printf("\t\t|  Silahkan tambahkan akun membership terlebih dahulu.  |\n");
    	printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageAkunMembership();
    } else {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|       L I S T  D A F T A R  M E M B E R S H I P       |\n");
	    printf("\t\t|_______________________________________________________|\n");
        printf("\t\t|  NO  |    Nama     |  Username   |      Password      |\n");
        printf("\t\t|-------------------------------------------------------|\n");

        int print = 1;
        while(!feof(fileMember))
        
        {
            fscanf(fileMember, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
            printf("\t\t|  %-4d| %-12s| %-12s| %-19s|\n", print, readUser.membership.nama, readUser.membership.username, readUser.membership.password);
            printf("\t\t|_______________________________________________________|\n");
            print++;
        }
    }
    fclose(fileMember);
}


/*
    Menghapus daftar akun membership
*/
void hapusMembership()
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|        H A P U S  D A T A  M E M B E R S H I P        |\n");
    printf("\t\t|_______________________________________________________|\n");
    showListMembership();

    printf("\t\t  Ketik username membership yang ingin dihapus : ");
    scanf("%19[^\n]", writeUser.membership.username);
    getchar();
    fflush(stdin);

    FILE *fileMember;
    fileMember = fopen("dataMembership.txt", "r");

    int cari=0;
     do {
        fscanf(fileMember, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        
        if(strcmp(readUser.membership.username, writeUser.membership.username)== 0){
            printf("\t\t _______________________________________________________ \n");
	        printf("\t\t|                 Data telah ditemukan.                 |\n");
	        printf("\t\t|_______________________________________________________|\n");
            cari=1;
            break;
        }
    } while (!feof(fileMember));

    if(cari==0) {
        printf("\t\t _______________________________________________________ \n");
	    printf("\t\t|                 Data tidak ditemukan.                 |\n");
	    printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageAkunMembership();
    } else {

    FILE *tempMembership;
	tempMembership=fopen("tempMembership.txt","w+");
	rewind(fileMember);
    while(!feof(fileMember)) {
        fscanf(fileMember, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        if(strcmp(readUser.membership.username, writeUser.membership.username)!= 0){
           fprintf(tempMembership, "%s;%s;%s;\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        } 
    }
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|             Data telah dihapus dari file.             |\n");
    printf("\t\t|_______________________________________________________|\n");
    fclose(fileMember);
    fclose(tempMembership);
    remove("dataMembership.txt");
    rename("tempMembership.txt","dataMembership.txt");
    systemPause();
    systemCLS();
    manageAkunMembership();
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
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-4) : ");
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
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) : ");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1){
        systemCLS();
        manageKaryawan();
    } else if (pilihan == 2){
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
        printf("\t\t|  NO  |    Nama     |  Username   |      Password      |\n");
        printf("\t\t|-------------------------------------------------------|\n");

        int print = 1;
        while(!feof(fileKaryawan))
        
        {
            fscanf(fileKaryawan, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
            printf("\t\t|  %-4d| %-12s| %-12s| %-19s|\n", print, readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
            printf("\t\t|_______________________________________________________|\n");
            print++;
        }
    }
    fclose(fileKaryawan);
}


/*
    Menghapus akun karyawan
*/
void hapusKaryawan() 
{
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|          H A P U S  D A T A  K A R Y A W A N          |\n");
    printf("\t\t|_______________________________________________________|\n");
    showListKaryawan();

    printf("\t\t  Ketik username karyawan yang ingin dihapus : ");
    scanf("%19[^\n]", writeUser.karyawan.username);
    getchar();
    fflush(stdin);

    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");

    int cari=0;
     do {
        fscanf(fileKaryawan, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
        
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
	printf("\t\t  Ketikkan pilihan anda (1-4) : ");
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

    // Memeriksa apakah file daftar menu sudah ada atau belum
    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        manageDaftarMenu();
    }

    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                 M A N A G E  S T O C K                |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t| Silahkan pilih menu yang diinginkan.                  |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Lihat stock saat ini                              |\n");
    printf("\t\t| [2] Atur jadwal restock                               |\n");
    printf("\t\t| [3] Tambahkan stock jadwal pagi  (%2d:00)              |\n", jamRestock.pagi);
    printf("\t\t| [4] Tambahkan stock jadwal siang (%2d:00)              |\n", jamRestock.siang);
    printf("\t\t| [5] Tambahkan stock jadwal sore  (%2d:00)              |\n", jamRestock.sore);
    printf("\t\t| [6] Lihat riwayat stock                               |\n");
    printf("\t\t| [7] Lihat status stock                                |\n");
    printf("\t\t| [8] Kembali ke menu pemilik                           |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-8) : ");
    pilihanUser(&pilihan, 1, 8);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        lihatStock();
    } else if (pilihan == 2) {
        systemCLS();
        aturJadwalRestock();
    } else if (pilihan == 3) {
        systemCLS();
        restockJadwalPagi();
    } else if (pilihan == 4) {
        systemCLS();
        restockJadwalSiang();
    } else if (pilihan == 5 ) {
        systemCLS();
        restockJadwalSore();
    } else if (pilihan == 6 ) {
        systemCLS();
        riwayatRestock();
    } else if (pilihan == 7 ) {
        systemCLS();
        statusRestock();
    } else if (pilihan == 8) {
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
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-5) : ");
    pilihanUser(&pilihan, 1, 5);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        konfirmasiBuka();
        } else if (pilihan == 2) {
            systemCLS();
            manageStockK();
        } else if (pilihan == 3 ) {
            systemCLS();
            lihatDaftarMenuK();
        } else if (pilihan == 4 ) {
            systemCLS();
            menulihatRiwayatTransaksi();
        } else if (pilihan == 5) {
            isKaryawan = false;
            systemCLS();
            menuPertama();
        }
}

/*
    Prosedur menu manage stock
    Definisi prosedur dapat dilihat pada restock.c
*/
void manageStockK()
{
    // Memeriksa apakah file daftar menu sudah ada atau belum
    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        menuAwalKaryawan();
    }

    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                  M A N A G E  S T O C K               |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t|           Silahkan pilih menu yang diinginkan.        |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| [1] Tambahkan stock jadwal pagi  (%2d:00)              |\n", jamRestock.pagi);
    printf("\t\t| [2] Tambahkan stock jadwal siang (%2d:00)              |\n", jamRestock.siang);
    printf("\t\t| [3] Tambahkan stock jadwal sore  (%2d:00)              |\n", jamRestock.sore);
    printf("\t\t| [4] Lihat jumlah stock                                |\n");
    printf("\t\t| [5] Lihat status restock                              |\n");
    printf("\t\t| [6] Kembali ke menu karyawan                          |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-6) : ");
    pilihanUser(&pilihan, 1, 6);
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
            lihatStock();
        } else if (pilihan == 5 ) {
            systemCLS();
            statusRestock(); 
        } else if (pilihan == 6) {
            systemCLS();
            menuAwalKaryawan();
        }
}

/*
    ========================================================
    A K S E S  B E R S A M A
    ========================================================
*/

/*
    Prosedur menu konfirmasi pembukaan program untuk pelanggan
    bila update stock belum dilaksanakan atau file menu tidak ada
    Bila terkonfirmasi, melanjutkan ke menu masuk pelanggan
    pada aksesPelanggan.c
*/
void konfirmasiBuka()
{
    // Memeriksa apakah file daftar menu sudah ada atau belum
    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        if (isPemilik) manageDaftarMenu();
        else if (isKaryawan) menuAwalKaryawan();
    }

    int pilihan;
    // Memeriksa apakah update stock sudah dilakukan
    if(!updateStockPagi && !updateStockSiang && !updateStockSore) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|                [!] P E R I N G A T A N                |\n");
        printf("\t\t|                                                       |\n");
        printf("\t\t|              Anda belum melakukan restock.            |\n");
        printf("\t\t|       Lanjutkan membuka program untuk pelanggan?      |\n");
        printf("\t\t|_______________________________________________________|\n");
        printf("\t\t| [1] Ya, lanjutkan                                     |\n");
        printf("\t\t| [2] Tidak, lanjutkan ke bagian restock                |\n");
        printf("\t\t| [3] Tidak, kembali ke menu awal                       |\n");
        printf("\t\t|_______________________________________________________|\n");
        printf("\t\t  Ketik pilihan dengan angka yang tertera (1-3) : ");
        pilihanUser(&pilihan, 1, 3);
        fflush(stdin);
        if (pilihan == 1) {
        systemCLS();
        menuMasukPelanggan();
        } else if (pilihan == 2) {
            systemCLS();
            if (isPemilik)
            manageStockP();
            else if (isKaryawan)
            manageStockK();
        } else if (pilihan == 3 ) {
            systemCLS();
            if (isKaryawan) menuAwalKaryawan();
            if (isPemilik) menuAwalPemilik();
        }
    } else {
        systemCLS();
        menuMasukPelanggan();
    }
}


/*
    Konfirmasi untuk menutup menu pelanggan
    Menu pelanggan hanya dapat ditutup oleh pemilik
*/
void konfirmasiTutup() 
{
    bool konfirmasiBenar = false;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|              [!] TUTUP PROGRAM PELANGGAN              |\n");
    printf("\t\t|                                                       |\n");
    printf("\t\t|      Silahkan masukkan username dan password Admin    |\n");
    printf("\t\t|_______________________________________________________|\n");
    
    if(isPemilik) {
        printf("\t\t  Username : ");
        scanf("%19[^\n]", writeUser.pemilik.username);
        getchar();
        fflush(stdin);

        printf("\t\t  Password : ");
        scanf("%19[^\n]", writeUser.pemilik.password);
        getchar();
        fflush(stdin);

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        if(strcmp(writeUser.pemilik.username, dataPemilik.username)==0 && strcmp(writeUser.pemilik.password, dataPemilik.password)==0) {
            konfirmasiBenar = true;
            systemPause();
            systemCLS();
            menuAwalPemilik();
        } 
    } 
    if(isKaryawan) {
        printf("\t\t  Username : ");
        scanf("%19[^\n]", writeUser.karyawan.username);
        getchar();
        fflush(stdin);

        printf("\t\t  Password : ");
        scanf("%19[^\n]", writeUser.karyawan.password);
        getchar();
        fflush(stdin);

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        if(strcmp(writeUser.karyawan.username, dataKaryawan.username)==0 && strcmp(writeUser.pemilik.password, dataKaryawan.password)==0) {
            systemPause();
            systemCLS();
            menuAwalKaryawan();
        }
    }
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|              Username atau Password Salah             |\n");
    printf("\t\t|_______________________________________________________|\n");

    systemPause();
    systemCLS();
    menuMasukPelanggan();
}