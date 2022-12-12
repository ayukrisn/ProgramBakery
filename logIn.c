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
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"


/*
    Union yang digunakan untuk menyimpan
    data pembeli (membership/tidak)
*/
tipePembeli;

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
    write: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    read:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
*/
tipeData write;
tipeData read;


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
        exit(0);
    }
}


/*
    Output yang menanyakan apakah pemilik memiliki akun atau tidak
*/
void akunPemilik()
{
    int pilihan;
    //Memeriksa apakah sudah ada akun yang terdaftar atau belum
    FILE *periksaData;

    periksaData = fopen("dataPemilik.txt", "r");
    if (periksaData == NULL) {
        printf("\t\t ____________________________________________________________________ \n");
        printf("\t\t| Anda belum memiliki akun. Silahkan melanjutkan ke Sign Un Pemilik. |\n");
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
        printf("\t\t| CATATAN: Bila melakukan sign up, maka data yang sebelumnya ada akan terhapus. |\n");
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
    inputNama(write.pemilik.nama);
    inputUsername(write.pemilik.username);
    inputPassword(write.pemilik.password);

    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataPemilik.txt", "w");

    fprintf(signUp, "%s,%s,%s\n", write.pemilik.nama, write.pemilik.username, write.pemilik.password);
    fclose(signUp);

    //Memeriksa apakah fprint berhasil
    if(fprintf != 0) {
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
void signInPemilik () {
    printf("\t\t ______________________________________________________ \n");
    printf("\t\t|                     SIGN IN PEMILIK                  |\n");
    printf("\t\t|------------------------------------------------------|\n");
    printf("\t\t|      Silahkan melakukan Sign In terlebih dahulu      |\n");
    printf("\t\t|______________________________________________________|\n");
    printf("\t\t  Username : ");
    scanf("%20s", write.pemilik.username);
    fflush(stdin);

    printf("\t\t  Password : ");
    scanf("%20s", write.pemilik.password);
    fflush(stdin);

    FILE *signIn;
    signIn = fopen("dataPemilik.txt", "r");

    //Memeriksa apakah username dan password yang diberikan benar atau tidak
    fscanf(signIn, "%[^,],%[^,],%[^\n]\n", read.pemilik.nama, read.pemilik.username, read.pemilik.password);
    
        if(strcmp(write.pemilik.username, read.pemilik.username)==0 && strcmp(write.pemilik.password, read.pemilik.password)==0) {
            dataPemilik = read.pemilik;

            fclose(signIn);
            printf("\t\t ______________________________________________________ \n");
            printf("\t\t|                Sign In telah berhasil.               |\n");
            printf("\t\t|______________________________________________________|\n");
            printf("\t\t  Selamat datang, %s.\n", dataPemilik.nama);
            systemPause();
            systemCLS();
            menuAwalPemilik();
        } else {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t| Username atau password yang dimasukkan salah. Mohon ulangi kembali. |\n");
            printf("\t\t|_____________________________________________________________________|\n");
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
    printf("\t\t _____________________________________________________________________ \n");
    printf("\t\t|     Silahkan lakukan registrasi data karyawan terlebih dahulu.      |\n");
    printf("\t\t|_____________________________________________________________________|\n");

    inputNama(write.karyawan.nama);
    inputUsername (write.karyawan.username);
    inputPassword (write.karyawan.password);

    // Pemeriksaan apakah nama dan username sudah terdaftar
    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");
     do {
        fscanf(fileKaryawan, "%[^,],%[^,],%[^\n]\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        if(strcmp(read.karyawan.nama, write.karyawan.nama)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|       Nama sudah terdaftar. Mohon masukkan nama yang berbeda.       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpKaryawan();
            break;
        } 
        else if (strcmp(read.karyawan.username, write.karyawan.username)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|   Username sudah terdaftar. Mohon masukkan username yang berbeda.   |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpKaryawan();
            break;
        }
    } while (!feof(fileKaryawan));
    fclose(fileKaryawan);

    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataKaryawan.txt", "a");

    fprintf(signUp, "%s,%s,%s\n", write.karyawan.nama, write.karyawan.username, write.karyawan.password);
    fclose(signUp);

    //Memeriksa apakah fprintf berhasil
    if(fprintf != 0) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|               Sign Up karyawan berhasil.              |\n");
        printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        manageKaryawan();
    } else {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|           Terjadi error pada proses Sign In.          |\n");
        printf("\t\t|_______________________________________________________|\n");
        exit(1);
    }
}

/*
    Prosedur sign in untuk karyawan
*/
void signInKaryawan () {

    FILE *signIn;
    signIn = fopen("dataKaryawan.txt", "r");

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
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|       Silahkan lakukan Sign In terlebih dahulu.       |\n");
        printf("\t\t|_______________________________________________________|\n");
        printf("\t\t  Username : ");
        scanf("%20s", write.karyawan.username);
        fflush(stdin);

        printf("\t\t  Password : ");
        scanf("%20s", write.karyawan.password);
        fflush(stdin);

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        fscanf(signIn, "%[^,],%[^,],%[^\n]\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        if(strcmp(write.karyawan.username, read.karyawan.username)==0 && strcmp(write.karyawan.password, read.karyawan.password)==0) {
            dataKaryawan = read.karyawan;

            printf("\t\t _______________________________________________________ \n");
            printf("\t\t|                Sign In telah berhasil.                |\n");
            printf("\t\t|_______________________________________________________|\n");
            printf("\t\t  Selamat datang, %s.\n", dataKaryawan.nama);
            fclose(signIn);
            //menuAwalKaryawan();
        } else {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t| Username atau password yang dimasukkan salah. Mohon ulangi kembali. |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            menuPertama();
        }
    }
}