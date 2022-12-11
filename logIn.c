#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"


/*
    Union yang digunakan untuk menyimpan
    data pembeli (membership/tidak)
*/
tipePembeli;

/*
    Struct untuk data pekerja
    yang akan disimpan selama
    program dijalankan
*/
daftarData dataKaryawan;
daftarData dataPemilik;
daftarData dataMembership;

/*
    Union yang akan digunakan saat berurusan dengan file
    write: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    read:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
*/
tipeData write;
tipeData read;


/*
    Menu pertama yang akan keluar saat program dibuka
*/
void menuPertama()
{
    int pilihan;
    printf("\t\t PROGRAM MANAJEMEN CAKE ME OUT\n");
    printf("\t\t Silahkan masuk terlebih dahulu.\n");
    printf("\t\t [1] Masuk sebagai Karyawan.\n");
    printf("\t\t [2] Masuk sebagai Pemilik.\n");
    printf("\t\t [3] Keluar dari program.\n");
    printf("\t\t Ketik pilihan dengan angka yang tertera:");
    scanf("%d", &pilihan);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        signInKaryawan();
    } else if (pilihan == 2) {
        systemCLS();
        akunPemilik();
    } else if (pilihan == 3) {
        exit(0);
    }
}


/*
    Output yang menanyakan apakah pemilik memiliki akun atau tidak
*/
void akunPemilik()
{
    int pilihan;
    //Memeriksa apakah sudah ada akun yang terdaftar atau belum
    FILE *periksaData;

    periksaData = fopen("dataPemilik.txt", "r");
    if (periksaData == NULL)
    {
        printf("\t\t Anda belum memiliki akun. Silahkan melanjutkan ke Sign Un Pemilik.\n");
        systemPause();
        systemCLS();
        signUpPemilik();
    } else {
        fclose(periksaData);
        printf("\t\t Sudah ada akun yang terdaftar. Apakah Anda ingin melakukan Sign In?\n");
        printf("\t\t [1] Ya, saya ingin melakukan sign in.\n");
        printf("\t\t [2] Tidak, saya ingin melakukan sign up.\n");
        printf("\t\t [3] Kembali ke menu awal.\n");
        printf("\t\t CATATAN: Bila melakukan sign up, maka data yang sebelumnya ada akan terhapus.\n");
        printf("\t\t Ketik pilihan dengan angka yang tertera:");
        scanf("%d", &pilihan);
        if (pilihan == 1) {
            systemCLS();
            signInPemilik();
        } else if (pilihan == 2 ) {
            systemCLS();
            signUpPemilik();
        } else if (pilihan == 3 ) {
            systemCLS();
            menuPertama();
        }
    }
}

/*
    Prosedur sign up untuk pemilik
*/
void signUpPemilik()
{
    printf("\t\t Silahkan lakukan registrasi terlebih dahulu.\n");

    //Memasukkan data yang diperlukan
    printf("\t\t Username: ");
    scanf("%10s", write.pemilik.username);
    fflush(stdin);

    printf("\t\t Password: ");
    scanf("%20s", write.pemilik.password);
    getchar();

    printf("\t\t Nama: ");
    // scanf("%20s", write.pemilik.nama);
    // fflush(stdin);    
    fgets(write.pemilik.nama, 30 , stdin);
    write.pemilik.nama[strcspn(write.pemilik.nama, "\n")] = '\0';

    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataPemilik.txt", "w");

    fprintf(signUp, "%s\n%s\n%s\n", write.pemilik.nama, write.pemilik.username, write.pemilik.password);
    fclose(signUp);

    //Memeriksa apakah fwrite berhasil
    if(fprintf != 0) {
        printf("\n\t\t Sign Up Pemilik Berhasil.\n");
        printf("\t\t Silahkan masuk kembali melalui Sign In.\n");
        systemPause();
        systemCLS();
        signInPemilik();
    } else {
        printf("\n\t\t Terjadi error pada proses Sign Up");
        exit(1);
    }
}

/*
    Prosedur sign in untuk pemilik
*/
void signInPemilik () {
    printf("\t\t Silahkan lakukan Sign In terlebih dahulu.\n");
    printf("\t\t Username: ");
    scanf("%10s", write.pemilik.username);
    fflush(stdin);

    printf("\t\t Password: ");
    scanf("%20s", write.pemilik.password);
    fflush(stdin);

    FILE *signIn;
    signIn = fopen("dataPemilik.txt", "r");

    //Memeriksa apakah username dan password yang diberikan benar atau tidak
    fscanf(signIn, "%[^\n]\n%s\n%s\n", read.pemilik.nama, read.pemilik.username, read.pemilik.password);
        if(strcmp(write.pemilik.username, read.pemilik.username)==0 && strcmp(write.pemilik.password, read.pemilik.password)==0) {
            dataPemilik = read.pemilik;

            fclose(signIn);
            printf("\n\t\t Sign In telah berhasil.\n");
            printf("\t\t Selamat datang, %s.\n", dataPemilik.nama);
            systemPause();
            systemCLS();
            menuAwalPemilik();
        } else {
            printf("\n\t\t Username atau password yang dimasukkan salah. Mohon ulangi kembali.\n");
            systemPause();
            systemCLS();
            akunPemilik();
        }
}


/*
    Prosedur sign up untuk karyawan
*/
void signUpKaryawan()
{
    printf("\t\t Silahkan lakukan registrasi data karyawan terlebih dahulu.\n");

    //Memasukkan data yang diperlukan
    //fflush(stdin);
    getchar();
    printf("\t\t Nama: ");
    fgets(write.karyawan.nama, 30 , stdin);
    write.karyawan.nama[strcspn(write.karyawan.nama, "\n")] = '\0';

    printf("\t\t Username: ");
    scanf("%10s", write.karyawan.username);
    fflush(stdin);

    printf("\t\t Password: ");
    scanf("%20s", write.karyawan.password);
    getchar();

    // Pemeriksaan apakah nama, username, dan password sudah terdaftar
    FILE *fileKaryawan;
    fileKaryawan = fopen("dataKaryawan.txt", "r");
     do {
        fscanf(fileKaryawan, "%29[^\n]\n%9[^\n]\n%19[^\n]\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        if(strcmp(read.karyawan.nama, write.karyawan.nama)== 0) {
            printf("\t\t Nama sudah terdaftar. Mohon masukkan nama yang berbeda.\n");
            printf("\t\t Ketik apapun untuk melanjutkan");
            getchar();
            systemCLS();
            signUpKaryawan();
            break;
        } 
        else if (strcmp(read.karyawan.username, write.karyawan.username)== 0) {
            printf("\t\t Username sudah terdaftar. Mohon masukkan username yang berbeda.\n");
            printf("\t\t Ketik apapun untuk melanjutkan. \n");
            getchar();
            systemCLS();
            signUpKaryawan();
            break;
        }
        else if (strcmp(read.karyawan.password, write.karyawan.password)== 0 ) {
            printf("\t\t Password sudah terdaftar. Mohon masukkan username yang berbeda.");
            printf("\t\t Ketik apapun untuk melanjutkan. \n");
            getchar();
            systemCLS();
            signUpKaryawan();
            break;
        }
    } while (!feof(fileKaryawan));
    fclose(fileKaryawan);

    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataKaryawan.txt", "a");

    fprintf(signUp, "%s\n%s\n%s\n", write.karyawan.nama, write.karyawan.username, write.karyawan.password);
    fclose(signUp);

    //Memeriksa apakah fprintf berhasil
    if(fprintf != 0) {
        printf("\n\t\t Sign Up Karyawan Berhasil.\n");
        systemPause();
        systemCLS();
        manageKaryawan();
    } else {
        printf("\n\t\t Terjadi error pada proses Sign In");
        exit(1);
    }
}

/*
    Prosedur sign in untuk karyawan
*/
void signInKaryawan () {

    FILE *signIn;
    signIn = fopen("dataKaryawan.txt", "r");

    if(signIn == NULL) {
        printf("\t\t Belum ada karyawan yang terdaftar.\n");
        printf("\t\t Silahkan hubungi pemilik untuk sign up karyawan.\n");
        systemPause();
        systemCLS();
        menuPertama();
    } else {
        printf("\t\t Silahkan lakukan Sign In terlebih dahulu.\n");
        printf("\t\t Username: ");
        scanf("%10s", write.karyawan.username);
        fflush(stdin);

        printf("\t\t Password: ");
        scanf("%20s", write.karyawan.password);
        fflush(stdin);

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        fscanf(signIn, "%[^\n]\n%s\n%s\n", read.karyawan.nama, read.karyawan.username, read.karyawan.password);
        if(strcmp(write.karyawan.username, read.karyawan.username)==0 && strcmp(write.karyawan.password, read.karyawan.password)==0) {
            dataKaryawan = read.karyawan;

            printf("\n\t\t Sign In telah berhasil.\n");
            printf("\t\t Selamat datang, %s.\n", dataKaryawan.nama);
            fclose(signIn);
            //menuAwalKaryawan();
        } else {
            printf("\n\t\t Username atau password yang dimasukkan salah. Mohon ulangi kembali.\n");
            systemPause();
            systemCLS();
            menuPertama();
        }
    }
}
