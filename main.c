/*
==================================================
    Source code "main.c" berisi fungsi int main
    sebagai source code utama
==================================================
*/

/*
==================================================
    PENJELASAN LIBRARY YANG DIGUNAKAN
    LIBRARY: kumpulan definisi dan deklarasi dari fungsi, prosedur, macro, atau variabel
    [1] #include <stdio.h>
        Library untuk melakukan proses input/output
    [2] #include <stdlib.h>
        Library untuk keperluan secara general (alokasi memori, kontrol proses, dsb)
    [3] #include <string.h>
        Library untuk keperluan manipulasi tipe data string
    [4] #include <stdbool.h>
        Library untuk keperluan definisi tipe data boolean
    [5] #include <ctype.h>
        Library untuk keperluan klasifikasi character sesuai tipenya
    [6] #include "logIn.h", #include "variabel.h", #include "aksesAdmin.h", #include "pendukung.h", #include "daftarMenu.h"
        Header file yang berisi deklarasi dari fungsi/variabel file.c lain
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
#include "daftarMenu.h"
#include "restock.h"
#include "transaksi.h"
#include "aksesPelanggan.h"

int main(void)
{
    // Melakukan set jam restock terlebih dahulu
    setJamRestock();
    // Membersihkan layar terlebih dahulu
    systemCLS();
    // Jalankan dari menu pertama
    menuPertama();
    return 0;
}
