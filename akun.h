#ifndef AKUN_H
#define AKUN_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum Role {
    ADMIN = 1,
    SISWA = 2,
    PENGAJAR = 3,
    INVALID_ROLE = 4
};

struct AkunNode {
    string username;
    string password;
    Role role;
    AkunNode* next;
};

class Akun {
private:
    AkunNode* head;
public:
    Akun();
    ~Akun();
    void loadFromFile();
    void appendNode(const string& u, const string& p, Role r);
    void registerAkun();
    void simpanAkunKeFile(const string& u, const string& p, Role r);
    // login now returns Role; sets outUsername if login success
    Role login(string &outUsername);
};

Akun::Akun() {
    head = nullptr;
    loadFromFile();
}

Akun::~Akun() {
    AkunNode* cur = head;
    while (cur) {
        AkunNode* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
}

void Akun::loadFromFile() {
    ifstream file("data_akun.txt");
    if (!file.is_open()) return;
    string u, p;
    int r;
    while (file >> u >> p >> r) {
        appendNode(u, p, (Role)r);
    }
    file.close();
}

void Akun::appendNode(const string& u, const string& p, Role r) {
    AkunNode* node = new AkunNode;
    node->username = u;
    node->password = p;
    node->role = r;
    node->next = nullptr;

    if (!head) head = node;
    else {
        AkunNode* t = head;
        while (t->next) t = t->next;
        t->next = node;
    }
}

void Akun::registerAkun() {
    string username, password;
    int pilih;
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;
    cout << "---[ Formulir Pendaftaran Akun Baru ]---";
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;
    cout << "Username\t: ";
    cin >> username;
    cout << "Password\t: ";
    cin >> password;
    cout << endl;
    cout << "--- Pilih Jenis Peran (Role) ---";
    cout << endl;
    cout << "1. Admin";
    cout << endl;
    cout << "2. Siswa";
    cout << endl;
    cout << "3. Pengajar";
    cout << endl;
    cout << "Pilihan Role (1/2/3): ";
    cin >> pilih;
    
    Role r = INVALID_ROLE;
    if (pilih == 1) r = ADMIN;
    else if (pilih == 2) r = SISWA;
    else if (pilih == 3) r = PENGAJAR;

    appendNode(username, password, r);
    simpanAkunKeFile(username, password, r);
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;
    cout << "Akun berhasil dibuat!";
    cout << endl;
    cout << ">> Username " << username << " terdaftar sebagai " << r;
    cout << endl << endl;
    
}

void Akun::simpanAkunKeFile(const string& u, const string& p, Role r) {
    ofstream file("data_akun.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file data_akun.txt\n";
        return;
    }
    file << u << " " << p << " " << (int)r << "\n";
    file.close();
}

Role Akun::login(string &outUsername) {
    string u, p;
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;
    cout << "---[ 	      Login Sistem          ]---";
    cout << endl;
    cout << "----------------------------------------";
    cout << endl << endl;
    cout << "Username\t: ";
    cin >> u;
    cout << "Password\t: ";
    cin >> p;
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;

    AkunNode* t = head;
    while (t) {
        if (t->username == u && t->password == p) {
//            cout << "Login berhasil. Role: " << (int)t->role << "\n";
            outUsername = u;
            return t->role;
        }
        t = t->next;
    }

    cout << "Login gagal! Username atau password salah.\n";
    return INVALID_ROLE;
}

#endif

