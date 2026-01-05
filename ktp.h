#ifndef KTP_H
#define KTP_H

#include <string>
using namespace std;

enum JenisKelamin { JK_LK = 1, JK_PR };
enum GolDarah { GD_A = 1, GD_B, GD_AB, GD_O, GD_TIDAK_TAHU };
enum Agama { 
    AG_ISLAM = 1, 
    AG_KRISTEN, 
    AG_KATOLIK, 
    AG_HINDU, 
    AG_BUDDHA, 
    AG_KHONGHUCU 
};
enum StatusPerkawinan { SP_BELUM = 1, SP_KAWIN };
enum Kewarganegaraan { KW_WNI = 1, KW_WNA };

enum UserRole { 
    ROLE_NONE = 0,          // Belum ditentukan
    ROLE_ADMIN = 1, 
    ROLE_SISWA = 2, 
    ROLE_PENGAJAR = 3
};

struct Date {
    int hari, bulan, tahun;
};

struct KTP_Array {
    long long nik;
    string nama;
    string tempatLahir;
    Date tanggalLahir;
    JenisKelamin jenisKelamin;
    GolDarah golonganDarah;
    string alamat;
    string rt, rw;
    string kelurahan, kecamatan;
    string kotaKabupaten, provinsi;
    Agama agama;
    StatusPerkawinan statusPerkawinan;
    string pekerjaan;
    Kewarganegaraan kewarganegaraan;
    string berlakuHingga;
    
    // Data untuk integrasi dengan bimbel
    UserRole userRole;       // Role di sistem bimbel
    string username;         // Biasanya NIK (string)
    string password;         // Password default
    string status;           // ACTIVE, INACTIVE, PENDING
};

struct NodeKTP {
    long long nik;
    string nama;
    string tempatLahir;
    Date tanggalLahir;
    JenisKelamin jenisKelamin;
    GolDarah golonganDarah;
    string alamat;
    string rt, rw;
    string kelurahan, kecamatan;
    string kotaKabupaten, provinsi;
    Agama agama;
    StatusPerkawinan statusPerkawinan;
    string pekerjaan;
    Kewarganegaraan kewarganegaraan;
    string berlakuHingga;

    NodeKTP* next;
    NodeKTP* prev;
};

#endif
