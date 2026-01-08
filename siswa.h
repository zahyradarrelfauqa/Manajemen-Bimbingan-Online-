#ifndef SISWA_H
#define SISWA_H

#include <iostream>
#include <fstream>
#include <string>
#include "kelas.h"
#include "akun.h"
using namespace std;

class SiswaMenu {
private:
    string nikLogin;   // username siswa = NIK siswa
     KelasManager* kelasManager;

public:
    SiswaMenu(const string& nik) {
        nikLogin = nik;
        kelasManager = new KelasManager();  // Inisialisasi
    }

    ~SiswaMenu() {
        delete kelasManager;  // Hapus di destructor
    }
    
    void tampilkanProfilKTP() {
	    Akun akunObj;
	    akunObj.tampilkanProfilKTP(nikLogin);
	}

    void menuSiswa();

    void lihatProfil();
    void lihatJadwal();
    void lihatNilai();
    void lihatAbsensi();
    void lihatStatusPembayaran();
     void daftarKelas();
    void lihatKelasSaya();
};

// ------------------------------------------------------------
//                         MENU UTAMA
// ------------------------------------------------------------
void SiswaMenu::menuSiswa() {
    int pilih;

    do {
    	cout << endl;
	    cout << "----------------------------------------";
	    cout << endl;
	    cout << "---[ 	       Menu Siswa      ]---";
	    cout << endl;
	    cout << "----------------------------------------";
	    cout << endl;
        cout << "1 >> Lihat Profil KTP Saya\n";
        cout << "2 >> Lihat Profil Saya\n";
        cout << "3 >> Lihat Jadwal Bimbingan\n";
        cout << "4 >> Lihat Nilai\n";
        cout << "5 >> Lihat Absensi Saya\n";
        cout << "6 >> Lihat Status Pembayaran\n";
        cout << "7 >> Daftar Kelas Baru\n";   
        cout << "8 >> Lihat Kelas Saya\n";
    	cout << "----------------------------------------";
    	cout << endl;
        cout << "0 >> Logout\n";
        cout << "----------------------------------------";
        cout << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {
        	case 1: tampilkanProfilKTP(); break;
            case 2: lihatProfil(); break;
            case 3: lihatJadwal(); break;
            case 4: lihatNilai(); break;
            case 5: lihatAbsensi(); break;
            case 6: lihatStatusPembayaran(); break;
            case 7: daftarKelas(); break;         
            case 8: lihatKelasSaya(); break; 
            case 0: cout << "Logout...\n"; break;
					cout << endl;
			break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);
}

// ------------------------------------------------------------
//                      PROFIL SISWA
// ------------------------------------------------------------
void SiswaMenu::lihatProfil() {
    ifstream file("data_siswa.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka data_siswa.txt\n";
        return;
    }

    string nik, nama, kelas, alamat, notelp;
    bool found = false;

    while (getline(file, nik, '|')) {
    	getline(file, nama, '|');
        getline(file, kelas, '|');
        getline(file, alamat, '|');
        getline(file, notelp);
        
        if (nik == nikLogin) {
            cout << endl;
		    cout << "----------------------------------------";
		    cout << endl;
		    cout << " 	     --- Profil Siswa ---         ";
		    cout << endl;
		    cout << "----------------------------------------";
		    cout << endl;
            cout << "NIK\t: " << nik << "\n";
            cout << "Nama\t: " << nama << "\n";
            cout << "Kelas\t: " << kelas << "\n";
            cout << "----------------------------------------";
            cout << endl;
            cout << "Kontak & Alamat";
            cout << endl << endl;
            cout << "Alamat\t: " << alamat << "\n";
            cout << "No.Telp\t: " << notelp << "\n";
            cout << "----------------------------------------";
            cout << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Data profil tidak ditemukan.\n";

    file.close();
}

// ------------------------------------------------------------
//                        JADWAL BIMBINGAN
// ------------------------------------------------------------
void SiswaMenu::lihatJadwal() {

    // Pertama ambil kelas siswa dari file siswa.txt
    ifstream fs("data_siswa.txt");
    string nik, nama, kelasSiswa, alamat, notelp;

    bool found = false;
    while (getline(fs, nik, '|')) {
    	getline(fs, nama, '|');
        getline(fs, kelasSiswa, '|'); // Kita butuh variabel ini
        getline(fs, alamat, '|');
        getline(fs, notelp);
        
        if (nik == nikLogin) {
            found = true;
            break;
        }
    }
    fs.close();

    if (!found) {
        cout << "Data kelas siswa tidak ditemukan!\n";
        return;
    }

    // Baca jadwal
    ifstream fj("data_jadwal.txt");
    if (!fj.is_open()) {
        cout << "Gagal membuka data_jadwal.txt\n";
        return;
    }

    cout << "\n========== JADWAL BIMBINGAN ==========\n";

    string id, hari, jam, mapel, pengajarNIP, kelas;
    bool ada = false;

    cout << left 
	     << setw(6) << "ID" 
	     << setw(10) << "Hari" 
	     << setw(12) << "Jam" 
	     << setw(20) << "Mapel" 
	     << setw(15) << "Pengajar" 
	     << setw(8) << "Kelas" 
	     << endl;
	cout << string(71, '-') << endl; // Garis pemisah

    while (getline(fj, id, '|')) {
    	getline(fj, hari, '|');
        getline(fj, jam, '|');
        getline(fj, mapel, '|');
        getline(fj, pengajarNIP, '|');
        getline(fj, kelas); // Baca sampai enter
        
        if (kelas == kelasSiswa) {
           cout << left
	             << setw(6) << id
	             << setw(10) << hari
	             << setw(12) << jam
	             << setw(20) << mapel
	             << setw(15) << pengajarNIP
	             << setw(8) << kelas
	             << endl;
            ada = true;
        }
    }

    if (!ada)
        cout << "Tidak ada jadwal untuk kelas anda.\n";

    fj.close();
}

// ------------------------------------------------------------
//                        NILAI SISWA
// ------------------------------------------------------------
void SiswaMenu::lihatNilai() {
    string nikAsli = ""; // Ini akan menyimpan NIK yang benar
    
    // --- TAHAP 1: Cari NIK Asli di data_siswa.txt ---
    ifstream fs("data_siswa.txt");
    if (fs.is_open()) {
        string fNik, fNama, fKelas, fAlamat, fNoTelp;
        
        // Loop baca data siswa untuk mencocokkan Login (Nama/NIK) dengan NIK asli
        while (getline(fs, fNik, '|')) {
            getline(fs, fNama, '|');
            getline(fs, fKelas, '|');
            getline(fs, fAlamat, '|');
            getline(fs, fNoTelp); // Baca sisa baris
            
            // Cek apakah akunLogin cocok dengan NIK atau Nama di database
            if (fNik == nikLogin || fNama == nikLogin) {
                nikAsli = fNik; // Ketemu! Simpan NIK-nya
                break;
            }
        }
        fs.close();
    }
    
    // Jika siswa tidak ditemukan/belum terdaftar
    if (nikAsli == "") {
        cout << "Data siswa tidak ditemukan. Tidak dapat menampilkan nilai.\n";
        return;
    }
    
    // --- TAHAP 2: Baca Nilai dari data_nilai.txt ---
    ifstream file("data_nilai.txt");
    if (!file.is_open()) {
        cout << "Belum ada data nilai (File tidak ditemukan).\n";
        return;
    }

    cout << "\n============ NILAI SAYA ============\n";
    cout << left 
	     << setw(25) << "Mata Pelajaran" 
	     << setw(10) << "Nilai" 
	     << setw(15) << "Tanggal" 
	     << endl;
	cout << string(50, '=') << endl; // Garis pemisah

    string nikStr, mapel, nilaiStr, tanggal;
    bool ada = false;

    // Perbaikan: Gunakan 'file' (bukan 'fs') dan delimiter '|'
    while (getline(file, nikStr, '|')) {
        getline(file, mapel, '|');
        getline(file, nilaiStr, '|');
        getline(file, tanggal); // baca sampai enter (newline)
        
        // Bandingkan NIK di file nilai dengan NIK Asli siswa
        if (nikStr == nikAsli) {
            // Tampilkan output
            // Jika nama mapel pendek, tambah tab agar lurus
            if (mapel.length() < 8)
                 cout << left
		             << setw(25) << mapel
		             << setw(10) << nilaiStr
		             << setw(15) << tanggal
		             << endl;
            else
                 cout << left
		             << setw(25) << mapel
		             << setw(10) << nilaiStr
		             << setw(15) << tanggal
		             << endl;
            
            ada = true;
        }
    }

    if (!ada)
        cout << "Belum ada nilai untuk anda.\n";

    file.close();
}

// ------------------------------------------------------------
//                   ABSENSI SISWA
// ------------------------------------------------------------
// COPY KE SISWA.H

void SiswaMenu::lihatAbsensi() {
    string nikAsli = ""; 

    // --- TAHAP 1: Cari NIK Asli di data_siswa.txt ---
    ifstream fs("data_siswa.txt");
    if (fs.is_open()) {
        string fNik, fNama, fKelas, fAlamat, fNoTelp;
        while (getline(fs, fNik, '|')) {
            getline(fs, fNama, '|');
            getline(fs, fKelas, '|');
            getline(fs, fAlamat, '|');
            getline(fs, fNoTelp); 
            
            if (fNik == nikLogin || fNama == nikLogin) {
                nikAsli = fNik; 
                break;
            }
        }
        fs.close();
    }

    if (nikAsli == "") {
        cout << "Data siswa tidak ditemukan.\n";
        return;
    }

    // --- TAHAP 2: Baca Absensi (Format '|') ---
    ifstream file("data_absensi.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka absensi.txt\n";
        return;
    }

    cout << "\n=========== ABSENSI SAYA ===========\n";
    cout << "Tanggal\t\tStatus\n";

    string nikStr, tanggal, status;
    bool ada = false;

    // Gunakan getline dengan delimiter '|'
    while (getline(file, nikStr, '|')) {
        getline(file, tanggal, '|');
        getline(file, status); // Baca sampai enter
        
        // Bandingkan
        if (nikStr == nikAsli) {
            cout << tanggal << "\t\t" << status << "\n";
            ada = true;
        }
    }

    if (!ada)
        cout << "Belum ada absensi untuk anda.\n";

    file.close();
}

// ------------------------------------------------------------
//               STATUS PEMBAYARAN SISWA
// ------------------------------------------------------------
void SiswaMenu::lihatStatusPembayaran() {
    string nikAsli = ""; 

    // --- TAHAP 1: Cari NIK Asli di data_siswa.txt ---
    ifstream fs("data_siswa.txt");
    if (fs.is_open()) {
        string fNik, fNama, fKelas, fAlamat, fNoTelp;
        while (getline(fs, fNik, '|')) {
            getline(fs, fNama, '|');
            getline(fs, fKelas, '|');
            getline(fs, fAlamat, '|');
            getline(fs, fNoTelp); 
            
            if (fNik == nikLogin || fNama == nikLogin) {
                nikAsli = fNik; 
                break;
            }
        }
        fs.close();
    }

    if (nikAsli == "") {
        cout << "Data siswa tidak ditemukan.\n";
        return;
    }

    // --- TAHAP 2: Baca Data Keuangan (Format '|') ---
    ifstream file("data_keuangan.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka data_keuangan.txt\n";
        return;
    }

    cout << "\n======= STATUS PEMBAYARAN SAYA =======\n";
    cout << left 
	     << setw(8) << "ID" 
	     << setw(20) << "Jenis Pembayaran" 
	     << setw(12) << "Jumlah" 
	     << setw(15) << "Tanggal" 
	     << setw(12) << "Status" 
	     << endl;
	cout << string(67, '-') << endl; // Garis pemisah

    string id, nikStr, jenis, jumlahStr, tanggal, status;
    bool ada = false;

    // Baca menggunakan getline '|'
    while (getline(file, id, '|')) {
        getline(file, nikStr, '|');
        getline(file, jenis, '|');
        getline(file, jumlahStr, '|');
        getline(file, tanggal, '|');
        getline(file, status); // Baca sampai enter

        if (nikStr == nikAsli) {
            // Tampilan output (sedikit formatting tab agar rapi)
            if (jenis.length() < 8)
                cout << left
		             << setw(8) << id
		             << setw(20) << jenis
		             << setw(12) << jumlahStr
		             << setw(15) << tanggal
		             << setw(12) << status
		             << endl;
		    else
                cout << left
		             << setw(8) << id
		             << setw(20) << jenis
		             << setw(12) << jumlahStr
		             << setw(15) << tanggal
		             << setw(12) << status
		             << endl;
                
            ada = true;
        }
    }

    if (!ada)
        cout << "Belum ada transaksi pembayaran.\n";

    file.close();
}

void SiswaMenu::daftarKelas() {
    // Cari nama siswa dari NIK
    ifstream file("data_siswa.txt");
    string nik, nama, kelas, alamat, notelp;
    string namaSiswa = "";
    
    while (getline(file, nik, '|')) {
        getline(file, nama, '|');
        getline(file, kelas, '|');
        getline(file, alamat, '|');
        getline(file, notelp);
        
        if (nik == nikLogin) {
            namaSiswa = nama;
            break;
        }
    }
    file.close();
    
    if (namaSiswa.empty()) {
        cout << "Data siswa tidak ditemukan!\n";
        return;
    }
    
    kelasManager->daftarKelasSiswa(stoll(nikLogin), namaSiswa);
}

void SiswaMenu::lihatKelasSaya() {
    kelasManager->lihatKelasSaya(stoll(nikLogin), "SISWA");
}
#endif
