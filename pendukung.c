#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"

/*
    Pengganti system("cls");
*/
void systemCLS()
{
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout); 
    fflush(stdout);
}

/*
    Pengganti system("pause");
*/
void systemPause()
{
    printf("\n\t\t Ketik apapun untuk melanjutkan.\n");
    int c = getchar();
    getchar();
}