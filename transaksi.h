/*
==================================================
    Header file "transaksi.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam transaksi.c

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

#ifndef TRANSAKSI_H
#define TRANSAKSI_H

void waktuSaatIni(); void infoStruk();

void cetakStruk(FILE *pfileStruk, int urutan); void simpanRiwayatTransaksi(int urutan); void cekFileStruk();

void menulihatRiwayatTransaksi(); void showRiwayatTransaksiAll();

void showRiwayatTransaksiK(); void showRiwayatTransaksiP(); void menuCariRiwayatWaktu();

void showRiwayatTransaksiHariIni(); void showRiwayatTransaksiKemarin(); void showRiwayatTransaksiBulanIni();
    void showRiwayatTransaksiBulanLalu(); void showRiwayatTransaksiTanggal(); void showRiwayatTransaksiMember();

#endif //TRANSAKSI_H