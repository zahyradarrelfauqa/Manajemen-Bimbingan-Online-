#ifndef PENGAJAR_H
#define PENGAJAR_H

#include <iostream>
#include <fstream>
#include <string>
#include "kelas.h"
#include "akun.h"
using namespace std;

class PengajarMenu {
private:
    string nikLogin;  // NIK pengajar yang login (bisa berupa Nama saat awal)
    KelasManager* kelasManager; 

public:
    PengajarMenu(const string& nik) {
        nikLogin = nik;
        kelasManager = new KelasManager();  // Inisialisasi
    }

     ~PengajarMenu() {
        delete kelasManager;  // Hapus di destructor
    }
    
    void tampilkanProfilKTP() {
	    Akun akunObj;
	    akunObj.tampilkanProfilKTP(nikLogin);
	}

    void menuPengajar();
    void lihatProfil();
    void lihatJadwalMengajar();
    void inputNilai();
    void lihatNilaiPengajar();
    void inputAbsensi();
     void buatKelas();
    void lihatKelasSaya();
};

// ------------------------------------------------------------
//                         MENU UTAMA
// ------------------------------------------------------------
void PengajarMenu::menuPengajar() {
    int pilih;

    do {
        cout << "\n========== MENU PENGAJAR ==========\n";
        cout << "Halo, " << nikLogin << "\n";
        cout << "1. Lihat Profil KTP Saya\n";
        cout << "2. Lihat Profil Saya\n";
        cout << "3. Lihat Jadwal Mengajar\n";
        cout << "4. Input Nilai Siswa\n";
        cout << "5. Lihat Nilai yang Pernah Diberikan\n";
        cout << "6. Input Absensi Siswa\n";
        cout << "7. Buat Kelas Baru\n";      
        cout << "8. Lihat Kelas Saya\n";
        cout << "9. Logout\n";
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {
        	case 1: tampilkanProfilKTP(); break;
            case 2: lihatProfil(); break;
            case 3: lihatJadwalMengajar(); break;
            case 4: inputNilai(); break;
            case 5: lihatNilaiPengajar(); break;
            case 6: inputAbsensi(); break;
            case 7: buatKelas(); break;     
            case 8: lihatKelasSaya(); break; 
            case 9: cout << "Logout...\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 9);
}

void PengajarMenu::buatKelas() {
    cout << "\n========== BUAT KELAS BARU ==========\n";
    
    // Cari nama pengajar
    ifstream file("data_pengajar.txt");
    string nik, nama, mapel, jadwal, alamat, notelp;
    string namaPengajar = "";
    string mapelUtama = "";
    
    while (getline(file, nik, '|')) {
        getline(file, nama, '|');
        getline(file, mapel, '|');
        getline(file, jadwal, '|');
        getline(file, alamat, '|');
        getline(file, notelp);
        
        if (nik == nikLogin || nama == nikLogin) {
            namaPengajar = nama;
            mapelUtama = mapel;
            break;
        }
    }
    file.close();
    
    if (namaPengajar.empty()) {
        cout << "Data pengajar tidak ditemukan!\n";
        return;
    }
    
    // Buat kelas
    cout << "Mata Pelajaran: " << mapelUtama << endl;
    
    string tingkat, kelas, hari, jam;
    int kapasitas;
    
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
    cout << "Kelas (contoh: 7A, 10 IPA 1): ";
    getline(cin, kelas);
    
    cout << "Hari: ";
    getline(cin, hari);
    
    cout << "Jam: ";
    getline(cin, jam);
    
    cout << "Kapasitas maksimal: ";
    cin >> kapasitas;
    
    // Buat ID kelas
    string id = "KLS" + to_string(time(0)) + nikLogin.substr(0, 4);
    
    // Simpan ke file (Anda perlu perluas KelasManager untuk ini)
    ofstream out("data_kelas_aktif.txt", ios::app);
    if (out.is_open()) {
        out << id << "|"
            << tingkat << "|"
            << kelas << "|"
            << mapelUtama << "|"
            << nikLogin << "|"
            << hari << "|"
            << jam << "|"
            << kapasitas << "|"
            << "0" << endl;  // Terisi = 0
        out.close();
        cout << "Kelas berhasil dibuat! ID Kelas: " << id << endl;
    } else {
        cout << "Gagal menyimpan kelas.\n";
    }
}

void PengajarMenu::lihatKelasSaya() {
    kelasManager->lihatKelasSaya(stoll(nikLogin), "PENGAJAR");
}

// ------------------------------------------------------------
//                        PROFIL PENGAJAR
// ------------------------------------------------------------
void PengajarMenu::lihatProfil() {
    ifstream file("data_pengajar.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka data_pengajar.txt\n";
        return;
    }

    // Variabel penampung baca file
    string nik, nama, mapel, jadwal, alamat, notelp;
    bool found = false;

    // Baca file dengan delimiter '|'
    while (getline(file, nik, '|')) {
        getline(file, nama, '|');
        getline(file, mapel, '|');
        getline(file, jadwal, '|'); // Penting: Admin menyimpan kolom jadwal di sini
        getline(file, alamat, '|');
        getline(file, notelp);      // Baca sisa baris

        // Cek login (NIK atau Nama)
        if (nik == nikLogin || nama == nikLogin) {
            cout << "\n========== PROFIL PENGAJAR ==========\n";
            cout << "NIK    : " << nik << "\n";
            cout << "Nama   : " << nama << "\n";
            cout << "Mapel  : " << mapel << "\n";
            cout << "Jadwal : " << jadwal << "\n";
            cout << "Alamat : " << alamat << "\n";
            cout << "No.Telp: " << notelp << "\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Data pengajar tidak ditemukan.\n";

    file.close();
}

// ------------------------------------------------------------
//                     JADWAL MENGAJAR
// ------------------------------------------------------------
void PengajarMenu::lihatJadwalMengajar() {
    // 1. Cari NIK Asli dulu (jika login pakai Nama)
    string nikAsli = "";
    ifstream fp("data_pengajar.txt");
    string pNik, pNama, pMapel, pJadwal, pAlamat, pNotelp;
    while(getline(fp, pNik, '|')) {
        getline(fp, pNama, '|');
        getline(fp, pMapel, '|');
        getline(fp, pJadwal, '|');
        getline(fp, pAlamat, '|');
        getline(fp, pNotelp);
        if (pNik == nikLogin || pNama == nikLogin) {
            nikAsli = pNik;
            break;
        }
    }
    fp.close();

    if (nikAsli == "") {
        cout << "Data pengajar tidak ditemukan.\n";
        return;
    }

    // 2. Baca Jadwal
    ifstream file("data_jadwal.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka data_jadwal.txt\n";
        return;
    }

    cout << "\n========== JADWAL MENGAJAR ==========\n";
    cout << "ID\tHari\tJam\tMapel\tKelas\n";

    string id, hari, jam, mapel, pengajarNIK, kelas;
    bool ada = false;

    while (getline(file, id, '|')) {
        getline(file, hari, '|');
        getline(file, jam, '|');
        getline(file, mapel, '|');
        getline(file, pengajarNIK, '|');
        getline(file, kelas); // Baca sampai enter

        if (pengajarNIK == nikAsli) {
            cout << id << "\t" << hari << "\t" << jam << "\t"
                 << mapel << "\t" << kelas << "\n";
            ada = true;
        }
    }

    if (!ada)
        cout << "Anda belum memiliki jadwal mengajar.\n";

    file.close();
}

// ------------------------------------------------------------
//                        INPUT NILAI
// ------------------------------------------------------------
void PengajarMenu::inputNilai() {
    ofstream file("data_nilai.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka data_nilai.txt\n";
        return;
    }

    string nis, mapel, tanggal;
    int nilai;

    cout << "\n========== INPUT NILAI SISWA ==========\n";
    cout << "Masukkan NIK Siswa : ";
    cin >> nis;
    cout << "Masukkan Mata Pelajaran : ";
    cin.ignore(); 
    getline(cin, mapel); // Pakai getline agar bisa spasi (contoh: Bahasa Inggris)
    cout << "Masukkan Nilai (Angka) : ";
    cin >> nilai;
    cout << "Masukkan Tanggal (YYYY-MM-DD) : ";
    cin >> tanggal;

    // Simpan dengan delimiter '|' agar konsisten dengan Admin
    file << nis << "|" << mapel << "|" << nilai << "|" << tanggal << endl;

    cout << "Nilai berhasil disimpan!\n";

    file.close();
}

// ------------------------------------------------------------
//         LIHAT NILAI YANG DIBERIKAN PENGAJAR
// ------------------------------------------------------------
void PengajarMenu::lihatNilaiPengajar() {
    // 1. Cari dulu mapel apa yang diajar oleh pengajar ini
    string mapelAjar = "";
    string nikAsli = "";

    ifstream fp("data_pengajar.txt");
    string pNik, pNama, pMapel, pJadwal, pAlamat, pNotelp;
    while(getline(fp, pNik, '|')) {
        getline(fp, pNama, '|');
        getline(fp, pMapel, '|');
        getline(fp, pJadwal, '|');
        getline(fp, pAlamat, '|');
        getline(fp, pNotelp);
        
        if (pNik == nikLogin || pNama == nikLogin) {
            mapelAjar = pMapel; // Dapatkan mapel pengajar
            nikAsli = pNik;
            break;
        }
    }
    fp.close();

    if (mapelAjar == "") {
        cout << "Data pengajar tidak valid.\n";
        return;
    }

    // 2. Baca file nilai dan filter berdasarkan mapel pengajar
    ifstream file("data_nilai.txt");
    if (!file.is_open()) {
        cout << "Belum ada data nilai.\n";
        return;
    }

    cout << "\n========== NILAI YANG ANDA BERIKAN (" << mapelAjar << ") ==========\n";
    cout << "NIK_Siswa\tMapel\t\tNilai\tTanggal\n";

    string nis, mapel, nilaiStr, tanggal;
    bool ada = false;

    while (getline(file, nis, '|')) {
        getline(file, mapel, '|');
        getline(file, nilaiStr, '|');
        getline(file, tanggal);

        // Hanya tampilkan nilai dari Mapel yang diajar oleh guru ini
        if (mapel == mapelAjar) {
             if (mapel.length() < 8)
                cout << nis << "\t" << mapel << "\t\t" << nilaiStr << "\t" << tanggal << "\n";
            else
                cout << nis << "\t" << mapel << "\t" << nilaiStr << "\t" << tanggal << "\n";
            ada = true;
        }
    }

    if (!ada)
        cout << "Anda belum menginput nilai untuk mata pelajaran " << mapelAjar << ".\n";

    file.close();
}

// ------------------------------------------------------------
//                       INPUT ABSENSI
// ------------------------------------------------------------
void PengajarMenu::inputAbsensi() {
    ofstream file("data_absensi.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka data_absensi.txt\n";
        return;
    }

    string nis, tanggal, status;

    cout << "\n========== INPUT ABSENSI ==========\n";
    cout << "Masukkan NIK Siswa : ";
    cin >> nis;
    cout << "Masukkan Tanggal (YYYY-MM-DD) : ";
    cin >> tanggal;
    cout << "Status (H/I/S/A) : ";
    cin >> status;

    // Simpan dengan delimiter '|' sesuai permintaan terakhir
    file << nis << "|" << tanggal << "|" << status << endl;

    cout << "Absensi berhasil direkam!\n";

    file.close();
}

#endif
