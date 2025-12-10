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

    bool isPrime(int n) const {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0) return false;
        return true;
    }

    bool isPerfectSquare(int n) const {
        int r = sqrt(n);
        return r * r == n;
    }

    bool isPerfectNumber(int n) const {
        if (n <= 1) return false;
        int sum = 1;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                sum += i;
                if (i != n / i) sum += n / i;
            }
        }
        return sum == n;
    }

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

    // a. Them phan tu vao cuoi danh sach
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

    // b. Xuat danh sach
    void printList() const {
        if (isEmpty()) {
            cout << "(Danh sach rong)\n";
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // c. Liet ke so nguyen to
    void listPrime() const {
        Node* temp = head;
        bool found = false;

        while (temp) {
            if (isPrime(temp->data)) {
                cout << temp->data << " ";
                found = true;
            }
            temp = temp->next;
        }

        if (!found) cout << "Khong co so nguyen to nao.";
        cout << endl;
    }

    // d. Tinh TBC
    double average() const {
        if (isEmpty()) return 0;

        int sum = 0, cnt = 0;
        Node* temp = head;
        while (temp) {
            sum += temp->data;
            cnt++;
            temp = temp->next;
        }
        return static_cast<double>(sum) / cnt;
    }

    // e. Ðem so lan xuat hien cua x
    int countX(int x) const {
        int cnt = 0;
        Node* temp = head;

        while (temp) {
            if (temp->data == x) cnt++;
            temp = temp->next;
        }
        return cnt;
    }

    // f. Tim so chinh phuong cuoi cung
    int lastPerfectSquare() const {
        int result = -1;
        Node* temp = head;

        while (temp) {
            if (isPerfectSquare(temp->data)) result = temp->data;
            temp = temp->next;
        }
        return result;
    }

    // g. Tra ve phan tu thu k
    int getKth(int k) const {
        if (k <= 0) return -1;

        int index = 1;
        Node* temp = head;

        while (temp) {
            if (index == k) return temp->data;
            index++;
            temp = temp->next;
        }
        return -1;
    }

    // h. Tim gia tri nho nhat
    int findMin() const {
        if (isEmpty()) return -1;

        int mn = head->data;
        Node* temp = head->next;

        while (temp) {
            if (temp->data < mn) mn = temp->data;
            temp = temp->next;
        }
        return mn;
    }

    // i. Them sau phan tu q
    bool insertAfter(int q, int x) {
        Node* temp = head;

        while (temp) {
            if (temp->data == q) {
                Node* p = new Node(x);
                p->next = temp->next;
                temp->next = p;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // j. Them phan tu khong trung
    bool addUnique(int x) {
        Node* temp = head;
        while (temp) {
            if (temp->data == x) return false;
            temp = temp->next;
        }
        addLast(x);
        return true;
    }

    // k. Xoa k phan tu dau
    void deleteFirstK(int k) {
        while (k-- > 0 && head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // l. Xoa phan tu co gia tri x
    void deleteX(int x) {
        while (head && head->data == x) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        Node* current = head;
        while (current && current->next) {
            if (current->next->data == x) {
                Node* tmp = current->next;
                current->next = tmp->next;
                delete tmp;
            } else {
                current = current->next;
            }
        }
    }

    // m. Xoa phan tu sau phan tu q
    bool deleteAfter(int q) {
        Node* temp = head;

        while (temp) {
            if (temp->data == q && temp->next != nullptr) {
                Node* del = temp->next;
                temp->next = del->next;
                delete del;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // n. Xoa phan tu lap lai
    void removeDuplicates() {
        if (isEmpty()) return;

        unordered_set<int> seen;
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (seen.count(current->data)) {
                prev->next = current->next;
                delete current;
                current = prev->next;
            } else {
                seen.insert(current->data);
                prev = current;
                current = current->next;
            }
        }
    }

    // o. Interchange Sort
    void interchangeSort() {
        for (Node* p = head; p != nullptr; p = p->next)
            for (Node* q = p->next; q != nullptr; q = q->next)
                if (p->data > q->data)
                    swap(p->data, q->data);
    }

    // p. Them phan tu vao DS tang dan
    void insertSorted(int x) {
        Node* p = new Node(x);

        if (!head || head->data >= x) {
            p->next = head;
            head = p;
            return;
        }

        Node* temp = head;
        while (temp->next && temp->next->data < x)
            temp = temp->next;

        p->next = temp->next;
        temp->next = p;
    }

    // q. Cap nhat so hoan thien thanh 0
    void updatePerfectNumbers() {
        Node* temp = head;
        while (temp) {
            if (isPerfectNumber(temp->data))
                temp->data = 0;
            temp = temp->next;
        }
    }
};

int main() {
    LinkedList list;
    cout << "Nhap danh sach so nguyen (nhap -1 de ket thuc):\n";

    while (true) {
        int x;
        cin >> x;

        if (x == -1) break;

        list.addLast(x);
    }

    cout << "\n=== DANH SACH BAN DAU ===\n";
    list.printList();             // (b)

    cout << "\n(c) Cac so nguyen to trong danh sach: ";
    list.listPrime();

    cout << "\n(d) Trung binh cong = " << list.average() << endl;

    int x;
    cout << "\n(e) Nhap x de dem so lan xuat hien: ";
    cin >> x;
    cout << "So lan xuat hien cua " << x << " = " << list.countX(x) << endl;

    cout << "\n(f) So chinh phuong cuoi cung: " << list.lastPerfectSquare() << endl;

    int k;
    cout << "\n(g) Nhap k de lay phan tu thu k: ";
    cin >> k;
    cout << "Phan tu thu " << k << " = " << list.getKth(k) << endl;

    cout << "\n(h) Gia tri nho nhat trong danh sach = " << list.findMin() << endl;

    int q;
    cout << "\n(i) Nhap gia tri q: ";
    cin >> q;
    cout << "Nhap gia tri muon chen sau q: ";
    cin >> x;
    if (list.insertAfter(q, x))
        cout << "Da chen thanh cong.\n";
    else
        cout << "Khong tim thay gia tri q trong danh sach.\n";

    cout << "Danh sach sau khi chen: ";
    list.printList();

    cout << "\n(j) Nhap 1 so muon them (khong duoc trung): ";
    cin >> x;
    if (list.addUnique(x))
        cout << "Them thanh cong.\n";
    else
        cout << "Gia tri bi trung — khong the them!\n";

    cout << "Danh sach sau khi them (j): ";
    list.printList();

    cout << "\n(k) Nhap so k de xoa k phan tu dau: ";
    cin >> k;
    list.deleteFirstK(k);
    cout << "Danh sach sau khi xoa k phan tu dau: ";
    list.printList();

    cout << "\n(l) Nhap gia tri x de xoa x trong danh sach: ";
    cin >> x;
    list.deleteX(x);
    cout << "Danh sach sau khi xoa tat ca x: ";
    list.printList();

    cout << "\n(m) Nhap gia tri q de xoa phan tu sau q: ";
    cin >> q;
    if (list.deleteAfter(q))
        cout << "Da xoa phan tu sau q.\n";
    else
        cout << "Khong the xoa (khong tim thay q hoac q nam cuoi danh sach).\n";
    cout << "Danh sach sau khi thuc hien (m): ";
    list.printList();

    cout << "\n(n) Xoa tat ca cac phan tu lap lai...\n";
    list.removeDuplicates();
    cout << "Danh sach sau khi xoa cac phan tu lap lai: ";
    list.printList();

    cout << "\n(o) Sap xep danh sach theo thu tu tang dan (Interchange Sort)...\n";
    list.interchangeSort();
    cout << "Danh sach sau khi sap xep: ";
    list.printList();

    cout << "\n(p) Nhap gia tri x de chen vao danh sach tang dan: ";
    cin >> x;
    list.insertSorted(x);
    cout << "Danh sach sau khi chen x vao dung vi tri: ";
    list.printList();

    cout << "\n(q) Cap nhat cac so hoan thien thanh 0...\n";
    list.updatePerfectNumbers();
    cout << "Danh sach sau khi cap nhat: ";
    list.printList();

    return 0;
}

