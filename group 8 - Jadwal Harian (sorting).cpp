#include <iostream>
#include <string>
using namespace std;

struct DataJadwal {
    int id;
    string nama;
    string tanggal;
    string jam;
    string status;
};

DataJadwal data[100];
int jumlah = 0;

void tampilData(string judul, int awal, int akhir) {
    cout << judul;
    cout << "ID      Nama Kegiatan           Tanggal        Jam       Status            \n";
    cout << "--------------------------------------------------------------------------\n";

    for (int i = awal; i <= akhir; i++) {
        cout << data[i].id;

        int angka = data[i].id;
        int digit = 1;
        while (angka >= 10) {
            digit++;
            angka = angka / 10;
        }

        for (int s = 0; s < 8 - digit; s++)
            cout << " ";

        cout << data[i].nama;
        for (int s = 0; s < 25 - (int)data[i].nama.length(); s++)
            cout << " ";

        cout << data[i].tanggal;
        for (int s = 0; s < 15 - (int)data[i].tanggal.length(); s++)
            cout << " ";

        cout << data[i].jam;
        for (int s = 0; s < 10 - (int)data[i].jam.length(); s++)
            cout << " ";

        cout << data[i].status;
        for (int s = 0; s < 18 - (int)data[i].status.length(); s++)
            cout << " ";

        cout << endl;
    }
}

void bubbleSort(int mode) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            bool tukar = false;

            if (mode == 1) {
                if (data[j].tanggal > data[j + 1].tanggal ||
                    (data[j].tanggal == data[j + 1].tanggal && data[j].jam > data[j + 1].jam)) {
                    tukar = true;
                }
            } else if (mode == 2) {
                if (data[j].id > data[j + 1].id) {
                    tukar = true;
                }
            }

            if (tukar) {
                DataJadwal temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int id) {
    bubbleSort(2);

    int kiri = 0;
    int kanan = jumlah - 1;

    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;

        if (data[tengah].id == id) {
            return tengah;
        } else if (id < data[tengah].id) {
            kanan = tengah - 1;
        } else {
            kiri = tengah + 1;
        }
    }

    return -1;
}

void tampilMenu() {
    cout << "\n=====================================\n";
    cout << "  SISTEM JADWAL KEGIATAN HARIAN\n";
    cout << "=====================================\n";
    cout << "1. Tambah Jadwal\n";
    cout << "2. Tampilkan Jadwal\n";
    cout << "3. Urutkan Jadwal\n";
    cout << "4. Cari Jadwal (Binary Search)\n";
    cout << "5. Perbarui Status Jadwal\n";
    cout << "6. Hapus Jadwal\n";
    cout << "7. Keluar\n";
    cout << "=====================================\n";
    cout << "Masukkan Pilihan : ";
}

void tambahJadwal() {
    if (jumlah >= 100) {
        cout << "\nData sudah penuh!\n";
        return;
    }

    cout << "\n===== TAMBAH JADWAL =====\n";
    cout << "ID Jadwal      : ";
    cin >> data[jumlah].id;
    cin.ignore();

    cout << "Nama Kegiatan  : ";
    getline(cin, data[jumlah].nama);

    cout << "Tanggal (YYYY/MM/DD) : ";
    getline(cin, data[jumlah].tanggal);

    cout << "Jam (HH:MM)          : ";
    getline(cin, data[jumlah].jam);

    int pilihStatus;
    cout << "\nStatus\n";
    cout << "1. Belum Selesai\n";
    cout << "2. Selesai\n";
    cout << "Pilih Status   : ";
    cin >> pilihStatus;

    if (pilihStatus == 1)
        data[jumlah].status = "Belum Selesai";
    else if (pilihStatus == 2)
        data[jumlah].status = "Selesai";
    else
        data[jumlah].status = "Tidak Diketahui";

    jumlah++;
    cout << "\nData berhasil ditambahkan.\n";
}

void tampilJadwal() {
    if (jumlah == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }

    tampilData("\n============================== DAFTAR JADWAL ==============================\n", 0, jumlah - 1);
}

void urutkanJadwal() {
    if (jumlah == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }

    bubbleSort(1);
    cout << "\nJadwal berhasil diurutkan berdasarkan tanggal dan jam.\n";
    tampilData("\n============================== DAFTAR JADWAL ==============================\n", 0, jumlah - 1);
}

void cariJadwal() {
    if (jumlah == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }

    int idCari;
    cout << "\n===== CARI JADWAL (BINARY SEARCH) =====\n";
    cout << "Masukkan ID Jadwal : ";
    cin >> idCari;

    int ditemukan = binarySearch(idCari);

    if (ditemukan == -1) {
        cout << "\nData jadwal tidak ditemukan.\n";
        return;
    }

    tampilData("\n=========================== DATA JADWAL DITEMUKAN =========================\n", ditemukan, ditemukan);
}

void updateStatus() {
    if (jumlah == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }

    int idUpdate;
    cout << "\nMasukkan ID Jadwal : ";
    cin >> idUpdate;

    int ditemukan = binarySearch(idUpdate);

    if (ditemukan == -1) {
        cout << "\nID Jadwal tidak ditemukan.\n";
        return;
    }

    int pilih;
    cout << "\nStatus Saat Ini : " << data[ditemukan].status << endl;
    cout << "1. Belum Selesai\n";
    cout << "2. Selesai\n";
    cout << "Pilih Status Baru : ";
    cin >> pilih;

    if (pilih == 1)
        data[ditemukan].status = "Belum Selesai";
    else if (pilih == 2)
        data[ditemukan].status = "Selesai";
    else {
        cout << "\nPilihan tidak valid.\n";
        return;
    }

    cout << "\nStatus berhasil diperbarui.\n";
    tampilData("\n=========================== DATA JADWAL DITEMUKAN =========================\n", ditemukan, ditemukan);
}

void hapusJadwal() {
    if (jumlah == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }

    int idHapus;
    cout << "\nMasukkan ID Jadwal yang akan dihapus : ";
    cin >> idHapus;

    int ditemukan = binarySearch(idHapus);

    if (ditemukan == -1) {
        cout << "\nID Jadwal tidak ditemukan.\n";
        return;
    }

    for (int i = ditemukan; i < jumlah - 1; i++) {
        data[i] = data[i + 1];
    }

    jumlah--;
    cout << "\nData berhasil dihapus.\n";
    cout << "\nSilakan pilih menu 2 (Tampilkan Jadwal) untuk melihat data terbaru.\n";
}

int main() {
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahJadwal();
            break;

        case 2:
            tampilJadwal();
            break;

        case 3:
            urutkanJadwal();
            break;

        case 4:
            cariJadwal();
            break;

        case 5:
            updateStatus();
            break;

        case 6:
            hapusJadwal();
            break;

        case 7:
            cout << "\nTerima kasih telah menggunakan program.\n";
            break;

        default:
            cout << "\nPilihan tidak valid!\n";
        }
    } while (pilihan != 7);

    return 0;
}
