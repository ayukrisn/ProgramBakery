#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"

/*
    Prosedur menu awal setelah melakukan sign in pemilik
*/
void menuAwalPemilik()
{
    int pilihan;
    printf("\t\t AKSES PEMILIK\n");
    printf("\t\t Silahkan pilih menu yang diinginkan.\n");
    printf("\t\t [1] Buka program untuk pelanggan.\n");
    printf("\t\t [2] Manage akun karyawan\n");
    printf("\t\t [3] Manage daftar menu\n");
    printf("\t\t [4] Lihat status penjualan\n");
    printf("\t\t [5] Sign out dan kembali ke menu awal\n");
    printf("\t\t Ketik pilihan dengan angka yang tertera:");
    scanf("%d", &pilihan);
    if (pilihan == 1) {
        systemCLS();
        //menuMasukPelanggan();
        } else if (pilihan == 2) {
            systemCLS();
            manageKaryawan();
        } else if (pilihan == 3 ) {
            systemCLS();
            //manageDaftarMenu();
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
    printf("\t\t Manage Akun Karyawan\n");
    printf("\t\t Silahkan pilih menu yang diinginkan.\n");
    printf("\t\t [1] Lihat daftar akun karyawan\n");
    printf("\t\t [2] Tambah akun karyawan\n");
    printf("\t\t [3] Hapus akun karyawan\n");
    printf("\t\t [4] Kembali ke akses pemilik\n");
    printf("\t\t Ketik pilihan dengan angka yang tertera:");
    scanf("%d", &pilihan);
    fflush(stdin);
        if (pilihan == 1) {
            systemCLS();
            listKaryawan();
        } else if (pilihan == 2 ) {
            systemCLS();
            signUpKaryawan();
        } else if (pilihan == 3 ) {
            systemCLS();
            // hapusKaryawan();
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
    printf("\t\t Ingin kembali ke menu sebelumnya?\n");
    printf("\t\t [1] Ya, kembali ke menu manage karyawan\n");
    printf("\t\t [2] Tidak, kembali ke menu awal\n");
    printf("\t\t Ketik pilihan dengan angka yang tertera:");
    scanf("%d", &pilihan);
    // printf("Pilihan: %d", pilihan);
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
        printf("\t\t Belum ada data yang tersimpan");
        systemPause();
        systemCLS();
        menuAwalPemilik();
    } else {
        // fread(&dataKaryawan, sizeof(dataKaryawan), 1, fileKaryawan);)
        printf("\t\t LIST DAFTAR KARYAWAN\n");
        int print = 1;
        while(!feof(fileKaryawan))
        // while ((fscanf(fileKaryawan, "%s %s %s\n", read.karyawan.username, read.karyawan.password, read.karyawan.nama)!=0))
        {
            fscanf(fileKaryawan, "%[^\n]\n%s\n%s\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
            printf("\t\t No: %d \n", print);
            printf("\t\t Nama: %s \n", read.karyawan.nama);
            printf("\t\t Username: %s \n", read.karyawan.username);
            printf("\t\t Password: %s \n", read.karyawan.password);
            print++;
        }
    }
    fclose(fileKaryawan);
}

/*
void hapusKaryawan() 
{
    printf("\t\t HAPUS DATA KARYAWAN\n");
    showListKaryawan();

    int c = getchar();
    printf("\t\t Ketik nama karyawan yang ingin dihapus: ");
    fgets(write.karyawan.nama, 30 , stdin);
    write.karyawan.nama[strcspn(write.karyawan.nama, "\n")] = '\0';
    getchar();

    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "a");

    rewind(fileKaryawan);
    int cari=0;
    while (!feof(fileKaryawan)) {
        fscanf(fileKaryawan, "%[^\n]\n%s\n%s\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        printf("Data dari file: %s", read.karyawan.nama);
        printf("Data dari input: %s", write.karyawan.nama);
        if(strstr(read.karyawan.nama, write.karyawan.nama)!= 0){
            printf("Data ditemukan");
            cari=1;
            break;
        } else cari=0;
    }

    if(cari==0) {
        printf("\t\t Data tidak ditemukan.");
        systemPause();
        systemCLS();
        manageKaryawan();
    } else {

    FILE *tempKaryawan;
	tempKaryawan=fopen("tempKaryawan.txt","w");
	rewind(fileKaryawan);
    while(!feof(fileKaryawan)) {
        fscanf(fileKaryawan, "%[^\n]\n%s\n%s\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        if(strstr(read.karyawan.nama, write.karyawan.nama)== 0){
           fprintf(tempKaryawan, "%s\n%s\n%s\n", read)
        }
    }
    printf("\t\t Data telah dihapus dari file.\n");
    fclose(fileKaryawan);
    fclose(tempKaryawan);
    remove("dataKaryawan.txt");
    rename("tempKaryawan.txt","dataKaryawan.txt");
    }
}
*/