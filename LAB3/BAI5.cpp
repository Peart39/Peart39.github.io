#include <iostream>
#include <sstream>
using namespace std;

class Node {
    friend class Stack;
private:
    int _data;
    Node* _pNext;
public:
    Node(int x) {
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

    void push(int x) {
        Node* pAdd = new Node(x);
        pAdd->_pNext = _pTop;
        _pTop = pAdd;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Loi: Stack rong!\n";
            return 0;
        }

        Node* pTemp = _pTop;
        int value = pTemp->_data;
        _pTop = _pTop->_pNext;
        delete pTemp;
        return value;
    }

    bool isEmpty() {
        return (_pTop == NULL);
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

int tinhHauTo(const string& s) {
    Stack st;
    stringstream ss(s);
    string token;

    while (ss >> token) {

        if (isdigit(token[0])) {
            st.push(stoi(token));
        }
        else {
            int b = st.pop();
            int a = st.pop();

            switch (token[0]) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
            }
        }
    }

    return st.pop();
}

int main() {
    string s;

    cout << "Nhap bieu thuc hau to (cac phan tu cach nhau boi dau cach): ";
    getline(cin, s);

    cout << "Ket qua: " << tinhHauTo(s) << endl;

    return 0;
}

