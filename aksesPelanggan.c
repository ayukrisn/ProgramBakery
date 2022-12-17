#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesAdmin.h"
#include "pendukung.h"
#include "daftarMenuRev.h"
#include "aksesPelanggan.h"

bool isPelanggan = false;
bool isMember = false;
char namaGuest[20];
detailTransaksi DTransaksi[12];

/*
    ===========================================================================
                     B A G I A N  A K S E S  P E L A N G G A N                 
    ===========================================================================
*/

/*
    Langkah selanjutnya setelah karyawan memilih bagian buka program untuk pelanggan
*/

void menuMasukPelanggan()
{
    int pilihan;
    printf("\t\t  _______________________________________________________\n");
    printf("\t\t |_______________________________________________________|\n");
    printf("\t\t |                     W E L C O M E !                   | \n");
    printf("\t\t |           C A K E  M E  O U T  B A K E R Y            | \n");
    printf("\t\t |_______________________________________________________| \n");
    printf("\t\t |     Apakah sebelumnya sudah memiliki akun member?     |\n");
    printf("\t\t |-------------------------------------------------------|\n");
    printf("\t\t |           [1] Ya, sudah           [2] Belum           |\n");
    printf("\t\t |                                                       |\n");
    printf("\t\t |     [3] Keluar dari program pelanggan [Perlu akses]   |\n");
    printf("\t\t +_______________________________________________________+\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2/3) : ");
    pilihanUser(&pilihan, 1, 3);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        signInAccount();
    } else if (pilihan == 2) {
        systemCLS();
        tanyaAkun();
    } else if (pilihan == 3){
        systemCLS();
        konfirmasiTutup();
    }
}

void tanyaAkun()
{
    int pilihan;
    printf("\t\t _______________________________________________________ \n");
    printf("\t\t|             Apakah Anda ingin ikut member?            |\n");
    printf("\t\t|-------------------------------------------------------|\n");
    printf("\t\t|    [1] Tentunya mau donggg    [2] Sorry, engga deh    |\n");
    printf("\t\t|_______________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) : ");
    pilihanUser(&pilihan, 1, 2);
    fflush(stdin);
    if (pilihan == 1) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|       Anda akan diarahkan untuk sign up account       |\n");
        printf("\t\t|_______________________________________________________|\n");
        systemPause();
        systemCLS();
        signUpAccount(); 
    } else if (pilihan == 2) {
        printf("\t\t _______________________________________________________ \n");
        printf("\t\t|    Anda akan diarahkan langsung ke menu pelanggan     |\n");
        printf("\t\t|_______________________________________________________|\n");
        printf("\t\t Mohon masukkan nama Anda terlebih dahulu.\n");
        inputNama(namaGuest);
        systemPause();
        systemCLS();
        menuAwalPelanggan();
    }
}

/*
    Prosedur sign up untuk pelanggan
*/

void signUpAccount()
{
    printf("\t\t _____________________________________________________________________ \n");
    printf("\t\t|         Silahkan lakukan sign up data member terlebih dahulu.       |\n");
    printf("\t\t|_____________________________________________________________________|\n");

    inputNama(writeUser.membership.nama);
    inputUsername(writeUser.membership.username);
    inputPassword(writeUser.membership.password);

    // Pemeriksaan apakah nama dan username sudah terdaftar
    FILE *member;
    member = fopen("dataMembership.txt", "r");
     do {
        fscanf(member, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        if(strcmp(readUser.membership.nama, writeUser.membership.nama)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|       Nama sudah terdaftar. Mohon masukkan nama yang berbeda.       |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpAccount();
            break;
        } 
        else if (strcmp(readUser.membership.username, writeUser.membership.username)== 0) {
            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|   Username sudah terdaftar. Mohon masukkan username yang berbeda.   |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            systemPause();
            systemCLS();
            signUpAccount();
            break;
        }
    } while (!feof(member));
    fclose(member);

    //Membuka file dataMembership.txt untuk memasukkan data
    FILE *memberShip;
    memberShip = fopen("dataMembership.txt", "a");

    fprintf(memberShip, "%s;%s;%s;\n", writeUser.membership.nama, writeUser.membership.username, writeUser.membership.password);
    fclose(memberShip);

    //Memeriksa apakah fprintf berhasil
    if(fprintf != 0) {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|                   Sign up member account berhasil.                  |\n");
        printf("\t\t|---------------------------------------------------------------------|\n");
        printf("\t\t|               Silahkan masuk kembali melalui Sign In.               |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        signInAccount();
    } else {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|                  Terjadi error pada proses sign up.                 |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        signUpAccount();
    }
}

/*
    Prosedur sign in untuk pelanggan
*/

void signInAccount()
{
    FILE *signInMember;
    signInMember = fopen("dataMembership.txt", "r");

    if(signInMember == NULL) {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|                Belum ada akun member yang terdaftar.                |\n");
        printf("\t\t|---------------------------------------------------------------------|\n");
        printf("\t\t|           Silahkan hubungi karyawan untuk sign up pelanggan.        |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        menuPertama();
    } else {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t|              Silahkan lakukan sign in terlebih dahulu.              |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        printf("\t\t  Username : ");
        scanf("%[^\n]", writeUser.membership.username);
        getchar();

        printf("\t\t  Password : ");
        scanf("%[^\n]", writeUser.membership.password);
        getchar();

        //Memeriksa apakah username dan password yang diberikan benar atau tidak
        bool tidakKetemu = 0;
        rewind(signInMember);
        do {
        fscanf(signInMember, "%[^;];%[^;];%[^;];\n", readUser.membership.nama, readUser.membership.username, readUser.membership.password);
        
        if(strcmp(writeUser.membership.username, readUser.membership.username)==0 && strcmp(writeUser.membership.password, readUser.membership.password)==0) {
            tidakKetemu = 0;
            dataMembership = readUser.membership;

            printf("\t\t _____________________________________________________________________ \n");
            printf("\t\t|                Sign in member account telah berhasil.               |\n");
            printf("\t\t|_____________________________________________________________________|\n");
            printf("\t\t  Selamat datang, %s\n", dataMembership.nama);
            fclose(signInMember);
            isMember = true;
            systemPause();
            systemCLS();
            menuAwalPelanggan();
            break;
        } else tidakKetemu = 1;
        } while (!feof(signInMember));

        if (tidakKetemu) {
        printf("\t\t _____________________________________________________________________ \n");
        printf("\t\t| Username atau password yang dimasukkan salah. Mohon ulangi kembali. |\n");
        printf("\t\t|_____________________________________________________________________|\n");
        systemPause();
        systemCLS();
        menuMasukPelanggan();
        }
    }
}


void menuAwalPelanggan() 
{
    isPelanggan = true;
    int pilihan;
    printf("\t\t+_____________________________________________________________________+\n");
    printf("\t\t|_____________________________________________________________________|\n");
    printf("\t\t|                           W E L C O M E !                           | \n");
    printf("\t\t|                  C A K E  M E  O U T  B A K E R Y                   | \n");
    printf("\t\t|_____________________________________________________________________| \n");
    if (isMember) {
    printf("\t\t|                     Selamat datang, %-30s  |\n", dataMembership.nama);
    } else {
    printf("\t\t|                     Selamat datang, %-30s  |\n", namaGuest);
    }
    printf("\t\t|_____________________________________________________________________|\n");
    printf("\t\t|                   Silahkan pilih menu di bawah ini                  |\n");
    printf("\t\t|---------------------------------------------------------------------|\n");
    printf("\t\t|   [1] Lihat daftar menu                                             |\n");
    printf("\t\t|   [2] Lakukan pemesanan                                             |\n");
    printf("\t\t|   [3] Sign out dan kembali ke menu awal                             |\n");
    printf("\t\t|_____________________________________________________________________|\n");
    printf("\t\t  Ketik pilihan dengan angka yang tertera (1-3) : ");
    pilihanUser(&pilihan, 1, 3);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        lihatDaftarMenuM();
    } else if (pilihan == 2) {
        systemCLS();
        pemesanan();
    } else if (pilihan == 3){
        systemCLS();
        isMember = false;
        menuMasukPelanggan();
    }
}

/*
    Lihat daftar menu untuk pelanggan
*/ 
void lihatDaftarMenuM()
{
    if (!cekFileDaftarMenu()) {
        systemPause();
        systemCLS();
        menuMasukPelanggan();
     }

    lihatDaftarMenu();
        int pilihan;
        printf("\t\t _________________________________________________________________ \n");    
        printf("\t\t|                        Lanjutkan ke pemesanan?                  |\n");
	    printf("\t\t|-----------------------------------------------------------------|\n");
        printf("\t\t|                        [1] Ya        [2] Tidak                  |\n");
        printf("\t\t|-----------------------------------------------------------------|\n");
        printf("\t\t|               [3] Sign out dan kembali ke menu masuk            |\n");
	    printf("\t\t|_________________________________________________________________|\n");
        printf("\t\t  Ketik pilihan dengan angka yang tertera (1-3) : ");
    pilihanUser(&pilihan, 1, 3);
    fflush(stdin);
    if (pilihan == 1) {
        systemCLS();
        pemesanan();
    } else if (pilihan == 2) {
        systemCLS();
        menuAwalPelanggan();
    } else if (pilihan == 3){
        systemCLS();
        isMember = false;
        menuMasukPelanggan();
    }
}

void pemesanan() {
    showDaftarMenuAll();
    int urutan = 0;
    int pilihan = 0;
    bool kodeKetemu = false;
    bool stokCukup = false;
    bool pemesananDone = false;
    char namaYgStokHabis[20];
    int sisaStok;
    printf("\t\t _________________________________________________________________ \n"); 
    printf("\t\t|                  C A K E  M E  O U T  B A K E R Y               | \n");   
    printf("\t\t|                         P E M E S A N A N                       |\n");
	printf("\t\t|-----------------------------------------------------------------|\n");
    // Selama pelanggan tidak menghentikan pemesanan ulang
    while (1) {
        printf("\t\t Urutan ke %d\n", urutan);
        printf("\t\t Masukkan kode makanan (Contoh: CABK)\n");
        printf("\t\t Kode Makanan yang diinginkan: ");
        // Untuk sementara, kode makanan ga make validasi. Nanti make
        scanf("%[^\n]", DTransaksi[urutan].kodeMakanan);
        getchar();

        printf("\t\t Banyak pembelian            : ");
        inputInteger(&DTransaksi[urutan].banyakPembelian);

        FILE *fileDaftarMenu;
        fileDaftarMenu = fopen("dataDaftarMenu.txt", "r");

        FILE *tempDaftarMenu;
        tempDaftarMenu = fopen("tempDaftarMenu.txt", "w");

        do {
            fscanf(fileDaftarMenu, "%[^;];%[^;];%[^;];%[^;];%f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
            readMenu.deskripsiMakanan, &readMenu.hargaMakanan, &readMenu.stock);

            //printf("\ntest %d\n", urutan);
            if(strcmp(readMenu.kodeMakanan, DTransaksi[urutan].kodeMakanan)== 0) {
                kodeKetemu = true;
                if(readMenu.stock >= DTransaksi[urutan].banyakPembelian) {
                    stokCukup = true;
                    readMenu.stock -= DTransaksi[urutan].banyakPembelian;
                    DTransaksi[urutan].hargaSatuan = readMenu.hargaMakanan;
                    DTransaksi[urutan].hargaTotal = DTransaksi[urutan].hargaSatuan*DTransaksi[urutan].banyakPembelian;
                    pemesananDone = true; //Artinya dia sudah melakukan pemesanan
                    printf("\t\t _________________________________________________________________\n");
                    printf("\t\t| Pesanan ke-%-2d                                                   |\n", urutan+1);
                    printf("\t\t| > Nama Pesanan  : %-45s |\n", readMenu.namaMakanan);
                    printf("\t\t| > Harga Satuan  : %-45.2f |\n", readMenu.hargaMakanan);
                    printf("\t\t| > Pembelian     : %-2d                                            |\n", DTransaksi[urutan].banyakPembelian);
	                printf("\t\t| > Harga Total   : %-45.2f |\n", DTransaksi[urutan].hargaTotal);
                } else {
                    strcpy(namaYgStokHabis, readMenu.namaMakanan);
                    sisaStok = readMenu.stock;
                }
            }
            
        fprintf(tempDaftarMenu, "%s;%s;%s;%s;%.2f;%d;\n", readMenu.jenisMakanan, readMenu.kodeMakanan, readMenu.namaMakanan, 
        readMenu.deskripsiMakanan, readMenu.hargaMakanan, readMenu.stock);
        } while (!feof(fileDaftarMenu));

        fclose(fileDaftarMenu);
        fclose(tempDaftarMenu);
        remove("dataDaftarMenu.txt");
        rename("tempDaftarMenu.txt","dataDaftarMenu.txt");

        if (!kodeKetemu) {
            printf("\t\t _________________________________________________________________\n");
            printf("\t\t|  Kode makanan tidak ditemukan. Ingin mengulang input pemesanan? |\n");
	        printf("\t\t|-----------------------------------------------------------------|\n");
        } else if (!stokCukup) {
            kodeKetemu = false;
            time_t waktuL = time(NULL);
            struct tm *waktuLokal = localtime(&waktuL);
            int jam = waktuLokal->tm_hour;
            printf("\t\t _________________________________________________________________\n");
            printf("\t\t|                   Maaf, stok makanan tidak cukup!               |\n");
	        printf("\t\t|-----------------------------------------------------------------|\n");
            printf("\t\t| > Sisa stok %-20s = %-29d|\n", namaYgStokHabis, sisaStok);
            if (jam > jamRestock.sore)
            printf("\t\t|                 Pilihan Anda akan direstock besok.              |\n");
            else if (jam > jamRestock.siang)
            printf("\t\t|                Restock akan dilakukan di jam %2d:00              |\n", jamRestock.sore);
            else if (jam > jamRestock.pagi)
            printf("\t\t|                Restock akan dilakukan di jam %2d:00              |\n", jamRestock.siang);
	        printf("\t\t|-----------------------------------------------------------------|\n");
            printf("\t\t|                 Ingin mengulang input pemesanan?                |\n");
        }

        if (kodeKetemu && stokCukup) {
            kodeKetemu = false;
            stokCukup = false;
            urutan++;
            printf("\t\t _________________________________________________________________\n");
            printf("\t\t|                  P E M E S A N A N  S E L E S A I               |\n");
            printf("\t\t|                 Ingin melakukan pemesanan lainnya?              |\n");
	        printf("\t\t|-----------------------------------------------------------------|\n");

        }

            printf("\t\t|                   [1] Ya              [2] Tidak                 |\n");
	        printf("\t\t|_________________________________________________________________|\n");
            printf("\t\t  Ketik pilihan dengan angka yang tertera (1-2) : ");
            pilihanUser(&pilihan, 1, 2);
            fflush(stdin);
            if (pilihan == 2) {
                if (pemesananDone) { //Artinya dia sudah melakukan pemesanan
                printf("\t\t Anda akan diarahkan ke pembayaran.\n");
                systemPause();
                systemCLS();
                transaksiPelanggan(); 
                break;
                } else {
                systemPause();
                systemCLS();
                menuAwalPelanggan();
                break;
                }
            }
    }
}

void transaksiPelanggan() {
    printf("Ini transaksi pelanggan.");
}