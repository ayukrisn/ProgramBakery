/*
==================================================
    Source code "pendukung.c" berisi definisi dari
    fungsi/prosedur untuk mendukung program
    Contoh: pengganti system(), validasi input
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
#include "restock.h"
#include "restock.h"

// +======================================================================================================================+
// FUNGSI DAN PROSEDUR VALIDASI INPUT
/*
    Validasi input integer 1
        Memeriksa apakah user memasukkan:
        - Enter saja
        - Karakter selain integer
*/
int validasiInteger (int *varInt)
{
    fflush(stdin);
    /*
        Variabel untuk menyimpan input pengguna (buffer)
        dan karakter (character) bila ada
    */
    char buffer[2000];
    char character;
    // Menerima input dan memeriksa apakah input NULL atau tidak
    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        //Memeriksa apakah ada integer/karakter atau tidak
        //Kalau hanya integer, maka ==1. Kalau ada yang lain, !=1
        if(sscanf(buffer, "%d %c", varInt, &character) == 1) return *varInt;
    }
    return 0;
}
/*
    Validasi input integer 2
        Memberikan pesan apabila input salah
*/
void inputInteger(int *varInt)
{
    while (1) { //infinite loop hingga break
        fflush(stdin);
        //Jika validasi integer benar, keluar dari loop
        if (validasiInteger(varInt)) break;
        //Jika tidak, berikan pesan dan ulang loop
        printf("\t\t Masukan salah. Mohon masukkan input sesuai arahan.\n");
        printf("\t\t Masukkan input: ");
    }
}

/*
    Validasi input integer 3
        Memeriksa apakah input sesuai dengan range
        pilihan yang diberikan
*/
void pilihanUser(int *varInt, int batasTerkecil, int batasTerbesar)
{
    while(1) {
        inputInteger(varInt);
        fflush(stdin);
        // Memeriksa apakah input user berada di antara batas yang
        // diberikan. Jika ya, keluar dari loop
        if (batasTerkecil <= *varInt && *varInt <= batasTerbesar) break;
        //Jika tidak, berikan pesan dan ulang loop
        printf("\t\t Masukan salah. Mohon masukkan input sesuai arahan.\n");
        printf("\t\t Masukkan input: ");
    }
}

// +======================================================================================================================+
// FUNGSI DAN PROSEDUR VALIDASI NAMA, USERNAME, DAN PASSWORD

/*
    Validasi input nama 1
        Memeriksa apakah nama mengandung angka dan/atau
        simbol (*, =, +, dll) atau tidak
        Dapat digunakan untuk nama pengguna atau daftar menu
*/
bool validasiNama (char *varNama)
{
    int panjangKarakter;
    int elemenNama;

    bool statusValidasiNama = true;

    fflush(stdin);
    printf("\t\t Nama : ");
    // Menerima input dan memeriksa apakah input NULL atau tidak
    if(fgets(varNama, 30, stdin) == NULL) statusValidasiNama = false;
    //Mengganti '\n' dengan '\0'
    varNama[strcspn(varNama, "\n")] = '\0';
    // Memeriksa apakah panjang karakter yang diberikan lebih dari
    // kurang dari 2 atau tidak
    panjangKarakter = strlen(varNama);
    if (panjangKarakter < 2) {
        printf("\t\t Nama kurang dari 2 karakter.\n");
        statusValidasiNama = false;
    }
    // Memeriksa tiap elemen dalam string
    for (elemenNama = 0; elemenNama <= panjangKarakter; elemenNama++) {
        // Jika karakter adalah digit, maka nama salah
        if (isdigit(varNama[elemenNama])) {
            printf("\t\t Nama mengandung digit angka.\n");
            statusValidasiNama = false;
            break;
        }
        // Jika karakter adalah simbol, maka nama salah
        if (ispunct(varNama[elemenNama])) {
            printf("\t\t Nama mengandung simbol.\n");
            statusValidasiNama = false;
            break;
        }
    }
    return statusValidasiNama;
}

/*
    Validasi input nama 2
        Memberikan pesan bila input nama salah
        dan mengulangi input nama
*/
void inputNama (char *varNama)
{
    while (1) {
        
        fflush(stdin);
        bool hasilValidasi = validasiNama(varNama);
        if (hasilValidasi) {
            break;
        } else {
        printf("\t\t Masukan salah. Mohon masukkan nama sesuai arahan.\n");
        }
    }
}

/*
    Validasi input username 1
        Memeriksa apakah username mengandung whitespace 
        dan/atau simbol (*, =, +, dll) atau tidak
*/
bool validasiUsername(char *varUsername)
{
    int panjangKarakter;
    int elemenUsername;

    bool statusValidasiUsername = true;

    fflush(stdin);
    printf("\t\t Username setidaknya terdiri dari 8 karakter.\n");
    printf("\t\t Username : ");
    // Menerima input dan memeriksa apakah input NULL atau tidak
    if(fgets(varUsername, 20, stdin) == NULL) return false;
    //Mengganti '\n' dengan '\0'
    varUsername[strcspn(varUsername, "\n")] = '\0';
    // Memeriksa apakah panjang karakter yang diberikan
    // kurang dari 8 atau tidak
    panjangKarakter = strlen(varUsername);
    if (panjangKarakter < 8) {
        printf("\t\t Username kurang dari 8 karakter.\n");
        //return false;
        statusValidasiUsername = false;
    }
    // Memeriksa tiap elemen dalam string
    for (elemenUsername = 0; elemenUsername <= panjangKarakter; elemenUsername++) {
        // Jika karakter adalah spasi, maka username salah
        if (isspace(varUsername[elemenUsername])) {
            printf("\t\t Username mengandung whitespace.\n");
            //return false;
            statusValidasiUsername= false;
            break;
        }
        // Jika karakter adalah simbol, maka username salah
        if (ispunct(varUsername[elemenUsername])) {
            printf("\t\t Username mengandung simbol.\n");
            //return false;
            statusValidasiUsername = false;
            break;
        }
    }
    return(statusValidasiUsername);
}

/*
    Validasi input username 2
        Memberikan pesan bila input username salah
        dan mengulangi input username
*/
void inputUsername (char *varUsername)
{
    while (1) {
        fflush(stdin);
        bool hasilValidasi = validasiUsername(varUsername);
        if (hasilValidasi) {
            break;
        } else {
        printf("\t\t Masukan salah. Mohon masukkan nama sesuai arahan.\n");
        }
    }
}


/*
    Validasi input password 1
        Memeriksa apakah password telah
        mengandung angka dan simbol (*, =, +, dll) atau tidak
*/
bool validasiPassword(char *varPassword)
{
    int panjangKarakter;
    int elemenPassword;

    // variabel untuk menentukan apakah password yang diinput
    // sudah sesuai dengan ketentuan
    bool simbol = 0;
    bool digit = 0;
    bool semicolon = 0;

    bool statusValidasiPassword=0;

    fflush(stdin);
    // Menerima input dan memeriksa apakah input NULL atau tidak
    printf("\t\t Password setidaknya terdiri dari 8 karakter serta mengandung simbol dan angka.\n");
    printf("\t\t Password tidak boleh mengandung simbol semicolon ';'.\n");
    printf("\t\t Password : ");
    if(fgets(varPassword, 20, stdin) == NULL) return 0;
    //Mengganti '\n' dengan '\0'
    varPassword[strcspn(varPassword, "\n")] = '\0';
    // Memeriksa apakah panjang karakter yang diberikan
    // kurang dari 8 atau tidak
    panjangKarakter = strlen(varPassword);
    if (panjangKarakter < 8) {
        printf("\t\t Password kurang dari 8 karakter.\n");
        return 0;
    }
    // Memeriksa tiap elemen dalam string
    for (elemenPassword = 0; elemenPassword<= panjangKarakter; elemenPassword++) {
        // Memeriksa apakah input password sesuai dengan ketentuan
        if (isdigit(varPassword[elemenPassword])) {
            digit = 1;
        }
        
        if (ispunct(varPassword[elemenPassword])) {
            simbol = 1;
        }
        if ((varPassword[elemenPassword]) == ';') {
            semicolon = 1;
        }
    } if (!digit) {
        printf("\t\t Password tidak berisi digit.\n");
    } if (!simbol) {
        printf("\t\t Password tidak berisi simbol.\n");
    } if (semicolon) {
        printf("\t\t Password tidak boleh berisi simbol semicolon ';'\n");
    }
    

    if(digit && simbol && !semicolon){
        statusValidasiPassword = 1;
    }else{
        statusValidasiPassword=0;
    }
    return statusValidasiPassword;
}

/*
    Validasi input password 2
        Memberikan pesan bila input password salah
        dan mengulangi input password
*/
void inputPassword (char *varPassword)
{
    bool hasilValidasi;
    while (1) {
        fflush(stdin);
        hasilValidasi = validasiPassword(varPassword);
        if (hasilValidasi) {
            break;
        } else {
        printf("\t\t Masukan salah. Mohon masukkan nama sesuai arahan.\n");
        }
    }
}


// +======================================================================================================================+
// PROSEDUR PENGGANTI FUNGSI SYSTEM()

/*
    Pengganti system("cls"); > untuk membersihkan layar
*/
void systemCLS()
{
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout); 
    fflush(stdout);
}

/*
    Pengganti system("pause"); > menjeda program hingga user memasukkan
    key apapun
*/
void systemPause()
{
    printf("\n\t\t Tekan tombol keyboard untuk melanjutkan.\n");
    getchar();
}