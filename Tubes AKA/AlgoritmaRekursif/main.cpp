#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

// Struct untuk menyimpan data pasien
struct PatientData {
    string name;
    int age;
    string disease;
};

// Fungsi untuk membangkitkan nama acak
string getRandomName(const vector<string>& firstNames, const vector<string>& lastNames) {
    return firstNames[rand() % firstNames.size()] + " " + lastNames[rand() % lastNames.size()];
}

// Fungsi untuk membangkitkan data pasien acak
vector<PatientData> generateData(int n, const vector<string>& firstNames, const vector<string>& lastNames, const vector<string>& diseases) {
    vector<PatientData> data;
    for (int i = 0; i < n; i++) {
        PatientData patient;
        patient.name = getRandomName(firstNames, lastNames);
        patient.age = rand() % 80 + 1; // Umur antara 1 hingga 80
        patient.disease = diseases[rand() % diseases.size()];
        data.push_back(patient);
    }
    return data;
}

// Fungsi Quick Sort (rekursif)
int partition(vector<PatientData>& data, int low, int high) {
    string pivot = data[high].disease;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (data[j].disease <= pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

void quickSort(vector<PatientData>& data, int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);
        quickSort(data, low, pi - 1);
        quickSort(data, pi + 1, high);
    }
}

// Fungsi Binary Search (rekursif)
int binarySearchRecursive(const vector<PatientData>& data, const string& targetDisease, int left, int right) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;
    if (data[mid].disease == targetDisease) {
        return mid;
    } else if (data[mid].disease < targetDisease) {
        return binarySearchRecursive(data, targetDisease, mid + 1, right);
    } else {
        return binarySearchRecursive(data, targetDisease, left, mid - 1);
    }
}

// Fungsi utama
int main() {
    srand(time(0));

    // Nama depan, belakang, dan penyakit umum di Indonesia
    vector<string> firstNames = {"Adi", "Budi", "Citra", "Dewi", "Eko", "Fajar", "Gita", "Hadi", "Indra", "Joko", "Kartini", "Lestari", "Maya", "Nia", "Oki", "Putu", "Qori", "Rini", "Satria", "Tina", "Umar", "Vina", "Wawan", "Yudi", "Zahra"};
    vector<string> lastNames = {"Putra", "Santoso", "Wijaya", "Permata", "Rahman", "Saputra", "Wardani", "Utami", "Kusuma", "Halim", "Pratama", "Sudirman", "Hidayat", "Fauzan", "Ramadhan", "Syahputra", "Pranoto", "Susilo", "Handoko", "Cahyadi", "Surya", "Gunawan", "Purnomo", "Wibowo", "Utomo"};
    vector<string> diseases = {"Demam", "Flu", "Batuk", "Diare", "Tipes", "Malaria", "Covid-19", "Hipertensi"};

    // Generate data acak
    int n = 100; // Jumlah data
    vector<PatientData> patients = generateData(n, firstNames, lastNames, diseases);

    // Sorting data
    auto startSort = chrono::high_resolution_clock::now();
    quickSort(patients, 0, patients.size() - 1);
    auto endSort = chrono::high_resolution_clock::now();

    // Menampilkan 100 data pertama setelah sorting
    cout << "\n100 data pertama setelah sorting:\n";
    for (int i = 0; i < 100 && i < patients.size(); i++) {
        cout << i + 1 << ". " << patients[i].disease << " - " << patients[i].name << " - " << patients[i].age << "\n";
    }

    // Menampilkan jumlah total data yang dihasilkan
    cout << "... Jumlah total data yang dihasilkan: " << patients.size() << "\n";

    // Menampilkan waktu eksekusi sorting
    chrono::duration<double> sortDuration = endSort - startSort;

    // Pencarian data penyakit
    string searchDisease;
    cout << "\nDaftar penyakit yang tersedia untuk pencarian:\n";
    for (const auto& disease : diseases) {
        cout << "- " << disease << "\n";
    }
    cout << "\nMasukkan nama penyakit yang ingin dicari: ";
    cin >> searchDisease;

    auto startSearch = chrono::high_resolution_clock::now();
    int index = binarySearchRecursive(patients, searchDisease, 0, patients.size() - 1);
    auto endSearch = chrono::high_resolution_clock::now();

    chrono::duration<double> searchDuration = endSearch - startSearch;

    if (index != -1) {
        cout << "\nHasil pencarian untuk penyakit '" << searchDisease << "':\n";
        int resultIndex = 1;
        for (int i = index; i < patients.size() && patients[i].disease == searchDisease; i++) {
            cout << resultIndex << ". " << patients[i].disease << " - " << patients[i].name << " - " << patients[i].age << "\n";
            resultIndex++;
        }
    } else {
        cout << "\nPenyakit '" << searchDisease << "' tidak ditemukan." << endl;
    }

    cout << "\nWaktu eksekusi sorting: " << sortDuration.count() << " detik" << endl;
    cout << "Waktu eksekusi pencarian: " << searchDuration.count() << " detik" << endl;


    return 0;
}
