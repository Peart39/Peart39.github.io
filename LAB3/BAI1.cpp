#include <iostream>
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

    ~Stack() {
        while (!isEmpty()) pop();
    }

    bool isEmpty() const {
        return (_pTop == NULL);
    }

    void push(int x) {
        Node* pAdd = new Node(x);
        pAdd->_pNext = _pTop;
        _pTop = pAdd;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack rong!\n";
            return -1;
        }

        Node* pTemp = _pTop;
        int value = pTemp->_data;

        _pTop = _pTop->_pNext;
        delete pTemp;

        return value;
    }

    int top() const {
        if (isEmpty()) return -1;
        return _pTop->_data;
    }
};

string convertToBinary(int n) {
    if (n == 0) return "0";

    Stack st;
    while (n > 0) {
        st.push(n % 2);   // push bit cuoi
        n /= 2;
    }

    string result = "";
    while (!st.isEmpty()) {
        result += char(st.pop() + '0');  // lay ra tung bit
    }
    return result;
}

int main() {
    int n;
    cout << "Nhap so nguyen duong N: ";
    cin >> n;

    cout << "Dang nhi phan: " << convertToBinary(n) << endl;

    return 0;
}

