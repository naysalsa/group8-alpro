#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Jadwal {
private:
    struct DataJadwal {
        int id;
        string nama;
        string tanggal;
        string jam;
        string status;
    };

    DataJadwal data[100];
    int jumlah = 0;

    int cariIndexById(int id) {
        for (int i = 0; i < jumlah; i++) {
            if (data[i].id == id) {
                return i;
            }
        }

        return -1;
    }

    string ubahKeHurufKecil(string teks) {
        int panjang = teks.length();

        for (int i = 0; i < panjang; i++) {
            if (teks[i] >= 'A' && teks[i] <= 'Z') {
                teks[i] = teks[i] + 32;
            }
        }

        return teks;
    }

    void tampilSatuJadwal(int index) {
        cout << "\n=========================== DATA JADWAL DITEMUKAN =========================\n";
        cout << left
             << setw(8) << "ID"
             << setw(25) << "Nama Kegiatan"
             << setw(15) << "Tanggal"
             << setw(10) << "Jam"
             << setw(18) << "Status" << endl;
        cout << "--------------------------------------------------------------------------\n";
        cout << left
             << setw(8) << data[index].id
             << setw(25) << data[index].nama
             << setw(15) << data[index].tanggal
             << setw(10) << data[index].jam
             << setw(18) << data[index].status << endl;
    }

public:
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

        cout << "\n============================== DAFTAR JADWAL ==============================\n";

        cout << left
             << setw(8) << "ID"
             << setw(25) << "Nama Kegiatan"
             << setw(15) << "Tanggal"
             << setw(10) << "Jam"
             << setw(18) << "Status" << endl;

        cout << "--------------------------------------------------------------------------\n";

        for (int i = 0; i < jumlah; i++) {
            cout << left
                 << setw(8) << data[i].id
                 << setw(25) << data[i].nama
                 << setw(15) << data[i].tanggal
                 << setw(10) << data[i].jam
                 << setw(18) << data[i].status << endl;
        }
    }

    void urutkanJadwal() {
        if (jumlah == 0) {
            cout << "\nData masih kosong.\n";
            return;
        }

        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - i - 1; j++) {

                bool tukar = false;

                if (data[j].tanggal > data[j + 1].tanggal) {
                    tukar = true;
                }

                else if (data[j].tanggal == data[j + 1].tanggal &&
                         data[j].jam > data[j + 1].jam) {
                    tukar = true;
                }

                if (tukar) {
                    DataJadwal temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }

        cout << "\nJadwal berhasil diurutkan berdasarkan tanggal dan jam.\n";
        tampilJadwal();
    }

    void cariJadwalLinear() {
        if (jumlah == 0) {
            cout << "\nData masih kosong.\n";
            return;
        }

        string kataKunci;
        bool adaData = false;

        cout << "\n===== CARI JADWAL (LINEAR SEARCH) =====\n";
        cout << "Masukkan kata kunci (ID/Nama/Tanggal/Jam/Status) : ";
        cin.ignore();
        getline(cin, kataKunci);

        if (kataKunci == "") {
            cout << "\nKata kunci tidak boleh kosong.\n";
            return;
        }

        kataKunci = ubahKeHurufKecil(kataKunci);

        cout << "\n=========================== HASIL PENCARIAN ===============================\n";
        cout << left
             << setw(8) << "ID"
             << setw(25) << "Nama Kegiatan"
             << setw(15) << "Tanggal"
             << setw(10) << "Jam"
             << setw(18) << "Status" << endl;
        cout << "--------------------------------------------------------------------------\n";

        for (int i = 0; i < jumlah; i++) {
            string id = to_string(data[i].id);
            string nama = ubahKeHurufKecil(data[i].nama);
            string tanggal = ubahKeHurufKecil(data[i].tanggal);
            string jam = ubahKeHurufKecil(data[i].jam);
            string status = ubahKeHurufKecil(data[i].status);

            bool cocok = false;

            if (id.find(kataKunci) != string::npos)
                cocok = true;
            else if (nama.find(kataKunci) != string::npos)
                cocok = true;
            else if (tanggal.find(kataKunci) != string::npos)
                cocok = true;
            else if (jam.find(kataKunci) != string::npos)
                cocok = true;
            else if (kataKunci == "selesai" && status == "selesai")
                cocok = true;
            else if (kataKunci != "selesai" && status.find(kataKunci) != string::npos)
                cocok = true;

            if (cocok) {
                cout << left
                     << setw(8) << data[i].id
                     << setw(25) << data[i].nama
                     << setw(15) << data[i].tanggal
                     << setw(10) << data[i].jam
                     << setw(18) << data[i].status << endl;
                adaData = true;
            }
        }

        if (!adaData) {
            cout << "\nData jadwal tidak ditemukan.\n";
        }
    }

    void updateStatus() {
        if (jumlah == 0) {
            cout << "\nData masih kosong.\n";
            return;
        }

        int id;
        cout << "\nMasukkan ID Jadwal : ";
        cin >> id;

        int ditemukan = cariIndexById(id);

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
        tampilSatuJadwal(ditemukan);
    }

    void hapusJadwal() {
        if (jumlah == 0) {
            cout << "\nData masih kosong.\n";
            return;
        }

        int id;
        cout << "\nMasukkan ID Jadwal yang akan dihapus : ";
        cin >> id;

        int ditemukan = cariIndexById(id);

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
};

int main() {
    Jadwal j;

    int pilihan;

        do {

            cout << "\n=====================================\n";
            cout << "  SISTEM JADWAL KEGIATAN HARIAN\n";
            cout << "=====================================\n";
            cout << "1. Tambah Jadwal\n";
            cout << "2. Tampilkan Jadwal\n";
            cout << "3. Urutkan Jadwal\n";
            cout << "4. Cari Jadwal (Linear Search)\n";
            cout << "5. Perbarui Status Jadwal\n";
            cout << "6. Hapus Jadwal\n";
            cout << "7. Keluar\n";
            cout << "=====================================\n";
            cout << "Masukkan Pilihan : ";
            cin >> pilihan;

            switch (pilihan) {

            case 1:
                j.tambahJadwal();
                break;

            case 2:
                j.tampilJadwal();
                break;

            case 3:
                j.urutkanJadwal();
                break;

            case 4:
                j.cariJadwalLinear();
                break;

            case 5:
                j.updateStatus();
                break;

            case 6:
                j.hapusJadwal();
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
