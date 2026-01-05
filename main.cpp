#include <iostream>
#include <iomanip>
#include "akun.h"
#include "admin.h"
#include "siswa.h"
#include "pengajar.h"
#include "kelas.h"

using namespace std;

int main() {
    Akun akun;
    Admin admin;
    int pilihan;

	cout << endl;
    cout << "---[ SELAMAT DATANG ]---";
    cout << endl << endl;
    
	do {
    	
    	cout << "========================";
    	cout << endl;
        cout << "   --- MENU UTAMA ---";
        cout << endl;
        cout << "========================";
    	cout << endl;
        cout << "1. Registrasi Akun";
        cout << endl;
        cout << "2. Login";
        cout << endl;
        cout << "3. Exit";
        cout << endl;
        cout << "========================";
    	cout << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        system("cls");

        switch (pilihan) {
            case 1:
                akun.registerAkun();
                break;

            case 2: {
                string uname;
                Role r = akun.login(uname);

                if (r == ADMIN) {
                    admin.menuAdmin();  
                } 
                else if (r == SISWA) {
                    cout << ">> Login berhasil sebagai siswa.\n";
				    SiswaMenu siswa(uname);
				    siswa.menuSiswa();
                } 
                else if (r == PENGAJAR) {
                    cout << "Login berhasil sebagai pengajar.\n";
				    PengajarMenu pg(uname);     // username digunakan untuk mencari NIK
				    pg.menuPengajar();
                } 
                else {
                    // login gagal
                }
                break;
            }

            case 3:
                cout << "Keluar...\n";
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }

    } while (pilihan != 3);

    return 0;
}

