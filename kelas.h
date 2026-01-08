#ifndef KELAS_H
#define KELAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>  
#include <iomanip>
using namespace std;

// ============================
// Struktur node untuk pendaftaran kelas
// ============================
struct KelasNode {
    string idPendaftaran;
    long long nik;           // NIK siswa/pengajar
    string nama;            // Nama siswa/pengajar
    string role;            // "SISWA" atau "PENGAJAR"
    string tingkat;         // SD, SMP, SMA
    string kelas;           // Contoh: "7A", "10 IPA 1"
    string mapel;           // Mata pelajaran
    string status;          // "PENDING", "DITERIMA", "DITOLAK"
    string tanggalDaftar;
    KelasNode* next;
};

// ============================
// Struktur node untuk daftar kelas aktif
// ============================
struct DaftarKelasNode {
    string idKelas;
    string tingkat;
    string kelas;
    string mapel;
    long long pengajarNIK;  // Pengajar yang mengajar
    string hari;
    string jam;
    int kapasitas;
    int terisi;
    DaftarKelasNode* next;
};

class KelasManager {
private:
    KelasNode* headPendaftaran;
    DaftarKelasNode* headKelasAktif;
    
    void loadPendaftaran();
    void loadKelasAktif();
    void simpanPendaftaranKeFile();
    void simpanKelasAktifKeFile();
    
public:
    KelasManager();
    ~KelasManager();
    
    // Untuk Siswa
    void daftarKelasSiswa(long long nik, const string& nama);
    
    // Untuk Pengajar
    void buatKelasPengajar(long long nik, const string& nama);
    
    // Untuk Admin
    void lihatSemuaPendaftaran();
    void lihatKelasAktif();
    void prosesPendaftaran(const string& idPendaftaran, bool diterima);
    void hapusKelas(const string& idKelas);
    
    // Untuk tampilan di menu siswa/pengajar
    void lihatKelasSaya(long long nik, const string& role);
    
    // Helper function untuk mendapatkan tanggal sekarang
    string getTanggalSekarang();
};

KelasManager::KelasManager() {
    headPendaftaran = nullptr;
    headKelasAktif = nullptr;
    loadPendaftaran();
    loadKelasAktif();
}

KelasManager::~KelasManager() {
    // Bebaskan memori pendaftaran
    KelasNode* curP = headPendaftaran;
    while (curP) {
        KelasNode* temp = curP;
        curP = curP->next;
        delete temp;
    }
    
    // Bebaskan memori kelas aktif
    DaftarKelasNode* curK = headKelasAktif;
    while (curK) {
        DaftarKelasNode* temp = curK;
        curK = curK->next;
        delete temp;
    }
}

string KelasManager::getTanggalSekarang() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string tahun = to_string(1900 + ltm->tm_year);
    string bulan = to_string(1 + ltm->tm_mon);
    string hari = to_string(ltm->tm_mday);
    
    // Format: YYYY-MM-DD
    if (bulan.length() == 1) bulan = "0" + bulan;
    if (hari.length() == 1) hari = "0" + hari;
    
    return tahun + "-" + bulan + "-" + hari;
}

void KelasManager::loadPendaftaran() {
    ifstream file("data_pendaftaran_kelas.txt");
    if (!file.is_open()) return;
    
    string id, nikStr, nama, role, tingkat, kelas, mapel, status, tanggal;
    
    while (getline(file, id, '|')) {
        if (id.empty()) break;
        
        getline(file, nikStr, '|');
        getline(file, nama, '|');
        getline(file, role, '|');
        getline(file, tingkat, '|');
        getline(file, kelas, '|');
        getline(file, mapel, '|');
        getline(file, status, '|');
        getline(file, tanggal);
        
        KelasNode* node = new KelasNode;
        node->idPendaftaran = id;
        node->nik = stoll(nikStr);
        node->nama = nama;
        node->role = role;
        node->tingkat = tingkat;
        node->kelas = kelas;
        node->mapel = mapel;
        node->status = status;
        node->tanggalDaftar = tanggal;
        node->next = nullptr;
        
        if (!headPendaftaran) {
            headPendaftaran = node;
        } else {
            KelasNode* cur = headPendaftaran;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
    }
    file.close();
}

void KelasManager::loadKelasAktif() {
    ifstream file("data_kelas_aktif.txt");
    if (!file.is_open()) return;
    
    string id, tingkat, kelas, mapel, nikStr, hari, jam, kapasitasStr, terisiStr;
    
    while (getline(file, id, '|')) {
        if (id.empty()) break;
        
        getline(file, tingkat, '|');
        getline(file, kelas, '|');
        getline(file, mapel, '|');
        getline(file, nikStr, '|');
        getline(file, hari, '|');
        getline(file, jam, '|');
        getline(file, kapasitasStr, '|');
        getline(file, terisiStr);
        
        DaftarKelasNode* node = new DaftarKelasNode;
        node->idKelas = id;
        node->tingkat = tingkat;
        node->kelas = kelas;
        node->mapel = mapel;
        node->pengajarNIK = stoll(nikStr);
        node->hari = hari;
        node->jam = jam;
        node->kapasitas = stoi(kapasitasStr);
        node->terisi = stoi(terisiStr);
        node->next = nullptr;
        
        if (!headKelasAktif) {
            headKelasAktif = node;
        } else {
            DaftarKelasNode* cur = headKelasAktif;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
    }
    file.close();
}

void KelasManager::simpanPendaftaranKeFile() {
    ofstream file("data_pendaftaran_kelas.txt", ios::trunc);
    if (!file.is_open()) {
        cout << "Gagal membuka file pendaftaran kelas\n";
        return;
    }
    
    KelasNode* cur = headPendaftaran;
    while (cur) {
        file << cur->idPendaftaran << "|"
             << cur->nik << "|"
             << cur->nama << "|"
             << cur->role << "|"
             << cur->tingkat << "|"
             << cur->kelas << "|"
             << cur->mapel << "|"
             << cur->status << "|"
             << cur->tanggalDaftar << endl;
        cur = cur->next;
    }
    file.close();
}

void KelasManager::simpanKelasAktifKeFile() {
    ofstream file("data_kelas_aktif.txt", ios::trunc);
    if (!file.is_open()) {
        cout << "Gagal membuka file kelas aktif\n";
        return;
    }
    
    DaftarKelasNode* cur = headKelasAktif;
    while (cur) {
        file << cur->idKelas << "|"
             << cur->tingkat << "|"
             << cur->kelas << "|"
             << cur->mapel << "|"
             << cur->pengajarNIK << "|"
             << cur->hari << "|"
             << cur->jam << "|"
             << cur->kapasitas << "|"
             << cur->terisi << endl;
        cur = cur->next;
    }
    file.close();
}

void KelasManager::daftarKelasSiswa(long long nik, const string& nama) {
    cout << "\n========== PENDAFTARAN KELAS ==========\n";
    
    // Generate ID unik
    string id = "REG" + to_string(time(0)) + "_" + to_string(nik);
    string tingkat, kelas, mapel;
    
    cout << "Pilih Tingkat Pendidikan:\n";
    cout << "1. SD\n2. SMP\n3. SMA\n";
    cout << "Pilihan: ";
    int pilih;
    cin >> pilih;
    
    if (pilih == 1) tingkat = "SD";
    else if (pilih == 2) tingkat = "SMP";
    else if (pilih == 3) tingkat = "SMA";
    else {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    cin.ignore();
    cout << "Kelas (contoh: 7A, 10 IPA 1): ";
    getline(cin, kelas);
    
    cout << "Mata Pelajaran: ";
    getline(cin, mapel);
    
    // Dapatkan tanggal saat ini
    string tanggal = getTanggalSekarang();
    
    // Buat node baru
    KelasNode* node = new KelasNode;
    node->idPendaftaran = id;
    node->nik = nik;
    node->nama = nama;
    node->role = "SISWA";
    node->tingkat = tingkat;
    node->kelas = kelas;
    node->mapel = mapel;
    node->status = "PENDING";
    node->tanggalDaftar = tanggal;
    node->next = nullptr;
    
    // Tambahkan ke linked list (QUEUE: FIFO)
    if (!headPendaftaran) {
        headPendaftaran = node;
    } else {
        KelasNode* cur = headPendaftaran;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    
    // Simpan ke file
    simpanPendaftaranKeFile();
    
    cout << "\nPendaftaran berhasil! ID Pendaftaran: " << id << endl;
    cout << "Status: PENDING (Menunggu persetujuan admin)\n";
}

void KelasManager::buatKelasPengajar(long long nik, const string& nama) {
    cout << "\n========== BUAT KELAS BARU ==========\n";
    
    // Cari data pengajar untuk mendapatkan mapel utama
    ifstream file("data_pengajar.txt");
    string nikStr, namaPengajar, mapelUtama, jadwal, alamat, notelp;
    bool found = false;
    
    while (getline(file, nikStr, '|')) {
        getline(file, namaPengajar, '|');
        getline(file, mapelUtama, '|');
        getline(file, jadwal, '|');
        getline(file, alamat, '|');
        getline(file, notelp);
        
        if (nikStr == to_string(nik)) {
            found = true;
            break;
        }
    }
    file.close();
    
    if (!found) {
        cout << "Data pengajar tidak ditemukan!\n";
        return;
    }
    
    string id = "KLS" + to_string(time(0)) + "_" + to_string(nik);
    string tingkat, kelas, hari, jam;
    int kapasitas;
    
    cout << "Mata Pelajaran: " << mapelUtama << " (bisa diubah)\n";
    
    cout << "Pilih Tingkat:\n1. SD\n2. SMP\n3. SMA\nPilihan: ";
    int pilih;
    cin >> pilih;
    
    if (pilih == 1) tingkat = "SD";
    else if (pilih == 2) tingkat = "SMP";
    else if (pilih == 3) tingkat = "SMA";
    else {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    cin.ignore();
    cout << "Nama Kelas (contoh: Matematika Dasar, Fisika Lanjutan): ";
    getline(cin, kelas);
    
    cout << "Mata Pelajaran (kosongkan untuk gunakan '" << mapelUtama << "'): ";
    string mapelInput;
    getline(cin, mapelInput);
    string mapel = mapelInput.empty() ? mapelUtama : mapelInput;
    
    cout << "Hari: ";
    getline(cin, hari);
    
    cout << "Jam (contoh: 08:00-09:30): ";
    getline(cin, jam);
    
    cout << "Kapasitas maksimal siswa: ";
    cin >> kapasitas;
    
    // Buat node kelas aktif
    DaftarKelasNode* node = new DaftarKelasNode;
    node->idKelas = id;
    node->tingkat = tingkat;
    node->kelas = kelas;
    node->mapel = mapel;
    node->pengajarNIK = nik;
    node->hari = hari;
    node->jam = jam;
    node->kapasitas = kapasitas;
    node->terisi = 0;
    node->next = nullptr;
    
    // Tambahkan ke linked list
    if (!headKelasAktif) {
        headKelasAktif = node;
    } else {
        DaftarKelasNode* cur = headKelasAktif;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    
    // Simpan ke file
    simpanKelasAktifKeFile();
    
    cout << "\nKelas berhasil dibuat! ID Kelas: " << id << endl;
}

void KelasManager::lihatKelasSaya(long long nik, const string& role) {
    cout << "\n========== KELAS SAYA ==========\n";
    
    if (role == "SISWA") {
        // Cari di pendaftaran yang sudah diterima
        KelasNode* cur = headPendaftaran;
        bool ditemukan = false;
        
        cout << "Kelas yang Anda ikuti:\n";
        cout << "==========================================\n";
        
        while (cur) {
            if (cur->nik == nik && cur->role == "SISWA") {
                cout << "ID Pendaftaran: " << cur->idPendaftaran << endl;
                cout << "Tingkat        : " << cur->tingkat << endl;
                cout << "Kelas          : " << cur->kelas << endl;
                cout << "Mata Pelajaran : " << cur->mapel << endl;
                cout << "Status         : " << cur->status << endl;
                cout << "Tanggal Daftar : " << cur->tanggalDaftar << endl;
                cout << "==========================================\n";
                ditemukan = true;
            }
            cur = cur->next;
        }
        
        if (!ditemukan) {
            cout << "Anda belum memiliki kelas yang aktif.\n";
        }
        
    } else if (role == "PENGAJAR") {
        // Cari di kelas aktif
        DaftarKelasNode* cur = headKelasAktif;
        bool ditemukan = false;
        
        cout << "Kelas yang Anda ajar:\n";
        cout << "==========================================\n";
        
        while (cur) {
            if (cur->pengajarNIK == nik) {
                cout << "ID Kelas    : " << cur->idKelas << endl;
                cout << "Tingkat     : " << cur->tingkat << endl;
                cout << "Nama Kelas  : " << cur->kelas << endl;
                cout << "Mata Pelajaran: " << cur->mapel << endl;
                cout << "Hari/Jam    : " << cur->hari << " " << cur->jam << endl;
                cout << "Kapasitas   : " << cur->terisi << "/" << cur->kapasitas << endl;
                cout << "==========================================\n";
                ditemukan = true;
            }
            cur = cur->next;
        }
        
        if (!ditemukan) {
            cout << "Anda belum memiliki kelas yang aktif.\n";
        }
    }
}

void KelasManager::lihatSemuaPendaftaran() {
    cout << endl;
    cout << "[" << string(110, '=') << "]" << endl;
    cout << left << setw(55) << " " << "SEMUA PENDAFTARAN KELAS" << setw(55) << " " << endl;
    cout << "[" << string(110, '=') << "]" << endl;
    cout << endl;
    
    if (!headPendaftaran) {
        cout << "Belum ada pendaftaran.\n";
        return;
    }
    
    KelasNode* cur = headPendaftaran;
    int count = 1;
    
   cout << left
         << setw(5) << "No."
         << setw(30) << "ID Pendaftaran"
         << setw(20) << "NIK"
         << setw(25) << "Nama"
         << setw(15) << "Status"
         << setw(15) << "Tanggal"
         << endl;
    
    cout << string(110, '-') << endl;
    
    while (cur) {
        cout << left << setw(5) << count++
             << setw(30) << cur->idPendaftaran
             << setw(20) << cur->nik 
             << setw(25) << cur->nama 
             << setw(15) << cur->status
             << setw(15) << cur->tanggalDaftar << endl;
             cout << string(110, '-') << endl;
        cur = cur->next;
        
    }
}

void KelasManager::lihatKelasAktif() {
    cout << endl;
    cout << "[" << string(100, '=') << "]" << endl;
    cout << left << setw(50) << " " << "KELAS AKTIF" << setw(50) << " " << endl;
    cout << "[" << string(100, '=') << "]" << endl;
    cout << endl;
    
    if (!headKelasAktif) {
        cout << "Belum ada kelas aktif.\n";
        return;
    }
    
    DaftarKelasNode* cur = headKelasAktif;
    int count = 1;
    
    cout << left
         << setw(5) << "No."
         << setw(12) << "ID Kelas"
         << setw(15) << "Kelas"
         << setw(25) << "Mata Pelajaran"
         << setw(25) << "Pengajar"
         << setw(15) << "Kapasitas"
         << endl;
    
    cout << string(97, '-') << endl;
    
    while (cur) {
        // Cari nama pengajar dari NIK
        string namaPengajar = "Tidak Diketahui";
        ifstream file("data_pengajar.txt");
        string nikStr, nama, mapel, jadwal, alamat, notelp;
        
        while (getline(file, nikStr, '|')) {
            getline(file, nama, '|');
            getline(file, mapel, '|');
            getline(file, jadwal, '|');
            getline(file, alamat, '|');
            getline(file, notelp);
            
            if (nikStr == to_string(cur->pengajarNIK)) {
                namaPengajar = nama;
                break;
            }
        }
        file.close();
        
        cout << setw(5) << count++ << "\t"
             << setw(12) << cur->idKelas << "\t"
             << setw(15) << cur->kelas << "\t\t"
             << setw(25) << cur->mapel << "\t\t"
             << setw(25) << namaPengajar << "\t\t"
             << setw(15) << cur->terisi << "/" << cur->kapasitas << endl;
        cur = cur->next;
        cout << string(97, '-') << endl;

    }
}

void KelasManager::prosesPendaftaran(const string& idPendaftaran, bool diterima) {
    KelasNode* cur = headPendaftaran;
    
    while (cur) {
        if (cur->idPendaftaran == idPendaftaran) {
            if (cur->status != "PENDING") {
                cout << "Pendaftaran ini sudah diproses sebelumnya.\n";
                return;
            }
            
            if (diterima) {
                cur->status = "DITERIMA";
                cout << "Pendaftaran " << idPendaftaran << " DITERIMA.\n";
                cout << "Siswa " << cur->nama << " berhasil ditambahkan ke kelas "
                     << cur->kelas << " - " << cur->mapel << endl;
                
                // Update jumlah siswa di kelas aktif (jika ada)
                // Implementasi ini bisa dikembangkan lebih lanjut
            } else {
                cur->status = "DITOLAK";
                cout << "Pendaftaran " << idPendaftaran << " DITOLAK.\n";
            }
            
            simpanPendaftaranKeFile();
            return;
        }
        cur = cur->next;
    }
    
    cout << "ID Pendaftaran tidak ditemukan.\n";
}

void KelasManager::hapusKelas(const string& idKelas) {
    if (!headKelasAktif) {
        cout << "Tidak ada kelas aktif.\n";
        return;
    }
    
    // Jika yang dihapus adalah head
    if (headKelasAktif->idKelas == idKelas) {
        DaftarKelasNode* temp = headKelasAktif;
        headKelasAktif = headKelasAktif->next;
        delete temp;
        simpanKelasAktifKeFile();
        cout << "Kelas " << idKelas << " berhasil dihapus.\n";
        return;
    }
    
    // Cari di tengah atau akhir
    DaftarKelasNode* prev = headKelasAktif;
    DaftarKelasNode* cur = headKelasAktif->next;
    
    while (cur) {
        if (cur->idKelas == idKelas) {
            prev->next = cur->next;
            delete cur;
            simpanKelasAktifKeFile();
            cout << "Kelas " << idKelas << " berhasil dihapus.\n";
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    
    cout << "Kelas dengan ID " << idKelas << " tidak ditemukan.\n";
}

#endif
