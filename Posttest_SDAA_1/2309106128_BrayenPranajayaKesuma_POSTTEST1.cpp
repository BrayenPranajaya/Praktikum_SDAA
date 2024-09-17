#include <iostream>
using namespace std;

int hitungSegitigaPascal(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    } else {
        return hitungSegitigaPascal(baris - 1, kolom - 1) + hitungSegitigaPascal(baris - 1, kolom);
    }
}

void cetakSegitigaPascalSikuSiku(int tingkat) {
    for (int baris = 0; baris < tingkat; baris++) {
        for (int kolom = 0; kolom <= baris; kolom++) {
            cout << hitungSegitigaPascal(baris, kolom) << " ";
        }
        cout << endl;
    }
}

int main() {
    int tingkat = 3; 
    
    cetakSegitigaPascalSikuSiku(tingkat);

    return 0;
}
