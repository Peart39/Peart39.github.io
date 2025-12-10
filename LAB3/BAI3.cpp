#include <iostream>
#include <string>
using namespace std;

class Node {
    friend class Stack;
private:
    char _data;
    Node* _pNext;
public:
    Node(char data) {
        _data = data;
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

    void push(char data) {
        Node* pAdd = new Node(data);
        pAdd->_pNext = _pTop;
        _pTop = pAdd;
    }

    char pop() {
        if (isEmpty()) return '\0';

        Node* pTemp = _pTop;
        char temp = pTemp->_data;
        _pTop = _pTop->_pNext;
        delete pTemp;

        return temp;
    }

    char top() const {
        if (isEmpty()) return '\0';
        return _pTop->_data;
    }
};

int priority(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

string infixToPostfix(const string& infix) {
    Stack st;
    string postfix = "";

    for (char c : infix) {

        // Bo qua khoang trang
        if (c == ' ') continue;

        // Neu la toan hang dua vao output
        if (isalnum(c)) {
            postfix += c;
        }
        // Neu gap '(' ? push vao stack
        else if (c == '(') {
            st.push(c);
        }
        // Neu gap ')'
        else if (c == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                postfix += st.pop();
            }
            st.pop(); // Bo dau '('
        }
        // Neu la toan tu
        else if (isOperator(c)) {
            while (!st.isEmpty() && priority(st.top()) >= priority(c)) {
                postfix += st.pop();
            }
            st.push(c);
        }
    }

    // Pop het toan tu con lai trong stack
    while (!st.isEmpty()) {
        postfix += st.pop();
    }

    return postfix;
}

int main() {
    string expr;
    cout << "Nhap bieu thuc trung to: ";
    getline(cin, expr);

    cout << "Bieu thuc hau to: " << infixToPostfix(expr) << endl;

    return 0;
}

