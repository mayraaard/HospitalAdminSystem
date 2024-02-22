#include <stdio.h>
#include <string.h>

// Struct untuk menyimpan data pasien rawat jalan
typedef struct {
    char nama[50];
    char tanggalLahir[20];
    char alamat[100];
    char jenisKelamin[10];
    char keluhan[100];
    int asuransi;
    int poli;
    int sesi;
} PasienRawatJalan;

// Struct untuk menyimpan data pasien rawat inap
typedef struct {
    char nama[50];
    char tanggalLahir[20];
    char alamat[100];
    char jenisKelamin[10];
    char keluhan[100];
    int asuransi;
    int kamar;
} PasienRawatInap;

// Array untuk menyimpan data antrian pasien rawat jalan
PasienRawatJalan antrianRawatJalan[100];
int jumlahAntrianRawatJalan = 0;

// Array untuk menyimpan data pasien rawat inap
PasienRawatInap pasienRawatInap[100];
int jumlahPasienRawatInap = 0;

// Fungsi untuk menampilkan menu utama
void tampilkanMenuUtama() {
    printf("\n===== MENU UTAMA =====\n");
    printf("1. Rawat Jalan\n");
    printf("2. Rawat Inap\n");
    printf("3. Logout\n");
}

// Fungsi untuk meminta input pilihan menu dari user
int mintaInputPilihan() {
    int pilihan;
    printf("Pilihan Anda: ");
    scanf("%d", &pilihan);
    return pilihan;
}

// Fungsi untuk mendaftarkan pasien rawat jalan
void daftarRawatJalan(PasienRawatJalan* pasien_RawatJalan) {
    printf("\n===== DAFTAR RAWAT JALAN =====\n");
    printf("Nama: ");
    scanf(" %[^\n]s", pasien_RawatJalan->nama);
    printf("Tanggal Lahir (dd/mm/yyyy): ");
    scanf(" %[^\n]s", pasien_RawatJalan->tanggalLahir);
    printf("Alamat: ");
    scanf(" %[^\n]s", pasien_RawatJalan->alamat);
    printf("Jenis Kelamin: ");
    scanf(" %[^\n]s", pasien_RawatJalan->jenisKelamin);
    printf("Keluhan: ");
    scanf(" %[^\n]s", pasien_RawatJalan->keluhan);
    printf("Apakah pasien memiliki asuransi?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pasien_RawatJalan->asuransi);
    printf("Pilih poli (1-10):\n");
    printf("1. Poli Umum\n");
    printf("2. Poli Gigi\n");
    printf("3. Poli THT\n");
    printf("4. Poli Mata\n");
    printf("5. Poli Syaraf\n");
    printf("6. Poli Jantung\n");
    printf("7. Poli Kulit & Kelamin\n");
    printf("8. Poli Penyakit Dalam\n");
    printf("9. Poli Kebidanan\n");
    printf("10. Poli Anak\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pasien_RawatJalan->poli);
    printf("Pilih sesi (1-3):\n");
    printf("1. Pagi\n");
    printf("2. Sore\n");
	printf("3. Malam\n");
	printf("Pilihan Anda: ");
	scanf("%d", &pasien_RawatJalan->sesi);
	jumlahAntrianRawatJalan++;
    printf("Registrasi berhasil. Nomor Antrian: %d\n", jumlahAntrianRawatJalan);
    antrianRawatJalan[jumlahAntrianRawatJalan - 1] = *pasien_RawatJalan;
}

//Fungsi untuk mengambil data antrian
void ambilDataAntrian() {
    FILE *file = fopen("antrian_rawat_jalan.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file antrian_rawat_jalan.txt\n");
    } else{
    	jumlahAntrianRawatJalan = 0;
    	PasienRawatJalan pasienRawatJalan;
    	
    	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",
                pasienRawatJalan.nama,
                pasienRawatJalan.tanggalLahir,
                pasienRawatJalan.alamat,
                pasienRawatJalan.jenisKelamin,
                pasienRawatJalan.keluhan,
                &pasienRawatJalan.asuransi,
                &pasienRawatJalan.poli,
                &pasienRawatJalan.sesi) == 8) {
        antrianRawatJalan[jumlahAntrianRawatJalan++] = pasienRawatJalan;
    	}	
    	fclose(file);
	}
}

//Fungsi untuk menyimpan data antrian
void simpanDataAntrian() {
    FILE *file = fopen("antrian_rawat_jalan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file antrian_rawat_jalan.txt\n");
    } else{
    	int i;
    	for (i = 0; i < jumlahAntrianRawatJalan; i++){
    		fprintf(file, "%s,%s,%s,%s,%s,%d,%d,%d\n",
    	        antrianRawatJalan[i].nama,
                antrianRawatJalan[i].tanggalLahir,
                antrianRawatJalan[i].alamat,
                antrianRawatJalan[i].jenisKelamin,
                antrianRawatJalan[i].keluhan,
                antrianRawatJalan[i].asuransi,
                antrianRawatJalan[i].poli,
                antrianRawatJalan[i].sesi);	
		}
		fclose(file);
	}
}

// Fungsi untuk menampilkan antrian pasien rawat jalan
void tampilkanAntrianRawatJalan() {
	int i;
    printf("\n===== ANTRIAN RAWAT JALAN =====\n");
    if (jumlahAntrianRawatJalan == 0) {
        printf("Tidak ada antrian pasien rawat jalan.\n");
    } else {
    	printf("No.  Nama\t\tPoli\tSesi\n");
    	for (i = 0; i < jumlahAntrianRawatJalan; i++) {
        	printf("%d.   %s\t\t%d\t%d\n", i + 1, antrianRawatJalan[i].nama, antrianRawatJalan[i].poli, antrianRawatJalan[i].sesi);
   			}
	}
}

// Fungsi untuk menghapus pasien pasien dari antrian setelah pembayaran
void hapusPasienAntrianRawatJalan(int index) {
    int i;
    for (i = index; i < jumlahAntrianRawatJalan - 1; i++) {
        antrianRawatJalan[i] = antrianRawatJalan[i + 1];
    }
    jumlahAntrianRawatJalan--;
}

// Fungsi untuk melakukan pembayaran pasien rawat jalan
void pembayaranRawatJalan() {
    printf("\n===== PEMBAYARAN RAWAT JALAN =====\n");
    if (jumlahAntrianRawatJalan == 0) {
        printf("Tidak ada pasien rawat jalan.\n");
        return;
    }

    int kodePasien;
    printf("Masukkan nomor antrian pasien: ");
    scanf("%d", &kodePasien);

    int ditemukan = 0;
    int i;
    for (i = 0; i < jumlahAntrianRawatJalan; i++) {
        if (i + 1 == kodePasien) {
            printf("Nama: %s\n", antrianRawatJalan[i].nama);
            printf("Poli: %d\n", antrianRawatJalan[i].poli);
            printf("Sesi: %d\n", antrianRawatJalan[i].sesi);
            float hargaPelayanan;
            switch (antrianRawatJalan[i].poli) {
                case 1:
                    hargaPelayanan = 50000;
                    break;
                case 2:
                    hargaPelayanan = 75000;
                    break;
                case 3:
                    hargaPelayanan = 100000;
                    break;
                case 4:
                    hargaPelayanan = 80000;
                    break;
                case 5:
                    hargaPelayanan = 120000;
                    break;
                case 6:
                    hargaPelayanan = 90000;
                    break;
                case 7:
                    hargaPelayanan = 60000;
                    break;
                case 8:
                    hargaPelayanan = 70000;
                    break;
                case 9:
                    hargaPelayanan = 85000;
                    break;
                case 10:
                    hargaPelayanan = 95000;
                    break;
                default:
                    hargaPelayanan = 0;
                    break;
            }
            printf("Harga obat: ");
            float hargaObat;
            scanf("%f", &hargaObat);
            printf("Harga pelayanan: %.2f\n", hargaPelayanan);
            float hargaTotal = hargaObat + hargaPelayanan;
            if (antrianRawatJalan[i].asuransi == 1) {
                printf("Harga Total (dibayar oleh asuransi): Rp. %.2f\n", hargaTotal);
            } else {
                printf("Harga Total: Rp. %.2f\n", hargaTotal);
            }
            ditemukan = 1;
            hapusPasienAntrianRawatJalan(i);
            break;
        }
    }

    if (!ditemukan) {
        printf("Kode pasien tidak valid.\n");
    }
}

// Fungsi untuk mendaftarkan pasien rawat inap
void daftarRawatInap(PasienRawatInap* pasien_RawatInap) {
    printf("\n===== DAFTAR RAWAT INAP =====\n");
    printf("Nama: ");
    scanf(" %[^\n]s", pasien_RawatInap->nama);
    printf("Tanggal Lahir (dd/mm/yyyy): ");
    scanf(" %[^\n]s", pasien_RawatInap->tanggalLahir);
    printf("Alamat: ");
    scanf(" %[^\n]s", pasien_RawatInap->alamat);
    printf("Jenis Kelamin: ");
    scanf(" %[^\n]s", pasien_RawatInap->jenisKelamin);
    printf("Keluhan: ");
    scanf(" %[^\n]s", pasien_RawatInap->keluhan);
    printf("Apakah pasien memiliki asuransi?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pasien_RawatInap->asuransi);
    printf("Pilih kamar (1-5):\n");
    printf("1. VIP\n");
    printf("2. Kelas 1\n");
    printf("3. Kelas 2\n");
    printf("4. Kelas 3\n");
    printf("5. Kelas 4\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pasien_RawatInap->kamar);
    jumlahPasienRawatInap++;
    printf("Registrasi berhasil. Kode pasien: %d\n", jumlahPasienRawatInap);
    pasienRawatInap[jumlahPasienRawatInap - 1] = *pasien_RawatInap;
}

//Fungsi untuk mengambil data pasien rawat inap
void ambilDataPasien() {
    FILE *file = fopen("pasien_rawat_inap.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file pasien_rawat_inap.txt\n");
        return;
    }

    jumlahPasienRawatInap = 0;
    PasienRawatInap pasien_RawatInap;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",
                  pasien_RawatInap.nama,
                  pasien_RawatInap.tanggalLahir,
                  pasien_RawatInap.alamat,
                  pasien_RawatInap.jenisKelamin,
                  pasien_RawatInap.keluhan,
                  &pasien_RawatInap.asuransi,
                  &pasien_RawatInap.kamar) == 7) {
        pasienRawatInap[jumlahPasienRawatInap++] = pasien_RawatInap;
    }

    fclose(file);
}

//Fungsi untuk menyimpan data pasien rawat inap
void simpanDataPasien() {
    FILE *file = fopen("pasien_rawat_inap.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file pasien_rawat_inap.txt\n");
        return;
    }

    int i;
    for (i = 0; i < jumlahAntrianRawatJalan; i++) {
        fprintf(file, "%s,%s,%s,%s,%s,%d,%d\n", 
                pasienRawatInap[i].nama,
                pasienRawatInap[i].tanggalLahir,
                pasienRawatInap[i].alamat,
                pasienRawatInap[i].jenisKelamin,
                pasienRawatInap[i].keluhan,
                pasienRawatInap[i].asuransi,
                pasienRawatInap[i].kamar);
    }

    fclose(file);
}

// Fungsi untuk menampilkan daftar pasien rawat inap
void tampilkanPasienRawatInap() {
	int i;
    printf("\n===== DAFTAR PASIEN RAWAT INAP =====\n");
    if (jumlahPasienRawatInap == 0) {
        printf("Tidak ada pasien rawat inap.\n");
        return;
    }
    printf("No.  Nama\t\tKamar\n");
    for (i = 0; i < jumlahPasienRawatInap; i++) {
        printf("%d.   %s\t\t%d\n", i + 1, pasienRawatInap[i].nama, pasienRawatInap[i].kamar);
    }
}

// Fungsi untuk menghapus pasien dari daftar setelah pembayaran
void hapusPasienDaftarRawatInap(int index) {
    int i;
    for (i = index; i < jumlahPasienRawatInap - 1; i++) {
        pasienRawatInap[i] = pasienRawatInap[i + 1];
    }
    jumlahPasienRawatInap--;
}

// Fungsi untuk melakukan pembayaran pasien rawat inap
void pembayaranRawatInap() {
    printf("\n===== PEMBAYARAN RAWAT INAP =====\n");
    if (jumlahPasienRawatInap == 0) {
        printf("Tidak ada pasien rawat inap.\n");
        return;
    }

    int kodePasien;
    printf("Masukkan kode pasien: ");
    scanf("%d", &kodePasien);

    int ditemukan = 0;
    int i;
    for (i = 0; i < jumlahPasienRawatInap; i++) {
        if (i + 1 == kodePasien) {
            printf("Nama: %s\n", pasienRawatInap[i].nama);
            printf("Kamar: %d\n", pasienRawatInap[i].kamar);
            printf("Jumlah hari: ");
            int jumlahHari;
            scanf("%d", &jumlahHari);
            float hargaTotal = 0;
            switch (pasienRawatInap[i].kamar) {
                case 1:
                    hargaTotal = jumlahHari * 1000000;
                    break;
                case 2:
                    hargaTotal = jumlahHari * 500000;
                    break;
                case 3:
                    hargaTotal = jumlahHari * 300000;
                    break;
                case 4:
                    hargaTotal = jumlahHari * 200000;
                    break;
                case 5:
                    hargaTotal = jumlahHari * 100000;
                    break;
            }
            if (pasienRawatInap[i].asuransi == 1) {
                printf("Harga Total (dibayar oleh asuransi): Rp. %.2f\n", hargaTotal);
            } else {
                printf("Harga Total: Rp. %.2f\n", hargaTotal);
            }
            ditemukan = 1;
            hapusPasienDaftarRawatInap(i);
            break;
        }
    }

    if (!ditemukan) {
        printf("Kode pasien tidak valid.\n");
    }
}

int main() {
	ambilDataAntrian();
	ambilDataPasien();
	PasienRawatJalan pasien_RawatJalan;
	PasienRawatInap pasien_RawatInap;
    int isLogout = 0;
    int isLoggedIn = 0;
    while (!isLogout) {
        printf("\n===== SISTEM ADMINISTRASI RUMAH SAKIT =====\n");

        printf("LOGIN\n");
        char username[20], password[20];
        printf("Username: ");
        scanf(" %[^\n]s", username);
        printf("Password: ");
        scanf(" %[^\n]s", password);

        // Simulasi login, username dan password di-hardcode
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
           isLoggedIn = 1;
        } else {
            printf("Login gagal. Silakan coba lagi.\n");
        }

        if (isLoggedIn) {
            int pilihan;
            while (1) {
                tampilkanMenuUtama();
                pilihan = mintaInputPilihan();

                switch (pilihan) {
                    case 1: {
                        int subPilihan;
                        while (1) {
                        	printf("\n===== MENU RAWAT JALAN =====\n");
                            printf("1. Registrasi data pasien\n");
                            printf("2. Display antrian\n");
                            printf("3. Pembayaran\n");
                            printf("4. Kembali ke menu utama\n");
                            printf("Pilihan Anda: ");
                            scanf("%d", &subPilihan);

                            switch (subPilihan) {
                                case 1:
									daftarRawatJalan(&pasien_RawatJalan);
                                    break;
                                case 2:
                                    tampilkanAntrianRawatJalan();
                                    break;
                                case 3:
                                    pembayaranRawatJalan();
                                    break;
                                case 4:
                                    subPilihan = -1;
                                    break;
                                default:
                                    printf("Pilihan tidak valid.\n");
                            }

                            if (subPilihan == -1) {
                                break;
                            }
                        }
                        break;
                    }
                    case 2: {
                        int subPilihan;
                        while (1) {
                        	printf("\n===== MENU RAWAT INAP =====\n");
                            printf("1. Registrasi data pasien\n");
                            printf("2. Daftar pasien rawat inap\n");
                            printf("3. Pembayaran\n");
                            printf("4. Kembali ke menu utama\n");
                            printf("Pilihan Anda: ");
                            scanf("%d", &subPilihan);

                            switch (subPilihan) {
                                case 1:
                                    daftarRawatInap(&pasien_RawatInap);
                                    break;
                                case 2:
                                    tampilkanPasienRawatInap();
                                    break;
                                case 3:
                                    pembayaranRawatInap();
                                    break;
                                case 4:
                                    subPilihan = -1;
                                    break;
                                default:
                                    printf("Pilihan tidak valid.\n");
                            }

                            if (subPilihan == -1) {
                                break;
                            }
                        }
                        break;
                    }
                    case 3:
                        isLogout = 1;
                        simpanDataAntrian();
                        simpanDataPasien();
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                }

                if (isLogout || pilihan == 3) {
                    break;
                }
            }
        } else {
            printf("Username atau password salah. Silakan coba lagi.\n");
        }
    }

    printf("Terima kasih telah menggunakan program administrasi rumah sakit.\n");
    return 0;
}
