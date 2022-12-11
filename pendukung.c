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
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"

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
void inputUser(int *varInt)
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
        inputUser(varInt);
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
*/
bool validasiNama (char *varNama)
{
    int panjangKarakter;
    int elemenNama;

    fflush(stdin);
    // Menerima input dan memeriksa apakah input NULL atau tidak
    printf("\t\t Nama : ");
    if(fgets(varNama, sizeof(varNama), stdin) == NULL) return false;
    //Mengganti '\n' dengan '\0'
    varNama[strcspn(varNama, "\n")] = '\0';
    // Memeriksa apakah panjang karakter yang diberikan lebih dari
    // 30 atau tidak
    panjangKarakter = strlen(varNama);
    if (panjangKarakter > 30) return false;
    printf("panjang karakter = %d\n", panjangKarakter);
    // Memeriksa tiap elemen dalam string
    for (elemenNama = 0; elemenNama <= panjangKarakter; elemenNama++) {
        // Jika karakter adalah digit, maka nama salah
        printf("elemen ke %d\n", elemenNama);
        if (isdigit(varNama[elemenNama])) {
            printf("Ada digit\n");
            return false;
            break;
        }
        // Jika karakter adalah simbol, maka nama salah
        if (ispunct(varNama[elemenNama])) {
            printf("Ada simbol\n");
            return false;
            break;
        }
    }
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
            printf("Input benar.\n");
            break;
        } else {
        printf("\t\t Masukan salah. Mohon masukkan nama sesuai arahan.\n");
        printf("\t\t Masukkan nama: ");
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
    int c = getchar();
    getchar();
}