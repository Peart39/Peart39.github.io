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

        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = p;
    }

    void printList() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool contains(int x) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == x) return true;
            temp = temp->next;
        }
        return false;
    }

    int length() const {
        int cnt = 0;
        Node* temp = head;
        while (temp) {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }

    int sum() const {
        int s = 0;
        Node* t = head;
        while (t) {
            s += t->data;
            t = t->next;
        }
        return s;
    }

    int findMax() const {
        if (!head) return INT_MIN;

        int mx = head->data;
        Node* t = head->next;

        while (t) {
            if (t->data > mx) mx = t->data;
            t = t->next;
        }
        return mx;
    }

    // (a) L3 = L1 noi L2
    LinkedList concatenate(const LinkedList& L2) const {
        LinkedList L3;

        Node* t = head;
        while (t) {
            L3.addLast(t->data);
            t = t->next;
        }

        t = L2.head;
        while (t) {
            L3.addLast(t->data);
            t = t->next;
        }

        return L3;
    }

    // (b) L3 = L1 - L2
    LinkedList difference(const LinkedList& L2) const {
        LinkedList L3;

        Node* t = head;
        while (t) {
            if (!L2.contains(t->data))
                L3.addLast(t->data);
            t = t->next;
        }

        return L3;
    }

    // (c) L3 = L1 giao L2
    LinkedList intersection(const LinkedList& L2) const {
        LinkedList L3;

        Node* t = head;
        while (t) {
            if (L2.contains(t->data))
                L3.addLast(t->data);
            t = t->next;
        }

        return L3;
    }

    // (d) 
    LinkedList unionList(const LinkedList& L2) const {
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

        return L3;
    }

    // (e)
    LinkedList sumList(const LinkedList& L2) const {
        LinkedList L3;

        Node* p = head;
        Node* q = L2.head;

        while (p != nullptr || q != nullptr) {
            int x = (p ? p->data : 0);
            int y = (q ? q->data : 0);

            L3.addLast(x + y);

            if (p) p = p->next;
            if (q) q = q->next;
        }

        return L3;
    }

    // (f)
    bool sameValues(const LinkedList& L2) const {
        if (length() != L2.length()) return false;

        Node* t = head;
        while (t) {
            if (!L2.contains(t->data)) return false;
            t = t->next;
        }

        t = L2.head;
        while (t) {
            if (!contains(t->data)) return false;
            t = t->next;
        }

        return true;
    }

    // (g)
    bool deleteFirstGreaterThan(const LinkedList& L2) {
        int total = L2.sum();

        while (head && head->data > total) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return true;
        }

        Node* cur = head;
        while (cur && cur->next) {
            if (cur->next->data > total) {
                Node* del = cur->next;
                cur->next = del->next;
                delete del;
                return true;
            }
            cur = cur->next;
        }

        return false;
    }

    // (h) 
    void deleteAllEqualToMaxOf(const LinkedList& L2) {
        int mx = L2.findMax();

        while (head && head->data == mx) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        Node* cur = head;
        while (cur && cur->next) {
            if (cur->next->data == mx) {
                Node* del = cur->next;
                cur->next = del->next;
                delete del;
            } else {
                cur = cur->next;
            }
        }
    }
};

int main() {
    LinkedList L1, L2;

    cout << "Nhap danh sach L1 (nhap -1 de ket thuc):\n";
    while (true) {
        int x;
        cin >> x;
        if (x == -1) break;
        L1.addLast(x);
    }

    cout << "Nhap danh sach L2 (nhap -1 de ket thuc):\n";
    while (true) {
        int x;
        cin >> x;
        if (x == -1) break;
        L2.addLast(x);
    }

    cout << "\nL1: "; L1.printList();
    cout << "L2: "; L2.printList();


    cout << "\n(a) Noi L2 vao sau L1:\n";
    LinkedList L3a = L1.concatenate(L2);
    L3a.printList();


    cout << "\n(b) Hieu L1 - L2:\n";
    LinkedList L3b = L1.difference(L2);
    L3b.printList();


    cout << "\n(c) Giao L1 va L2:\n";
    LinkedList L3c = L1.intersection(L2);
    L3c.printList();


    cout << "\n(d) Hop L1 va L2:\n";
    LinkedList L3d = L1.unionList(L2);
    L3d.printList();


    cout << "\n(e) Tong tung phan tu L1 + L2:\n";
    LinkedList L3e = L1.sumList(L2);
    L3e.printList();


    cout << "\n(f) L1 va L2 co trung gia tri hay khong? ";
    cout << (L1.sameValues(L2) ? "CO" : "KHONG") << endl;


    cout << "\n(g) Xoa phan tu dau tien cua L1 > tong L2:\n";
    L1.deleteFirstGreaterThan(L2);
    L1.printList();


    cout << "\n(h) Xoa tat ca phan tu cua L1 = max(L2):\n";
    L1.deleteAllEqualToMaxOf(L2);
    L1.printList();

    return 0;
}

