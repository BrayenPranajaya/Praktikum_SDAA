#include <iostream>
#include <string>

using namespace std;

struct Proyek {
    int idProyek;
    string namaProyek;
    string klien;
    float biaya;
};

struct Node {
    Proyek data;
    Node* next;
};

Node* head = nullptr;

void tambahProyek(Node*& head) {
    Node* newNode = new Node;
    
    cout << "Masukkan ID proyek: ";
    cin >> newNode->data.idProyek;
    cout << "Masukkan nama proyek: ";
    cin.ignore();
    getline(cin, newNode->data.namaProyek);
    cout << "Masukkan nama klien: ";
    getline(cin, newNode->data.klien);
    cout << "Masukkan biaya proyek: ";
    cin >> newNode->data.biaya;
    
    newNode->next = head;
    head = newNode;
}

void tampilkanProyek(Node* head) {
    Node* current = head;
    cout << "\nDaftar Proyek Freelance:" << endl;
    while (current != nullptr) {
        cout << "ID: " << current->data.idProyek
             << ", Nama Proyek: " << current->data.namaProyek
             << ", Klien: " << current->data.klien
             << ", Biaya: Rp " << current->data.biaya << endl;
        current = current->next;
    }
}

void hapusProyek(Node*& head, int idProyek) {
    Node* current = head;
    Node* prev = nullptr;
    
    if (current != nullptr && current->data.idProyek == idProyek) {
        head = current->next;
        delete current;
        cout << "Proyek dengan ID " << idProyek << " berhasil dihapus.\n";
        return;
    }
    
    while (current != nullptr && current->data.idProyek != idProyek) {
        prev = current;
        current = current->next;
    }
    
    if (current == nullptr) {
        cout << "Proyek dengan ID " << idProyek << " tidak ditemukan.\n";
        return;
    }
    
    prev->next = current->next;
    delete current;
    cout << "Proyek dengan ID " << idProyek << " berhasil dihapus.\n";
}

int main() {
    int pilihan, idProyek;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Proyek\n";
        cout << "2. Tampilkan Proyek\n";
        cout << "3. Hapus Proyek\n";
        cout << "4. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahProyek(head);
                break;
            case 2:
                tampilkanProyek(head);
                break;
            case 3:
                cout << "Masukkan ID proyek yang ingin dihapus: ";
                cin >> idProyek;
                hapusProyek(head, idProyek);
                break;
            case 4:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 4);

    return 0;
}
