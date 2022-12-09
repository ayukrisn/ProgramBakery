#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"


daftarDataMembership dataMembership;

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
daftarDataPekerja dataKaryawan;
daftarDataPekerja dataPemilik;

/*
    Union yang akan digunakan saat berurusan dengan file
    write: data dari input pengguna, yang nanti akan digunakan
           untuk dimasukkan ke file/variabel program
    read:  data yang dibaca dari file, yang nanti dimasukkan
           ke variabel di dalam program
*/
tipeData write;
tipeData read; //note: menghapus variabel struct 'data'


/*
    Menu pertama yang akan keluar saat program dibuka
*/
void menuPertama()
{
    int pilihan;
    printf("\t\t Silahkan masuk terlebih dahulu.\n");
    printf("\t\t [1] Buka program untuk pelanggan.\n");
    printf("\t\t [2] Masuk sebagai Karyawan.\n");
    printf("\t\t [3] Masuk sebagai Pemilik.\n");
    printf("\t\t [4] Keluar dari program.\n");
    printf("\t\t Ketik pilihan dengan angka yang tertera:");
    scanf("%d", &pilihan);
    fflush(stdin);
    if (pilihan == 1) {
        //pemesananPelanggan();
    } else if (pilihan == 2) {
        signInKaryawan();
    } else if (pilihan == 3) {
        akunPemilik();
    } else if (pilihan == 4) {
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
        printf("\n\t\t Anda belum memiliki akun. Silahkan melanjutkan ke Sign Un Pemilik.\n");
        signUpPemilik();
    } else {
        fclose(periksaData);
        printf("\n\t\t Sudah ada akun yang terdaftar. Apakah Anda ingin melakukan Sign In?\n");
        printf("\t\t [1] Ya, saya ingin melakukan sign in.\n");
        printf("\t\t [2] Tidak, saya ingin melakukan sign up.\n");
        printf("\t\t [3] Kembali ke menu awal.\n");
        printf("\t\t CATATAN: Bila melakukan sign up, maka data yang sebelumnya ada akan terhapus.\n");
        printf("\t\t Ketik pilihan dengan angka yang tertera:");
        scanf("%d", &pilihan);
        if (pilihan == 1) {
            signInPemilik();
        } else if (pilihan == 2 ) {
            signUpPemilik();
        } else if (pilihan == 3 ) {
            menuPertama(0);
        }
    }
}

/*
    Prosedur sign up untuk pemilik
*/
void signUpPemilik()
{
    printf("\n\t\t Silahkan lakukan registrasi terlebih dahulu.\n");

    //Memasukkan data yang diperlukan
    printf("\t\t Username: ");
    scanf("%10s", write.pemilik.username);
    fflush(stdin);

    printf("\t\t Password: ");
    scanf("%20s", write.pemilik.password);
    fflush(stdin);

    printf("\t\t Email: ");
    scanf("%20s", write.pemilik.email);
    fflush(stdin);

    printf("\t\t Nama: ");
    fgets(write.pemilik.nama, 30 , stdin);
    write.pemilik.nama[strcspn(write.pemilik.nama, "\n")] = '\0';

    printf("\t\t No Telepon: ");
    scanf("%20s", write.pemilik.noTelp);
    fflush(stdin);

    strcpy(write.pemilik.jabatan, "Pemilik");
    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataPemilik.txt", "w");

    fwrite(&write, sizeof(write), 1, signUp);
    //fprintf(signUp, "%s\n%s\n%s\n%s\n%s", write.pemilik.username, write.pemilik.password, write.pemilik.email, write.pemilik.nama, write.pemilik.noTelp);
    fclose(signUp);

    //Memeriksa apakah fwrite berhasil
    if(fwrite != 0) {
        printf("\n\t\t Sign Up Pemilik Berhasil.\n");
        printf("\t\t Silahkan masuk kembali melalui Sign In.\n");
        signInPemilik();
    } else {
        printf("\n\t\t Terjadi error pada proses Sign In");
        exit(1);
    }
}

/*
    Prosedur sign in untuk pemilik
*/
void signInPemilik () {
    printf("\n\t\t Silahkan lakukan Sign In terlebih dahulu.\n");
    printf("\t\t Username: ");
    scanf("%10s", write.pemilik.username);
    fflush(stdin);

    printf("\t\t Password: ");
    scanf("%20s", write.pemilik.password);
    fflush(stdin);

    FILE *signIn;
    signIn = fopen("dataPemilik.txt", "r");

    //Memeriksa apakah username dan password yang diberikan benar atau tidak
    fread(&read.pemilik, sizeof(read.pemilik), 1, signIn);
        if(strcmp(write.pemilik.username, read.pemilik.username)==0 && strcmp(write.pemilik.password, read.pemilik.password)==0) {
            strcpy(dataPemilik.email, read.pemilik.email);
            strcpy(dataPemilik.jabatan, read.pemilik.jabatan);
            strcpy(dataPemilik.nama, read.pemilik.nama);
            strcpy(dataPemilik.noTelp, read.pemilik.noTelp);
            strcpy(dataPemilik.password, read.pemilik.password);
            strcpy(dataPemilik.username, read.pemilik.username);

            printf("\n\t\t Sign In telah berhasil.\n");
            printf("\t\t Selamat datang, %s.\n", dataPemilik.nama);
            fclose(signIn);
            menuAwalPemilik();
        } else {
            printf("\n\t\t Username atau password yang dimasukkan salah. Mohon ulangi kembali.\n");
            akunPemilik();
        }
}


/*
    Prosedur sign up untuk karyawan
*/
void signUpKaryawan()
{
    printf("\n\t\t Silahkan lakukan registrasi data karyawan terlebih dahulu.\n");

    //Memasukkan data yang diperlukan
    printf("\t\t Username: ");
    scanf("%10s", write.karyawan.username);
    fflush(stdin);


    printf("\t\t Password: ");
    scanf("%20s", write.karyawan.password);
    fflush(stdin);

    printf("\t\t Email: ");
    scanf("%20s", write.karyawan.email);
    fflush(stdin);

    printf("\t\t Nama: ");
    fgets(write.karyawan.nama, 30 , stdin);
    write.karyawan.nama[strcspn(write.karyawan.nama, "\n")] = '\0';

    printf("\t\t No Telepon: ");
    scanf("%20s", write.karyawan.noTelp);
    fflush(stdin);

    printf("\t\t Jabatan: ");
    fgets(write.karyawan.jabatan, 30 , stdin);
    write.karyawan.jabatan[strcspn(write.karyawan.jabatan, "\n")] = '\0';

    //Membuka file dataPemilik.txt untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataKaryawan.txt", "a");

    fwrite(&write, sizeof(write), 1, signUp);
    fclose(signUp);

    //Memeriksa apakah fwrite berhasil
    if(fwrite != 0) {
        printf("\n\t\t Sign Up Karyawan Berhasil.\n");
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
    } else {
        printf("\n\t\t Silahkan lakukan Sign In terlebih dahulu.\n");
        printf("\t\t Username: ");
        scanf("%10s", write.karyawan.username);
        fflush(stdin);

        printf("\t\t Password: ");
        scanf("%20s", write.karyawan.password);
        fflush(stdin);

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        fread(&read.karyawan, sizeof(read.karyawan), 1, signIn);
        if(strcmp(write.karyawan.username, read.karyawan.username)==0 && strcmp(write.karyawan.password, read.karyawan.password)==0) {
            strcpy(dataKaryawan.email, read.karyawan.email);
            strcpy(dataKaryawan.jabatan, read.karyawan.jabatan);
            strcpy(dataKaryawan.nama, read.karyawan.nama);
            strcpy(dataKaryawan.noTelp, read.karyawan.noTelp);
            strcpy(dataKaryawan.password, read.karyawan.password);
            strcpy(dataKaryawan.username, read.karyawan.username);

            printf("\n\t\t Sign In telah berhasil.\n");
            printf("\t\t Selamat datang, %s.\n", dataKaryawan.nama);
            fclose(signIn);
            //menuAwalKaryawan();
        } else {
            printf("\n\t\t Username atau password yang dimasukkan salah. Mohon ulangi kembali.\n");
            menuPertama();
        }
    }
}
