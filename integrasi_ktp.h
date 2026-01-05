#ifndef INTEGRASI_KTP_H
#define INTEGRASI_KTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class IntegrasiKTP {
public:
    // Cek apakah NIK ada di database KTP
    static bool cekNIK(const string& nik) {
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
    
    // Ambil data KTP berdasarkan NIK
    static vector<string> getDataKTP(const string& nik) {
        vector<string> data;
        ifstream file("data_ktp_linkedlist.txt");
        
        if (!file.is_open()) {
            data.push_back("File tidak ditemukan");
            return data;
        }
        
        string line;
        bool found = false;
        int dataCount = 0;
        
        while (getline(file, line) && dataCount < 17) {
            if (line.find("NIK") != string::npos && line.find(nik) != string::npos) {
                found = true;
            }
            
            if (found) {
                data.push_back(line);
                dataCount++;
            }
            
            if (dataCount >= 17) break;
        }
        
        file.close();
        return data;
    }
    
    // Hitung umur dari tanggal lahir
    static int hitungUmur(const string& tglLahir) {
        // Format: DD/MM/YYYY
        if (tglLahir.length() < 10) return 0;
        
        int tahun = stoi(tglLahir.substr(6, 4));
        int tahunSekarang = 2024; // Gunakan fungsi time() untuk tahun aktual
        return tahunSekarang - tahun;
    }
};

#endif
