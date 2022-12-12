/*
==================================================
    Source code "main.c" berisi fungsi int main
    sebagai source code utama
==================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesAdmin.h"
#include "pendukung.h"
#include "daftarMenuRev.h"

int main(void)
{
    systemCLS();
    menuPertama();
    return 0;
}

/*
    Catatan: nambah stok
             file txt untuk harga, atau intinya semua informasi tentang barang dagangan
*/
