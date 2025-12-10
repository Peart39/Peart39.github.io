#include <iostream>
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

    LinkedList findFirstSubsequence(const LinkedList& L2) const {
        LinkedList L3;

        Node* start1 = head;

        while (start1 != nullptr) {
            Node* p1 = start1;
            Node* p2 = L2.head;

            // tim vi tri dau tien cua p1 trong L2
            while (p2 && p2->data != p1->data)
                p2 = p2->next;

            // neu khong tim thay p1 trong L2
            if (!p2) {
                start1 = start1->next;
                continue;
            }

            // kiem tra day trung
            Node* a = p1;
            Node* b = p2;

            while (a && b && a->data == b->data) {
                L3.addLast(a->data);
                a = a->next;
                b = b->next;
            }

            if (!L3.isEmpty())
                return L3;
            else
                L3 = LinkedList(); // reset

            start1 = start1->next;
        }

        return L3; // khong tim thay
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

    cout << "L3 (day con dau tien co trong L2): ";
    LinkedList L3 = L1.findFirstSubsequence(L2);
    L3.printList();

    return 0;
}

