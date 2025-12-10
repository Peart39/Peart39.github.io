#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node<T>* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    // Them cuoi
    void addLast(const T& value) {
        Node<T>* p = new Node<T>(value);
        if (isEmpty()) {
            head = p;
            return;
        }
        Node<T>* t = head;
        while (t->next) t = t->next;
        t->next = p;
    }

    // In danh sach
    void printList() const {
        if (isEmpty()) {
            cout << "(Danh sach rong)\n";
            return;
        }
        Node<T>* t = head;
        while (t) {
            cout << t->data << " ";
            t = t->next;
        }
        cout << endl;
    }

    // Tim phan tu
    Node<T>* search(const T& x) const {
        Node<T>* t = head;
        while (t) {
            if (t->data == x) return t;
            t = t->next;
        }
        return nullptr;
    }

    // Xoa phan tu dau tien bang x
    bool remove(const T& x) {
        if (isEmpty()) return false;

        // xoa dau
        if (head->data == x) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node<T>* t = head;
        while (t->next) {
            if (t->next->data == x) {
                Node<T>* del = t->next;
                t->next = del->next;
                delete del;
                return true;
            }
            t = t->next;
        }
        return false;
    }
};

int main() {

    LinkedList<int> intList;
    intList.addLast(10);
    intList.addLast(20);
    intList.addLast(30);
    cout << "Danh sach so nguyen: ";
    intList.printList();

    LinkedList<double> doubleList;
    doubleList.addLast(3.14);
    doubleList.addLast(2.718);
    doubleList.addLast(1.414);
    cout << "Danh sach so thuc: ";
    doubleList.printList();

    LinkedList<char> charList;
    charList.addLast('A');
    charList.addLast('B');
    charList.addLast('C');
    cout << "Danh sach ky tu: ";
    charList.printList();

    LinkedList<string> strList;
    strList.addLast("Hello");
    strList.addLast("World");
    strList.addLast("C++");
    cout << "Danh sach chuoi: ";
    strList.printList();

    return 0;
}

