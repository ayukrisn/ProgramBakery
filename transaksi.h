/*
==================================================
    Header file "transaksi.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam transaksi.c
==================================================
*/

/*
    IFNDEF, DEFINE, DAN ENDIF
    Header guard yang digunakan untuk mencegah
    double inclusion saat menangani include directive
*/

#ifndef TRANSAKSI_H
#define TRANSAKSI_H

void cetakStruk(FILE *pfileStruk, int urutan); void simpanStrukPelanggan(int urutan); void simpanRiwayatTransaksi(int urutan);

void riwayatTransaksiMember(); void lihatRiwayatTransaksi(); void readFileStruk(FILE *pfileStruk);

#endif //TRANSAKSI_H