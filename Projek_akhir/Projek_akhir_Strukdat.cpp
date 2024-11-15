#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm>

class Product {
public:
    int id;
    std::string name;
    double price;
    int stock;
    std::shared_ptr<Product> next;

    Product(int id = 0, const std::string& name = "", double price = 0.0, int stock = 0)
        : id(id), name(name), price(price), stock(stock), next(nullptr) {}
};

class User {
public:
    std::string username;
    std::string password;
    bool isAdmin;

    User(const std::string& username = "", const std::string& password = "", bool isAdmin = false)
        : username(username), password(password), isAdmin(isAdmin) {}
};

class InventorySystem {
private:
    std::shared_ptr<Product> products;
    std::shared_ptr<Product> stackTop;
    std::shared_ptr<Product> queueFront;
    std::shared_ptr<Product> queueRear;
    std::vector<User> users;
    User currentUser;

    // Utility function to clear input buffer
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Validate numeric input
    template<typename T>
    T getValidInput(const std::string& prompt, T min_value) {
        T value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value && value >= min_value) {
                break;
            }
            std::cout << "Input tidak valid. Silakan coba lagi.\n";
            clearInputBuffer();
        }
        return value;
    }

public:
    InventorySystem() {
        // Add default admin user
        users.emplace_back("admin", "admin", true);
    }

    void displayProducts() const {
        if (!products) {
            std::cout << "Tidak ada produk tersedia.\n";
            return;
        }

        std::cout << "\nDaftar Produk:\n";
        std::cout << std::string(50, '-') << "\n";
        std::cout << "ID\tNama\t\tHarga\tStok\n";
        std::cout << std::string(50, '-') << "\n";

        auto current = products;
        while (current) {
            std::cout << current->id << "\t"
                      << current->name << "\t\t"
                      << current->price << "\t"
                      << current->stock << "\n";
            current = current->next;
        }
        std::cout << std::string(50, '-') << "\n";
    }

    void addProduct() {
        auto newProduct = std::make_shared<Product>();

        newProduct->id = getValidInput<int>("Masukkan ID Produk: ", 1);
        
        // Check for duplicate ID
        if (findProduct(newProduct->id)) {
            std::cout << "ID Produk sudah ada. Silakan gunakan ID lain.\n";
            return;
        }

        clearInputBuffer();
        std::cout << "Masukkan Nama Produk: ";
        std::getline(std::cin, newProduct->name);

        newProduct->price = getValidInput<double>("Masukkan Harga Produk: ", 0.0);
        newProduct->stock = getValidInput<int>("Masukkan Stok Produk: ", 1);

        // Add to front of list
        newProduct->next = products;
        products = newProduct;

        std::cout << "Produk berhasil ditambahkan.\n";
    }

    std::shared_ptr<Product> findProduct(int id) const {
        auto current = products;
        while (current) {
            if (current->id == id) {
                return std::make_shared<Product>(*current);
            }
            current = current->next;
        }
        return nullptr;
    }

    // Stack operations
    void displayStack() const {
        if (!stackTop) {
            std::cout << "Stack kosong.\n";
            return;
        }

        std::cout << "\nProduk dalam Stack:\n";
        std::cout << std::string(50, '-') << "\n";
        auto current = stackTop;
        while (current) {
            std::cout << "ID: " << current->id << ", Nama: " << current->name
                      << ", Harga: " << current->price << ", Stok: " << current->stock << "\n";
            current = current->next;
        }
        std::cout << std::string(50, '-') << "\n";
    }

    void pushToStack(int id) {
        auto product = findProduct(id);
        if (product) {
            product->next = stackTop;
            stackTop = product;
            std::cout << "Produk berhasil ditambahkan ke Stack.\n";
        } else {
            std::cout << "Produk dengan ID " << id << " tidak ditemukan.\n";
        }
    }

    void popFromStack() {
        if (!stackTop) {
            std::cout << "Stack kosong.\n";
            return;
        }
        stackTop = stackTop->next;
        std::cout << "Produk berhasil dihapus dari Stack.\n";
    }

    // Queue operations
    void displayQueue() const {
        if (!queueFront) {
            std::cout << "Queue kosong.\n";
            return;
        }

        std::cout << "\nProduk dalam Queue:\n";
        std::cout << std::string(50, '-') << "\n";
        auto current = queueFront;
        while (current) {
            std::cout << "ID: " << current->id << ", Nama: " << current->name
                      << ", Harga: " << current->price << ", Stok: " << current->stock << "\n";
            current = current->next;
        }
        std::cout << std::string(50, '-') << "\n";
    }

    void enqueue(int id) {
        auto product = findProduct(id);
        if (!product) {
            std::cout << "Produk dengan ID " << id << " tidak ditemukan.\n";
            return;
        }

        product->next = nullptr;
        if (!queueRear) {
            queueFront = queueRear = product;
        } else {
            queueRear->next = product;
            queueRear = product;
        }
        std::cout << "Produk berhasil ditambahkan ke Queue.\n";
    }

    void dequeue() {
        if (!queueFront) {
            std::cout << "Queue kosong.\n";
            return;
        }
        queueFront = queueFront->next;
        if (!queueFront) queueRear = nullptr;
        std::cout << "Produk berhasil dihapus dari Queue.\n";
    }

    // User management
    bool login(const std::string& username, const std::string& password) {
        auto it = std::find_if(users.begin(), users.end(),
            [&](const User& user) {
                return user.username == username && user.password == password;
            });

        if (it != users.end()) {
            currentUser = *it;
            return true;
        }
        return false;
    }

    void registerUser(const std::string& username, const std::string& password) {
        // Check if username already exists
        if (std::any_of(users.begin(), users.end(),
            [&](const User& user) { return user.username == username; })) {
            std::cout << "Username sudah digunakan. Silakan pilih username lain.\n";
            return;
        }

        users.emplace_back(username, password, false);
        std::cout << "Registrasi berhasil. Silakan login.\n";
    }

    bool isCurrentUserAdmin() const {
        return currentUser.isAdmin;
    }

    void logout() {
        currentUser = User();
    }
};

int main() {
    InventorySystem system;
    std::string username, password;
    int choice;

    while (true) {
        std::cout << "\n=== Sistem Manajemen Inventori ===\n";
        std::cout << "1. Login\n2. Register\n3. Exit\n";
        std::cout << "Pilihan Anda: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input tidak valid. Silakan coba lagi.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::cout << "Username: ";
                std::cin >> username;
                std::cout << "Password: ";
                std::cin >> password;

                if (system.login(username, password)) {
                    std::cout << "Login berhasil sebagai " 
                              << (system.isCurrentUserAdmin() ? "Admin" : "Guest") << ".\n";

                    while (true) {
                        if (system.isCurrentUserAdmin()) {
                            std::cout << "\n=== Menu Admin ===\n"
                                      << "1. Tampilkan Produk\n"
                                      << "2. Tambah Produk\n"
                                      << "3. Push ke Stack\n"
                                      << "4. Pop dari Stack\n"
                                      << "5. Enqueue ke Queue\n"
                                      << "6. Dequeue dari Queue\n"
                                      << "7. Tampilkan Stack\n"
                                      << "8. Tampilkan Queue\n"
                                      << "9. Logout\n"
                                      << "Pilihan Anda: ";
                        } else {
                            std::cout << "\n=== Menu Guest ===\n"
                                      << "1. Tampilkan Produk\n"
                                      << "2. Logout\n"
                                      << "Pilihan Anda: ";
                        }

                        if (!(std::cin >> choice)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Input tidak valid. Silakan coba lagi.\n";
                            continue;
                        }

                        if (system.isCurrentUserAdmin()) {
                            switch (choice) {
                                case 1: system.displayProducts(); break;
                                case 2: system.addProduct(); break;
                                case 3: {
                                    int id;
                                    std::cout << "Masukkan ID Produk: ";
                                    std::cin >> id;
                                    system.pushToStack(id);
                                    break;
                                }
                                case 4: system.popFromStack(); break;
                                case 5: {
                                    int id;
                                    std::cout << "Masukkan ID Produk: ";
                                    std::cin >> id;
                                    system.enqueue(id);
                                    break;
                                }
                                case 6: system.dequeue(); break;
                                case 7: system.displayStack(); break;
                                case 8: system.displayQueue(); break;
                                case 9: {
                                    system.logout();
                                    std::cout << "Logout berhasil.\n";
                                    goto main_menu;
                                }
                                default: std::cout << "Pilihan tidak valid.\n";
                            }
                        } else {
                            switch (choice) {
                                case 1: system.displayProducts(); break;
                                case 2: {
                                    system.logout();
                                    std::cout << "Logout berhasil.\n";
                                    goto main_menu;
                                }
                                default: std::cout << "Pilihan tidak valid.\n";
                            }
                        }
                    }
                } else {
                    std::cout << "Username atau password salah.\n";
                }
                break;
            }
            case 2: {
                std::cout << "Username baru: ";
                std::cin >> username;
                std::cout << "Password: ";
                std::cin >> password;
                system.registerUser(username, password);
                break;
            }
            case 3: {
                std::cout << "Terima kasih telah menggunakan sistem ini.\n";
                return 0;
            }
            default: {
                std::cout << "Pilihan tidak valid.\n";
            }
        }
        main_menu:;
    }
}