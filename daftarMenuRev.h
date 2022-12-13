/*
==================================================
    Header file "daftarMenuRev.h" berisi deklarasi 
    dari prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam daftarMenuRev.c
==================================================
*/

/*
    IFNDEF, DEFINE, DAN ENDIF
    Header guard yang digunakan untuk mencegah
    double inclusion saat menangani include directive
*/
#ifndef DAFTAR_MENU_H
#define DAFTAR_MENU_H

void tambahDaftarMenu(); void showDaftarMenuAll(); void showDaftarMenuJenis();
    void lihatDaftarMenu(); void lihatDaftarMenuK(); void lihatDaftarMenuP();
    void hapusDaftarMenu();


#endif //DAFTAR_MENU_H