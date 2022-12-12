/*
==================================================
    Header file "aksesAdmin.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam aksesAdmin.c
==================================================
*/

/*
    IFNDEF, DEFINE, DAN ENDIF
    Header guard yang digunakan untuk mencegah
    double inclusion saat menangani include directive
*/
#ifndef AKSES_PEMILIK_H
#define AKSES_PEMILIK_H

void menuAwalPemilik(); void manageKaryawan(); void listKaryawan(); void showListKaryawan();
    void hapusKaryawan(); 

#endif //AKSES_PEMILIK_H