#include <iostream>
#include <string>
using namespace std;

class NodeA {
    friend class ListA;
private:
    int _data;
    NodeA* _pNext;

public:
    NodeA(int ghe) {
        _data = ghe;
        _pNext = NULL;
    }
};

class ListA {
private:
    NodeA* _pHead;

public:
    ListA() {
        _pHead = NULL;
    }

    bool isEmpty() {
        return (_pHead == NULL);
    }

    void addLast(int x) {
        NodeA* pAdd = new NodeA(x);
        if (!_pHead) {
            _pHead = pAdd;
        }
        else {
            NodeA* p = _pHead;
            while (p->_pNext)
                p = p->_pNext;
            p->_pNext = pAdd;
        }
    }

    int removeFirst() {
        if (isEmpty()) return -1;

        NodeA* pTemp = _pHead;
        int val = pTemp->_data;

        _pHead = _pHead->_pNext;
        delete pTemp;

        return val;
    }

    void addFirst(int x) {
        NodeA* pAdd = new NodeA(x);
        pAdd->_pNext = _pHead;
        _pHead = pAdd;
    }
};

class NodeB {
    friend class QueueB;
private:
    int _data;
    NodeB* _pNext;

public:
    NodeB(int stt) {
        _data = stt;
        _pNext = NULL;
    }
};

class QueueB {
private:
    NodeB* _pFront;
    NodeB* _pRear;

public:
    QueueB() {
        _pFront = _pRear = NULL;
    }

    bool isEmpty() {
        return (_pFront == NULL);
    }

    void push(int stt) {
        NodeB* pAdd = new NodeB(stt);

        if (isEmpty()) {
            _pFront = _pRear = pAdd;
        }
        else {
            _pRear->_pNext = pAdd;
            _pRear = pAdd;
        }
    }

    int pop() {
        if (isEmpty()) return -1;

        NodeB* pTemp = _pFront;
        int val = pTemp->_data;

        _pFront = _pFront->_pNext;
        delete pTemp;

        if (!_pFront) _pRear = NULL;

        return val;
    }

    int lastValue() {
        if (isEmpty()) return 0;
        return _pRear->_data;
    }
};

class NodeC {
    friend class ListC;
private:
    string _ten;
    int _ghe;
    NodeC* _pNext;

public:
    NodeC(string ten, int ghe) {
        _ten = ten;
        _ghe = ghe;
        _pNext = NULL;
    }
};

class ListC {
private:
    NodeC* _pHead;

public:
    ListC() {
        _pHead = NULL;
    }

    void addLast(string ten, int ghe) {
        NodeC* pAdd = new NodeC(ten, ghe);

        if (!_pHead) {
            _pHead = pAdd;
        }
        else {
            NodeC* p = _pHead;
            while (p->_pNext)
                p = p->_pNext;
            p->_pNext = pAdd;
        }
    }

    bool removeByName(string ten, int& gheOut) {
        NodeC* p = _pHead;
        NodeC* prev = NULL;

        while (p) {
            if (p->_ten == ten) {

                gheOut = p->_ghe;

                if (prev)
                    prev->_pNext = p->_pNext;
                else
                    _pHead = p->_pNext;

                delete p;
                return true;
            }
            prev = p;
            p = p->_pNext;
        }
        return false;
    }

    void print() {
        cout << "Danh sach khach da mua ve:\n";

        if (!_pHead) {
            cout << "(rong)\n";
            return;
        }

        NodeC* p = _pHead;
        while (p) {
            cout << "- " << p->_ten << ", ghe: " << p->_ghe << endl;
            p = p->_pNext;
        }
    }
};

int main() {
    int N;
    cout << "Nhap so ghe trong rap: ";
    cin >> N;
    cin.ignore();

    ListA A;
    QueueB B;
    ListC C;

    for (int i = 1; i <= N; i++)
        A.addLast(i);

    int chon;

    do {
        cout << "1. Lay so xep hang\n"
             << "2. Mua ve\n"
             << "3. Huy ve\n"
             << "4. Hien thi danh sach da mua\n"
             << "0. Thoat\n"
             << "Nhap lua chon: ";

        cin >> chon;
        cin.ignore();

        switch (chon) {

        case 1: {
            int stt = B.lastValue() + 1;
            B.push(stt);
            cout << "So xep hang cua ban: " << stt << endl;
            break;
        }

        case 2: {
            if (A.isEmpty()) {
                cout << "Het ghe! Khong the mua ve.\n";
                break;
            }
            if (B.isEmpty()) {
                cout << "Hay lay so xep hang truoc!\n";
                break;
            }

            int stt = B.pop();
            int ghe = A.removeFirst();
            string ten;

            cout << "Nhap ten khach (STT " << stt << "): ";
            getline(cin, ten);

            C.addLast(ten, ghe);

            cout << "Da mua ve thanh cong. Ghe cua ban la: " << ghe << endl;
            break;
        }

        case 3: {
            string ten;
            cout << "Nhap ten khach muon huy ve: ";
            getline(cin, ten);

            int gheTra = -1;
            if (C.removeByName(ten, gheTra)) {
                cout << "Da huy ve cua " << ten << ". Ghe " << gheTra << " da trong lai.\n";
            }
            else {
                cout << "Khong tim thay khach nay trong danh sach mua ve.\n";
            }
            break;
        }

        case 4:
            C.print();
            break;

        case 0:
            cout << "Thoat chuong trinh...\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);

    return 0;
}

