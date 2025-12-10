#include <iostream>
using namespace std;

class BinarySearchTrace {
private:
    int M[100];
    int n;
public:
    void nhap() {
        do {
            cout << "Nhap so phan tu n: ";
            cin >> n;
        } while (n <= 0 || n > 100);

        cout << "Nhap mang:\n";
        for (int i = 0; i < n; i++) {
            cin >> M[i];
        }
    }

    void xuat() const {
        cout << "Mang: ";
        for (int i = 0; i < n; i++)
            cout << M[i] << " ";
        cout << endl;
    }

	void sort() {
        for (int i = 0; i < n - 1; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (M[j] < M[min])
                    min = j;
            }
           
            int temp = M[i];
            M[i] = M[min];
            M[min] = temp;
        }
    }
    void traceSearch(int x) const {
        int left = 0, right = n - 1, count = 0;
        cout << "Qua trinh chia doi:\n";
        while (left <= right) {
            count++;
            int mid = (left + right) / 2;
            
            if (M[mid] == x) {
                cout << "Tim thay x tai vi tri " << mid << ".\n";
                break;
            } 
			else if (M[mid] > x){
				right = mid - 1;
				cout << "Lan " << count << ": x=" << x << " nam trong doan [" << left << ".." << right << "]" << " // mid = " << mid << endl;
        	}
			else{
                left = mid + 1;
                cout << "Lan " << count << ": x=" << x << " nam trong doan [" << left << ".." << right << "]" << " // mid = " << mid << endl;
            }
        }
        cout << "Tong so lan chia doi mang: " << count - 1 << endl;
    }
};

int main() {
    BinarySearchTrace bs;
    bs.nhap();
    bs.sort(); 
    bs.xuat();
    int x;
    cout << "Nhap gia tri x can tim: ";
    cin >> x;
    bs.traceSearch(x);
    return 0;
}

