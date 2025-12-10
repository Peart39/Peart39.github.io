#include <iostream>
using namespace std;

class LinearSearchArray {
private:
    int A[100];
    int n;
public:
    void nhap() {
        do {
            cout << "Nhap so phan tu n: ";
            cin >> n;
        } 
		while (n <= 0 || n > 100);
        cout << "Nhap cac phan tu:\n";
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
    }

    void xuat() const {
        cout << "Mang: ";
        for (int i = 0; i < n; i++)
            cout << A[i] << " ";
        cout << endl;
    }

    void timall(int x) const {
        bool found = false;
        cout << "Cac vi tri co gia tri " << x << ": ";
        for (int i = 0; i < n; i++) {
            if (A[i] == x) {
                cout << i << " ";
                found = true;
            }
        }
        if (!found)
            cout << "Khong co";
        cout << endl;
    }
};

int main() {
    LinearSearchArray arr;
    arr.nhap();
    arr.xuat();
    int x;
    cout << "Nhap khoa can tim: ";
    cin >> x;
    arr.timall(x);
    return 0;
}

