#include <iostream>
#include <conio.h>
#include "ktp.h"
#include "array1d.h"
#include "linkedlist.h"
using namespace std;

void clearScreen() {
    system("cls");
}

void tampilkanHeader() {
    cout << "\n" << string(50, '=');
    cout << "\n     SISTEM DATABASE KTP";
    cout << "\n" << string(50, '=');
}

void inputKTP(KTP_Array &d) {
    cout << "\n=== INPUT DATA KTP BARU ===\n";

    cout << "NIK (16 digit)          : ";
    while (!(cin >> d.nik) || (d.nik < 1000000000000000 || d.nik > 9999999999999999)) {
        cout << "NIK harus 16 digit angka! Coba lagi: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();
    
    cout << "Nama Lengkap            : ";
    getline(cin, d.nama);
    
    cout << "Tempat Lahir            : ";
    getline(cin, d.tempatLahir);

    cout << "Tanggal Lahir (DD MM YYYY): ";
    while (!(cin >> d.tanggalLahir.hari >> d.tanggalLahir.bulan >> d.tanggalLahir.tahun) ||
           d.tanggalLahir.hari < 1 || d.tanggalLahir.hari > 31 ||
           d.tanggalLahir.bulan < 1 || d.tanggalLahir.bulan > 12 ||
           d.tanggalLahir.tahun < 1900 || d.tanggalLahir.tahun > 2100) {
        cout << "Tanggal tidak valid! Coba lagi (DD MM YYYY): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int jk;
    cout << "\nJenis Kelamin:";
    cout << "\n1. Laki-laki";
    cout << "\n2. Perempuan";
    cout << "\nPilih (1-2): ";
    while (!(cin >> jk) || (jk < 1 || jk > 2)) {
        cout << "Pilihan tidak valid! Coba lagi (1-2): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    d.jenisKelamin = (jk == 1 ? JK_LK : JK_PR);

    int gd;
    cout << "\nGolongan Darah:";
    cout << "\n1. A";
    cout << "\n2. B";
    cout << "\n3. AB";
    cout << "\n4. O";
    cout << "\n5. Tidak Tahu";
    cout << "\nPilih (1-5): ";
    while (!(cin >> gd) || (gd < 1 || gd > 5)) {
        cout << "Pilihan tidak valid! Coba lagi (1-5): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    d.golonganDarah = static_cast<GolDarah>(gd);

    cin.ignore();
    cout << "\nAlamat Lengkap          : ";
    getline(cin, d.alamat);
    
    cout << "RT                      : ";
    getline(cin, d.rt);
    
    cout << "RW                      : ";
    getline(cin, d.rw);
    
    cout << "Kelurahan/Desa          : ";
    getline(cin, d.kelurahan);
    
    cout << "Kecamatan               : ";
    getline(cin, d.kecamatan);
    
    cout << "Kota/Kabupaten          : ";
    getline(cin, d.kotaKabupaten);
    
    cout << "Provinsi                : ";
    getline(cin, d.provinsi);

    int ag;
    cout << "\nAgama:";
    cout << "\n1. Islam";
    cout << "\n2. Kristen";
    cout << "\n3. Katolik";
    cout << "\n4. Hindu";
    cout << "\n5. Buddha";
    cout << "\n6. Khonghucu";
    cout << "\nPilih (1-6): ";
    while (!(cin >> ag) || (ag < 1 || ag > 6)) {
        cout << "Pilihan tidak valid! Coba lagi (1-6): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    d.agama = static_cast<Agama>(ag);

    int sp;
    cout << "\nStatus Perkawinan:";
    cout << "\n1. Belum Kawin";
    cout << "\n2. Kawin";
    cout << "\nPilih (1-2): ";
    while (!(cin >> sp) || (sp < 1 || sp > 2)) {
        cout << "Pilihan tidak valid! Coba lagi (1-2): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    d.statusPerkawinan = static_cast<StatusPerkawinan>(sp);

    cin.ignore();
    cout << "Pekerjaan               : ";
    getline(cin, d.pekerjaan);

    int kw;
    cout << "\nKewarganegaraan:";
    cout << "\n1. WNI";
    cout << "\n2. WNA";
    cout << "\nPilih (1-2): ";
    while (!(cin >> kw) || (kw < 1 || kw > 2)) {
        cout << "Pilihan tidak valid! Coba lagi (1-2): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    d.kewarganegaraan = (kw == 1 ? KW_WNI : KW_WNA);

    cin.ignore();
    cout << "Berlaku Hingga (DD-MM-YYYY): ";
    getline(cin, d.berlakuHingga);
}

void editPosisiMenu(LinkedListKTP& listDB) {
    int p;
    cout << "\n=== EDIT POSISI LINKED LIST ===\n";
    cout << "1. Tambah Depan\n";
    cout << "2. Tambah Belakang\n";
    cout << "3. Tambah di Posisi Tertentu\n";
    cout << "Pilihan: ";
    cin >> p;

    KTP_Array d;
    inputKTP(d);

    if (p == 1) {
        listDB.tambahDepan(d);
    } else if (p == 2) {
        listDB.tambahBelakang(d);
    } else if (p == 3) {
        int pos;
        cout << "Masukkan posisi: ";
        cin >> pos;
        listDB.tambahPosisi(d, pos);
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

int main() {
    ArrayKTP arrayDB;
    LinkedListKTP listDB;

    int pilihan;

    do {
        clearScreen();
        tampilkanHeader();
        
        cout << "\nMENU UTAMA:\n";
        cout << "1. Tambah Data KTP Baru\n";
        cout << "2. Tampilkan Data (Dari Memory)\n";
        cout << "3. Tampilkan Data (Dari File TXT)\n";
        cout << "4. Edit Posisi Data di LinkedList\n";
        cout << "5. Cari Data KTP\n";
        cout << "6. Hapus Data KTP\n";
        cout << "7. Keluar\n";
        cout << "\nPilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1: {
                clearScreen();
                KTP_Array d;
                inputKTP(d);
                arrayDB.tambah(d);       // Otomatis simpan ke file array
                listDB.tambahBelakang(d); // Otomatis simpan ke file linkedlist
                cout << "\n? Data berhasil ditambahkan dan disimpan ke file TXT!\n";
                cout << "  - data_ktp_array.txt (untuk Array)\n";
                cout << "  - data_ktp_linkedlist.txt (untuk Linked List)\n";
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }

            case 2: {
                clearScreen();
                int tampilPilihan;
                cout << "\n=== TAMPILKAN DATA DARI MEMORY ===\n";
                cout << "1. Tampilkan Data Array (Detail)\n";
                cout << "2. Tampilkan Data Linked List (Detail)\n";
                cout << "3. Tampilkan Keduanya\n";
                cout << "4. Tampilkan Linked List (Ringkas)\n";
                cout << "Pilihan: ";
                cin >> tampilPilihan;

                clearScreen();
                if (tampilPilihan == 1) {
                    arrayDB.tampilkan();
                } else if (tampilPilihan == 2) {
                    listDB.tampilkanDetailed();
                } else if (tampilPilihan == 3) {
                    arrayDB.tampilkan();
                    listDB.tampilkanDetailed();
                } else if (tampilPilihan == 4) {
                    listDB.tampilkanRingkas();
                } else {
                    cout << "Pilihan tidak valid!\n";
                }
                
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }

            case 3: {
                clearScreen();
                int filePilihan;
                cout << "\n=== TAMPILKAN DATA DARI FILE TXT ===\n";
                cout << "1. Tampilkan Data Array dari File\n";
                cout << "2. Tampilkan Data Linked List dari File\n";
                cout << "3. Tampilkan Keduanya dari File\n";
                cout << "Pilihan: ";
                cin >> filePilihan;

                clearScreen();
                if (filePilihan == 1) {
                    arrayDB.tampilkanDariFile();
                } else if (filePilihan == 2) {
                    listDB.tampilkanDariFile();
                } else if (filePilihan == 3) {
                    cout << "\n" << string(50, '=');
                    cout << "\nDATA ARRAY DARI FILE";
                    cout << "\n" << string(50, '=') << "\n";
                    arrayDB.tampilkanDariFile();
                    
                    cout << "\n\n" << string(50, '=');
                    cout << "\nDATA LINKED LIST DARI FILE";
                    cout << "\n" << string(50, '=') << "\n";
                    listDB.tampilkanDariFile();
                } else {
                    cout << "Pilihan tidak valid!\n";
                }
                
                cout << "\n\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }

            case 4: {
                clearScreen();
                editPosisiMenu(listDB);
                cout << "\n? Data berhasil ditambahkan ke Linked List dan disimpan ke file!\n";
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }

            case 5: {
                clearScreen();
                long long nik;
                cout << "\n=== CARI DATA KTP ===\n";
                cout << "Masukkan NIK yang dicari: ";
                cin >> nik;

                NodeKTP* ketemu = listDB.cariNIK(nik);
                if (ketemu) {
                    cout << "\n? DATA DITEMUKAN!\n";
                    cout << "\nNIK      : " << ketemu->nik;
                    cout << "\nNama     : " << ketemu->nama;
                    cout << "\nAlamat   : " << ketemu->alamat;
                    cout << "\nKota     : " << ketemu->kotaKabupaten;
                    cout << "\nProvinsi : " << ketemu->provinsi;
                } else {
                    cout << "\n? NIK tidak ditemukan!\n";
                }
                
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }

            case 6: {
                clearScreen();
                long long nik;
                cout << "\n=== HAPUS DATA KTP ===\n";
                cout << "Masukkan NIK yang akan dihapus: ";
                cin >> nik;

                if (listDB.hapusNIK(nik)) {
                    cout << "\n? Data berhasil dihapus dari Linked List dan file diperbarui!\n";
                    cout << "Catatan: Data di Array tidak dapat dihapus (struktur tetap)\n";
                } else {
                    cout << "\n? NIK tidak ditemukan!\n";
                }
                
                cout << "\nTekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
            }

            case 7: {
                cout << "\nTerima kasih telah menggunakan sistem database KTP!\n";
                break;
            }

            default: {
                cout << "\nPilihan tidak valid! Coba lagi.\n";
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
                break;
            }
        }
    } while (pilihan != 7);

    return 0;
}
