#include <bits/stdc++.h>
using namespace std;

class Node {
	friend class Stack;
private:
    char _data;
    Node* _pNext;
public:
    Node(char data){
    	_data=data;
    	_pNext=NULL;
	}
};

class Stack {
private:
    Node* _pTop;

public:
    Stack(){
		_pTop=NULL;
	}
    
    void push(char data) {
        Node* pAdd = new Node(data);
        pAdd->_pNext = _pTop;
        _pTop = pAdd;
    }

	bool isEmpty(){
		return (_pTop==NULL);
	}
    char pop() {
        if (isEmpty()) return '\0';
        Node* pTemp = _pTop;
        char temp = _pTop->_data;
        _pTop = _pTop -> _pNext;
        delete pTemp;
        return temp;
    }

    char top(){
        if (isEmpty()) return '\0';
        return _pTop -> _data;
    }
};

// Ham kiem tra cap ngoac
bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// Ham kiem tra xau ngoac dung
bool isValidBracketString(const string& s) {
    Stack st;

    for (char c : s) {

        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {

            // Neu stack rong thi sai ngay
            if (st.isEmpty()) return false;

            char topChar = st.pop();

            // Neu cap ngoac khong khop thi sai
            if (!isMatching(topChar, c))
                return false;
        }
    }

    // Cuoi cung stack phai rong
    return st.isEmpty();
}

int main() {
    string s;
    cout << "Nhap xau ngoac: ";
    getline(cin, s);

    if (isValidBracketString(s))
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}

