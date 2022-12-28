/*
==================================================
    Header file "daftarMenuRev.h" berisi deklarasi 
    dari prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam daftarMenuRev.c

    Kontributor: I Gusti Ayu Krisna Kusuma Dewi
                 (2205551072)
    Informasi lengkap dapat dilihat pada history
    commit GitHub
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
    void hapusDaftarMenu(); bool cekFileDaftarMenu();


#endif //DAFTAR_MENU_H