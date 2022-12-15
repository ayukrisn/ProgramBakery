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
#include "aksesPelanggan.h"

/*
    ===========================================================================
                     B A G I A N  A K S E S  P E L A N G G A N                 
    ===========================================================================
*/

/*
    Langkah selanjutnya setelah karyawan memilih bagian buka program untuk pelanggan
*/

void menuMasukPelanggan()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|              A K S E S  P E L A N G G A N             |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t|     Apakah sebelumnya sudah memiliki akun member?     |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t|           [1] Ya, sudah           [2] Belum           |\n");
    printf("\t\t|                                                       |\n");
    printf("\t\t|             [3] Kembali ke menu sebelumnya            |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2/3) : ");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        signInAccount();
    } else if (pilihan == 2) {
        systemCLS();
        tanyaAkun();
    } else if (pilihan == 3){
        systemCLS();
        menuAwalKaryawan();
    }
}

void tanyaAkun()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|             Apakah Anda ingin ikut member?            |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t|    [1] Tentunya mau donggg    [2] Sorry, engga deh    |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) : ");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|       Anda akan diarahkan untuk sign up account       |\n");
        printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        signUpAccount(); 
    } else if (pilihan == 2) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|      Anda akan diarahkan langsung ke daftar menu      |\n");
        printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        lihatDaftarMenu();
    }
}

/*
    Prosedur sign up untuk pelanggan
*/

void signUpAccount()
{
    printf("\t\t _____________________________________________________________________ \n");
    printf("\t\t|      Silahkan lakukan sign up data pelanggan terlebih dahulu.       |\n");
    printf("\t\t|_____________________________________________________________________|\n");

    inputNama(writeUser.membership.nama);
    inputUsername(writeUser.membership.username);
    inputPassword(writeUser.membership.password);

    // Pemeriksaan apakah nama dan username sudah terdaftar
    FILE *member;
    member = fopen("dataMembership.txt", "r");
     do {
        fscanf(member, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        if(strcmp(readUser.membership.nama, writeUser.membership.nama)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|       Nama sudah terdaftar. Mohon masukkan nama yang berbeda.       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpAccount();
            break;
        } 
        else if (strcmp(readUser.membership.username, writeUser.membership.username)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|   Username sudah terdaftar. Mohon masukkan username yang berbeda.   |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpAccount();
            break;
        }
    } while (!feof(member));
    fclose(member);

    //Membuka file dataMembership.txt untuk memasukkan data
    FILE *memberShip;
    memberShip = fopen("dataMembership.txt", "a");

    fprintf(memberShip, "%s;%s;%s;\n", writeUser.membership.nama, writeUser.membership.username, writeUser.membership.password);
    fclose(memberShip);

    //Memeriksa apakah fprintf berhasil
    if(fprintf != 0) {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|                     Sign up pelanggan berhasil.                     |\n");
        printf("\t\t|---------------------------------------------------------------------|\n");
        printf("\t\t|               Silahkan masuk kembali melalui Sign In.               |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        signInAccount();
    } else {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|                  Terjadi error pada proses sign up.                 |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        signUpAccount();
    }
}

/*
    Prosedur sign in untuk pelanggan
*/

void signInAccount()
{
    FILE *signInMember;
    signInMember = fopen("dataMembership.txt", "r");

    if(signInMember == NULL) {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|                Belum ada akun member yang terdaftar.                |\n");
        printf("\t\t|---------------------------------------------------------------------|\n");
        printf("\t\t|           Silahkan hubungi karyawan untuk sign up pelanggan.        |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        menuPertama();
    } else {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|              Silahkan lakukan sign in terlebih dahulu.              |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        printf("\t\t  Username : ");
        scanf("%[^\n]", writeUser.membership.username);
        getchar();

        printf("\t\t  Password : ");
        scanf("%[^\n]", writeUser.membership.password);
        getchar();

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        bool tidakKetemu = 0;
        rewind(signInMember);
        do {
        fscanf(signInMember, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        
        if(strcmp(writeUser.membership.username, readUser.membership.username)==0 && strcmp(writeUser.membership.password, readUser.membership.password)==0) {
            tidakKetemu = 0;
            dataMembership = readUser.membership;

            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|                Sign in account member telah berhasil.               |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            printf("\t\t  Selamat datang, %s\n", dataMembership.nama);
            fclose(signInMember);
            systemPause();
            systemCLS();
            //masuk milih menu pesanan, ini mau dipisah atau gabung ma fungsi ini lihatDaftarMenu();?
            break;
        } else tidakKetemu = 1;
        } while (!feof(signInMember));

        if (tidakKetemu) {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t| Username atau password yang dimasukkan salah. Mohon ulangi kembali. |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        signInAccount();
        }
    }
}