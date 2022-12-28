/*
==================================================
    Header file "aksesAdmin.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam aksesAdmin.c

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
#ifndef AKSES_ADMIN_H
#define AKSES_ADMIN_H

/*
    Menu awal pemilik
*/
void menuAwalPemilik(); 

/*
    Prosedur untuk memanage akun membership
        manageAkunMembership(): menu manage akun membership
        listMembership() dan showListMembership(): melihat daftar akun membership
        hapusMembership(): menghapus akun membership
*/
void manageAkunMembership(); void listMembership(); void showListMembership(); void hapusMembership(); 

/*
    Prosedur untuk memanage akun karyawan
        manageKaryawan(): menu manage akun karyawan
        listKaryawan() dan showListKaryawan(): melihat daftar akun karyawan
        hapusKaryawan(): menghapus akun karyawan 
*/
void manageKaryawan(); void listKaryawan(); void showListKaryawan(); void hapusKaryawan(); 

/*
    Prosedur untuk menunjukkan setiap sub-menu
*/
void manageDaftarMenu(); void manageStockP(); void menuAwalKaryawan(); void manageStockK();

/*
    Prosedur untuk melakukan konfirmasi buka/tutup program pelanggan
*/
void konfirmasiBuka(); void konfirmasiTutup();

#endif //AKSES_ADMIN_H