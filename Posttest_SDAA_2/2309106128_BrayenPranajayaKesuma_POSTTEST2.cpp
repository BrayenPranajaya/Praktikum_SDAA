#include <iostream>
#include <string>

using namespace std;


struct Proyek {
    int idProyek;
    string namaProyek;
    string klien;
    float biaya;
};


void tampilkanProyek(Proyek* daftarProyek, int jumlahProyek) {
    cout << "\nDaftar Proyek Freelance:" << endl;
    for (int i = 0; i < jumlahProyek; i++) {
        cout << "ID: " << daftarProyek[i].idProyek 
             << ", Nama Proyek: " << daftarProyek[i].namaProyek 
             << ", Klien: " << daftarProyek[i].klien 
             << ", Biaya: Rp " << daftarProyek[i].biaya << endl;
    }
}


void tambahProyek(Proyek* daftarProyek, int* jumlahProyek) {
    cout << "Masukkan ID proyek: ";
    cin >> daftarProyek[*jumlahProyek].idProyek;
    cout << "Masukkan nama proyek: ";
    cin.ignore();
    getline(cin, daftarProyek[*jumlahProyek].namaProyek);
    cout << "Masukkan nama klien: ";
    getline(cin, daftarProyek[*jumlahProyek].klien);
    cout << "Masukkan biaya proyek: ";
    cin >> daftarProyek[*jumlahProyek].biaya;
    (*jumlahProyek)++;
}


void editProyek(Proyek* daftarProyek, int jumlahProyek) {
    int id;
    cout << "Masukkan ID proyek yang akan diedit: ";
    cin >> id;
    
    for (int i = 0; i < jumlahProyek; i++) {
        if (daftarProyek[i].idProyek == id) {
            cout << "Masukkan nama proyek baru: ";
            cin.ignore();
            getline(cin, daftarProyek[i].namaProyek);
            cout << "Masukkan nama klien baru: ";
            getline(cin, daftarProyek[i].klien);
            cout << "Masukkan biaya proyek baru: ";
            cin >> daftarProyek[i].biaya;
            cout << "Proyek berhasil diedit!" << endl;
            return;
        }
    }
    cout << "Proyek dengan ID " << id << " tidak ditemukan." << endl;
}

void hapusProyek(Proyek* daftarProyek, int* jumlahProyek) {
    int id;
    cout << "Masukkan ID proyek yang akan dihapus: ";
    cin >> id;
    
    for (int i = 0; i < *jumlahProyek; i++) {
        if (daftarProyek[i].idProyek == id) {
            for (int j = i; j < *jumlahProyek - 1; j++) {
                daftarProyek[j] = daftarProyek[j + 1];
            }
            (*jumlahProyek)--;
            cout << "Proyek berhasil dihapus!" << endl;
            return;
        }
    }
    cout << "Proyek dengan ID " << id << " tidak ditemukan." << endl;
}

int main() {
    int pilihan;
    int jumlahProyek = 0;
    Proyek daftarProyek[30];  

    do {
        cout << "\n=== Manajemen Proyek Freelance ===" << endl;
        cout << "1. Tambah Proyek" << endl;
        cout << "2. Tampilkan Semua Proyek" << endl;
        cout << "3. Edit Proyek" << endl;
        cout << "4. Hapus Proyek" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahProyek(daftarProyek, &jumlahProyek);
                break;
            case 2:
                tampilkanProyek(daftarProyek, jumlahProyek);
                break;
            case 3:
                editProyek(daftarProyek, jumlahProyek);
                break;
            case 4:
                hapusProyek(daftarProyek, &jumlahProyek);
                break;
            case 5:
                cout << "Terima kasih, program selesai!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
