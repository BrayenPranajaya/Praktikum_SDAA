#include <iostream>
#include <string>
#include <limits>

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
Node* stackTop = nullptr;
Node* queueFront = nullptr;
Node* queueRear = nullptr;

void tambahProyek(Node*& head) {
    Node* newNode = new Node;

    cout << "Masukkan ID proyek: ";
    cin >> newNode->data.idProyek;
    cout << "Masukkan nama proyek: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newNode->data.namaProyek);
    cout << "Masukkan nama klien: ";
    getline(cin, newNode->data.klien);
    cout << "Masukkan biaya proyek: ";
    cin >> newNode->data.biaya;

    newNode->next = head;
    head = newNode;
}

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

void updateProyek(Node*& head) {
    int id;
    cout << "Masukkan ID proyek yang ingin diperbarui: ";
    cin >> id;

    Node* current = head;
    while (current != nullptr) {
        if (current->data.idProyek == id) {
            cout << "Masukkan nama proyek baru: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, current->data.namaProyek);
            cout << "Masukkan nama klien baru: ";
            getline(cin, current->data.klien);
            cout << "Masukkan biaya proyek baru: ";
            cin >> current->data.biaya;
            cout << "Proyek berhasil diperbarui.\n";
            return;
        }
        current = current->next;
    }
    cout << "Proyek dengan ID " << id << " tidak ditemukan.\n";
}

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

void pushStack(Proyek data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = stackTop;
    stackTop = newNode;
    cout << "Proyek berhasil ditambahkan ke stack.\n";
}

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

void merge(Node* first, Node* second, Node*& merged) {
    if (first == nullptr) {
        merged = second;
        return;
    }
    if (second == nullptr) {
        merged = first;
        return;
    }

    if (first->data.biaya <= second->data.biaya) {
        merged = first;
        merge(first->next, second, merged->next);
    } else {
        merged = second;
        merge(first, second->next, merged->next);
    }
}

void mergeSort(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* first;
    Node* second;
    Node* middle = head;
    Node* fast = head->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            middle = middle->next;
            fast = fast->next;
        }
    }

    first = head;
    second = middle->next;
    middle->next = nullptr;

    mergeSort(first);
    mergeSort(second);

    merge(first, second, head);
}

Node* partition(Node* low, Node* high) {
    Proyek pivot = high->data;
    Node* i = low->next;

    for (Node* j = low->next; j != high; j = j->next) {
        if (j->data.biaya >= pivot.biaya) {
            swap(i->data, j->data);
            i = i->next;
        }
    }
    swap(i->data, high->data);
    return i;
}

void quickSort(Node* low, Node* high) {
    if (low != nullptr && low != high && low != high->next) {
        Node* pivot = partition(low, high);
        quickSort(low, pivot->next);
        quickSort(pivot->next, high);
    }
}

Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

void urutkanProyek() {
    cout << "\nMengurutkan proyek berdasarkan biaya (Ascending):\n";
    mergeSort(head);
    tampilkanLinkedList();

    cout << "\nMengurutkan proyek berdasarkan biaya (Descending):\n";
    Node* tail = getTail(head);
    quickSort(head, tail);
    tampilkanLinkedList();
}

int main() {
    int pilihan;
    Proyek proyekBaru;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Proyek (Linked List)\n";
        cout << "2. Tampilkan Proyek (Linked List)\n";
        cout << "3. Update Proyek\n";
        cout << "4. Tampilkan Isi Stack dan Queue\n";
        cout << "5. Menambahkan Proyek (Push ke Stack)\n";
        cout << "6. Menghapus Proyek (Pop dari Stack)\n";
        cout << "7. Menambahkan Proyek (Enqueue ke Queue)\n";
        cout << "8. Menghapus Proyek (Dequeue dari Queue)\n";
        cout << "9. Urutkan Proyek\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahProyek(head);
                break;
            case 2:
                tampilkanLinkedList();
                break;
            case 3:
                updateProyek(head);
                break;
            case 4:
                tampilkanStack();
                tampilkanQueue();
                break;
            case 5:
                if (head != nullptr) {
                    pushStack(head->data);
                } else {
                    cout << "Tidak ada proyek untuk ditambahkan ke stack.\n";
                }
                break;
            case 6:
                popStack();
                break;
            case 7:
                if (head != nullptr) {
                    enqueue(head->data);
                } else {
                    cout << "Tidak ada proyek untuk ditambahkan ke queue.\n";
                }
                break;
            case 8:
                dequeue();
                break;
            case 9:
                urutkanProyek();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    while (stackTop != nullptr) {
        Node* temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
    }
    while (queueFront != nullptr) {
        Node* temp = queueFront;
        queueFront = queueFront->next;
        delete temp;
    }

    return 0;
}
