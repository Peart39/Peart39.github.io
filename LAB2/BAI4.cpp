#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    void addLast(int x) {
        Node* p = new Node(x);
        if (isEmpty()) {
            head = p;
            return;
        }
        Node* t = head;
        while (t->next) t = t->next;
        t->next = p;
    }

    void printList() const {
        Node* t = head;
        while (t) {
            cout << t->data << " ";
            t = t->next;
        }
        cout << endl;
    }

    bool contains(int x) const {
        Node* t = head;
        while (t) {
            if (t->data == x) return true;
            t = t->next;
        }
        return false;
    }

    // ====== Interchange Sort ======
    void sortAscending() {
        for (Node* p = head; p != nullptr; p = p->next)
            for (Node* q = p->next; q != nullptr; q = q->next)
                if (p->data > q->data)
                    swap(p->data, q->data);
    }


    // (a) 
    LinkedList differenceSorted(const LinkedList& L2) const {
        LinkedList L3;

        Node* t = head;
        while (t) {
            if (!L2.contains(t->data))
                L3.addLast(t->data);
            t = t->next;
        }

        L3.sortAscending();
        return L3;
    }

    // (b) 
    LinkedList intersectionSorted(const LinkedList& L2) const {
        LinkedList L3;

        Node* t = head;
        while (t) {
            if (L2.contains(t->data))
                L3.addLast(t->data);
            t = t->next;
        }

        L3.sortAscending();
        return L3;
    }

    // (c) 
    LinkedList unionSorted(const LinkedList& L2) const {
        LinkedList L3;

        Node* t = head;
        while (t) {
            if (!L3.contains(t->data))
                L3.addLast(t->data);
            t = t->next;
        }

        t = L2.head;
        while (t) {
            if (!L3.contains(t->data))
                L3.addLast(t->data);
            t = t->next;
        }

        L3.sortAscending();
        return L3;
    }
};

int main() {
    LinkedList L1, L2;

    cout << "Nhap L1 (nhap -1 de dung): ";
    while (true) {
        int x; cin >> x;
        if (x == -1) break;
        L1.addLast(x);
    }

    cout << "Nhap L2 (nhap -1 de dung): ";
    while (true) {
        int x; cin >> x;
        if (x == -1) break;
        L2.addLast(x);
    }

    cout << "L1: "; L1.printList();
    cout << "L2: "; L2.printList();

    cout << "\n(a) Hieu L1 - L2 (tang dan): ";
    L1.differenceSorted(L2).printList();

    cout << "\n(b) Giao L1 & L2 (tang dan): ";
    L1.intersectionSorted(L2).printList();

    cout << "\n(c) Hop L1 & L2 (tang dan): ";
    L1.unionSorted(L2).printList();

    return 0;
}

