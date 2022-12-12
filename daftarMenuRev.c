/*
==================================================
    Source code "daftarMenuRev.c" berisi definisi 
    dari fungsi/prosedur untuk manage menu
    Contoh: show menu, edit menu, dsb
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

/*
    Struct yang digunakan untuk menyimpan
    data menu dan sat berurusan dengan file
    write: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    read:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
    data:  variabel yang digunakan untuk menyimpan data
           selama program dijalankan
*/
dataMenu data; dataMenu write; dataMenu read;

/*
    Melihat daftar menu
*/
// void lihatDaftarMenu()


/*
    Menambah daftar menu (hanya dapat dilakukan pemilik)
*/

