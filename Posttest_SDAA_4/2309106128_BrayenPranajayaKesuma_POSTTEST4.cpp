#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Struktur Proyek
struct Proyek {
    int idProyek;
    string namaProyek;
    string klien;
    float biaya;
};

// Node untuk Linked List, Stack, dan Queue
struct Node {
    Proyek data;
    Node* next;
};

// Inisialisasi pointer untuk Linked List, Stack, dan Queue
Node* head = nullptr;        // Linked List
Node* stackTop = nullptr;    // Stack
Node* queueFront = nullptr;  // Queue (depan)
Node* queueRear = nullptr;   // Queue (belakang)

// Fungsi untuk menambahkan proyek ke Linked List
void tambahProyek(Node*& head) {
    Node* newNode = new Node;

    cout << "Masukkan ID proyek: ";
    cin >> newNode->data.idProyek;
    cout << "Masukkan nama proyek: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan newline
    getline(cin, newNode->data.namaProyek);
    cout << "Masukkan nama klien: ";
    getline(cin, newNode->data.klien);
    cout << "Masukkan biaya proyek: ";
    cin >> newNode->data.biaya;

    newNode->next = head;
    head = newNode;
}

// Fungsi untuk menampilkan isi Linked List
void tampilkanLinkedList() {
    Node* current = head;
    cout << "\nDaftar Proyek (Linked List):\n";
    while (current != nullptr) {
        cout << "ID: " << current->data.idProyek
             << ", Nama Proyek: " << current->data.namaProyek
             << ", Klien: " << current->data.klien
             << ", Biaya: Rp " << current->data.biaya << endl;
        current = current->next;
    }
}

// Fungsi untuk menampilkan isi Stack
void tampilkanStack() {
    if (stackTop == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }

    Node* current = stackTop;
    cout << "Isi Stack:\n";
    while (current != nullptr) {
        cout << "ID: " << current->data.idProyek
             << ", Nama Proyek: " << current->data.namaProyek
             << ", Klien: " << current->data.klien
             << ", Biaya: Rp " << current->data.biaya << endl;
        current = current->next;
    }
}

// Fungsi untuk menampilkan isi Queue
void tampilkanQueue() {
    if (queueFront == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }

    Node* current = queueFront;
    cout << "Isi Queue:\n";
    while (current != nullptr) {
        cout << "ID: " << current->data.idProyek
             << ", Nama Proyek: " << current->data.namaProyek
             << ", Klien: " << current->data.klien
             << ", Biaya: Rp " << current->data.biaya << endl;
        current = current->next;
    }
}

// Fungsi Push untuk menambahkan proyek ke Stack
void pushStack(Proyek data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = stackTop;
    stackTop = newNode;
    cout << "Proyek berhasil ditambahkan ke stack.\n";
}

// Fungsi Pop untuk menghapus proyek dari Stack
void popStack() {
    if (stackTop == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Node* temp = stackTop;
    stackTop = stackTop->next;
    delete temp;
    cout << "Proyek berhasil dihapus dari stack.\n";
}

// Fungsi Enqueue untuk menambahkan proyek ke Queue
void enqueue(Proyek data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    if (queueRear == nullptr) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }
    cout << "Proyek berhasil ditambahkan ke queue.\n";
}

// Fungsi Dequeue untuk menghapus proyek dari Queue
void dequeue() {
    if (queueFront == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    Node* temp = queueFront;
    queueFront = queueFront->next;
    if (queueFront == nullptr) {
        queueRear = nullptr;
    }
    delete temp;
    cout << "Proyek berhasil dihapus dari queue.\n";
}

int main() {
    int pilihan;
    Proyek proyekBaru;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Proyek (Linked List)\n";
        cout << "2. Tampilkan Proyek (Linked List)\n";  // Tampilkan Linked List
        cout << "3. Tampilkan Isi Stack dan Queue\n";  // Gabungan
        cout << "4. Menambahkan Proyek (Push ke Stack)\n";
        cout << "5. Menghapus Proyek (Pop dari Stack)\n";
        cout << "6. Menambahkan Proyek (Enqueue ke Queue)\n";
        cout << "7. Menghapus Proyek (Dequeue dari Queue)\n";
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        // Penanganan input invalid
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            pilihan = 0; // Set pilihan invalid
        }

        switch (pilihan) {
            case 1:
                tambahProyek(head);  // Tambah proyek ke Linked List
                break;
            case 2:
                tampilkanLinkedList();  // Tampilkan proyek dari Linked List
                break;
            case 3:
                tampilkanStack();  // Tampilkan isi Stack
                tampilkanQueue();  // Tampilkan isi Queue
                break;
            case 4:
                // Input proyek untuk Stack
                cout << "Masukkan ID proyek: ";
                cin >> proyekBaru.idProyek;
                cout << "Masukkan nama proyek: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan newline
                getline(cin, proyekBaru.namaProyek);
                cout << "Masukkan nama klien: ";
                getline(cin, proyekBaru.klien);
                cout << "Masukkan biaya proyek: ";
                cin >> proyekBaru.biaya;
                pushStack(proyekBaru);  // Push proyek ke Stack
                break;
            case 5:
                popStack();  // Pop proyek dari Stack
                break;
            case 6:
                // Input proyek untuk Queue
                cout << "Masukkan ID proyek: ";
                cin >> proyekBaru.idProyek;
                cout << "Masukkan nama proyek: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan newline.
                getline(cin, proyekBaru.namaProyek);
                cout << "Masukkan nama klien: ";
                getline(cin, proyekBaru.klien);
                cout << "Masukkan biaya proyek: ";
                cin >> proyekBaru.biaya;
                enqueue(proyekBaru);  // Enqueue proyek ke Queue
                break;
            case 7:
                dequeue();  // Dequeue proyek dari Queue
                break;
            case 8:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 8);

    return 0;
}
