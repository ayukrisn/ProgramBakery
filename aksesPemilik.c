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
            //hapusKaryawan();
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
        // while(!feof(fileKaryawan))
        while ( (fread(&dataKaryawan, sizeof(dataKaryawan), 1, fileKaryawan))==1)
        {
        // fread(&dataKaryawan, sizeof(dataKaryawan), 1, fileKaryawan);
        //printf("\t\t No | Username    | Password          | Nama                  | Jabatan           | Email             | No Telepon       |\n");
        //printf("\t\t %d |%-12s | %20s | %30s | %20s | %30s | %30s | %20s\n", print, dataKaryawan.username, dataKaryawan.password, dataKaryawan.nama, dataKaryawan.jabatan, dataKaryawan.email, dataKaryawan.noTelp);
        printf("\t\t No: %d \n", print);
        printf("\t\t Username: %s \n", dataKaryawan.username);
        printf("\t\t Password: %s \n", dataKaryawan.password);
        printf("\t\t Nama: %s \n", dataKaryawan.nama);
        printf("\t\t Jabatan: %s \n", dataKaryawan.jabatan);
        printf("\t\t Email: %s \n", dataKaryawan.email);
        printf("\t\t No telp: %s \n", dataKaryawan.noTelp);
        print++;
        }
    }
    fclose(fileKaryawan);
    int pilihan;
    printf("\t\t Ingin kembali ke menu sebelumnya?\n");
    printf("\t\t [1] Ya, kembali ke menu manage karyawan\n");
    printf("\t\t [2] Tidak, kembali ke menu awal\n");
    printf("\t\t Ketik pilihan dengan angka yang tertera:");
    scanf("%d", &pilihan);
    printf("Pilihan: %d", pilihan);
    fflush(stdin);
    if (pilihan == 1){
        systemCLS();
        manageKaryawan();
    } else if (pilihan ==2){
        systemCLS();
        menuAwalPemilik();
    }
}