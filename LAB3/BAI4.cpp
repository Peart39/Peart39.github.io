#include <iostream>
using namespace std;

class Node {
    friend class Stack;
private:
    int _low, _high;
    Node* _pNext;

public:
    Node(int low, int high) {
        _low = low;
        _high = high;
        _pNext = NULL;
    }
};

class Stack {
private:
    Node* _pTop;

public:
    Stack() {
        _pTop = NULL;
    }

    ~Stack() {
        while (!isEmpty()) {
            int l, h;
            pop(l, h);
        }
    }

    bool isEmpty() const {
        return (_pTop == NULL);
    }

    void push(int low, int high) {
        Node* pAdd = new Node(low, high);
        pAdd->_pNext = _pTop;
        _pTop = pAdd;
    }

    void pop(int &low, int &high) {
        if (isEmpty()) return;

        Node* pTemp = _pTop;
        low = pTemp->_low;
        high = pTemp->_high;

        _pTop = _pTop->_pNext;
        delete pTemp;
    }
};

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortIterative(int arr[], int n) {
    Stack st;
    st.push(0, n - 1);

    while (!st.isEmpty()) {
        int low, high;
        st.pop(low, high);

        if (low < high) {
            int p = partition(arr, low, high);

            if (p - 1 > low)
                st.push(low, p - 1);

            if (p + 1 < high)
                st.push(p + 1, high);
        }
    }
}

int main() {
    int n;

    cout << "Nhap so phan tu: ";
    cin >> n;

    int* arr = new int[n];

    cout << "Nhap cac phan tu:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    quickSortIterative(arr, n);

    cout << "Mang sau khi sap xep: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    delete[] arr;
    return 0;
}

