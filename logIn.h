/*
==================================================
    Header file "logIn.h" berisi deklarasi dari 
    prosedur, fungsi, atau pun variabel yang 
    didefinisikan di dalam logIn.c
==================================================
*/


/*
    IFNDEF, DEFINE, DAN ENDIF
    Header guard yang digunakan untuk mencegah
    double inclusion saat menangani include directive
*/
#ifndef LOG_IN
#define LOG_IN

/*
    DEKLARASI VARIABEL
*/



/*
    DEKLARASI PROSEDUR DAN FUNGSI
*/
/*
        void menuPertama();
    Prosedur yang dipanggil untuk menampilkan menu pertama
    pada saat program dijalankan
*/
void menuPertama(); 

/*
        void akunPemilik();
    Prosedur yang dipanggil untuk memeriksa apakah pemilik
    sudah memiliki akun atau tidak dan menanyakan apakah pemilik
    ingin melakukan sign in atau sign up
*/
void akunPemilik();

/*
        void signUpPemilik(); void signInPemilik();
        void signUpKaryawan(); void signInKaryawan();
    Prosedur untuk sign in atau sign up
*/
void signUpPemilik(); void signInPemilik();
void signUpKaryawan(); void signInKaryawan();




#endif // LOG_IN