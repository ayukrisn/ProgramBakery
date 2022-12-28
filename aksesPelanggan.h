/*
==================================================
    Header file "aksesPelanggan.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam aksesPelanggan.c
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
#ifndef AKSES_PELANGGAN_H
#define AKSES_PELANGGAN_H

void menuMasukPelanggan(); void tanyaAkun(); void signUpAccount(); void signInAccount();
    void menuAwalPelanggan(); void lihatDaftarMenuM();

void pemesanan(); void pembayaran(); void hitungPembayaran(); void hitungTotalBiaya();

#endif //AKSES_PELANGGAN_H
