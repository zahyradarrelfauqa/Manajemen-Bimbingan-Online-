#ifndef ADMIN_H
#define ADMIN_H

#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<iomanip>
#include "kelas.h"
using namespace std;
// ============================
// Struktur node untuk keuangan
// ============================
struct KeuanganNode 
{
    string idTransaksi;   
    long long nik;           // siswa
    string jenis;         // spp, modul, les, dll
    int jumlah;           
    string tanggal;       
    string status;        // Lunas / Belum_Lunas
    KeuanganNode* next;
};

// ===========================
// Struktur node untuk absensi
// ===========================
struct AbsensiNode 
{
    long long nik; // Isiswa
    string tanggal;     
    string status;      
    AbsensiNode* next;
};

// ==========================
// Struktur node untuk jadwal
// ==========================
struct NilaiNode 
{
    long long nik; // siswa       
    string mapel;         
    int nilai;            
    string tanggal;  
    NilaiNode* next;     
};

// ==========================
// Struktur node untuk jadwal
// ==========================
struct JadwalNode 
{
    string idJadwal;      
    string hari;          
    string jam;           
    string mapel;         
    long long pengajarNIK;   
    string kelas;         
    JadwalNode* next;
};

// ============================
// Struktur node untuk pengajar
// ============================
struct NodePengajar
{
    long long nik;
    string nama;
    string mataPelajaran;
    string jadwal;
    string alamat;
    long long noTelp;
    NodePengajar* next;
};
// =========================
// Struktur node untuk siswa
// =========================
struct NodeSiswa
{
    long long nik;
    string nama;
    string kelas;
    string alamat;
    long long noTelp;
    NodeSiswa* next;
};

class Admin 
{
    private:
        // siswa
        NodeSiswa* head;
        NodeSiswa* cariDariNik(const long long& nik);
        void loadSiswa();
        void simpanSiswaKeFile(const NodeSiswa* s);
        void ubahFileSiswa(); //(update/delete)

        // pengajar
        NodePengajar* headPengajar;
        NodePengajar* cariPengajarDariNik(const long long& nik);
        void loadPengajar();
        void simpanPengajarKeFile(const NodePengajar* t);
        void ubahFilePengajar(); //(update/delete)
        JadwalNode* headJadwal;

        // jadwal
        void loadJadwal();
        void simpanJadwalKeFile(const JadwalNode* j);
        void UbahJadwalFile();
        JadwalNode* CariJadwalDariId(const string& id);

        // nilai
        NilaiNode* headNilai;
        void loadNilai();
        void simpanNilaiKeFile(const NilaiNode* n);
        void UbahNilaiFile();
        NilaiNode* cariNilai(const long long& nik, const string& mapel);

        // absensi
        AbsensiNode* headAbsensi;
        void loadAbsensi();
        void simpanAbsensikeFile(const AbsensiNode* a);
        void ubahAbsensiFile();
        // koreksi: fungsi ini seharusnya mengembalikan NodeSiswa* untuk memeriksa keberadaan siswa
        NodeSiswa* cariAbsensidariNik(const long long& nik);
        
        // keuangan
        KeuanganNode* headKeuangan;
        void loadKeuangan();
        void simpanKeuanganKeFIle(const KeuanganNode* k);
        void ubahKeuanganFile();
        KeuanganNode* cariKeuanganDariId(const string& id);

        KelasManager* kelasManager;  // Tambahkan pointer ke KelasManager

        //backup data
        void menuBackupData();
        void backupSemuaData();
        
        public:
        Admin();
        ~Admin();
        // menu admin utama
        void menuAdmin();

        // menu manajamen siswa
        void menuManajemenSiswa();
        // operasi siswa
        void tambahSiswa();
        void daftarSiswa();
        void editSiswa();
        void hapusSiswa();
        void cariSiswa();
        
        // menu manajamen pengajar
        void menuManajemenPengajar();
        // operasi pengajar
        void tambahPengajar();
        void daftarPengajar();
        void editPengajar();
        void hapusPengajar();
        void cariPengajarDariMapel();
        
        //menu manajemen jadwal
        void menuManajemenJadwal();
        // operasi jadwal
        void tambahJadwal();
        void lihatSemuaJadwal();
        void cariJadwal();
        
        // menu manajemen nilai
        void menuManajemenNilai();
        // operasi nilai
        void tambahNilai();
        void lihatSemuaNilai();
        void evaluasiPerMapel();
        
        // menu manajemen absensi
        void menuManajemenAbsensi();
        // operasi absensi
        void inputAbsensi();
        void lihatAbsensi();
        void laporanKehadiranBulanan();
        void hitungPersentaseKehadiran();
        
        // menu manajemen kuangan
        void menuManajemenKeuangan();
        //operasi keuangan
        void tambahPembayaran();
        void lihatDaftarPembayaran();
        void laporanKeuanganSiswa();
        void updateStatusPembayaran();
        
        // menu manajemen kelas
        void menuManajemenKelas();
        void lihatPendaftaranKelas();
        void prosesPendaftaranKelas();

        // menulaporan & rekap
        void menuLaporanRekap();
        void laporanDataSiswa();
        void laporanDataPengajar();
        void laporanDataNilai();
        void laporanDataKehadiran();
        void eksporSemuaLaporan();

        // backup data
        bool backupFile(const string& sumber, const string& tujuan);
    };

Admin::Admin()
{
    kelasManager = new KelasManager();

    // inisialisasi semua head sebelum load
    head = nullptr;
    headPengajar = nullptr;
    headJadwal = nullptr;
    headNilai = nullptr;
    headAbsensi = nullptr;
    headKeuangan = nullptr;

    loadSiswa();
    loadPengajar();
    loadJadwal();
    loadNilai();
    loadAbsensi();
    loadKeuangan();
}

Admin::~Admin()
{
    // bebaskan semua linked list untuk menghindari memory leak
    NodeSiswa* curS = head;
    while (curS)
    {
        NodeSiswa* temp = curS;
        curS = curS->next;
        delete temp;
    }

    NodePengajar* curP = headPengajar;
    while (curP)
    {
        NodePengajar* temp = curP;
        curP = curP->next;
        delete temp;
    }

    JadwalNode* curJ = headJadwal;
    while (curJ)
    {
        JadwalNode* temp = curJ;
        curJ = curJ->next;
        delete temp;
    }

    NilaiNode* curN = headNilai;
    while (curN)
    {
        NilaiNode* temp = curN;
        curN = curN->next;
        delete temp;
    }

    AbsensiNode* curA = headAbsensi;
    while (curA)
    {
        AbsensiNode* temp = curA;
        curA = curA->next;
        delete temp;
    }

    KeuanganNode* curK = headKeuangan;
    while (curK)
    {
        KeuanganNode* temp = curK;
        curK = curK->next;
        delete temp;
    }

    delete kelasManager;
}

void Admin::backupSemuaData() 
{
    cout << endl;
    cout << "[-----------------------------]";
    cout << endl;
    cout << "[---   BACKUP SEMUA DATA   ---]";
    cout << endl;
    cout << "[-----------------------------]";
    cout << endl;

    // Daftar file yang akan di-backup
    string files[] = {
        "data_siswa.txt",
        "data_pengajar.txt",
        "data_jadwal.txt",
        "data_nilai.txt",
        "data_absensi.txt",
        "data_keuangan.txt",
        "data_akun.txt"
    };

    // Folder tujuan
    string folder = "backup_";
    
    // Gunakan timestamp sederhana (YYYYMMDDHHMMSS)
    time_t now = time(0);
    tm *ltm = localtime(&now);

    folder += to_string(1900 + ltm->tm_year);
    folder += to_string(1 + ltm->tm_mon);
    folder += to_string(ltm->tm_mday);
    folder += to_string(ltm->tm_hour);
    folder += to_string(ltm->tm_min);
    folder += to_string(ltm->tm_sec);

    cout << "Membuat backup...\n";

    for (int i = 0; i < 7; i++) {
        string sumber = files[i];
        string tujuan = folder + "_" + files[i];

        if (backupFile(sumber, tujuan))
            cout << "Backup " << files[i] << " -> " << tujuan << " [BERHASIL]\n";
        else
            cout << "Backup " << files[i] << " [GAGAL]\n";
    }

    cout << "\nBackup selesai!\n";
}

void Admin::menuBackupData() 
{
    int pilih;
    do 
    {
        cout << endl;
        cout << "[----------------------------]";
        cout << endl;
        cout << "[---   MENU BACKUP DATA   ---]";
        cout << endl;
        cout << "[----------------------------]";
        cout << endl;
        cout << "1. Backup Semua Data";
        cout << endl;
        cout << "2. Kembali";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) 
        {
            case 1:
                backupSemuaData();
                break;
            case 2:
                cout << "Kembali...";
                cout << endl;
                break;
            default:
                cout << "Pilihan tidak valid!";
                cout << endl;
        }

    } while (pilih != 2);
}

bool Admin::backupFile(const string& sumber, const string& tujuan) 
{
    ifstream in(sumber.c_str());
    ofstream out(tujuan.c_str());

    if (!in.is_open()) 
    {
        cout << "Gagal membuka file sumber: " << sumber;
        cout << endl;
        return false;
    }
    if (!out.is_open()) 
    {
        cout << "Gagal membuat file backup: " << tujuan;
        cout << endl;
        return false;
    }

    string line;
    while (getline(in, line)) 
    {
        out << line << endl;
    }

    in.close();
    out.close();

    return true;
}

void Admin::laporanDataSiswa() 
{
    cout << endl;
    cout << "[" << string(70, '-') << "]" << endl;
    cout << left << setw(35) << " " << "LAPORAN DATA SISWA" << setw(35) << " " << endl;
    cout << "[" << string(70, '-') << "]" << endl;
    cout << endl;

    if (!head) 
    {
        cout << "Belum ada data siswa.";
        cout << endl;
        return;
    }

    NodeSiswa* cur = head;
    cout << setw(20) << "NIK"
		 << setw(25) << "Nama"
		 << setw(15) << "Kelas"
		 << endl;
	cout << string(70, '-') << endl;
    cout << endl;
    
    while (cur) 
    {
        cout << left << setw(20) << cur->nik
             << setw(25) << cur->nama
             << setw(15) << cur->kelas;
    	cout << string(70, '-') << endl;

        cur = cur->next;
    }
}

void Admin::laporanDataPengajar() 
{
    cout << endl;
    cout << "[" << string(80, '-') << "]" << endl;
    cout << left << setw(40) << " " << "LAPORAN DATA PENGAJAR" << setw(40) << " " << endl;
    cout << "[" << string(80, '-') << "]" << endl;
    cout << endl;

    if (!headPengajar) 
    {
        cout << "Belum ada data pengajar.";
        cout << endl;
        return;
    }

    NodePengajar* cur = headPengajar;
    cout << left
         << setw(20) << "NIK"
         << setw(25) << "Nama"
         << setw(30) << "Mata Pelajaran"
         << endl;
    while (cur) 
    {
        cout << left << setw(20) << cur->nik 
             << setw(25) << cur->nama
             << setw(30) << cur->mataPelajaran;
	    cout << "[" << string(80, '-') << "]" << endl;
        cout << endl;
        cur = cur->next;
    }
}

void Admin::laporanDataNilai() 
{
    cout << endl;
    cout << "[" << string(80, '-') << "]" << endl;
    cout << left << setw(40) << " " << "LAPORAN NILAI SISWA" << setw(40) << " " << endl;
    cout << "[" << string(80, '-') << "]" << endl;
    cout << endl;

    if (!headNilai) 
    {
        cout << "Belum ada data nilai.";
        cout << endl;
        return;
    }

    NilaiNode* cur = headNilai;

    cout << left
         << setw(20) << "NIK"
         << setw(25) << "Mata Pelajaran"
         << setw(10) << "Nilai"
         << setw(15) << "Kategori"
         << endl;
    
    cout << string(70, '-') << endl;

    while (cur) 
    {
        cout << left << setw(20) << cur->nik
             << setw(25) << cur->mapel  
             << setw(10) << cur->nilai 
             << setw(15) << cur->mapel;
        cout << endl;
		cout << string(70, '-') << endl;

        cur = cur->next;
    }
}

void Admin::laporanDataKehadiran() 
{
    cout << endl;
    cout << "[" << string(70, '-') << "]" << endl;
    cout << left << setw(35) << " " << "LAPORAN KEHADIRAN SISWA" << setw(35) << " " << endl;
    cout << "[" << string(70, '-') << "]" << endl;
    cout << endl;

    if (!headAbsensi) 
    {
        cout << "Belum ada data absensi.";
        cout << endl;
        return;
    }

    AbsensiNode* cur = headAbsensi;

    cout << left
         << setw(20) << "NIK"
         << setw(15) << "Tanggal"
         << setw(10) << "Status"
         << endl;
    
    cout << string(45, '-') << endl;
    
    while (cur) 
    {
        cout << left << setw(20) << cur->nik
             << setw(15) << cur->tanggal 
             << setw(10) << cur->status;
        cout << endl;
        cout << string(45, '-') << endl;
        cur = cur->next;
    }
}

void Admin::eksporSemuaLaporan() 
{
    ofstream file("rekap_semua_laporan.txt");
    if (!file.is_open()) 
    {
        cout << "Gagal membuat file laporan.";
        cout << endl;
        return;
    }

    // ====== DATA SISWA ======
    file << endl <<"[--- DATA SISWA ---]" << endl;
    if (!head) 
    {
        file << "Tidak ada data siswa.";
        cout << endl;
    } else {
        NodeSiswa* s = head;
        while (s) 
        {
            file << s->nik << " " 
                 << s->nama << " "
                 << s->kelas << " "
                 << s->alamat << " "
                 << s->noTelp << endl;
            s = s->next;
        }
    }

    // ====== DATA PENGAJAR ======
    file << endl << "[--- DATA PENGAJAR ---]" << endl;
    if (!headPengajar) 
    {
        file << "Tidak ada data pengajar.";
        cout << endl;
    } else {
        NodePengajar* t = headPengajar;
        while (t) 
        {
            file << t->nik << " " 
                 << t->nama << " " 
                 << t->mataPelajaran << " "
                 << t->jadwal << " "
                 << t->alamat << " "
                 << t->noTelp << endl;
            t = t->next;
        }
    }

    // ====== DATA NILAI ======
    file << endl << "[--- DATA NILAI ---]" << endl;
    if (!headNilai) 
    {
        file << "Tidak ada data nilai.";
        cout << endl;
    } else {
        NilaiNode* n = headNilai;
        while (n) {
            file << n->nik << " "
                 << n->mapel << " "
                 << n->nilai << " "
                 << n->tanggal << endl;
            n = n->next;
        }
    }

    // ====== DATA ABSENSI ======
    file << endl << "[--- DATA ABSENSI ---]" << endl;
    if (!headAbsensi) 
    {
        file << "Tidak ada data absensi.";
        cout << endl;
    } else {
        AbsensiNode* a = headAbsensi;
        while (a) 
        {
            file << a->nik << " "
                 << a->tanggal << " "
                 << a->status << endl;
            a = a->next;
        }
    }

    file.close();
    cout << "Semua laporan berhasil diekspor ke rekap_semua_laporan.txt!";
    cout << endl;
}

void Admin::menuLaporanRekap() 
{
    int pilih;
    do 
    {
        cout << endl;
        cout << "[---------------------------------]";
        cout << endl;
        cout << "[--- MENU LAPORAN & REKAP DATA ---]";
        cout << endl;
        cout << "[---------------------------------]";
        cout << endl;
        cout << "1. Laporan Data Siswa";
        cout << endl;
        cout << "2. Laporan Data Pengajar";
        cout << endl;
        cout << "3. Laporan Nilai";
        cout << endl;
        cout << "4. Laporan Kehadiran";
        cout << endl;
        cout << "5. Ekspor Semua Laporan ke File";
        cout << endl;
        cout << "6. Kembali";
        cout << endl;
        cout << "[---------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) 
        {
            case 1: 
                laporanDataSiswa(); 
                break;
            case 2: 
                laporanDataPengajar(); 
                break;
            case 3: 
                laporanDataNilai(); 
                break;
            case 4:    
                laporanDataKehadiran(); 
                break;
            case 5: 
                eksporSemuaLaporan(); 
                break;
            case 6: 
                cout << "Kembali...";
                cout << endl; 
                break;
            default: 
                cout << "Pilihan tidak valid!";
                cout << endl; 
                break;
        }

    } while (pilih != 6);
}

void Admin::menuManajemenKelas() {
    int pilih;
    do {
        cout << "\n========== MANAJEMEN KELAS ==========\n";
        cout << "1. Lihat Semua Pendaftaran\n";
        cout << "2. Proses Pendaftaran\n";
        cout << "3. Lihat Kelas Aktif\n";
        cout << "4. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilih;
        
        switch(pilih) {
            case 1:
                kelasManager->lihatSemuaPendaftaran();
                break;
            case 2:
                prosesPendaftaranKelas();
                break;
            case 3:
                kelasManager->lihatKelasAktif();
                break;
            case 4:
                cout << "Kembali...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while(pilih != 4);
}

void Admin::prosesPendaftaranKelas() {
    string id;
    char konfirmasi;
    
    cout << "\nMasukkan ID Pendaftaran: ";
    cin >> id;
    
    cout << "Terima (Y) atau Tolak (N)? ";
    cin >> konfirmasi;
    
    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        kelasManager->prosesPendaftaran(id, true);
    } else if (konfirmasi == 'N' || konfirmasi == 'n') {
        kelasManager->prosesPendaftaran(id, false);
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

void Admin::loadKeuangan() 
{
    ifstream file("data_keuangan.txt");
    if (!file.is_open()) 
    {
        return;
    }

    string id;   
    long long int nik;           // siswa
    string jenis;         // spp, modul, les, dll
    int jumlah;           
    string tanggal;       
    string status; 
    
    // Helper untuk konversi
    string nikStr, jumlahStr;

    while (getline(file, id, '|')) 
    {
    	if (id.empty() || id == "\n") break;

        getline(file, nikStr, '|');    // Baca NIK
        getline(file, jenis, '|');     // Baca Jenis (aman ada spasi)
        getline(file, jumlahStr, '|'); // Baca Jumlah
        getline(file, tanggal, '|');   // Baca Tanggal
        getline(file, status);         // Baca Status sampai enter

        try {
            nik = stoll(nikStr);
            jumlah = stoi(jumlahStr);
        } catch (...) {
            continue; // Skip data rusak
        }
        
        KeuanganNode* k = new KeuanganNode;
        k->idTransaksi = id;
        k->nik = nik;
        k->jenis = jenis;
        k->jumlah = jumlah;
        k->tanggal = tanggal;
        k->status = status;
        k->next = nullptr;

        if (!headKeuangan) 
        {
            headKeuangan = k;
        } else {
            KeuanganNode* cur = headKeuangan;
            while (cur->next) 
            {
                cur = cur->next;
            }
            cur->next = k;
        }
    }

    file.close();
}

void Admin::simpanKeuanganKeFIle(const KeuanganNode* k) 
{
    ofstream file("data_keuangan.txt", ios::app);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka data_keuangan.txt";
        cout << endl;
        return;
    }

    file << k->idTransaksi << "|"
         << k->nik << "|"
         << k->jenis << "|"
         << k->jumlah << "|"
         << k->tanggal << "|"
         << k->status << endl;

    file.close();
}

void Admin::ubahKeuanganFile() 
{
    ofstream file("data_keuangan.txt", ios::trunc);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka data_keuangan.txt";
        cout << endl;
        return;
    }

    KeuanganNode* cur = headKeuangan;
    while (cur) 
    {
        file << cur->idTransaksi << "|"
             << cur->nik << "|"
             << cur->jenis << "|"
             << cur->jumlah << "|"
             << cur->tanggal << "|"
             << cur->status << endl;
        cur = cur->next;
    }

    file.close();
}

KeuanganNode* Admin::cariKeuanganDariId(const string& id) 
{
    KeuanganNode* cur = headKeuangan;
    while (cur) 
    {
        if (cur->idTransaksi == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

void Admin::tambahPembayaran() 
{
    cout << endl;
    cout << "[-------------------------]";
    cout << endl;
    cout << "[--- TAMBAH PEMBAYARAN ---]";
    cout << endl;
    cout << "[-------------------------]";
    cout << endl;

    string id;   
    long  long nik;           // siswa
    string jenis;         // spp, modul, les, dll
    int jumlah;           
    string tanggal;       
    string status; 

    cout << "ID Transaksi: ";
    cin >> id;

    if (cariKeuanganDariId(id)) 
    {
        cout << "ID Transaksi sudah ada!";
        cout << endl;
        return;
    }

    cout << "NIK Siswa: ";
    cin >> nik;

    if (!cariDariNik(nik)) 
    {
        cout << "Siswa tidak ditemukan!";
        cout << endl;
        return;
    }

    cout << "Jenis Pembayaran (misal: SPP, Modul, Les): ";
    cin >> jenis;

    cout << "Jumlah (angka): ";
    cin >> jumlah;

    cout << "Tanggal (YYYY-MM-DD): ";
    cin >> tanggal;

    cout << "Status (Lunas / Belum_Lunas): ";
    cin >> status;

    KeuanganNode* k = new KeuanganNode;
    k->idTransaksi = id;
    k->nik = nik;
    k->jenis = jenis;
    k->jumlah = jumlah;
    k->tanggal = tanggal;
    k->status = status;
    k->next = nullptr;

    if (!headKeuangan) 
    {
        headKeuangan = k;
    } else {
        KeuanganNode* cur = headKeuangan;
        while (cur->next) 
        {
            cur = cur->next;
        }
        cur->next = k;
    }

    simpanKeuanganKeFIle(k);

    cout << "Transaksi pembayaran berhasil ditambahkan!";
    cout << endl;
}

void Admin::lihatDaftarPembayaran() 
{
    cout << endl;
    cout << "[" << string(90, '-') << "]" << endl;
    cout << "[" << setw(45) << "DAFTAR PEMBAYARAN" << setw(45) << "]" << endl;
    cout << "[" << string(90, '-') << "]" << endl;

    if (!headKeuangan) 
    {
        cout << "Belum ada data pembayaran.";
        cout << endl;
        return;
    }

    cout << left 
	     << setw(8) << "ID" 
	     << setw(20) << "NIK" 
	     << setw(20) << "Jenis" 
	     << setw(15) << "Jumlah" 
	     << setw(15) << "Tanggal" 
	     << setw(12) << "Status" 
	     << endl;
	cout << string(90, '-') << endl;

    KeuanganNode* cur = headKeuangan;
    while (cur) 
    {
        cout << left
         << setw(8) << cur->idTransaksi
         << setw(20) << cur->nik
         << setw(20) << cur->jenis
         << setw(15) << cur->jumlah
         << setw(15) << cur->tanggal
         << setw(12) << cur->status;
    cout << endl;
        cur = cur->next;
    }
}

void Admin::laporanKeuanganSiswa() 
{
    cout << endl;
    cout << "[-----------------------------]";
    cout << endl;
    cout << "[--- LAPORAN KUANGAN SISWA ---]";
    cout << endl;
    cout << "[-----------------------------]";
    cout << endl;

    long long int nik;
    cout << "Masukkan NIK: ";
    cin >> nik;

    if (!cariDariNik(nik)) 
    {
        cout << "Siswa tidak ditemukan!";
        cout << endl;
        return;
    }

    int total = 0;
    int lunas = 0;
    int belum = 0;

    KeuanganNode* cur = headKeuangan;
    bool ditemukan = false;

    cout << "\nID\t\tJenis\t\tJumlah\t\tTanggal\t\tStatus";
    cout << endl;

    while (cur) 
    {
        if (cur->nik == nik) 
        {
            ditemukan = true;
            cout << cur->idTransaksi << "\t\t"
                 << cur->jenis << "\t\t"
                 << cur->jumlah << "\t\t"
                 << cur->tanggal << "\t\t"
                 << cur->status;
            cout << endl;

            total += cur->jumlah;

            if (cur->status == "Lunas") 
            {
                lunas++;
            } else { 
                belum++;
            }
        }
        cur = cur->next;
    }

    if (!ditemukan) {
        cout << "Tidak ada transaksi untuk siswa ini.\n";
        return;
    }

    cout << endl;
    cout << "\nTotal Transaksi  : " << total;
    cout << endl;
    cout << "Lunas            : " << lunas;
    cout << endl;
    cout << "Belum Lunas      : " << belum;
    cout << endl;
}

void Admin::updateStatusPembayaran() 
{
    cout << endl;
    cout << "[--------------------------------]";
    cout << endl;
    cout << "[--- UPDATE STATUS PEMBAYARAN ---]";
    cout << endl;
    cout << "[--------------------------------]";
    cout << endl;

    string id;
    cout << "Masukkan ID Transaksi: ";
    cin >> id;

    KeuanganNode* k = cariKeuanganDariId(id);
    if (!k) 
    {
        cout << "Transaksi tidak ditemukan!";
        cout << endl;
        return;
    }

    cout << "Status saat ini: " << k->status;
    cout << endl;
    cout << "Masukkan status baru (Lunas / Belum_Lunas): ";

    string status;
    cin >> status;

    k->status = status;

    ubahKeuanganFile();
    cout << "Status pembayaran berhasil diperbarui!";
    cout << endl;
}

void Admin::menuManajemenKeuangan() 
{
    int pilih;
    do 
    {
        cout << endl;
        cout << "[--------------------------------]";
        cout << endl;
        cout << "[---    MANAJEMEN KEUANGAN    ---]";
        cout << endl;
        cout << "[--------------------------------]";
        cout << endl;
        cout << "1. Tambah Pembayaran";
        cout << endl;
        cout << "2. Lihat Daftar Pembayaran";
        cout << endl;
        cout << "3. Laporan Keuangan Siswa";
        cout << endl;
        cout << "4. Update Status Pembayaran";
        cout << endl;
        cout << "5. Kembali";
        cout << endl;
        cout << "[--------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) 
        {
            case 1: 
                tambahPembayaran(); 
                break;
            case 2: 
                lihatDaftarPembayaran(); 
                break;
            case 3: 
                laporanKeuanganSiswa(); 
                break;
            case 4: 
                updateStatusPembayaran(); 
                break;
            case 5: 
                cout << "Kembali...";
                cout << endl; 
                break;
            default: 
                cout << "Pilihan tidak valid!";
                cout <<endl;
                break;
        }
    } while (pilih != 5);
}


void Admin::loadAbsensi() 
{
    // perbaikan nama file
    ifstream file("data_absensi.txt");
    if (!file.is_open()) 
    {
        return;
    }

    long long int nik; // Isiswa
    string tanggal;     
    string status; 
    
    string nikStr;

    while (getline(file, nikStr, '|')) 
    {
    	// Hindari error baris kosong
        if (nikStr.empty() || nikStr == "\n") break;

        getline(file, tanggal, '|'); // Baca tanggal
        getline(file, status);       // Baca status sampai enter

        try {
            nik = stoll(nikStr);     // Konversi string ke angka
        } catch (...) {
            continue; // Lewati jika data korup
        }
        
        AbsensiNode* a = new AbsensiNode;
        a->nik = nik;
        a->tanggal = tanggal;
        a->status = status;
        a->next = nullptr;

        if (!headAbsensi) 
        {
            headAbsensi = a;
        } else {
            AbsensiNode* cur = headAbsensi;
            while (cur->next) 
            {
                cur = cur->next;
            }
            cur->next = a;
        }
    }

    file.close();
}

void Admin::simpanAbsensikeFile(const AbsensiNode* a) 
{
    ofstream file("data_absensi.txt", ios::app);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka absensi.txt";
        cout << endl;
        return;
    }
    
    file << a->nik << "|"
         << a->tanggal << "|"
         << a->status 
		 << endl;
    file.close();
}

void Admin::inputAbsensi() 
{
    long long nik; // Isiswa
    string tanggal;     
    string status; 

    cout << endl;
    cout << "[---------------------------------]";
    cout << endl;
    cout << "[---    INPUT ABSENSI SISWA    ---]";
    cout << endl;
    cout << "[---------------------------------]";
    cout << endl;
    cout << "Masukkan NIK: ";
    cin >> nik;

    // gunakan fungsi yang benar untuk mengecek keberadaan siswa
    if (!cariDariNik(nik)) 
    {
        cout << "Siswa tidak ditemukan!";
        cout << endl;
        return;
    }

    cout << "Tanggal (YYYY-MM-DD): ";
    cin >> tanggal;

    cout << "Status: ";
    cout << endl;
    cout << "H = Hadir";
    cout << endl;
    cout << "I = Izin" ;
    cout << endl;
    cout << "S = Sakit";
    cout << endl;
    cout << "A = Alpha";
    cout << endl;
    cout << "Pilih status: ";
    cin >> status;

    if (status != "H" && status != "I" && status != "S" && status != "A") 
    {
        cout << "Status tidak valid!";
        cout << endl;
        return;
    }

    AbsensiNode* a = new AbsensiNode;
    a->nik = nik;
    a->tanggal = tanggal;
    a->status = status;
    a->next = nullptr;

    if (!headAbsensi) 
    {
        headAbsensi = a;
    } else {
        AbsensiNode* cur = headAbsensi;
        while (cur->next) 
        {
            cur = cur->next;
        }
        cur->next = a;
    }

    simpanAbsensikeFile(a);

    cout << "Absensi berhasil dicatat!";
    cout << endl;
}

void Admin::lihatAbsensi() 
{
	string title = "DAFTAR ABSENSI";
    cout << endl;
    cout << "[" << string(60 - 2, '-') << "]" << endl;

    cout << "["
         << setw((60 - 2 + title.length()) / 2) << title
         << setw((60 - 2 - title.length()) / 2) << ""
         << "]" << endl;

    cout << "[" << string(60 - 2, '-') << "]" << endl;
    cout << endl;

    if (!headAbsensi) 
    {
        cout << "Belum ada data absensi.";
        cout << endl;
        return;
    }

    cout << left 
	     << setw(20) << "NIK" 
	     << setw(25) << "Tanggal" 
	     << setw(15) << "Status" 
	     << endl;
	cout << string(60, '-') << endl; // Garis pemisah

    AbsensiNode* cur = headAbsensi;
    while (cur) 
    {
        cout << left
	         << setw(20) << cur->nik
	         << setw(25) << cur->tanggal
	         << setw(15) << cur->status;
	    cout << endl;
        cur = cur->next;
    }
}

void Admin::laporanKehadiranBulanan() 
{
    cout << endl;
	cout << "[" << string(70, '-') << "]" << endl;
	cout << left << setw(35) << " " << "LAPORAN KEHADIRAN SISWA" << setw(35) << " " << endl;
	cout << "[" << string(70, '-') << "]" << endl;
	cout << endl;

    string bulan;
    string tahun;
    cout << "Masukkan bulan (MM): ";
    cin >> bulan;
    cout << "Masukkan tahun (YYYY): ";
    cin >> tahun;

    bool ditemukan = false;

    AbsensiNode* cur = headAbsensi;
    cout << left
     << setw(20) << "NIK"
     << setw(15) << "Tanggal"
     << setw(10) << "Status"
     << endl;
	cout << string(45, '-') << endl;
    
	while (cur) 
    {
        // tanggal format YYYY-MM-DD: ambil MM
        if (cur->tanggal.size() >= 7) {
            string bulanData = cur->tanggal.substr(5, 2);
            string tahunData = cur->tanggal.substr(0, 4);

            if (bulanData == bulan && tahunData == tahun) 
            {
                cout << left
			         << setw(20) << cur->nik
			         << setw(15) << cur->tanggal
			         << setw(10) << cur->status
			         << endl;
			    cout << string(45, '-') << endl;

                ditemukan = true;
            }
        }
        cur = cur->next;
    }

    if (!ditemukan) {
        cout << "Tidak ada data absensi pada bulan tersebut.";
        cout << endl;
    }
}

void Admin::hitungPersentaseKehadiran() 
{
    cout << endl;
    cout << "[-----------------------------------]";
    cout << endl;
    cout << "[--- HITUNG PRESENTASE KEHADIRAN ---]";
    cout << endl;
    cout << "[-----------------------------------]";
    cout << endl;

    long long int nik;
    cout << "Masukkan NIK: ";
    cin >> nik;

    int total = 0;
    int hadir = 0;

    AbsensiNode* cur = headAbsensi;

    while (cur) {
        if (cur->nik == nik) 
        {
            total++;
            if (cur->status == "H") hadir++;
        }
        cur = cur->next;
    }

    if (total == 0) 
    {
        cout << "Tidak ada data absensi untuk siswa tersebut.";
        cout << endl;
        return;
    }

    double persen = (double)hadir * 100.0 / total;

    cout << "Total Pertemuan: " << total;
    cout << endl;
    cout << "Total Hadir    : " << hadir;
    cout << endl;
    cout << "Persentase     : " << persen << "%";
    cout << endl;
}

void Admin::menuManajemenAbsensi() 
{
    int pilih;
    do 
    {
        cout << endl;
        cout << "[-------------------------------------]";
        cout << endl;
        cout << "[--- MANAJEMEN ABSENSI & KEHADIRAN ---]";
        cout << endl;
        cout << "[-------------------------------------]";
        cout << endl;
        cout << "1. Input Absensi";
        cout << endl;
        cout << "2. Lihat Daftar Absensi";
        cout << endl;
        cout << "3. Laporan Kehadiran Per Bulan";
        cout << endl;
        cout << "4. Hitung Persentase Kehadiran";
        cout << endl;
        cout << "5. Kembali";
        cout << endl;
        cout << "[-------------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) 
        {
            case 1: 
                inputAbsensi(); 
                break;
            case 2: 
                lihatAbsensi(); 
                break;
            case 3: 
                laporanKehadiranBulanan(); 
                break;
            case 4: 
                hitungPersentaseKehadiran(); 
                break;
            case 5: 
                cout << "Kembali...";
                cout << endl; 
                break;
            default: 
                cout << "Pilihan tidak valid!";
                cout << endl;
                break;
        }

    } while (pilih != 5);
}

void Admin::loadNilai() 
{
    ifstream file("data_nilai.txt");
    if (!file.is_open())
    {
        return;
    }

    long long int nik;           
    string mapel;         
    int nilai;            
    string tanggal;  

	string nikStr, nilaiStr;
	
    while (getline(file, nikStr, '|')) 
    {
    	if (nikStr.empty()) break; // Cek baris kosong

        getline(file, mapel, '|');     // Baca Mapel (Bisa spasi)
        getline(file, nilaiStr, '|');  // Baca Nilai string
        getline(file, tanggal);        // Baca Tanggal sampai enter

        try {
            nik = stoll(nikStr);       // Convert string ke angka
            nilai = stoi(nilaiStr);    // Convert string ke angka
        } catch (...) { continue; }    // Skip jika data rusak
        
        NilaiNode* n = new NilaiNode;
        n->nik = nik;
        n->mapel = mapel;
        n->nilai = nilai;
        n->tanggal = tanggal;
        n->next = nullptr;

        if (!headNilai) 
        {
            headNilai = n;
        } else {
            NilaiNode* cur = headNilai;
            while (cur->next) cur = cur->next;
            cur->next = n;
        }
    }

    file.close();
}

void Admin::simpanNilaiKeFile(const NilaiNode* n) 
{
    ofstream file("data_nilai.txt", ios::app);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka data_nilai.txt";
        cout << endl;
        return;
    }
    
    file << n->nik << "|" 
         << n->mapel << "|"
         << n->nilai << "|"
         << n->tanggal << endl;
    file.close();
}

void Admin::UbahNilaiFile() 
{
    ofstream file("data_nilai.txt", ios::trunc);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka data_nilai.txt";
        cout << endl;
        return;
    }

    NilaiNode* cur = headNilai;
    while (cur) 
    {
        file << cur->nik << "|" 
             << cur->mapel << "|"
             << cur->nilai << "|"
             << cur->tanggal << endl;
        cur = cur->next;
    }

    file.close();
}

NilaiNode* Admin::cariNilai(const long long& nik, const string& mapel) 
{
    NilaiNode* cur = headNilai;
    while (cur) 
    {
        if (cur->nik == nik && cur->mapel == mapel)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

void Admin::tambahNilai() 
{
    cout << endl;
    cout << "[--------------------------]";
    cout << endl;
    cout << "[--- TAMBAH NILAI SISWA ---]";
    cout << endl;
    cout << "[--------------------------]";
    cout << endl;
    
    long long int nik;           
    string mapel;         
    int nilai;            
    string tanggal;

    cout << "Masukkan NIK: ";
    cin >> nik;

    // cek siswa menggunakan cariDariNik
    if (!cariDariNik(nik)) 
    {
        cout << "Siswa tidak ditemukan!";
        cout << endl;
        return;
    }

    cout << "Mata Pelajaran: ";
    cin >> ws;
    getline(cin, mapel);

    cout << "Nilai (0-100): ";
    cin >> nilai;

    if (nilai < 0 || nilai > 100) 
    {
        cout << "Nilai tidak valid!";
        cout << endl;
        return;
    }

    cout << "Tanggal (YYYY-MM-DD): ";
    cin >> tanggal;

    NilaiNode* n = new NilaiNode;
    n->nik = nik;
    n->mapel = mapel;
    n->nilai = nilai;
    n->tanggal = tanggal;
    n->next = nullptr;

    if (!headNilai) 
    {
        headNilai = n;
    } else {
        NilaiNode* cur = headNilai;
        while (cur->next)  
        {
            cur = cur->next;
        }
        cur->next = n;
    }

    simpanNilaiKeFile(n);

    cout << "Nilai berhasil ditambahkan!";
    cout << endl;
}

void Admin::lihatSemuaNilai() 
{
    string title = "DAFTAR SEMUA NILAI";

	cout << endl;
	cout << "[" << string(75 - 2, '-') << "]" << endl;
	cout << "["
     	 << setw((75 - 2 + title.length()) / 2) << title
     	 << setw((75 - 2 - title.length()) / 2) << ""
     	 << "]" << endl;
	cout << "[" << string(75 - 2, '-') << "]" << endl;

    if (!headNilai) 
    {
        cout << "Tidak ada data nilai.";
        cout << endl;
        return;
    }

    cout << left
     << setw(20) << "NIK Siswa"
     << setw(25) << "Mata Pelajaran"
     << setw(10) << "Nilai"
     << setw(15) << "Tanggal"
     << endl;
	cout << string(75, '-') << endl;

    NilaiNode* cur = headNilai;
    while (cur) 
    {
        cout << left
	         << setw(20) << cur->nik
	         << setw(25) << cur->mapel
	         << setw(10) << cur->nilai
	         << setw(15) << cur->tanggal;
	    cout << endl; 
        cur = cur->next;
    }
}

void Admin::evaluasiPerMapel() 
{
    cout << endl;
    cout << "[--------------------------------]";
    cout << endl;
    cout << "[--- EVALUASI NILAI PER MAPEL ---]";
    cout << endl;
    cout << "[--------------------------------]";
    cout << endl;

    string mapel;
    cout << "Masukkan mata pelajaran: ";
    cin >> mapel;

    int total = 0; 
    int count = 0;
    int maxNilai = -1;
    int minNilai = 101;

    NilaiNode* cur = headNilai;

    while (cur) 
    {
        if (cur->mapel == mapel) 
        {
            total += cur->nilai;
            count++;

            if (cur->nilai > maxNilai) 
            {
                maxNilai = cur->nilai;
            }

            if (cur->nilai < minNilai) 
            {
                minNilai = cur->nilai;
            }
        }
        cur = cur->next;
    }

    if (count == 0) 
    {
        cout << "Tidak ada nilai untuk mapel tersebut.";
        cout << endl;
        return;
    }

    cout << endl;
    cout << "[---       Hasil Evaluasi       ---]";
    cout << endl;
    cout << "Jumlah Siswa\t: " << count;
    cout << endl;
    cout << "Rata-rata\t: " << (total / count);
    cout << endl;
    cout << "Nilai Tertinggi\t: " << maxNilai;
    cout << endl;
    cout << "Nilai Terendah\t: " << minNilai;
    cout << endl;
}

void Admin::menuManajemenNilai() 
{
    int pilih;
    do {
        cout << endl;
        cout << "[--------------------------------]";
        cout << endl;
        cout << "[---     MANAJEMEN NILAI      ---]";
        cout << endl;
        cout << "[--------------------------------]";
        cout << endl;
        
        cout << "1. Tambah Nilai";
        cout << endl;
        cout << "2. Lihat Semua Nilai";
        cout << endl;
        cout << "3. Evaluasi Siswa per Mapel";
        cout << endl;
        cout << "4. Kembali";
        cout << endl;
        cout << "[--------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) 
        {
            case 1: 
                tambahNilai(); 
                break;
            case 2: 
                lihatSemuaNilai(); 
                break;
            case 3: 
                evaluasiPerMapel(); 
                break;
            case 4: 
                cout << "Kembali..."; 
                cout << endl;
                break;
            default: 
                cout << "Pilihan tidak valid!";
                cout << endl;
                break;
        }

    } while (pilih != 4);
}


void Admin::loadJadwal() 
{
    ifstream file("data_jadwal.txt");
    if (!file.is_open()) return;

    string id; 
    string hari; 
    string jam; 
    string mapel; 
    long long int nik; 
    string kelas;
    
    string nikStr;

    while (getline(file, id, '|')) 
    {
    	getline(file, hari, '|');     // Baca hari
        getline(file, jam, '|');      // Baca jam
        getline(file, mapel, '|');    // Baca mapel (aman meski ada spasi)
        
        getline(file, nikStr, '|');   // Baca NIK sebagai string dulu
        // Cek jika baris kosong (biasanya di akhir file)
        if (id == "" || nikStr == "") break; 
        
        nik = stoll(nikStr);          // Ubah string NIK ke angka long long

        getline(file, kelas);
        
        JadwalNode* j = new JadwalNode;
        j->idJadwal = id;
        j->hari = hari;
        j->jam = jam;
        j->mapel = mapel;
        j->pengajarNIK = nik;
        j->kelas = kelas;
        j->next = nullptr;

        if (!headJadwal) 
        {
            headJadwal = j;
        } else {
            JadwalNode* cur = headJadwal;
            while (cur->next) cur = cur->next;
            cur->next = j;
        }
    }
    file.close();
}

void Admin::simpanJadwalKeFile(const JadwalNode* j) 
{
    ofstream file("data_jadwal.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka data_jadwal.txt\n";
        return;
    }
    file << j->idJadwal << "|" 
         << j->hari << "|"
         << j->jam << "|"
         << j->mapel << "|"
         << j->pengajarNIK << "|"
         << j->kelas << endl;
    file.close();
}

void Admin::UbahJadwalFile() 
{
    ofstream file("data_jadwal.txt", ios::trunc);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka data_jadwal.txt";
        cout << endl;
        return;
    }
    JadwalNode* j = headJadwal;
    while (j) 
    {
        file << j->idJadwal << "|"
             << j->hari << "|"
             << j->jam << "|"
             << j->mapel << "|"
             << j->pengajarNIK << "|"
             << j->kelas << "\n";
        j = j->next;
    }
    file.close();
}

JadwalNode* Admin::CariJadwalDariId(const string& id) 
{
    JadwalNode* j = headJadwal;
    while (j) 
    {
        if (j->idJadwal == id)
        {
            return j;
        } 
        j = j->next;
    }
    return nullptr;
}

void Admin::tambahJadwal() 
{
    cout << endl;
    cout << "[-------------------------------]";
    cout << endl;
    cout << "[--- Tambah Jadwal Bimbingan ---]";
    cout << endl;
    cout << "[-------------------------------]";
    cout << endl;

    string id; 
    string hari; 
    string jam; 
    string mapel; 
    long long int nik; 
    string kelas;

    cout << "ID Jadwal: ";
    cin >> id;
    if (CariJadwalDariId(id)) 
    {
        cout << "ID Jadwal sudah ada!";
        cout << endl;
        return;
    }

    cout << "Hari (Senin-Sabtu): ";
    cin >> hari;
    cout << "Jam (jam:menit): ";
    cin >> jam;
    cout << "Mata Pelajaran: ";
    cin.ignore();
    getline(cin, mapel);
    cout << "NIK Pengajar: ";
    cin >> nik;
    cout << "Kelas: ";
    cin >> kelas;

    JadwalNode* j = new JadwalNode;
    j->idJadwal = id;
    j->hari = hari;
    j->jam = jam;
    j->mapel = mapel;
    j->pengajarNIK = nik;
    j->kelas = kelas;
    j->next = nullptr;

    if (!headJadwal) headJadwal = j;
    else {
        JadwalNode* cur = headJadwal;
        while (cur->next) cur = cur->next;
        cur->next = j;
    }

    simpanJadwalKeFile(j);

    cout << "Jadwal berhasil ditambahkan!";
    cout << endl;
}

void Admin::lihatSemuaJadwal() 
{
	string title = "Daftar Semua Jadwal";
    cout << endl;
	cout << string(85, '-') << endl;
    cout << endl;
    cout << setw((85 + title.length()) / 2) << title << endl;
    cout << endl;
	cout << string(85, '-') << endl;
    cout << endl;

    if (!headJadwal) 
    {
        cout << "Belum ada jadwal.";
        cout << endl;
        return;
    }

    JadwalNode* j = headJadwal;
    cout << left
     << setw(8)  << "ID"
     << setw(12) << "Hari"
     << setw(15) << "Jam"
     << setw(22) << "Mata Pelajaran"
     << setw(18) << "Pengajar"
     << setw(10) << "Kelas"
     << endl;

	cout << string(85, '-') << endl;
    cout << endl;
    while (j) 
    {
        cout << left
         << setw(8) << j->idJadwal
         << setw(12) << j->hari  
         << setw(15) << j->jam
         << setw(22) << j->mapel
         << setw(18) << j->pengajarNIK
         << setw(10) << j->kelas;
    cout << endl;
        j = j->next;
    }
}

void Admin::cariJadwal() 
{
    string id;
    cout << endl;
    cout << "[-------------------------------]";
    cout << endl;
    cout << "[---       Cari Jadwal       ---]";
    cout << endl;
    cout << "[-------------------------------]";
    
    cout << "Masukkan ID Jadwal: ";
    cin >> id;

    JadwalNode* j = CariJadwalDariId(id);
    if (!j) 
    {
        cout << "Jadwal tidak ditemukan.";
        cout << endl;
        return;
    }

    cout << endl;
    cout << "[---        Ditemukan        ---]";
    cout << endl;
    cout << "ID\t: " << j->idJadwal;
    cout << endl;
    cout << "Hari\t: " << j->hari;
    cout << endl;
    cout << "Jam\t: " << j->jam;
    cout << endl;
    cout << "Mapel\t: " << j->mapel;
    cout << endl;
    cout << "NIK\t: " << j->pengajarNIK;
    cout << endl;
    cout << "Kelas\t: " << j->kelas;
    cout << endl;
}

void Admin::menuManajemenJadwal() 
{
    int pilih;
    do 
    {
        cout << endl;
        cout << "[----------------------------------]";
        cout << endl;
        cout << "[--- Manajemen Jadwal Bimbingan ---]";
        cout << endl;
        cout << "[----------------------------------]";
        cout << endl;

        cout << "1. Tambah Jadwal";
        cout << endl;
        cout << "2. Lihat Semua Jadwal";
        cout << endl;
        cout << "3. Cari Jadwal";
        cout << endl;
        cout << "4. Kembali";
        cout << endl;
        cout << "[----------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) 
        {
            case 1: 
                tambahJadwal(); 
                break;
            case 2: 
                lihatSemuaJadwal(); 
                break;
            case 3: 
                cariJadwal(); 
                break;
            case 4: 
                cout << "Kembali..."; 
                cout << endl;
                break;
            default: 
                cout << "Pilihan tidak valid!";
                cout << endl;
                break;
        }
    } while (pilih != 4);
}

void Admin::loadPengajar() 
{
    ifstream file("data_pengajar.txt");
    if (!file.is_open())
    {
        return;
    }

    long long nik;
    string nama;
    string mataPelajaran;
    string jadwal;
    string alamat;
    long long noTelp;

	string nikStr, noTelpStr;
	
    while (getline(file, nikStr, '|'))
    {
    	if(nikStr.empty()) break; // Menghindari baris kosong terakhir
        nik = stoll(nikStr);

        getline(file, nama, '|');   // Baca Nama sampai ketemu '#'
        getline(file, mataPelajaran, '|');  // Baca Kelas sampai ketemu '#'
        getline(file, jadwal, '|'); // Baca Alamat sampai ketemu '#'
        getline(file, alamat, '|'); // Baca Alamat sampai ketemu '#'
        
        getline(file, noTelpStr);   // Baca sisanya (No Telp) sampai enter
        noTelp = stoll(noTelpStr);
        
        NodePengajar* t = new NodePengajar;
        t->nik = nik;
        t->nama = nama;
        t->mataPelajaran = mataPelajaran;
        t->jadwal = jadwal;
        t->alamat = alamat;
        t->noTelp = noTelp;
        t->next = nullptr;

        if (!headPengajar)
        {
            headPengajar = t;
        } else {
            NodePengajar* temp = headPengajar;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = t;
        }
    }

    file.close();
}

NodePengajar* Admin::cariPengajarDariNik(const long long& nik) 
{
    NodePengajar* t = headPengajar;
    while (t)
    {
        if (t->nik == nik)
        {
            return t;
        }
        t = t->next;
    }

    return nullptr;
}

void Admin::simpanPengajarKeFile(const NodePengajar* t)
{
    ofstream file("data_pengajar.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Gagal membuka data_pengajar.txt";
        cout << endl;
        return;
    }

    file << t->nik << "|" 
         << t->nama << "|" 
         << t->mataPelajaran << "|" 
         << t->jadwal << "|" 
         << t->alamat << "|" 
         << t->noTelp 
		 << endl;
    file.close();
}

void Admin::ubahFilePengajar()
{
    ofstream file("data_pengajar.txt", ios::trunc);
    if (!file.is_open())
    {
        cout << "Gagal membuka data_pengajar.txt.";
        cout << endl;
        return;
    }

    NodePengajar* t = headPengajar;
    while (t) 
    {
        file << t->nik << " " << t->nama << " " << t->mataPelajaran 
             << " " << t->jadwal << " " << t->alamat << " " << t->noTelp << endl;
        t = t->next;
    }

    file.close();
}

void Admin::tambahPengajar()
{
    long long nik;
    string nama;
    string mataPelajaran;
    string jadwal;
    string alamat;
    long long noTelp;

    cout << endl;
    cout << "[---------------------------------]";
    cout << endl;
    cout << "[---      TAMBAH PENGAJAR      ---]";
    cout << endl;
    cout << "[---------------------------------]";
    cout << endl;

    cout << "NIK: ";
    cin >> nik;
    if (cariPengajarDariNik(nik))
    {
        cout << "NIK sudah ada!";
        cout << endl;
        return;
    }

    cout << "Nama: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Mata Pelajaran: ";
    getline(cin, mataPelajaran);
    cout << "Jadwal: ";
    getline(cin, jadwal);
    cout << "Alamat: ";
    getline(cin, alamat);
    cout << "No. Telp: ";
    cin >> noTelp;

    NodePengajar* t = new NodePengajar;
    t->nik = nik;
    t->nama = nama;
    t->mataPelajaran= mataPelajaran;
    t->jadwal = jadwal;
    t->alamat = alamat;
    t->noTelp = noTelp;
    t->next = nullptr;

    if (!headPengajar) 
    {
        headPengajar = t;
    } else {
        NodePengajar* cur = headPengajar;
        while (cur->next)
        {
            cur = cur->next;
        }
        cur->next = t;
    }

    simpanPengajarKeFile(t);
    cout << "Pengajar berhasil ditambahkan!";
    cout << endl;
}

void Admin::daftarPengajar()
{
    cout << endl;
    cout << "[" << string(120, '-') << "]" << endl;

    string title = "DAFTAR PENGAJAR";
    cout << "["
        << setw((120 + title.length()) / 2) << title
        << setw((120 - title.length()) / 2) << ""
        << "]" << endl;

    cout << "[" << string(120, '-') << "]" << endl << endl;

    if (!headPengajar)
    {
        cout << "Belum ada data pengajar.";
        cout << endl;
        return;
    }

    cout << left
     << setw(20) << "NIK"
     << setw(20) << "Nama"
     << setw(20) << "Mata Pelajaran"
     << setw(15) << "Jadwal"
     << setw(30) << "Alamat"
     << setw(15) << "No. Telp"
     << endl;
    cout << string(120, '-') << endl;


    NodePengajar* t = headPengajar;
    while(t)
    {
        cout << left
            << setw(20) << t->nik
            << setw(20) << t->nama
            << setw(20) << t->mataPelajaran
            << setw(15) << t->jadwal
            << setw(30) << t->alamat
            << setw(15) << t->noTelp
            << endl;

        t = t->next;
    }
}

void Admin::cariPengajarDariMapel()
{
    cout << endl;
    cout << "[-----------------------------------------]";
    cout << endl;
    cout << "[--- CARI PENGAJAR DARI MATA PELAJARAN ---]";
    cout << endl;
    cout << "[-----------------------------------------]";
    cout << endl;

    string mataPelajaran;
    cout << "Masukkan mata pelajaran: ";
    cin >> mataPelajaran;

    NodePengajar* t = headPengajar;
    bool ditemukan = false;

    cout << endl;
    cout << "Pengajar yang mengajar " << mataPelajaran << ": ";
    cout << endl;
    while (t)
    {
        if (t->mataPelajaran == mataPelajaran)
        {
            cout << "- " << t->nama << " (NIK: " << t->nik << ", No. Telp: " << t->noTelp;
            cout << endl;
            ditemukan = true;
        }
        t = t->next;
    }

    if (!ditemukan)
    {
        cout << "Tidak ditemukan pengajar dengan mata pelajaran tersebut.";
        cout << endl;
    }
}

void Admin::menuManajemenPengajar()
{
    int pilih;
    do
    {
        cout << endl;
        cout << "[-------------------------------------]";
        cout << endl;
        cout << "[---    MANAJEMEN DATA PENGAJAR    ---]";
        cout << endl;
        cout << "[-------------------------------------]";
        cout << endl;

        cout << "1. Tambah Pengajar";
        cout << endl;
        cout << "2. Lihat Daftar Pengajar";
        cout << endl;
        cout << "3. Cari Pengajar";
        cout << endl;
        cout << "4. Kembali";
        cout << endl;
        cout << "[-------------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            tambahPengajar();
            break;
        case 2:
            daftarPengajar();
            break;
        case 3:
            cariPengajarDariMapel();
            break;
        case 4:
            cout << "Kembali...";
            cout << endl;
            break;
        default:
            cout << "Pilihan tidak valid!";
            cout << endl;
            break;
        }
    } while (pilih != 4);
}

void Admin::loadSiswa() {
    ifstream file("data_siswa.txt");
    if (!file.is_open())
    {
        return;
    }

    long long nik;
    string nama;
    string kelas;
    string alamat;
    long long noTelp;
    
	string nikStr, noTelpStr;
	
    while (getline(file, nikStr, '|'))
    {
        if(nikStr.empty()) break; // Menghindari baris kosong terakhir
        nik = stoll(nikStr);

        getline(file, nama, '|');   // Baca Nama sampai ketemu '#'
        getline(file, kelas, '|');  // Baca Kelas sampai ketemu '#'
        getline(file, alamat, '|'); // Baca Alamat sampai ketemu '#'
        
        getline(file, noTelpStr);   // Baca sisanya (No Telp) sampai enter
        noTelp = stoll(noTelpStr);

        // --- Proses pembuatan Node (SAMA SEPERTI KODEMU) ---
        NodeSiswa* n = new NodeSiswa;
        n->nik = nik;
        n->nama = nama;
        n->kelas = kelas;
        n->alamat = alamat;
        n->noTelp = noTelp;
        n->next = nullptr;

        if (!head)
        {
            head = n;
        } else {
            NodeSiswa* temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
    }

    file.close();
}

void Admin::simpanSiswaKeFile(const NodeSiswa* s)
{
    ofstream file("data_siswa.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Gagal membuka file data_siswa.txt.";
        cout << endl;
        return;
    }

    file << s->nik << "|" 
		 << s->nama << "|" 
		 << s->kelas << "|" 
         << s->alamat << "|" 
		 << s->noTelp 
		 << endl;
    file.close();
}

void Admin::ubahFileSiswa()
{
    ofstream file("data_siswa.txt", ios::trunc);
    if (!file.is_open())
    {
        cout << "Gagal membuka file data_siswa.txt.";
        cout << endl;
        return;
    }

    NodeSiswa* temp = head;
    while (temp)
    {
        file << temp->nik << " " << temp->nama << " " << temp->kelas << " " << temp->alamat << " " << temp->noTelp << endl;
        temp = temp->next;
    }

    file.close();
}

NodeSiswa* Admin::cariDariNik(const long long& nik)
{
    NodeSiswa* temp = head;
    while (temp)
    {
        if (temp->nik == nik)
        {
            return temp;
        }
        temp = temp->next;
    }

    return nullptr;
}

void Admin::tambahSiswa()
{
    long long nik;
    string nama;
    string kelas;
    string alamat;
    long long noTelp;

    cout << endl;
    cout << "[--------------------------]";
    cout << endl;
    cout << "[---    TAMBAH SISWA    ---]";
    cout << endl;
    cout << "[--------------------------]";
    cout << endl;
    cout << "NIK\t: ";
    cin >> nik;

    if (cariDariNik(nik))
    {
        cout << "NIK sudah ada. Tidak bisa menambahkan.";
        cout << endl;
        return;
    }

    cout << "Nama\t: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Kelas\t: ";
    getline(cin, kelas);
    cout << "Alamat\t: ";
    getline(cin, alamat);
    cout << "No. Telp\t: ";
    cin >> noTelp;

    NodeSiswa* n = new NodeSiswa;
    n->nik = nik;
    n->nama = nama;
    n->kelas = kelas;
    n->alamat = alamat;
    n->noTelp = noTelp;
    n->next = nullptr;

    if (!head)
    {
        head = n;
    } else {
        NodeSiswa* temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = n;
    }

    simpanSiswaKeFile(n);
    cout << "Siswa berhasil ditambahkan!";
    cout << endl;
}

void Admin::daftarSiswa()
{
    cout << endl;
    cout << "[" << string(100, '-') << "]";
    cout << endl;
    cout << "[" << setw(50 + 13 / 2) << "DAFTAR SISWA" << setw(50 - 13 / 2) << "" << "]";
    cout << endl;
    cout << "[" << string(100, '-') << "]";
    cout << endl;

    if (!head)
    {
        cout << "Belum ada data siswa.";
        cout << endl;
        return;
    }

    NodeSiswa* temp = head;
    cout << left
        << setw(20) << "NIK"
        << setw(20) << "Nama"
        << setw(10) << "Kelas"
        << setw(35) << "Alamat"
        << setw(15) << "No. Telp"
        << endl;
    cout << string(100, '-') << endl;

    while (temp)
    {
    cout << left
        << setw(20) << temp->nik
        << setw(20) << temp->nama
        << setw(10) << temp->kelas
        << setw(35) << temp->alamat
        << setw(15) << temp->noTelp
        << endl;
        temp = temp->next;
    }
}

void Admin::editSiswa()
{
    long long nik;

    cout << endl;
    cout << "[---------------------------]";
    cout << endl;
    cout << "[---   UBAH DATA SISWA   ---]";
    cout << endl;
    cout << "[---------------------------]";
    cout << endl;
    cout << "Masukkan NIK siswa yang akan diubah: ";
    cin >> nik;

    NodeSiswa* s = cariDariNik(nik);
    if(!s)
    {
        cout << "Siswa tidak ditemukan.";
        cout << endl;
        return;
    }

    cout << "Data saat ini: ";
    cout << endl;

    string nama;
    cout << "Masukkan nama baru (atau - untuk tidak diubah): ";
    cin.ignore();
    getline(cin, nama);
    if (nama != "-")
    {
        s->nama = nama;
    }
    
    string kelas;
    cout << "Masukkan kelas baru (atau - untuk tidak diubah): ";
    getline(cin, kelas);
    if (kelas != "-")
    {
        s->kelas = kelas;
    }

    string alamat;
    cout << "Masukkan alamat baru (atau - untuk tidak diubah): ";
    getline(cin, alamat);
    if (alamat != "-")
    {
        s->alamat = alamat;
    }

    long long noTelp;
    cout << "Masukkan No. Telp baru (atau 0 untuk tidak diubah): ";
    cin >> noTelp;
    if (noTelp != 0)
    {
        s->noTelp = noTelp;
    }

    // ubah file karena update
    ubahFileSiswa();
    cout << "Data siswa berhasil diperbarui.";
    cout << endl;
}

void Admin::hapusSiswa()
{
    cout << endl;
    cout << "[-------------------------]";
    cout << endl;
    cout << "[---    HAPUS SISWA    ---]";
    cout << endl;
    cout << "[-------------------------]";
    cout << endl;

    long long nik;
    cout << "Masukkan NIK: ";
    cin >> nik;
    if (!head)
    {
        cout << "Belum ada data siswa.";
        cout << endl;
        return;
    }

    //jika mengahpus head
    if (head->nik == nik)
    {
        NodeSiswa* temp = head;
        head= head->next;
        delete temp;

        ubahFileSiswa();
        cout << "Siswa dihapus.";
        cout << endl;
        return;
    }

    NodeSiswa* prev = head;
    NodeSiswa* cur = head->next;
    while (cur)
    {
        if (cur->nik == nik)
        {
            prev->next = cur->next;
            delete cur;

            ubahFileSiswa();
            cout << "Siswa dihapus.";
            cout << endl;
            return;
        }

        prev = cur;
        cur = cur->next;
    }

    cout << "Siswa dengan NIK tersebut tidak dapat ditemukan";
    cout << endl;
}

void Admin::cariSiswa()
{
    cout << endl;
    cout << "[--------------------------]";
    cout << endl;
    cout << "[---     CARI SISWA     ---]";
    cout << endl;
    cout << "[--------------------------]";
    cout << endl;

    long long nik;
    cout << "Masukkan NIK: ";
    cin >> nik;
    NodeSiswa* s = cariDariNik(nik);
    if (!s)
    {
        cout << "Siswa tidak ditemukan.";
        cout << endl;
        return;
    }

    cout << "[--- Ditemukan ---]";
    cout << endl;
    cout << "NIK\t: " << s->nik;
    cout << endl;
    cout << "Nama\t: " << s->nama;
    cout << endl;
    cout << "Kelas\t: " << s->kelas;
    cout << endl;
    cout << "Alamat\t: " << s->alamat;
    cout << endl;
    cout << "No. Telp\t: " << s->noTelp;
    cout << endl;
}

void Admin::menuManajemenSiswa()
{
    int pilih = 0;
    do 
    {
        cout << endl;
        cout << "[----------------------------]";
        cout << endl;
        cout << "[--- MANAJEMEN DATA SISWA ---]";
        cout << endl;
        cout << "[----------------------------]";
        cout << endl;

        cout << "1. Tambah Siswa";
        cout << endl;
        cout << "2. Lihat Daftar Siswa";
        cout << endl;
        cout << "3. Ubah Data Siswa";
        cout << endl;
        cout << "4. Hapus Siswa";
        cout << endl;
        cout << "5. Cari Siswa";
        cout << endl;
        cout << "6. Kembali";
        cout << endl;
        cout << "[----------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            tambahSiswa();
            break;
        case 2:
            daftarSiswa();
            break;
        case 3:
            editSiswa();
            break;
        case 4:
            hapusSiswa();
            break;
        case 5:
            cariSiswa();
            break;
        case 6:
            cout << "Kembali ke menu admin...";
            cout << endl;
            break;
        default:
        cout << "Pilihan tidak valid!";
        cout << endl;
            break;
        }
    } while (pilih != 6);
}

void Admin::menuAdmin()
{
    int pilih = 0;
    do
    {
        cout << endl;
        cout << "[----------------------------------]";
        cout << endl;
        cout << "[---         MENU ADMIN         ---]";
        cout << endl;
        cout << "[----------------------------------]";
        cout << endl;

        cout << "1. Manajemen Data Siswa";
        cout << endl;
        cout << "2. Manajemen Data Pengajar";
        cout << endl;
        cout << "3. Manajemen Jadwal Bimbingan";
        cout << endl;
        cout << "4. Manajemen Nilai";
        cout << endl;
        cout << "5. Manajemen Absensi & Kehadiran";
        cout << endl;
        cout << "6. Manajemen Keuangan ";
        cout << endl;
        cout << "7. Laporan &Rekap Data";
        cout << endl;
        cout << "8. Backup Data";
        cout << endl;
        cout << "9. Manajemen Kelas\n";  
        cout << "10. Logout";    
        cout << endl;
        cout << "[----------------------------------]";
        cout << endl;
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            menuManajemenSiswa();
            break;
        case 2:
            menuManajemenPengajar();
            break;
        case 3:
            menuManajemenJadwal();
            break;
        case 4:
            menuManajemenNilai();
            break;
        case 5:
            menuManajemenAbsensi();
            break;
        case 6:
            menuManajemenKeuangan();
            break;
        case 7:
            menuLaporanRekap();
            break;
        case 8:
            menuBackupData();
            break;
        case 9:
            menuManajemenKelas();
            break;
        case 10:
            cout << "Logout...";
            cout << endl;
            break;
        default:
            cout << "Pilihan tidak valid!";
            cout << endl;
            break;
        }
    } while (pilih != 10);
}

// Implementasi tambahan: cariAbsensidariNik (menggunakan cariDariNik)
NodeSiswa* Admin::cariAbsensidariNik(const long long& nik) {
    return cariDariNik(nik);
}

#endif
