#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "ktp.h"
using namespace std;

class LinkedListKTP {
private:
    NodeKTP* head;
    NodeKTP* tail;
    const string FILE_NAME = "data_ktp_linkedlist.txt";

    // Helper function untuk konversi enum ke string
    string agamaToString(Agama a) {
        switch(a) {
            case AG_ISLAM: return "Islam";
            case AG_KRISTEN: return "Kristen";
            case AG_KATOLIK: return "Katolik";
            case AG_HINDU: return "Hindu";
            case AG_BUDDHA: return "Buddha";
            case AG_KHONGHUCU: return "Khonghucu";
            default: return "Tidak Diketahui";
        }
    }

    string statusToString(StatusPerkawinan s) {
        switch(s) {
            case SP_BELUM: return "Belum Kawin";
            case SP_KAWIN: return "Kawin";
            default: return "Tidak Diketahui";
        }
    }

    string golDarahToString(GolDarah g) {
        switch(g) {
            case GD_A: return "A";
            case GD_B: return "B";
            case GD_AB: return "AB";
            case GD_O: return "O";
            case GD_TIDAK_TAHU: return "Tidak Tahu";
            default: return "?";
        }
    }

    string jenisKelaminToString(JenisKelamin jk) {
        switch(jk) {
            case JK_LK: return "Laki-laki";
            case JK_PR: return "Perempuan";
            default: return "Tidak Diketahui";
        }
    }

    string kewarganegaraanToString(Kewarganegaraan kw) {
        switch(kw) {
            case KW_WNI: return "WNI";
            case KW_WNA: return "WNA";
            default: return "Tidak Diketahui";
        }
    }

    // Fungsi internal untuk menyimpan ke file
    void simpanKeFileInternal() {
        ofstream file(FILE_NAME);
        
        if (!file.is_open()) {
            return; // Return quietly, error handling di fungsi public
        }

        file << "================================================================================\n";
        file << "                            DATA KTP (LINKED LIST)\n";
        file << "================================================================================\n\n";

        if (!head) {
            file << "Tidak ada data.\n";
            file.close();
            return;
        }

        NodeKTP* current = head;
        int no = 1;

        while (current) {
            file << "Data ke-" << no++ << "\n";
            file << string(40, '-') << "\n";
            file << "NIK               : " << current->nik << "\n";
            file << "Nama              : " << current->nama << "\n";
            file << "Tempat Lahir      : " << current->tempatLahir << "\n";
            file << "Tanggal Lahir     : " 
                 << setw(2) << setfill('0') << current->tanggalLahir.hari << "/"
                 << setw(2) << setfill('0') << current->tanggalLahir.bulan << "/"
                 << current->tanggalLahir.tahun << "\n";
            file << "Jenis Kelamin     : " << jenisKelaminToString(current->jenisKelamin) << "\n";
            file << "Gol. Darah        : " << golDarahToString(current->golonganDarah) << "\n";
            file << "Alamat            : " << current->alamat << "\n";
            file << "RT/RW             : " << current->rt << "/" << current->rw << "\n";
            file << "Kelurahan         : " << current->kelurahan << "\n";
            file << "Kecamatan         : " << current->kecamatan << "\n";
            file << "Kota/Kabupaten    : " << current->kotaKabupaten << "\n";
            file << "Provinsi          : " << current->provinsi << "\n";
            file << "Agama             : " << agamaToString(current->agama) << "\n";
            file << "Status Perkawinan : " << statusToString(current->statusPerkawinan) << "\n";
            file << "Pekerjaan         : " << current->pekerjaan << "\n";
            file << "Kewarganegaraan   : " << kewarganegaraanToString(current->kewarganegaraan) << "\n";
            file << "Berlaku Hingga    : " << current->berlakuHingga << "\n\n";
            
            current = current->next;
        }

        int count = hitungJumlahData();
        file << "\nTotal data: " << count << "\n";
        file << "================================================================================\n";
        
        file.close();
    }

public:
    LinkedListKTP() : head(nullptr), tail(nullptr) {}

    ~LinkedListKTP() {
        NodeKTP* current = head;
        while (current) {
            NodeKTP* next = current->next;
            delete current;
            current = next;
        }
    }

    // ===================== INSERT =====================

    void tambahDepan(const KTP_Array& d) {
        NodeKTP* baru = new NodeKTP{
            d.nik, d.nama, d.tempatLahir, d.tanggalLahir,
            d.jenisKelamin, d.golonganDarah, d.alamat,
            d.rt, d.rw, d.kelurahan, d.kecamatan, d.kotaKabupaten,
            d.provinsi, d.agama, d.statusPerkawinan, d.pekerjaan,
            d.kewarganegaraan, d.berlakuHingga,
            head, nullptr
        };

        if (!head) {
            head = tail = baru;
        } else {
            head->prev = baru;
            head = baru;
        }
        simpanKeFileInternal(); // Otomatis simpan setelah tambah
    }

    void tambahBelakang(const KTP_Array& d) {
        NodeKTP* baru = new NodeKTP{
            d.nik, d.nama, d.tempatLahir, d.tanggalLahir,
            d.jenisKelamin, d.golonganDarah, d.alamat,
            d.rt, d.rw, d.kelurahan, d.kecamatan, d.kotaKabupaten,
            d.provinsi, d.agama, d.statusPerkawinan, d.pekerjaan,
            d.kewarganegaraan, d.berlakuHingga,
            nullptr, tail
        };

        if (!tail) {
            head = tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
        simpanKeFileInternal(); // Otomatis simpan setelah tambah
    }

    void tambahPosisi(const KTP_Array& d, int pos) {
        if (pos <= 1 || !head) {
            tambahDepan(d);
            return;
        }

        NodeKTP* current = head;
        int index = 1;

        while (current && index < pos) {
            current = current->next;
            index++;
        }

        if (!current) {
            tambahBelakang(d);
            return;
        }

        NodeKTP* baru = new NodeKTP{
            d.nik, d.nama, d.tempatLahir, d.tanggalLahir,
            d.jenisKelamin, d.golonganDarah, d.alamat,
            d.rt, d.rw, d.kelurahan, d.kecamatan, d.kotaKabupaten,
            d.provinsi, d.agama, d.statusPerkawinan, d.pekerjaan,
            d.kewarganegaraan, d.berlakuHingga,
            current, current->prev
        };

        current->prev->next = baru;
        current->prev = baru;
        simpanKeFileInternal(); // Otomatis simpan setelah tambah
    }

    // ===================== SEARCH =====================

    NodeKTP* cariNIK(long long nik) {
        NodeKTP* current = head;
        while (current) {
            if (current->nik == nik) return current;
            current = current->next;
        }
        return nullptr;
    }

    // ===================== DELETE =====================

    bool hapusNIK(long long nik) {
        NodeKTP* node = cariNIK(nik);
        if (!node) return false;

        if (node == head && node == tail) {
            head = tail = nullptr;
        } else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        simpanKeFileInternal(); // Otomatis simpan setelah hapus
        return true;
    }

    // ===================== DISPLAY =====================

    void tampilkanDetailed() {
        cout << "\n" << string(60, '=');
        cout << "\nDATA KTP (LINKED LIST - DETAIL)";
        cout << "\n" << string(60, '=');
        
        if (!head) {
            cout << "\nLinked List kosong.\n";
            return;
        }

        NodeKTP* current = head;
        int no = 1;

        while (current) {
            cout << "\n\n" << string(40, '-');
            cout << "\nNODE KE-" << no++;
            cout << "\n" << string(40, '-');

            cout << "\nNIK               : " << current->nik;
            cout << "\nNama              : " << current->nama;
            cout << "\nTempat/Tgl Lahir  : " << current->tempatLahir << ", "
                 << setw(2) << setfill('0') << current->tanggalLahir.hari << "/"
                 << setw(2) << setfill('0') << current->tanggalLahir.bulan << "/"
                 << current->tanggalLahir.tahun;
            cout << "\nJenis Kelamin     : " << jenisKelaminToString(current->jenisKelamin);
            cout << "\nGol. Darah        : " << golDarahToString(current->golonganDarah);
            cout << "\nAlamat            : " << current->alamat;
            cout << "\nRT/RW             : " << current->rt << "/" << current->rw;
            cout << "\nKelurahan         : " << current->kelurahan;
            cout << "\nKecamatan         : " << current->kecamatan;
            cout << "\nKota/Kabupaten    : " << current->kotaKabupaten;
            cout << "\nProvinsi          : " << current->provinsi;
            cout << "\nAgama             : " << agamaToString(current->agama);
            cout << "\nStatus Perkawinan : " << statusToString(current->statusPerkawinan);
            cout << "\nPekerjaan         : " << current->pekerjaan;
            cout << "\nKewarganegaraan   : " << kewarganegaraanToString(current->kewarganegaraan);
            cout << "\nBerlaku Hingga    : " << current->berlakuHingga;
            
            current = current->next;
        }
        
        int count = hitungJumlahData();
        cout << "\n\nTotal data dalam Linked List: " << count << "\n";
    }

    void tampilkanRingkas() {
        cout << "\n" << string(50, '=');
        cout << "\nDATA KTP (LINKED LIST - RINGKAS)";
        cout << "\n" << string(50, '=');
        
        if (!head) {
            cout << "\nLinked List kosong.\n";
            return;
        }

        NodeKTP* current = head;
        int no = 1;

        cout << "\nNo.  NIK              Nama";
        cout << "\n" << string(50, '-');

        while (current) {
            cout << "\n" << no++ << ".   " 
                 << current->nik << "  " 
                 << current->nama;
            current = current->next;
        }
        
        int count = hitungJumlahData();
        cout << "\n\nTotal data: " << count << "\n";
    }

    // Fungsi untuk membaca dan menampilkan data dari file TXT
    void tampilkanDariFile() {
        ifstream file(FILE_NAME);
        
        if (!file.is_open()) {
            cout << "\nFile tidak ditemukan atau belum ada data tersimpan.\n";
            return;
        }

        string line;
        cout << "\n" << string(50, '=');
        cout << "\nDATA KTP DARI FILE (LINKED LIST)";
        cout << "\n" << string(50, '=') << "\n";
        
        while (getline(file, line)) {
            cout << line << "\n";
        }
        
        file.close();
    }

    // ===================== UTILITY =====================

    int hitungJumlahData() {
        int count = 0;
        NodeKTP* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

#endif
