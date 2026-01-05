#ifndef AKUN_H
#define AKUN_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

enum Role {
    ADMIN = 1,
    SISWA = 2,
    PENGAJAR = 3,
    INVALID_ROLE = 4
};

struct AkunNode {
    string username;  // Akan menjadi NIK untuk siswa/pengajar
    string password;
    Role role;
    AkunNode* next;
};

class Akun {
private:
    AkunNode* head;
    
    // Fungsi untuk memeriksa apakah NIK ada di database KTP
    bool cekNIKDiKTP(const string& nik) {
        ifstream file("data_ktp_linkedlist.txt");
        if (!file.is_open()) return false;
        
        string line;
        while (getline(file, line)) {
            if (line.find("NIK") != string::npos && line.find(nik) != string::npos) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    
    // Fungsi untuk mendaftarkan data KTP baru
    void daftarKTPBaru() {
        cout << "\n>> NIK tidak ditemukan di database KTP.\n";
        cout << "Silakan lengkapi data KTP Anda untuk mendaftar:\n";
        
        string nik, nama, tempatLahir, tanggalLahir, jenisKelamin, golDarah, alamat;
        string rt, rw, kelurahan, kecamatan, kotaKab, provinsi, agama, statusKawin;
        string pekerjaan, kewarganegaraan, berlakuHingga;
        
        // Input data KTP
        cout << "NIK (16 digit): ";
        cin >> nik;
        
        cin.ignore();
        cout << "Nama Lengkap: ";
        getline(cin, nama);
        
        cout << "Tempat Lahir: ";
        getline(cin, tempatLahir);
        
        cout << "Tanggal Lahir (DD/MM/YYYY): ";
        getline(cin, tanggalLahir);
        
        cout << "Jenis Kelamin (1:L / 2:P): ";
        string jk;
        cin >> jk;
        jenisKelamin = (jk == "1") ? "Laki-laki" : "Perempuan";
        
        cout << "Golongan Darah (A/B/AB/O): ";
        cin >> golDarah;
        
        cin.ignore();
        cout << "Alamat: ";
        getline(cin, alamat);
        
        cout << "RT: ";
        getline(cin, rt);
        
        cout << "RW: ";
        getline(cin, rw);
        
        cout << "Kelurahan: ";
        getline(cin, kelurahan);
        
        cout << "Kecamatan: ";
        getline(cin, kecamatan);
        
        cout << "Kota/Kabupaten: ";
        getline(cin, kotaKab);
        
        cout << "Provinsi: ";
        getline(cin, provinsi);
        
        cout << "Agama: ";
        getline(cin, agama);
        
        cout << "Status Perkawinan (Kawin/Belum Kawin): ";
        getline(cin, statusKawin);
        
        cout << "Pekerjaan: ";
        getline(cin, pekerjaan);
        
        cout << "Kewarganegaraan (WNI/WNA): ";
        getline(cin, kewarganegaraan);
        
        cout << "Berlaku Hingga (DD-MM-YYYY): ";
        getline(cin, berlakuHingga);
        
        // Simpan ke file KTP
        ofstream ktpFile("data_ktp_linkedlist.txt", ios::app);
        if (ktpFile.is_open()) {
            // Cari total data yang ada
            ifstream countFile("data_ktp_linkedlist.txt");
            int totalData = 0;
            string line;
            while (getline(countFile, line)) {
                if (line.find("Total data:") != string::npos) {
                    size_t pos = line.find(":");
                    if (pos != string::npos) {
                        totalData = stoi(line.substr(pos + 1));
                    }
                }
            }
            countFile.close();
            
            // Pindahkan pointer ke akhir file sebelum "Total data"
            ktpFile.seekp(0, ios::end);
            long pos = ktpFile.tellp();
            
            // Jika file kosong, tulis header
            if (pos == 0) {
                ktpFile << "================================================================================\n";
                ktpFile << "                            DATA KTP (LINKED LIST)\n";
                ktpFile << "================================================================================\n\n";
            } else {
                // Mundur ke sebelum "Total data"
                ktpFile.seekp(-20, ios::cur); // Adjust as needed
            }
            
            // Tulis data baru
            ktpFile << "Data ke-" << totalData + 1 << "\n";
            ktpFile << "----------------------------------------\n";
            ktpFile << "NIK               : " << nik << "\n";
            ktpFile << "Nama              : " << nama << "\n";
            ktpFile << "Tempat Lahir      : " << tempatLahir << "\n";
            ktpFile << "Tanggal Lahir     : " << tanggalLahir << "\n";
            ktpFile << "Jenis Kelamin     : " << jenisKelamin << "\n";
            ktpFile << "Gol. Darah        : " << golDarah << "\n";
            ktpFile << "Alamat            : " << alamat << "\n";
            ktpFile << "RT/RW             : " << rt << "/" << rw << "\n";
            ktpFile << "Kelurahan         : " << kelurahan << "\n";
            ktpFile << "Kecamatan         : " << kecamatan << "\n";
            ktpFile << "Kota/Kabupaten    : " << kotaKab << "\n";
            ktpFile << "Provinsi          : " << provinsi << "\n";
            ktpFile << "Agama             : " << agama << "\n";
            ktpFile << "Status Perkawinan : " << statusKawin << "\n";
            ktpFile << "Pekerjaan         : " << pekerjaan << "\n";
            ktpFile << "Kewarganegaraan   : " << kewarganegaraan << "\n";
            ktpFile << "Berlaku Hingga    : " << berlakuHingga << "\n\n";
            ktpFile << "Total data: " << totalData + 1 << "\n";
            ktpFile << "================================================================================\n";
            
            ktpFile.close();
            cout << "\n? Data KTP berhasil disimpan!\n";
        } else {
            cout << "? Gagal menyimpan data KTP.\n";
        }
    }
    
    // Fungsi untuk mendapatkan informasi KTP berdasarkan NIK
    bool getDataKTP(const string& nik, string& nama, string& provinsi) {
        ifstream file("data_ktp_linkedlist.txt");
        if (!file.is_open()) return false;
        
        string line;
        bool found = false;
        bool captureNama = false;
        bool captureProvinsi = false;
        
        while (getline(file, line)) {
            // Cari data dengan NIK yang sesuai
            if (line.find("NIK") != string::npos && line.find(nik) != string::npos) {
                found = true;
                continue;
            }
            
            if (found) {
                if (line.find("Nama") != string::npos) {
                    size_t pos = line.find(":");
                    if (pos != string::npos) {
                        nama = line.substr(pos + 2);
                        captureNama = true;
                    }
                }
                else if (line.find("Provinsi") != string::npos) {
                    size_t pos = line.find(":");
                    if (pos != string::npos) {
                        provinsi = line.substr(pos + 2);
                        captureProvinsi = true;
                    }
                }
                
                // Jika sudah mendapatkan nama dan provinsi, keluar
                if (captureNama && captureProvinsi) {
                    file.close();
                    return true;
                }
            }
            
            // Reset jika menemukan data baru
            if (line.find("Data ke-") != string::npos && found) {
                break;
            }
        }
        
        file.close();
        return found;
    }

public:
    Akun();
    ~Akun();
    void loadFromFile();
    void appendNode(const string& u, const string& p, Role r);
    void registerAkun();
    void simpanAkunKeFile(const string& u, const string& p, Role r);
    Role login(string &outUsername);
    
    // Fungsi baru untuk menampilkan profil KTP
    void tampilkanProfilKTP(const string& nik);
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
    system("cls");
    cout << "\nREGISTER USER BARU\n";
    cout << "=============================\n";
    
    string nik;
    cout << "Masukkan NIK Anda : ";
    cin >> nik;
    
    // Cek apakah NIK sudah ada di database KTP
    if (!cekNIKDiKTP(nik)) {
        // NIK tidak ditemukan, arahkan untuk daftar KTP
        daftarKTPBaru();
    }
    
    // Lanjutkan dengan pendaftaran akun bimbingan
    cout << "\n>> Data KTP Ditemukan!\n";
    
    // Ambil nama dari data KTP
    string nama, provinsi;
    if (getDataKTP(nik, nama, provinsi)) {
        cout << "Nama : " << nama << "\n";
        cout << "Daerah : " << provinsi << "\n";
    } else {
        cout << "Nama : [Data dari KTP]\n";
        cout << "Daerah : [Data dari KTP]\n";
    }
    
    cout << "---\n";
    cout << "Silakan buat password untuk akun Anda.\n";
    
    string password;
    cout << "Buat Password (maks 10): ";
    cin >> password;
    
    int pilih;
    cout << "\n--- Pilih Jenis Peran (Role) ---\n";
    cout << "1. Admin\n";
    cout << "2. Siswa\n";
    cout << "3. Pengajar\n";
    cout << "Pilihan Role (1/2/3): ";
    cin >> pilih;
    
    Role r = INVALID_ROLE;
    if (pilih == 1) r = ADMIN;
    else if (pilih == 2) r = SISWA;
    else if (pilih == 3) r = PENGAJAR;
    
    // Simpan akun dengan NIK sebagai username
    appendNode(nik, password, r);
    simpanAkunKeFile(nik, password, r);
    
    cout << "\n? Registrasi berhasil!\n";
    cout << "NIK: " << nik << " telah terdaftar sebagai ";
    if (r == ADMIN) cout << "Admin";
    else if (r == SISWA) cout << "Siswa";
    else if (r == PENGAJAR) cout << "Pengajar";
    cout << "\n\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
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
    system("cls");
    cout << "\n---[ LOGIN SISTEM BIMBINGAN ]---\n\n";
    
    string u, p;
    cout << "Username (NIK) : ";
    cin >> u;
    cout << "Password       : ";
    cin >> p;
    
    AkunNode* t = head;
    while (t) {
        if (t->username == u && t->password == p) {
            outUsername = u;
            return t->role;
        }
        t = t->next;
    }
    
    cout << "\n? Login gagal! Username atau password salah.\n";
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    return INVALID_ROLE;
}

void Akun::tampilkanProfilKTP(const string& nik) {
    system("cls");
    cout << "\nPROFIL KTP ANGGOTA\n";
    cout << "===========================================================\n";
    
    ifstream file("data_ktp_linkedlist.txt");
    if (!file.is_open()) {
        cout << "Data KTP tidak ditemukan.\n";
        return;
    }
    
    string line;
    bool found = false;
    bool inData = false;
    int linesToShow = 0;
    
    while (getline(file, line)) {
        // Cari data dengan NIK yang sesuai
        if (line.find("NIK") != string::npos && line.find(nik) != string::npos) {
            found = true;
            inData = true;
            linesToShow = 17; // Jumlah baris data KTP
        }
        
        if (inData && linesToShow > 0) {
            // Format ulang tampilan
            if (line.find("NIK") != string::npos) {
                cout << "NIK    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Nama") != string::npos) {
                cout << "Nama    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Tempat Lahir") != string::npos) {
                string tempat = line.substr(line.find(":") + 2);
                // Ambil tanggal lahir dari baris berikutnya
                string tglLine;
                getline(file, tglLine);
                linesToShow--;
                string tgl = tglLine.substr(tglLine.find(":") + 2);
                cout << "Tempat/Tgl Lahir : " << tempat << ", " << tgl << "\n";
            }
            else if (line.find("Jenis Kelamin") != string::npos) {
                cout << "Jenis Kelamin    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Gol. Darah") != string::npos) {
                cout << "Golongan Darah : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Alamat") != string::npos) {
                cout << "Alamat    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("RT/RW") != string::npos) {
                cout << "RT/RW    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Kelurahan") != string::npos) {
                cout << "Kelurahan/Desa : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Kecamatan") != string::npos) {
                cout << "Kecamatan    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Provinsi") != string::npos) {
                cout << "Wilayah (NIK)    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Agama") != string::npos) {
                cout << "Agama    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Status Perkawinan") != string::npos) {
                cout << "Status Perkawinan : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Pekerjaan") != string::npos) {
                cout << "Pekerjaan    : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Kewarganegaraan") != string::npos) {
                cout << "Kewarganegaraan : " << line.substr(line.find(":") + 2) << "\n";
            }
            else if (line.find("Berlaku Hingga") != string::npos) {
                string berlaku = line.substr(line.find(":") + 2);
                if (berlaku == "SEUMUR HIDUP") {
                    cout << "Berlaku hingga    : Selamanya\n";
                } else {
                    cout << "Berlaku hingga    : " << berlaku << "\n";
                }
            }
            
            linesToShow--;
            
            // Hitung umur dari tanggal lahir (sederhana)
            if (line.find("Tanggal Lahir") != string::npos) {
                string tgl = line.substr(line.find(":") + 2);
                // Parsing tanggal lahir sederhana
                int tahun = stoi(tgl.substr(6, 4));
                int tahunSekarang = 2024; // Bisa diganti dengan fungsi time()
                int umur = tahunSekarang - tahun;
                cout << "Umur    : " << umur << " Tahun\n";
            }
        }
        
        if (linesToShow <= 0 && inData) {
            break;
        }
    }
    
    if (!found) {
        cout << "Data KTP dengan NIK " << nik << " tidak ditemukan.\n";
    }
    
    cout << "===========================================================\n";
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
    
    file.close();
}

#endif
