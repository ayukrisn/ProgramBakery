#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"





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
// void systemPause(char *keterangan)
{
    printf("\n\t\t Tekan tombol keyboard untuk melanjutkan ke %s.\n", keterangan);
    int c = getchar();
    getchar();
}