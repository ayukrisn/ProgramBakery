#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuPertama(); void akunPemilik();
    void signUpPemilik(); void signInPemilik();
    void signUpKaryawan(); void signInKaryawan();


/*
    Struct untuk data membership
    yang akan disimpan selama
    program dijalankan
*/
typedef struct {
    char username[10];
    char password[20];
    char email[30];
    char noTelp[20];
    char nama[30];
    char tipeMembership[10];
} daftarDataMembership;
daftarDataMembership dataMembership;

typedef union {
    daftarDataMembership dataMembership;
    char guest[];
} tipePembeli;

typedef struct {
    char username[10];
    char password[20];
    char email[30];
    char noTelp[20];
    char nama[30];
    char jabatan[20];
} daftarDataPekerja;
daftarDataPekerja dataKaryawan, dataPemilik;

/*
    Union yang akan digunakan saat berurusan dengan file
*/
typedef union {
    daftarDataMembership membership;
    daftarDataPekerja karyawan;
    daftarDataPekerja pemilik;
} tipeData;
tipeData write, read, data;

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
    } else if (pilihan == 2) {
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

    periksaData = fopen("dataPemilik.bin", "r");
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
    //Membuka file dataPemilik.bin untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataPemilik.bin", "w");

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
    signIn = fopen("dataPemilik.bin", "r");

    //Memeriksa apakah username dan password yang diberikan benar atau tidak
    fread(&read.pemilik, sizeof(read.pemilik), 1, signIn);
        if(strcmp(write.pemilik.username, read.pemilik.username)==0 && strcmp(write.pemilik.password, read.pemilik.password)==0) {
            strcpy(dataPemilik.nama, read.pemilik.nama);
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

    //Membuka file dataPemilik.bin untuk memasukkan data tadi
    FILE *signUp;
    signUp = fopen("dataKaryawan.bin", "a");

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
    signIn = fopen("dataKaryawan.bin", "r");

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
            strcpy(dataKaryawan.nama, read.karyawan.nama);
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
