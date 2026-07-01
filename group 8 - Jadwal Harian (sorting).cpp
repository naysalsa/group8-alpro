#include <iostream>
#include <iomanip>
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
    int jumlah=0;

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

	void updateStatus() {
    if (jumlah == 0) {
        cout << "\nData masih kosong.\n";
        return;
    }

    int id;
    cout << "\nMasukkan ID Jadwal : ";
    cin >> id;

    for (int i = 0; i < jumlah; i++) {

        if (data[i].id == id) {

            int pilih;

            cout << "\nStatus Saat Ini : " << data[i].status << endl;
            cout << "1. Belum Selesai\n";
            cout << "2. Selesai\n";
            cout << "Pilih Status Baru : ";
            cin >> pilih;

            if (pilih == 1)
                data[i].status = "Belum Selesai";
            else if (pilih == 2)
                data[i].status = "Selesai";
            else {
                cout << "\nPilihan tidak valid.\n";
                return;
            }

            cout << "\nStatus berhasil diperbarui.\n";
            cout << "\nSilakan pilih menu 2 (Tampilkan Jadwal) untuk melihat status terbaru.\n";
            return;
        }
    }

    cout << "\nID Jadwal tidak ditemukan.\n";
	}
	
    void hapusJadwal() {
        if (jumlah == 0) {
            cout << "\nData masih kosong.\n";
            return;
        }

        int id;
        cout << "\nMasukkan ID Jadwal yang akan dihapus : ";
        cin >> id;

        int ditemukan = -1;

        for (int i = 0; i < jumlah; i++) {

            if (data[i].id == id) {
                ditemukan = i;
                break;
            }

        }

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
            cout << "4. Perbarui Status Jadwal\n";
            cout << "5. Hapus Jadwal\n";
            cout << "6. Keluar\n";
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
            	j.updateStatus();
                break;

			case 5:
				j.hapusJadwal();
				break;
				
            case 6:
                cout << "\nTerima kasih telah menggunakan program.\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
            }

        } while (pilihan != 6);

    return 0;
}