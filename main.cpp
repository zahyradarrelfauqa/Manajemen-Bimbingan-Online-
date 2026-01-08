#include <iostream>
#include <iomanip>
#include "akun.h"
#include "admin.h"
#include "siswa.h"
#include "pengajar.h"
#include "kelas.h"

using namespace std;

void clearScreen() {
    system("cls");
}

int main() {
    Akun akun;
    Admin admin;
    int pilihan;

    clearScreen();
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
        cout << "3. Ganti Password";
        cout << endl;
        cout << "4. Exit";
        cout << endl;
        cout << "========================";
    	cout << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                akun.registerAkun();
                break;

            case 2: {
				break;
                string uname;
                Role r = akun.login(uname);

                if (r == ADMIN) {
                	cout << "\n>> Login berhasil sebagai Admin.\n";
                    cout << "Tekan Enter untuk melanjutkan...";
                    cin.ignore();
                    cin.get();
                    admin.menuAdmin();  
                } 
                else if (r == SISWA) {
                    cout << "\n>> Login berhasil sebagai Siswa.\n";
                    cout << "Tekan Enter untuk melanjutkan...";
                    cin.ignore();
                    cin.get();
				    SiswaMenu siswa(uname);
				    siswa.menuSiswa();
                } 
                else if (r == PENGAJAR) {
                    cout << "\n>> Login berhasil sebagai Pengajar.\n";
                    cout << "Tekan Enter untuk melanjutkan...";
                    cin.ignore();
                    cin.get();
				    PengajarMenu pg(uname);     // username digunakan untuk mencari NIK
				    pg.menuPengajar();
                } 
                else {
                    cout << "Login gagal...\n";
                }
                break;
            }
            
			case 3: {
                string username;
		        cout << "Masukkan NIK yang akan diganti passwordnya: ";
		        cin >> username;
		        akun.gantiPassword(username);
                break;
            }
                
            case 4:
                cout << "\nTerima kasih telah mengunjungi BimOn!\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
        }

    } while (pilihan != 3);

    return 0;
}
