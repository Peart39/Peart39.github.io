#include <iostream>
#include <string>
using namespace std;

class HangHoa {
public:
    string ma;
    string ten;
    int soLuong;
    double donGia;
};

class Node {
    friend class Queue;
private:
    HangHoa _data;
    Node* _pNext;

public:
    Node(const HangHoa& hh) {
        _data = hh;
        _pNext = NULL;
    }
};

class Queue {
private:
    Node* _pFront;
    Node* _pRear;

public:
    Queue() {
        _pFront = _pRear = NULL;
    }

    bool isEmpty() {
        return (_pFront == NULL);
    }

    void push(const HangHoa& hh) {
        Node* pAdd = new Node(hh);

        if (isEmpty()) {
            _pFront = _pRear = pAdd;
        } else {
            _pRear->_pNext = pAdd;
            _pRear = pAdd;
        }
    }

    HangHoa pop() {
        if (isEmpty()) {
            cout << "Kho rong!\n";
            return {"", "", 0, 0};
        }

        Node* pTemp = _pFront;
        HangHoa hh = pTemp->_data;

        _pFront = _pFront->_pNext;
        delete pTemp;

        if (_pFront == NULL)
            _pRear = NULL;

        return hh;
    }

    void inHang(const HangHoa& hh) {
        cout << "- Ma: " << hh.ma
             << ", Ten: " << hh.ten
             << ", So luong: " << hh.soLuong
             << ", Don gia: " << hh.donGia << endl;
    }

    void xemDau() {
        if (isEmpty()) {
            cout << "Kho rong!\n";
            return;
        }
        cout << "Mat hang sap xuat:\n";
        inHang(_pFront->_data);
    }

    void xemTatCa() {
        if (isEmpty()) {
            cout << "Kho rong!\n";
            return;
        }
        Node* p = _pFront;
        while (p != NULL) {
            inHang(p->_data);
            p = p->_pNext;
        }
    }

    ~Queue() {
        while (!isEmpty()) pop();
    }
};


int main() {
    Queue kho;
    int chon;

    do {
        cout << "1. Them mot mat hang\n";
        cout << "2. Xem tat ca hàng trong kho\n";
        cout << "3. Xem mat hang sap xuat\n";
        cout << "4. Xuat mot mat hang\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;
        cin.ignore();

        switch (chon) {
        case 1: {
            HangHoa hh;
            cout << "Ma hang: "; getline(cin, hh.ma);
            cout << "Ten hang: "; getline(cin, hh.ten);
            cout << "So luong: "; cin >> hh.soLuong;
            cout << "Don gia: "; cin >> hh.donGia;
            cin.ignore();

            kho.push(hh);
            break;
        }
        case 2:
            kho.xemTatCa();
            break;

        case 3:
            kho.xemDau();
            break;

        case 4: {
            HangHoa hh = kho.pop();
            if (hh.ma != "") {
                cout << "Da xuat hang: " << hh.ten << endl;
            }
            break;
        }

        case 0:
            cout << "tam biet!";
            break;

        default:
            cout << "Khong hop le! ";
        }

    } while (chon != 0);

    return 0;
}

