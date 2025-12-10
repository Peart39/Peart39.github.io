#include <iostream>
#include <string>
using namespace std;

enum Type { INT, DOUBLE, CHAR, STRING };

class Data {
public:
    Type _type;
    union {
        int _i;
        double _d;
        char _c;
    };
    string _s;

    Data() {
        _type = INT;
        _i = 0;
        _s = "";
    }
};

class Node {
    friend class Stack;
private:
    Data _data;
    Node* _pNext;

public:
    Node(const Data& x) {
        _data = x;
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

    bool isEmpty() {
        return (_pTop == NULL);
    }

    void push(const Data& x) {
        Node* pAdd = new Node(x);
        pAdd->_pNext = _pTop;
        _pTop = pAdd;
    }

    Data pop() {
        if (isEmpty()) {
            cout << "Stack rong!\n";
            Data temp;
            temp._type = INT;
            temp._i = 0;
            return temp;
        }

        Node* pTemp = _pTop;
        Data value = pTemp->_data;
        _pTop = _pTop->_pNext;
        delete pTemp;
        return value;
    }

    void print(const Data& d) {
        switch (d._type) {
            case INT:    cout << d._i; break;
            case DOUBLE: cout << d._d; break;
            case CHAR:   cout << d._c; break;
            case STRING: cout << d._s; break;
        }
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

int main() {
    Stack st;
    int chon;

    do {
        cout << "1. Push INT\n"
             << "2. Push DOUBLE\n"
             << "3. Push CHAR\n"
             << "4. Push STRING\n"
             << "5. Pop 1 phan tu\n"
             << "0. Thoat\n"
             << "Nhap lua chon: ";
        cin >> chon;
        cin.ignore();

        switch (chon) {
        case 1: {
            Data x; x._type = INT;
            cout << "Nhap int: ";
            cin >> x._i; cin.ignore();
            st.push(x);
            break;
        }

        case 2: {
            Data x; x._type = DOUBLE;
            cout << "Nhap double: ";
            cin >> x._d; cin.ignore();
            st.push(x);
            break;
        }

        case 3: {
            Data x; x._type = CHAR;
            cout << "Nhap char: ";
            cin >> x._c; cin.ignore();
            st.push(x);
            break;
        }

        case 4: {
            Data x; x._type = STRING;
            cout << "Nhap string: ";
            getline(cin, x._s);
            st.push(x);
            break;
        }

        case 5: {
            Data x = st.pop();
            cout << "Pop du lieu: ";
            st.print(x);
            cout << endl;
            break;
        }

        case 0:
            cout << "tam biet\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }

    } while (chon != 0);

    return 0;
}

