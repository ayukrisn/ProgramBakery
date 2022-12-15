/*
==================================================
    Header file "restock.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam restock.c
==================================================
*/

/*
    IFNDEF, DEFINE, DAN ENDIF
    Header guard yang digunakan untuk mencegah
    double inclusion saat menangani include directive
*/

#ifndef RESTOCK_H
#define RESTOCK_H

void waktuRestock (FILE *pfileLog); void prosesRestock (int *restock);
    void aturJadwalRestock(); void setJamRestock(); 
    void restockJadwalPagi(); void restockJadwalSiang(); void restockJadwalSore();
    void lihatStockK(); void lihatStockP(); void statusRestock(); void riwayatRestock();
    void resetStock();
#endif //RESTOCK_H