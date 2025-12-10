#include <iostream>
using namespace std;

class Array {
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

    void xoa(int x) {
        int k = 0;
        for (int i = 0; i < n; i++)
            if (A[i] != x)
                A[k++] = A[i];
        n = k;
    }

    void xuat() const {
        cout << "Mang hien tai: ";
        for (int i = 0; i < n; i++)
            cout << A[i] << " ";
        cout << endl;
    }
};

int main() {
    Array arr;
    arr.nhap();
    int x;
    cout << "Nhap gia tri x can xoa: ";
    cin >> x;
    arr.xoa(x);
    arr.xuat();
    return 0;
}

