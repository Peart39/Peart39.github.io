#include <bits/stdc++.h>
using namespace std;

class MonHoc {
public:
    string maMon, tenMon;
    int soTinChi;
    float diem;

    void nhap() {
        cout << "Ma mon: ";
        cin >> maMon;

        cout << "Ten mon: ";
        cin.ignore();
        getline(cin, tenMon);

        do {
            cout << "So tin chi (1-5): ";
            cin >> soTinChi;
        } while (soTinChi < 1 || soTinChi > 5);

        do {
            cout << "Diem (0-10): ";
            cin >> diem;
        } while (diem < 0 || diem > 10);
    }
};

class SinhVien {
public:
    string maSV, hoTen, ngaySinh;
    vector<MonHoc> dsMon;

    bool hopLeNgaySinh(string s) {
        if (s.size() != 10) return false;
        if (s[2] != '/' || s[5] != '/') return false;

        int d = stoi(s.substr(0, 2));
        int m = stoi(s.substr(3, 2));
        int y = stoi(s.substr(6, 4));

        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;
        if (y < 1900 || y > 2025) return false;
        return true;
    }

    void nhap() {
        do {
            cout << "Ma SV (11 ky tu): ";
            cin >> maSV;
        } while (maSV.size() != 11);

        cout << "Ho ten: ";
        cin.ignore();
        getline(cin, hoTen);

        do {
            cout << "Ngay sinh (dd/mm/yyyy): ";
            getline(cin, ngaySinh);
        } while (!hopLeNgaySinh(ngaySinh));

        int soMon;
        do {
            cout << "Nhap so mon hoc (>0): ";
            cin >> soMon;
        } while (soMon <= 0);

        dsMon.resize(soMon);
        for (int i = 0; i < soMon; i++) {
            cout << "\nNhap mon thu " << i + 1 << ":\n";
            dsMon[i].nhap();
        }
    }

    float diemTB() const {
        float sum = 0;
        for (auto &m : dsMon) sum += m.diem;
        return dsMon.empty() ? 0 : sum / dsMon.size();
    }

    bool duocHocBong() const {
        if (diemTB() < 7) return false;
        for (auto &m : dsMon)
            if (m.diem < 5) return false;
        return true;
    }

    int getNamSinh() const {
        return stoi(ngaySinh.substr(6, 4));
    }
};

class DanhSachSV {
    vector<SinhVien> ds;

public:

    void nhapDS() {
        int n;
        do {
            cout << "Nhap so SV (>0): ";
            cin >> n;
        } while (n <= 0);

        ds.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "\n===== Nhap SV thu " << i + 1 << " =====\n";
            ds[i].nhap();
        }
    }

    bool timMaVaSuaTen(string ma, string tenMoi) {
        for (auto &sv : ds)
            if (sv.maSV == ma) {
                sv.hoTen = tenMoi;
                return true;
            }
        return false;
    }

    void sapXepTheoTenGiam() {
        for (int i = 1; i < ds.size(); i++) {
            SinhVien key = ds[i];
            int j = i - 1;
            while (j >= 0 && ds[j].hoTen < key.hoTen) {
                ds[j + 1] = ds[j];
                j--;
            }
            ds[j + 1] = key;
        }
    }

    void sapXepTheoTenTang() {
        for (int i = 1; i < ds.size(); i++) {
            SinhVien key = ds[i];
            int j = i - 1;
            while (j >= 0 && ds[j].hoTen > key.hoTen) {
                ds[j + 1] = ds[j];
                j--;
            }
            ds[j + 1] = key;
        }
    }

    bool timTenVaXoa(string ten) {
        sapXepTheoTenTang();

        int l = 0, r = ds.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (ds[mid].hoTen == ten) {
                ds.erase(ds.begin() + mid);
                return true;
            }
            if (ds[mid].hoTen < ten) l = mid + 1;
            else r = mid - 1;
        }
        return false;
    }

    void sapXepTheoDiemTB() {
        int n = ds.size();
        for (int i = 0; i < n - 1; i++) {
            int minPos = i;
            for (int j = i + 1; j < n; j++)
                if (ds[j].diemTB() < ds[minPos].diemTB())
                    minPos = j;
            swap(ds[i], ds[minPos]);
        }
    }

    void inHocBong() {
        cout << "\n=== DANH SACH SINH VIEN HOC BONG ===\n";
        for (auto &sv : ds)
            if (sv.duocHocBong())
                cout << sv.hoTen << " | DTB: " << sv.diemTB() << endl;
    }

    void quickSort(int l, int r) {
        int i = l, j = r;
        int pivot = ds[(l + r) / 2].getNamSinh();

        while (i <= j) {
            while (ds[i].getNamSinh() < pivot) i++;
            while (ds[j].getNamSinh() > pivot) j--;
            if (i <= j) {
                swap(ds[i], ds[j]);
                i++; j--;
            }
        }
        if (l < j) quickSort(l, j);
        if (i < r) quickSort(i, r);
    }

    void sapXepTheoNamSinh() {
        if (!ds.empty())
            quickSort(0, ds.size() - 1);
    }

    void xuat() {
        cout << "\n===== DANH SACH SINH VIEN =====\n";
        for (auto &sv : ds)
            cout << setw(12) << sv.maSV << " | "
                 << setw(20) << sv.hoTen << " | "
                 << sv.ngaySinh << " | DTB: "
                 << fixed << setprecision(2) << sv.diemTB() << endl;
    }
};

int main() {
    DanhSachSV ql;
    ql.nhapDS();

    cout << "\n--- b. Sua ten theo ma ---\n";
    string ma, tenMoi;
    cout << "Nhap ma SV: ";
    cin >> ma;
    cin.ignore();
    cout << "Nhap ten moi: ";
    getline(cin, tenMoi);

    if (ql.timMaVaSuaTen(ma, tenMoi))
        cout << "Cap nhat thanh cong!\n";
    else
        cout << "Khong tim thay!\n";

    cout << "\n--- c. Sap xep ten giam dan ---\n";
    ql.sapXepTheoTenGiam();
    ql.xuat();

    cout << "\n--- d. Xoa theo ten ---\n";
    string tenXoa;
    cout << "Nhap ten can xoa: ";
    getline(cin, tenXoa);

    if (ql.timTenVaXoa(tenXoa))
        cout << "Da xoa!\n";
    else
        cout << "Khong tim thay!\n";

    ql.xuat();

    cout << "\n--- e. Sap xep theo diem TB ---\n";
    ql.sapXepTheoDiemTB();
    ql.xuat();

    cout << "\n--- f. Sinh vien hoc bong ---\n";
    ql.inHocBong();

    cout << "\n--- g. Sap xep theo nam sinh ---\n";
    ql.sapXepTheoNamSinh();
    ql.xuat();

    return 0;
}

