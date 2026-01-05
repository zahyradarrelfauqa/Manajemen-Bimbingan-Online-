#ifndef ARRAY1D_H
#define ARRAY1D_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "ktp.h"
using namespace std;

class ArrayKTP {
private:
    KTP_Array data[200];
    int size;
    const string FILE_NAME = "data_ktp_array.txt";

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

public:
    ArrayKTP() : size(0) {}

    void tambah(const KTP_Array& d) {
        if (size < 200) {
            data[size++] = d;
            simpanKeFile(); // Otomatis simpan ke file
        } else {
            cout << "Kapasitas array penuh!\n";
        }
    }

    void tampilkan() {
        cout << "\n" << string(50, '=');
        cout << "\nDATA KTP (ARRAY 1D)";
        cout << "\n" << string(50, '=');
        
        if (size == 0) {
            cout << "\nArray kosong.\n";
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << "\n" << string(40, '-');
            cout << "\nData ke-" << i + 1;
            cout << "\n" << string(40, '-');
            
            cout << "\nNIK               : " << data[i].nik;
            cout << "\nNama              : " << data[i].nama;
            cout << "\nTempat/Tgl Lahir  : " << data[i].tempatLahir << ", "
                 << setw(2) << setfill('0') << data[i].tanggalLahir.hari << "/"
                 << setw(2) << setfill('0') << data[i].tanggalLahir.bulan << "/"
                 << data[i].tanggalLahir.tahun;
            cout << "\nJenis Kelamin     : " << jenisKelaminToString(data[i].jenisKelamin);
            cout << "\nGol. Darah        : " << golDarahToString(data[i].golonganDarah);
            cout << "\nAlamat            : " << data[i].alamat;
            cout << "\nRT/RW             : " << data[i].rt << "/" << data[i].rw;
            cout << "\nKelurahan         : " << data[i].kelurahan;
            cout << "\nKecamatan         : " << data[i].kecamatan;
            cout << "\nKota/Kabupaten    : " << data[i].kotaKabupaten;
            cout << "\nProvinsi          : " << data[i].provinsi;
            cout << "\nAgama             : " << agamaToString(data[i].agama);
            cout << "\nStatus Perkawinan : " << statusToString(data[i].statusPerkawinan);
            cout << "\nPekerjaan         : " << data[i].pekerjaan;
            cout << "\nKewarganegaraan   : " << kewarganegaraanToString(data[i].kewarganegaraan);
            cout << "\nBerlaku Hingga    : " << data[i].berlakuHingga;
            cout << "\n";
        }
        cout << "\nTotal data: " << size << "\n";
    }

    // Fungsi untuk menyimpan data ke file TXT (otomatis dipanggil setelah tambah)
    void simpanKeFile() {
        ofstream file(FILE_NAME);
        
        if (!file.is_open()) {
            cout << "Gagal membuka file untuk penyimpanan!\n";
            return;
        }

        file << "================================================================================\n";
        file << "                              DATA KTP (ARRAY)\n";
        file << "================================================================================\n\n";

        if (size == 0) {
            file << "Tidak ada data.\n";
            file.close();
            return;
        }

        for (int i = 0; i < size; i++) {
            file << "Data ke-" << i + 1 << "\n";
            file << string(40, '-') << "\n";
            file << "NIK               : " << data[i].nik << "\n";
            file << "Nama              : " << data[i].nama << "\n";
            file << "Tempat Lahir      : " << data[i].tempatLahir << "\n";
            file << "Tanggal Lahir     : " 
                 << setw(2) << setfill('0') << data[i].tanggalLahir.hari << "/"
                 << setw(2) << setfill('0') << data[i].tanggalLahir.bulan << "/"
                 << data[i].tanggalLahir.tahun << "\n";
            file << "Jenis Kelamin     : " << jenisKelaminToString(data[i].jenisKelamin) << "\n";
            file << "Gol. Darah        : " << golDarahToString(data[i].golonganDarah) << "\n";
            file << "Alamat            : " << data[i].alamat << "\n";
            file << "RT/RW             : " << data[i].rt << "/" << data[i].rw << "\n";
            file << "Kelurahan         : " << data[i].kelurahan << "\n";
            file << "Kecamatan         : " << data[i].kecamatan << "\n";
            file << "Kota/Kabupaten    : " << data[i].kotaKabupaten << "\n";
            file << "Provinsi          : " << data[i].provinsi << "\n";
            file << "Agama             : " << agamaToString(data[i].agama) << "\n";
            file << "Status Perkawinan : " << statusToString(data[i].statusPerkawinan) << "\n";
            file << "Pekerjaan         : " << data[i].pekerjaan << "\n";
            file << "Kewarganegaraan   : " << kewarganegaraanToString(data[i].kewarganegaraan) << "\n";
            file << "Berlaku Hingga    : " << data[i].berlakuHingga << "\n\n";
        }

        file << "\nTotal data: " << size << "\n";
        file << "================================================================================\n";
        
        file.close();
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
        cout << "\nDATA KTP DARI FILE (ARRAY)";
        cout << "\n" << string(50, '=') << "\n";
        
        while (getline(file, line)) {
            cout << line << "\n";
        }
        
        file.close();
    }

    int getSize() const {
        return size;
    }
};

#endif
