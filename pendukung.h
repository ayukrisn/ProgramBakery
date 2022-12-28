/*
==================================================
    Header file "pendukung.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam pendukung.c

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
#ifndef PENDUKUNG_H
#define PENDUKUNG_H

/*
    FUNGSI DAN PROSEDUR VALIDASI INPUT
*/
int validasiInteger (int *varInt); void inputInteger(int *varInt);
    void pilihanUser(int *varInt, int batasTerkecil, int batasTerbesar);

/*
    FUNGSI DAN PROSEDUR VALIDASI HARGA
*/
float validasiFloat (float *varFloat); void inputHarga(float *varFloat);

/*
    FUNGSI DAN PROSEDUR VALIDASI NAMA, USERNAME, DAN PASSWORD
*/
bool validasiNama (char *varNama); void inputNama (char *varNama);
bool validasiUsername (char *varUsername); void inputUsername (char *varUsername);
bool validasiPassword (char *varPassword); void inputPassword (char *varPassword);
bool validasiKode (char *varKode); void inputKode (char *varKode);

/*
    PENGGANTI SYSTEM() DAN LAINNYA
*/
void systemCLS(); void systemPause();

#endif //PENDUKUNG_H