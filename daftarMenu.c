#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "logIn.h"
#include "variabel.h"
#include "aksesPemilik.h"
#include "pendukung.h"

typedef struct
{
    char namaMakanan[10];
    char deskripsiMakanan[100];
    float hargaMakanan;
} daftarMenu;

/*
    Daftar menu yang akan diakses nanti oleh pelanggan/member
*/
void daftarMenu(){
    int pilihan, jumlahPesanan;
	  float totalHarga;
	  printf("\t\t ____________________________________________________________________________________________\n");
	  printf("\t\t|                                    D A F T A R  M E N U                                    |\n");
    printf("\t\t|                                     CAKE ME OUT BAKERY                                     |\n");
    printf("\t\t| __________________________________________________________________________________________ |\n");
    printf("\t\t| Pilih menu yang anda inginkan (0-9)!                                         [0] - Kembali |\n");
    printf("\t\t| ------------------------------------------------------------------------------------------ |\n");
    printf("\t\t|  NO |  NAMA MAKANAN   |                         DESKRIPSI                        |  HARGA  |\n");
    printf("\t\t| ------------------------------------------------------------------------------------------ |\n");
    printf("\t\t| [1] | Hokkaido Dome 	| Sweet bread with cookies topping                         | Rp8500  |\n");
	  printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [2] | Hamtaro         | Hazelnut chocolate bread filled with vanilla cream       | Rp10500 |\n");
    printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [3] | Twilight        | Bread filled with minced meat, onion, and parsley on top | Rp9500  |\n");
    printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [4] | Granola Caramel	| Cookies with granola and caramel                         | Rp18000 |\n");
    printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [5] | Crunchy Mede    | Cashew nuts fried with crispy flour                      | Rp55000 |\n");
    printf("\t\t|     |               	|                                                          |         |\n");
    printf("\t\t| [6] | Triple Magic    | Chocolate cookies with oatmeal, raisin, and almond       | Rp15000 |\n");
    printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [7] | Soft Cheese     | Soft bread with cheese                                   | Rp28000 |\n");
    printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [8] | Mocha Meyses  	| Soft bread with mocha cream and meyses                   | Rp25000 |\n");
	  printf("\t\t|     |                 |                                                          |         |\n");
    printf("\t\t| [9] | Eq Cheese       | Toast with melted cheese on top                          | Rp27500 |\n");
    printf("\t\t|__________________________________________________________________________________|_________|\n");
	  printf("\t\t  Ketikkan pilihan anda	: 													 				                                 |\n");
	  pilihanUser(&pilihan, 1, 9);
    fflush(stdin);
	  switch(pilihan){
		case 0 :
			systemCLS();
			//balik ke bagian login pelanggan
			break;
		case 1 :
			printf("\t\t _______________________________________________________ \n");
      printf("\t\t|    Anda memilih Hokkaido Dome dengan harga Rp8500     |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %d\n", jumlahPesanan);
			totalHarga = 8500*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 2 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|       Anda memilih Hamtaro dengan harga Rp10500       |\n");
			printf("\t\t|_______________________________________________________|\n");
      printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 10500*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 3 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|       Anda memilih Twilight dengan harga Rp9500       |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 9500*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 4 :
			printf("\t\t _______________________________________________________ \n");
      printf("\t\t|   Anda memilih Granola Caramel dengan harga Rp18000   |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 18000*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 5 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|    Anda memilih Crunchy Mede dengan harga Rp55000     |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 55000*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 6 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|    Anda memilih Triple Magic dengan harga Rp15000     |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 15000*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : Rp%.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 7 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|    Anda memilih Soft Cheese dengan harga RpRp28000    |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 28000*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 8 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|    Anda memilih Mocha Meyses dengan harga RpRp25000   |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 25000*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
		case 9 :
      printf("\t\t _______________________________________________________ \n");
			printf("\t\t|     Anda memilih Eq Cheese dengan harga RpRp27500     |\n");
      printf("\t\t|_______________________________________________________|\n");
			printf("\t\t  Jumlah pesanan : %.d\n", jumlahPesanan);
			totalHarga = 27500*jumlahPesanan;
			printf("\t\t  Total yang harus dibayarkan : %.2f\n",totalHarga);
			systemCLS();
			//pergi ke bagian struk
			break;
	}
}


/*
	Lanjutan ketika memilih pilihan menu yang no 3 pada bagian akses pemilik
*/

void manageDaftarMenu()
{
	int pilihDaftar;
	printf("\t\t _______________________________________________________ \n");
	printf("\t\t|           M A N A G E  D A F T A R  M E N U           |\n");
	printf("\t\t|-------------------------------------------------------|\n");
	printf("\t\t| Silahkan pilih opsi dibawah ini                       |\n");
	printf("\t\t|-------------------------------------------------------|\n");
	printf("\t\t| [1] Lihat Daftar Menu                                 |\n");
	printf("\t\t| [2] Edit Daftar Menu                                  |\n");
	printf("\t\t| [3] Tambah Daftar Menu                                |\n");
	printf("\t\t| [4] Hapus Daftar Menu                                 |\n");
	printf("\t\t| [5] Kembali ke akses pemilik                          |\n");
	printf("\t\t|_______________________________________________________|\n");
	printf("\t\t  Ketikkan pilihan anda (1-5) :                          \n");
	pilihanUser(&pilihan, 1, 5);
  fflush(stdin);
	if(pilihDaftar == 1){
      systemCLS();
      lihatDaftarMenu();
  } else if (pilihDaftar == 2) {
      systemCLS();
      editDaftarMenu();
  } else if (pilihDaftar == 3 ) {
      systemCLS();
      tambahDaftarMenu();
  } else if (pilihDaftar == 4 ) {
      systemCLS();
      hapusDaftarMenu();
	} else if (pilihDaftar == 5 ) {
      systemCLS();
      menuAwalPemilik(); //kembali ke bagian akses pemilik
  }
}
	

//Lihat Daftar Menu

void lihatMenu()
{
	cekDaftarMenu();
	int pilih;
	printf("\t\t _________________________________________________________ \n");
	printf("\t\t|            Ingin kembali ke menu sebelumnya?            |\n");
	printf("\t\t|---------------------------------------------------------|\n");
  printf("\t\t| [1] Ya, kembali ke menu manage daftar menu              |\n");
  printf("\t\t| [2] Tidak, kembali ke menu akses pemilik                |\n");
	printf("\t\t|_________________________________________________________|\n");
  printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) :          \n");
  pilihanUser(&pilihan, 1, 2);
  fflush(stdin);
  if (pilih == 1){
      systemCLS();
      manageDaftarMenu(); //kebagian manage daftar menu
  } else if (pilih ==2){
      systemCLS();
      menuAwalPemilik(); //kebagian akses pemilik
  }
}


void cekDaftarMenu()
{
	//membuka file daftarMenu.txt dan membacanya
	FILE *menuDaftar;
	menuDaftar=fopen("daftarMenu.txt","r");

	//mengecek apakah datanya tersedia atau tidak
	if(menuDaftar == NULL){
		printf("\t\t|_______________________________________________________ \n");
    printf("\t\t|              DAFTAR MENU TIDAK TERSEDIA!              |\n");
    printf("\t\t|_______________________________________________________|\n");
		systemPause():
		systemCLS();
		menuAwalPemilik(); //balik ke bagian pemilik
	}
	//while(fgets(
	//belum selesai

	fclose(daftarMenu);
}


//Edit Daftar Menu

void editDaftarMenu()
{
	perbaikiDaftarMenu();
  int pilihan;
	printf("\t\t _________________________________________________________ \n");
	printf("\t\t|            Ingin kembali ke menu sebelumnya?            |\n");
	printf("\t\t|---------------------------------------------------------|\n");
  printf("\t\t| [1] Ya, kembali ke menu manage daftar menu              |\n");
  printf("\t\t| [2] Tidak, kembali ke menu akses pemilik                |\n");
	printf("\t\t|_________________________________________________________|\n");
  printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) :          \n");
  pilihanUser(&pilihan, 1, 2);
  fflush(stdin);
  if (pilihan == 1){
      systemCLS();
      manageDaftarMenu(); //kebagian manage daftar menu
  } else if (pilihan ==2){
      systemCLS();
      menuAwalPemilik(); //kebagian akses pemilik
  }
}

void perbaikiDaftarMenu()
{

}


//Tambah Daftar Menu

void tambahDaftarMenu()
{
	penambahanDaftarMenu();
	int pilihan;
	printf("\t\t _________________________________________________________ \n");
	printf("\t\t|            Ingin kembali ke menu sebelumnya?            |\n");
	printf("\t\t|---------------------------------------------------------|\n");
  printf("\t\t| [1] Ya, kembali ke menu manage daftar menu              |\n");
  printf("\t\t| [2] Tidak, kembali ke menu akses pemilik                |\n");
	printf("\t\t|_________________________________________________________|\n");
  printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) :          \n");
  pilihanUser(&pilihan, 1, 2);
  fflush(stdin);
  if (pilihan == 1){
      systemCLS();
      manageDaftarMenu(); //kebagian manage daftar menu
  } else if (pilihan ==2){
      systemCLS();
      menuAwalPemilik(); //kebagian akses pemilik
  }
}

void penambahanDaftarMenu()
{
	FILE *daftarMenu;
	daftarMenu = fopen("daftarMenu.txt", "a");

	fprintf(daftarMenu,"\t\t __________________________________________________________________________ \n");
	fprintf(daftarMenu,"\t\t|                     T A M B A H  D A F T A R  M E N U                    |\n");
	fprintf(daftarMenu,"\t\t|                            CAKE ME OUT BAKERY                            |\n");
	fprintf(daftarMenu,"\t\t| ------------------------------------------------------------------------ |\n");
	fprintf(daftarMenu,"\t\t|  NO  |  NAMA MAKANAN   |				 	       DESKRIPSI				 	   |  HARGA  |\n");
  fprintf(daftarMenu,"\t\t| ------------------------------------------------------------------------ |\n");
	for (n = 0 ; n < i; n++)
	{
	    fprintf(daftarMenu,"\t\t| %-2d.| %-10s    		   | %s              	 	                   |  Rp%.2f |\n", n+1, daftarMenu.namaMakanan, daftarMenu.deskripsiMakanan, daftarMenu.hargaMakanan);
	}
	fprintf(daftarMenu,"\t\t|__________________________________________________________________________|\n\n");
    
	fclose(daftarMenu);
}


//Hapus Daftar Menu

void hapusDaftarMenu()
{
	penghapusanDaftarMenu();
	int pilihan;
	printf("\t\t _________________________________________________________ \n");
	printf("\t\t|            Ingin kembali ke menu sebelumnya?            |\n");
	printf("\t\t|---------------------------------------------------------|\n");
  printf("\t\t| [1] Ya, kembali ke menu manage daftar menu              |\n");
  printf("\t\t| [2] Tidak, kembali ke menu akses pemilik                |\n");
	printf("\t\t|_________________________________________________________|\n");
  printf("\t\t  Ketik pilihan dengan angka yang tertera (1/2) :          \n");
  pilihanUser(&pilihan, 1, 2);
  fflush(stdin);
  if (pilihan == 1){
      systemCLS();
      manageDaftarMenu(); //kebagian manage daftar menu
  } else if (pilihan ==2){
      systemCLS();
      menuAwalPemilik(); //kebagian akses pemilik
  }
}

void penghapusanDaftarMenu()
{
  
} 
