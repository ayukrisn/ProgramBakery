/*
==================================================
    Header file "pendukung.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam pendukung.c
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
int validasiInteger (int *varInt); void inputUser(int *varInt);
    void pilihanUser(int *varInt, int batasTerkecil, int batasTerbesar);

/*
    FUNGSI DAN PROSEDUR VALIDASI NAMA, USERNAME, DAN PASSWORD
*/
bool validasiNama (char *varNama); void inputNama (char *varNama);
bool validasiUsername (char *varUsername); void inputUsername (char *varUsername);
bool validasiPassword (char *varPassword); void inputPassword (char *varPassword);

/*
    PENGGANTI SYSTEM()
*/
void systemCLS(); void systemPause();

#endif //PENDUKUNG_H