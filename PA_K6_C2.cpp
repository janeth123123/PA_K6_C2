#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>

using namespace std;

const int MAX_NARAPIDANA = 3;
const int MAX_LOGIN_ATTEMPTS = 3;
const int MAX_PENJAGA_PENJARA = 3;

struct Narapidana {
    string nama;
    string nomor_identifikasi;
    string jenis_kejahatan;
    string tanggal_masuk_penjara;
    string jangka_waktu_hukuman;
    string status_kesehatan;
};

struct PenjagaPenjara {
    string nama;
    string nomor_identifikasi;
    string posisi;
    string tanggal_mulai_bertugas;
};

struct DataNarapidana {
    int jumlah_narapidana;
    Narapidana* narapidana[MAX_NARAPIDANA];
    PenjagaPenjara* penjaga_penjara[MAX_PENJAGA_PENJARA];
    int jumlah_penjaga_penjara;
};

DataNarapidana data_narapidana;

void simpanDataNarapidanaKeFile() {
    ofstream file("data_narapidana.txt");
    if (file.is_open()) {
        for (int i = 0; i < data_narapidana.jumlah_narapidana; ++i) {
            file << data_narapidana.narapidana[i]->nama << endl;
            file << data_narapidana.narapidana[i]->nomor_identifikasi << endl;
            file << data_narapidana.narapidana[i]->jenis_kejahatan << endl;
            file << data_narapidana.narapidana[i]->tanggal_masuk_penjara << endl;
            file << data_narapidana.narapidana[i]->jangka_waktu_hukuman << endl;
            file << data_narapidana.narapidana[i]->status_kesehatan << endl;
        }
        file.close();
    } else {
        cout << "Gagal menyimpan data narapidana ke dalam file." << endl;
    }
}

void bacaDataNarapidanaDariFile() {
    ifstream file("data_narapidana.txt");
    if (file.is_open()) {
        data_narapidana.jumlah_narapidana = 0; // Reset jumlah narapidana
        while (!file.eof() && data_narapidana.jumlah_narapidana < MAX_NARAPIDANA) {
            Narapidana* ptrNarapidana = new Narapidana;
            getline(file, ptrNarapidana->nama);
            getline(file, ptrNarapidana->nomor_identifikasi);
            getline(file, ptrNarapidana->jenis_kejahatan);
            getline(file, ptrNarapidana->tanggal_masuk_penjara);
            getline(file, ptrNarapidana->jangka_waktu_hukuman);
            getline(file, ptrNarapidana->status_kesehatan);
            if (!ptrNarapidana->nama.empty()) {
                data_narapidana.narapidana[data_narapidana.jumlah_narapidana++] = ptrNarapidana;
            } else {
                delete ptrNarapidana;
            }
        }
        file.close();
    } else {
        cout << "Gagal membaca data narapidana dari file." << endl;
    }
}

void simpanDataPenjagaPenjaraKeFile() {
    ofstream file("data_penjaga_penjara.txt");
    if (file.is_open()) {
        for (int i = 0; i < data_narapidana.jumlah_penjaga_penjara; ++i) {
            file << data_narapidana.penjaga_penjara[i]->nama << endl;
            file << data_narapidana.penjaga_penjara[i]->nomor_identifikasi << endl;
            file << data_narapidana.penjaga_penjara[i]->posisi << endl;
            file << data_narapidana.penjaga_penjara[i]->tanggal_mulai_bertugas << endl;
        }
        file.close();
    } else {
        cout << "Gagal menyimpan data penjaga penjara ke dalam file." << endl;
    }
}

void bacaDataPenjagaPenjaraDariFile() {
    ifstream file("data_penjaga_penjara.txt");
    if (file.is_open()) {
        data_narapidana.jumlah_penjaga_penjara = 0; // Reset jumlah penjaga penjara
        while (!file.eof() && data_narapidana.jumlah_penjaga_penjara < MAX_PENJAGA_PENJARA) {
            PenjagaPenjara* ptrPenjagaPenjara = new PenjagaPenjara;
            getline(file, ptrPenjagaPenjara->nama);
            getline(file, ptrPenjagaPenjara->nomor_identifikasi);
            getline(file, ptrPenjagaPenjara->posisi);
            getline(file, ptrPenjagaPenjara->tanggal_mulai_bertugas);
            if (!ptrPenjagaPenjara->nama.empty()) {
                data_narapidana.penjaga_penjara[data_narapidana.jumlah_penjaga_penjara++] = ptrPenjagaPenjara;
            } else {
                delete ptrPenjagaPenjara;
            }
        }
        file.close();
    } else {
        cout << "Gagal membaca data penjaga penjara dari file." << endl;
    }
}

bool isEmpty() {
    return data_narapidana.jumlah_narapidana == 0;
}

bool login() {
    int i = 0;
    string nama, NIM;

    while (i < MAX_LOGIN_ATTEMPTS) {
        cout << "Masukkan nama: ";
        getline(cin, nama);
        cout << "Masukkan NIM: ";
        getline(cin, NIM);

        if (nama.empty() || NIM.empty()) {
            cout << "Nama dan NIM tidak boleh kosong!" << endl;
            continue;
        }

        if (nama == "kelompok 6" && NIM == "1234") {
            cout << "Selamat, login berhasil!" << endl;
            return true;
        } else {
            int remainingAttempts = MAX_LOGIN_ATTEMPTS - i - 1;
            if (remainingAttempts > 0) {
                cout << "Maaf, login gagal. Nama atau NIM salah." << endl;
                cout << "Anda memiliki " << remainingAttempts << " kesempatan login tersisa." << endl;
            } else {
                cout << "Maaf, login gagal. Batas percobaan login tercapai." << endl;
                return false;
            }
            i++;
        }
    }

    return false;
}

void add() {
    char loop;
    do {
        if (data_narapidana.jumlah_narapidana < MAX_NARAPIDANA) {
            Narapidana* ptrNarapidana = new Narapidana;

            cout << "Masukkan nama narapidana: ";
            getline(cin, ptrNarapidana->nama);
            cout << "Masukkan nomor identifikasi narapidana: ";
            getline(cin, ptrNarapidana->nomor_identifikasi);
            cout << "Masukkan jenis kejahatan: ";
            getline(cin, ptrNarapidana->jenis_kejahatan);
            cout << "Masukkan tanggal masuk penjara: ";
            getline(cin, ptrNarapidana->tanggal_masuk_penjara);
            cout << "Masukkan jangka waktu hukuman: ";
            getline(cin, ptrNarapidana->jangka_waktu_hukuman);
            cout << "Masukkan status kesehatan: ";
            getline(cin, ptrNarapidana->status_kesehatan);

            data_narapidana.narapidana[data_narapidana.jumlah_narapidana++] = ptrNarapidana;
        } else {
            cout << "===DATA NARAPIDANA SUDAH PENUH===" << endl;
        }

        cout << "Tambahkan data narapidana lain (y/t): ";
        cin >> loop;
        cin.ignore();
    } while (loop == 'y');
}

void addPenjagaPenjara() {
    char loop;
    do {
        if (data_narapidana.jumlah_penjaga_penjara < MAX_PENJAGA_PENJARA) {
            PenjagaPenjara* ptrPenjagaPenjara = new PenjagaPenjara;

            cout << "Masukkan nama penjaga penjara: ";
            getline(cin, ptrPenjagaPenjara->nama);
            cout << "Masukkan nomor identifikasi penjaga penjara: ";
            getline(cin, ptrPenjagaPenjara->nomor_identifikasi);
            cout << "Masukkan posisi penjaga penjara: ";
            getline(cin, ptrPenjagaPenjara->posisi);
            cout << "Masukkan tanggal mulai bertugas: ";
            getline(cin, ptrPenjagaPenjara->tanggal_mulai_bertugas);

            data_narapidana.penjaga_penjara[data_narapidana.jumlah_penjaga_penjara++] = ptrPenjagaPenjara;
        } else {
            cout << "===DATA PENJAGA PENJARA SUDAH PENUH===" << endl;
        }

        cout << "Tambahkan data penjaga penjara lain (y/t): ";
        cin >> loop;
        cin.ignore();
    } while (loop == 'y');
}

void display() {
    if (!isEmpty()) {
        for (int i = 0; i < data_narapidana.jumlah_narapidana; i++) {
            cout << "Narapidana #" << (i + 1) << endl;
            cout << "Nama: " << data_narapidana.narapidana[i]->nama << endl;
            cout << "Nomor Identifikasi: " << data_narapidana.narapidana[i]->nomor_identifikasi << endl;
            cout << "Jenis Kejahatan: " << data_narapidana.narapidana[i]->jenis_kejahatan << endl;
            cout << "Tanggal Masuk Penjara: " << data_narapidana.narapidana[i]->tanggal_masuk_penjara << endl;
            cout << "Jangka Waktu Hukuman: " << data_narapidana.narapidana[i]->jangka_waktu_hukuman << endl;
            cout << "Status Kesehatan: " << data_narapidana.narapidana[i]->status_kesehatan << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DITAMPILKAN===" << endl;
    }
}

void displayPenjagaPenjara() {
    if (data_narapidana.jumlah_penjaga_penjara > 0) {
        for (int i = 0; i < data_narapidana.jumlah_penjaga_penjara; i++) {
            cout << "Penjaga Penjara #" << (i + 1) << endl;
            cout << "Nama: " << data_narapidana.penjaga_penjara[i]->nama << endl;
            cout << "Nomor Identifikasi: " << data_narapidana.penjaga_penjara[i]->nomor_identifikasi << endl;
            cout << "Posisi: " << data_narapidana.penjaga_penjara[i]->posisi << endl;
            cout << "Tanggal Mulai Bertugas: " << data_narapidana.penjaga_penjara[i]->tanggal_mulai_bertugas << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DITAMPILKAN===" << endl;
    }
}

void deleteNarapidana() {
    if (!isEmpty()) {
        display();
        int index;
        cout << "Masukkan nomor narapidana yang ingin dihapus: ";
        cin >> index;
        cin.ignore();

        if (index > 0 && index <= data_narapidana.jumlah_narapidana) {
            delete data_narapidana.narapidana[index - 1];

            for (int i = index - 1; i < data_narapidana.jumlah_narapidana - 1; i++) {
                data_narapidana.narapidana[i] = data_narapidana.narapidana[i + 1];
            }

            data_narapidana.jumlah_narapidana--;
            cout << "Narapidana berhasil dihapus." << endl;
        } else {
            cout << "Nomor narapidana tidak valid." << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DIHAPUS===" << endl;
    }
}

void deletePenjagaPenjara() {
    if (data_narapidana.jumlah_penjaga_penjara > 0) {
        displayPenjagaPenjara();
        int index;
        cout << "Masukkan nomor penjaga penjara yang ingin dihapus: ";
        cin >> index;
        cin.ignore();

        if (index > 0 && index <= data_narapidana.jumlah_penjaga_penjara) {
            delete data_narapidana.penjaga_penjara[index - 1];

            for (int i = index - 1; i < data_narapidana.jumlah_penjaga_penjara - 1; i++) {
                data_narapidana.penjaga_penjara[i] = data_narapidana.penjaga_penjara[i + 1];
            }

            data_narapidana.jumlah_penjaga_penjara--;
            cout << "Penjaga penjara berhasil dihapus." << endl;
        } else {
            cout << "Nomor penjaga penjara tidak valid." << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DIHAPUS===" << endl;
    }
}

void updateNarapidana() {
    if (!isEmpty()) {
        display();
        int index;
        cout << "Masukkan nomor narapidana yang ingin diubah: ";
        cin >> index;
        cin.ignore();

        if (index > 0 && index <= data_narapidana.jumlah_narapidana) {
            Narapidana* ptrNarapidana = data_narapidana.narapidana[index - 1];

            cout << "Masukkan nama narapidana baru: ";
            getline(cin, ptrNarapidana->nama);
            cout << "Masukkan nomor identifikasi narapidana baru: ";
            getline(cin, ptrNarapidana->nomor_identifikasi);
            cout << "Masukkan jenis kejahatan baru: ";
            getline(cin, ptrNarapidana->jenis_kejahatan);
            cout << "Masukkan tanggal masuk penjara baru: ";
            getline(cin, ptrNarapidana->tanggal_masuk_penjara);
            cout << "Masukkan jangka waktu hukuman baru: ";
            getline(cin, ptrNarapidana->jangka_waktu_hukuman);
            cout << "Masukkan status kesehatan baru: ";
            getline(cin, ptrNarapidana->status_kesehatan);

            cout << "Narapidana berhasil diupdate." << endl;
        } else {
            cout << "Nomor narapidana tidak valid." << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DIUBAH===" << endl;
    }
}

void updatePenjagaPenjara() {
    if (data_narapidana.jumlah_penjaga_penjara > 0) {
        displayPenjagaPenjara();
        int index;
        cout << "Masukkan nomor penjaga penjara yang ingin diubah: ";
        cin >> index;
        cin.ignore();

        if (index > 0 && index <= data_narapidana.jumlah_penjaga_penjara) {
            PenjagaPenjara* ptrPenjagaPenjara = data_narapidana.penjaga_penjara[index - 1];

            cout << "Masukkan nama penjaga penjara baru: ";
            getline(cin, ptrPenjagaPenjara->nama);
            cout << "Masukkan nomor identifikasi penjaga penjara baru: ";
            getline(cin, ptrPenjagaPenjara->nomor_identifikasi);
            cout << "Masukkan posisi penjaga penjara baru: ";
            getline(cin, ptrPenjagaPenjara->posisi);
            cout << "Masukkan tanggal mulai bertugas baru: ";
            getline(cin, ptrPenjagaPenjara->tanggal_mulai_bertugas);

            cout << "Penjaga penjara berhasil diupdate." << endl;
        } else {
            cout << "Nomor penjaga penjara tidak valid." << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DIUBAH===" << endl;
    }
}

void sortByName() {
    if (!isEmpty()) {
        for (int i = 0; i < data_narapidana.jumlah_narapidana - 1; ++i) {
            for (int j = 0; j < data_narapidana.jumlah_narapidana - i - 1; ++j) {
                if (data_narapidana.narapidana[j]->nama > data_narapidana.narapidana[j + 1]->nama) {
                    swap(data_narapidana.narapidana[j], data_narapidana.narapidana[j + 1]);
                }
            }
        }
        cout << "Data narapidana berhasil diurutkan berdasarkan nama." << endl;
    } else {
        cout << "===TIDAK ADA DATA UNTUK DIURUTKAN===" << endl;
    }
}

void searchByID() {
    if (!isEmpty()) {
        string nomor_identifikasi;
        cout << "Masukkan nomor identifikasi narapidana: ";
        getline(cin, nomor_identifikasi);

        bool found = false;
        for (int i = 0; i < data_narapidana.jumlah_narapidana; i++) {
            if (data_narapidana.narapidana[i]->nomor_identifikasi == nomor_identifikasi) {
                cout << "Narapidana #" << (i + 1) << endl;
                cout << "Nama: " << data_narapidana.narapidana[i]->nama << endl;
                cout << "Nomor Identifikasi: " << data_narapidana.narapidana[i]->nomor_identifikasi << endl;
                cout << "Jenis Kejahatan: " << data_narapidana.narapidana[i]->jenis_kejahatan << endl;
                cout << "Tanggal Masuk Penjara: " << data_narapidana.narapidana[i]->tanggal_masuk_penjara << endl;
                cout << "Jangka Waktu Hukuman: " << data_narapidana.narapidana[i]->jangka_waktu_hukuman << endl;
                cout << "Status Kesehatan: " << data_narapidana.narapidana[i]->status_kesehatan << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Narapidana dengan nomor identifikasi " << nomor_identifikasi << " tidak ditemukan." << endl;
        }
    } else {
        cout << "===TIDAK ADA DATA UNTUK DICARI===" << endl;
    }
}

int main() {
    int pilihan;
    data_narapidana.jumlah_narapidana = 0;
    data_narapidana.jumlah_penjaga_penjara = 0;

    if (login()) {
        do {
            cout << "\n===== MENU =====" << endl;
            cout << "1. Tambah Data Narapidana" << endl;
            cout << "2. Tambah Data Penjaga Penjara" << endl;
            cout << "3. Tampilkan Data Narapidana" << endl;
            cout << "4. Tampilkan Data Penjaga Penjara" << endl;
            cout << "5. Hapus Data Narapidana" << endl;
            cout << "6. Hapus Data Penjaga Penjara" << endl;
            cout << "7. Update Data Narapidana" << endl;
            cout << "8. Update Data Penjaga Penjara" << endl;
            cout << "9. Urutkan Data Narapidana Berdasarkan Nama" << endl;
            cout << "10. Cari Data Narapidana Berdasarkan Nomor Identifikasi" << endl;
            cout << "11. Simpan Data Narapidana ke File" << endl;
            cout << "12. Baca Data Narapidana dari File" << endl;
            cout << "13. Simpan Data Penjaga Penjara ke File" << endl;
            cout << "14. Baca Data Penjaga Penjara dari File" << endl;
            cout << "0. Keluar" << endl;

            cout << "Pilih menu: ";
            cin >> pilihan;
            cin.ignore();

            switch (pilihan) {
                case 1:
                    add();
                    break;
                case 2:
                    addPenjagaPenjara();
                    break;
                case 3:
                    display();
                    break;
                case 4:
                    displayPenjagaPenjara();
                    break;
                case 5:
                    deleteNarapidana();
                    break;
                case 6:
                    deletePenjagaPenjara();
                    break;
                case 7:
                    updateNarapidana();
                    break;
                case 8:
                    updatePenjagaPenjara();
                    break;
                case 9:
                    sortByName();
                    break;
                case 10:
                    searchByID();
                    break;
                case 11:
                    simpanDataNarapidanaKeFile();
                    break;
                case 12:
                    bacaDataNarapidanaDariFile();
                    break;
                case 13:
                    simpanDataPenjagaPenjaraKeFile();
                    break;
                case 14:
                    bacaDataPenjagaPenjaraDariFile();
                    break;
                case 0:
                    cout << "Keluar program." << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        } while (pilihan != 0);
    }

    return 0;
}