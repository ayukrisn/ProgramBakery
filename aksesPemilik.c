#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"

/*
    Prosedur menu awal setelah melakukan sign in pemilik
*/
void menuAwalPemilik()
{
    int pilihan;
    printf("\n\t\t AKSES PEMILIK\n");
    printf("\t\t Silahkan pilih menu yang diinginkan.\n");
    printf("\t\t [1] Manage akun karyawan\n");
    printf("\t\t [2] Manage daftar menu\n");
    printf("\t\t [3] Lihat status penjualan\n");
    printf("\t\t [4] Sign out dan kembali ke menu awal\n");
    scanf("%d", &pilihan);
    if (pilihan == 1) {
            manageKaryawan();
        } else if (pilihan == 2 ) {
            //manageDaftarMenu();
        } else if (pilihan == 3 ) {
            //manageStatusPenjualan();
        } else if (pilihan == 4) {
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
    printf("\t\t [4] Kembali ke akses pemilik");
    scanf("%d", &pilihan);
        if (pilihan == 1) {
            //listKaryawan();
        } else if (pilihan == 2 ) {
            signUpKaryawan();
        } else if (pilihan == 3 ) {
            //hapusKaryawan();
        } else if (pilihan == 4) {
            menuAwalPemilik();
        }
}

/*
    Melihat daftar karyawan
*/
/*
void listKaryawan()
{
    //Membuka file dataKaryawan.bin dan membacanya

    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan,bin", "r");

    //Melihat apakah ada data atau tidak
    if (fileKaryawan == NULL) {
        printf("\t\t Belum ada data yang tersimpan");
    } else {
        fread(&dataKaryawan, sizeof(dataKaryawan), 1, fileKaryawan);)
        printf("\t\t LIST DAFTAR KARYAWAN");
    }
}
*/
