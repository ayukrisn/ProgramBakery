/*
==================================================
    Source code "logIn.c" berisi definisi dari
    fungsi/prosedur untuk menjalankan sign in
    atau sign up untuk pemilik, karyawan, dan 
    pembeli (membership)
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
#include "aksesPelanggan.h"


/*
    Struct untuk data pekerja
    yang akan disimpan selama
    program dijalankan
*/
daftarData dataKaryawan;
daftarData dataPemilik;
daftarData dataMembership;

/*
    Union yang akan digunakan saat berurusan dengan file
    writeUserUser: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    readUser:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
*/
tipeData writeUser;
tipeData readUser;


/*
    Menu pertama yang akan keluar saat program dibuka
*/
void menuPertama()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t| P R O G R A M  M A N A J E M E N  C A K E  M E  O U T |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t| Silahkan masuk terlebih dahulu.                       |\n");
    printf("\t\t| [1] Masuk sebagai Karyawan.                           |\n");
    printf("\t\t| [2] Masuk sebagai Pemilik.                            |\n");
    printf("\t\t| [3] Keluar dari program.                              |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-3) : ");
    pilihanUser(&pilihan, 1, 3);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        signInKaryawan();
    } else if (pilihan == 2) {
        systemCLS();
        akunPemilik();
    } else if (pilihan == 3) {
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|                  S A M P A I  J U M P A !             |\n");
    printf("\t\t|_______________________________________________________|\n");
        exit(0);
    }
}


/*
    Menanyakan apakah pemilik memiliki akun atau tidak
*/
void akunPemilik()
{
    int pilihan;
    //Memeriksa apakah sudah ada akun yang terdaftar atau belum
    FILE *periksaData;

    periksaData = fopen("dataPemilik.txt", "r");
    if (periksaData == NULL) {
        printf("\t\t ____________________________________________________________________ \n");
        printf("\t\t| Anda belum memiliki akun. Silahkan melanjutkan ke Sign Up Pemilik. |\n");
        printf("\t\t|____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        signUpPemilik();
    } else {
        fclose(periksaData);
        printf("\t\t _______________________________________________________________________________ \n");
        printf("\t\t|      Sudah ada akun yang terdaftar. Apakah Anda ingin melakukan Sign In?      |\n");
        printf("\t\t|-------------------------------------------------------------------------------|\n");
        printf("\t\t| [1] Ya, saya ingin melakukan sign in.                                         |\n");
        printf("\t\t| [2] Tidak, saya ingin melakukan sign up.                                      |\n");
        printf("\t\t| [3] Kembali ke menu awal.                                                     |\n");
        printf("\t\t|-------------------------------------------------------------------------------|\n");
        printf("\t\t| CATATAN : Bila melakukan sign up, maka data yang sebelumnya ada akan terhapus.|\n");
        printf("\t\t|_______________________________________________________________________________|\n");
        printf("\t\t  Ketik pilihan dengan angka yang tertera (1-3) : ");
        pilihanUser(&pilihan, 1, 3);
        if (pilihan == 1) {
            systemCLS();
            signInPemilik();
        } else if (pilihan == 2 ) {
            systemCLS();
            signUpPemilik();
        } else if (pilihan == 3 ) {
            systemCLS();
            menuPertama();
        }
    }
}

/*
    Prosedur sign up untuk pemilik
*/
void signUpPemilik()
{
    printf("\t\t ______________________________________________________ \n");
    printf("\t\t|                    SIGN UP PEMILIK                   |\n");
    printf("\t\t|------------------------------------------------------|\n");
    printf("\t\t|      Silahkan melakukan sign up terlebih dahulu      |\n");
    printf("\t\t|______________________________________________________|\n");

    //Memasukkan data yang diperlukan
    inputNama(writeUser.pemilik.nama);
    inputUsername(writeUser.pemilik.username);
    inputPassword(writeUser.pemilik.password);

    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataPemilik.txt", "w");

    fprintf(signUp, "%s,%s,%s\n", writeUser.pemilik.nama, writeUser.pemilik.username, writeUser.pemilik.password);
    fclose(signUp);

    //Memeriksa apakah fprint berhasil
    if(fprintf != 0) {
        remove("dataKaryawan.txt");
        remove("dataMembership.txt");
        remove("dataTransaksi.txt");
        remove("jadwalRestock.txt");
        remove("logRestock.txt");
        printf("\t\t ______________________________________________________ \n");
        printf("\t\t|                Sign Up Pemilik Berhasil.             |\n");
        printf("\t\t|------------------------------------------------------|\n");
        printf("\t\t|        Silahkan masuk kembali melalui Sign In.       |\n");
        printf("\t\t|______________________________________________________|\n");
        systemPause();
        systemCLS();
        signInPemilik();
    } else {
        printf("\t\t ______________________________________________________ \n");
        printf("\t\t|          Terjadi error pada proses Sign Up           |\n");
        printf("\t\t|______________________________________________________|\n");
        exit(1);
    }
}

/*
    Prosedur sign in untuk pemilik
*/
void signInPemilik (){
    printf("\t\t ______________________________________________________ \n");
    printf("\t\t|                     SIGN IN PEMILIK                  |\n");
    printf("\t\t|------------------------------------------------------|\n");
    printf("\t\t|      Silahkan melakukan Sign In terlebih dahulu      |\n");
    printf("\t\t|______________________________________________________|\n");
    printf("\t\t  Username : ");
    scanf("%20s", writeUser.pemilik.username);
    fflush(stdin);

    printf("\t\t  Password : ");
    scanf("%20s", writeUser.pemilik.password);
    fflush(stdin);

    FILE *signIn;
    signIn = fopen("dataPemilik.txt", "r");

    //Memeriksa apakah username dan password yang diberikan benar atau tidak
    fscanf(signIn, "%[^,],%[^,],%[^\n]\n", readUser.pemilik.nama, readUser.pemilik.username, readUser.pemilik.password);
    
        if(strcmp(writeUser.pemilik.username, readUser.pemilik.username)==0 && strcmp(writeUser.pemilik.password, readUser.pemilik.password)==0) {
            dataPemilik = readUser.pemilik;

            fclose(signIn);
            printf("\t\t ______________________________________________________ \n");
            printf("\t\t|                Sign in telah berhasil.               |\n");
            printf("\t\t|______________________________________________________|\n");
            printf("\t\t  |            Selamat datang, %-23s|\n", dataPemilik.nama);
            printf("\t\t   |_________________________________________________|\n");
            getchar();
            isPemilik = true;
            systemPause();
            systemCLS();
            menuAwalPemilik();
        } else {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t| Username atau password yang dimasukkan salah. Mohon ulangi kembali. |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            getchar();
            systemPause();
            systemCLS();
            akunPemilik();
        }
}


/*
    Prosedur sign up untuk karyawan
*/
void signUpKaryawan()
{
    printf("\t\t ____________________________________________________________________ \n");
    printf("\t\t|                     S I G N  U P  K A R Y A W A N                   |\n");
    printf("\t\t|---------------------------------------------------------------------|\n");
    printf("\t\t|     Silahkan lakukan registrasi data karyawan terlebih dahulu.      |\n");
    printf("\t\t|_____________________________________________________________________|\n");

    // User memasukkan data yang diperlukan
    inputNama(writeUser.karyawan.nama);
    inputUsername (writeUser.karyawan.username);
    inputPassword (writeUser.karyawan.password);

    // Pemeriksaan apakah nama dan username sudah terdaftar
    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");
     do {
        fscanf(fileKaryawan, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);
        if(strcmp(readUser.karyawan.nama, writeUser.karyawan.nama)== 0) {
            printf("\t\t ____________________________________________________________________ \n");
            printf("\t\t|       Nama sudah terdaftar. Mohon masukkan nama yang berbeda.       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpKaryawan();
            break;
        } 
        else if (strcmp(readUser.karyawan.username, writeUser.karyawan.username)== 0) {
            printf("\t\t ____________________________________________________________________ \n");
            printf("\t\t|   Username sudah terdaftar. Mohon masukkan username yang berbeda.   |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpKaryawan();
            break;
        }
    } while (!feof(fileKaryawan));
    fclose(fileKaryawan);

    //Membuka file dataKaryawan.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataKaryawan.txt", "a");

    fprintf(signUp, "%s;%s;%s;\n", writeUser.karyawan.nama, writeUser.karyawan.username, writeUser.karyawan.password);
    fclose(signUp);

    //Memeriksa apakah fprintf berhasil
    if(fprintf != 0) {
        printf("\t\t ____________________________________________________________________ \n");
        printf("\t\t|                       Sign up karyawan berhasil.                    |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        manageKaryawan();
    } else {
        printf("\t\t ____________________________________________________________________ \n");
        printf("\t\t|                   Terjadi error pada proses sign up.                |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        exit(1);
    }
}

/*
    Prosedur sign in untuk karyawan
*/
void signInKaryawan () {

    FILE *signIn;
    signIn = fopen("dataKaryawan.txt", "r");

    // Memeriksa apakah file dataKaryawan ada atau tidak
    if(signIn == NULL) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|           Belum ada karyawan yang terdaftar.          |\n");
        printf("\t\t|-------------------------------------------------------|\n");
        printf("\t\t|    Silahkan hubungi pemilik untuk sign up karyawan.   |\n");
        printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        menuPertama();
    } else {
        printf("\t\t ____________________________________________________________________ \n");
        printf("\t\t|                     S I G N  I N  K A R Y A W A N                   |\n");
        printf("\t\t|---------------------------------------------------------------------|\n");
        printf("\t\t|              Silahkan lakukan sign in terlebih dahulu.              |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        printf("\t\t  Username : ");
        scanf("%19[^\n]", writeUser.karyawan.username);
        getchar();

        printf("\t\t  Password : ");
        scanf("%19[^\n]", writeUser.karyawan.password);
        getchar();

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        bool tidakKetemu = 0;
        rewind(signIn);
        do {
        fscanf(signIn, "%[^;];%[^;];%[^;];\n", readUser.karyawan.nama, readUser.karyawan.username, readUser.karyawan.password);

        // Memeriksa apakah username dan password benar
        if(strcmp(writeUser.karyawan.username, readUser.karyawan.username)==0 && strcmp(writeUser.karyawan.password, readUser.karyawan.password)==0) {
            tidakKetemu = 0;
            dataKaryawan = readUser.karyawan;
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|                       Sign in telah berhasil.                       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            printf("\t\t  |                   Selamat datang, %-31s|\n", dataKaryawan.nama);
            printf("\t\t   |________________________________________________________________|\n");
            fclose(signIn);
            // Memberikan tanda bahwa yang melakukan log in adalah karyawan
            isKaryawan = true;
            systemPause();
            systemCLS();
            menuAwalKaryawan();
            break;
        } else tidakKetemu = 1;
        } while (!feof(signIn));

        if (tidakKetemu) {
        printf("\t\t ____________________________________________________________________ \n");
        printf("\t\t| Username atau password yang dimasukkan salah. Mohon ulangi kembali. |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        menuPertama();
        }
    }
}