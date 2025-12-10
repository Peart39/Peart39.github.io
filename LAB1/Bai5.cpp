#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Sach {
public:
    string maSach, tuaSach;
    int namXB, gia;

    void nhap() {
        do {
            cout << "Ma sach (toi da 6 ky tu): ";
            cin >> maSach;
        } 
		while (maSach.size() > 6);

        cout << "Tua sach: "; cin.ignore(); getline(cin, tuaSach);
        do {
            cout << "Nam xuat ban (>1900): "; cin >> namXB;
        } 
		while (namXB <= 1900);
        do {
            cout << "Gia (toi da 6 chu so): "; cin >> gia;
        } 
		while (gia <= 0 || gia > 999999);
    }
};

class ThuVien {
    vector<Sach> ds;
public:
    void nhapDS() {
        int n; 
		cout << "Nhap so luong sach: "; 
		cin >> n;
        ds.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "\n== Sach thu " << i + 1 << " ==\n";
            ds[i].nhap();
        }
    }

    void xuatDS() {
        cout << "\n=== DANH SACH SACH ===\n";
        for (auto &s : ds)
            cout << left << setw(8) << s.maSach
                 << setw(30) << s.tuaSach
                 << setw(10) << s.namXB
                 << setw(10) << s.gia << endl;
    }

    void timVaSuaGiaTheoTua(string x, int y) {
        for (auto &s : ds)
            if (s.tuaSach == x) {
                s.gia = y;
                cout << "Da sua gia sach.\n";
                return;
            }
        cout << "Khong tim thay tua sach.\n";
    }

    void selectionSort_Ma() {
        int n = ds.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++)
                if (ds[j].maSach < ds[minIdx].maSach)
                    minIdx = j;
            swap(ds[i], ds[minIdx]);
        }
    }

    void xoaTheoMa(string ma) {
        selectionSort_Ma();
        int left = 0, right = ds.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (ds[mid].maSach == ma) {
                ds.erase(ds.begin() + mid);
                cout << "Da xoa sach co ma: " << ma << endl;
                return;
            } 
			else if (ds[mid].maSach < ma) left = mid + 1;
            	else right = mid - 1;
        }
        cout << "Khong tim thay ma sach.\n";
    }

    void insertionSort_NamXB() {
        for (int i = 1; i < ds.size(); i++) {
            Sach key = ds[i];
            int j = i - 1;

            while (j >= 0 && ds[j].namXB < key.namXB) {
                ds[j + 1] = ds[j];
                j--;
            }
            ds[j + 1] = key;
        }
    }

    void bubbleSort_Tua() {
        for (int i = 0; i < ds.size() - 1; i++)
            for (int j = 0; j < ds.size() - i - 1; j++)
                if (ds[j].tuaSach > ds[j + 1].tuaSach)
                    swap(ds[j], ds[j + 1]);
    }

    int partitionGia(int low, int high) {
        int pivot = ds[high].gia;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (ds[j].gia > pivot) {     
                i++;
                swap(ds[i], ds[j]);
            }
        }
        swap(ds[i + 1], ds[high]);
        return i + 1;
    }

    void quickSortGia(int low, int high) {
        if (low < high) {
            int pi = partitionGia(low, high);
            quickSortGia(low, pi - 1);
            quickSortGia(pi + 1, high);
        }
    }

    void quickSort_Gia() {
        if (!ds.empty())
            quickSortGia(0, ds.size() - 1);
    }
};

int main() {
    ThuVien tv;

    cout << "===== Cau a =====\n";
    tv.nhapDS();
    tv.xuatDS();

    cout << "\n===== Cau b: Tim tua & sua gia =====\n";
    cin.ignore();
    string tua;
    int g;
    cout << "Nhap tua sach can sua: ";
    getline(cin, tua);
    cout << "Nhap gia moi: ";
    cin >> g;
    tv.timVaSuaGiaTheoTua(tua, g);
    tv.xuatDS();

    cout << "\n===== Cau c: Xoa theo ma (Binary Search) =====\n";
    cin.ignore();
    string ma;
    cout << "Nhap ma sach can xoa: ";
    getline(cin, ma);
    tv.xoaTheoMa(ma);
    tv.xuatDS();

    cout << "\n===== Cau d: SelectionSort tang dan theo ma =====\n";
    tv.selectionSort_Ma();
    tv.xuatDS();

    cout << "\n===== Cau e: InsertionSort giam dan theo nam XB =====\n";
    tv.insertionSort_NamXB();
    tv.xuatDS();

    cout << "\n===== Cau f: BubbleSort tang dan theo tua sach =====\n";
    tv.bubbleSort_Tua();
    tv.xuatDS();

    cout << "\n===== Cau g: QuickSort giam dan theo gia =====\n";
    tv.quickSort_Gia();
    tv.xuatDS();

    return 0;
}

