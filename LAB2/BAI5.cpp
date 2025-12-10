#include <bits/stdc++.h>
using namespace std;

struct Date {
    int day, month, year;
};

struct Student {
    string id;       
    string name;    
    string lop;     
    Date dob;   
    float gpa;   
};

class Node {
public:
    Student data;
    Node* next;

    Node(const Student& s) : data(s), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* t;
        while (head) {
            t = head;
            head = head->next;
            delete t;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    void addLast(const Student& s) {
        Node* p = new Node(s);
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
        cout << left;
        cout << setw(12) << "MaSV"
             << setw(25) << "Ho Ten"
             << setw(10) << "Lop"
             << setw(12) << "Ngay sinh"
             << setw(5) << "GPA" << endl;

        while (t) {
            cout << setw(12) << t->data.id
                 << setw(25) << t->data.name
                 << setw(10) << t->data.lop
                 << t->data.dob.day << "/" << t->data.dob.month << "/" << t->data.dob.year << "   "
                 << t->data.gpa << endl;
            t = t->next;
        }
    }

    void printPassed() const {
        Node* t = head;
        cout << "\nDanh sach sinh vien GPA >= 5:\n";
        while (t) {
            if (t->data.gpa >= 5)
                cout << t->data.id << " - " << t->data.name << " - GPA: " << t->data.gpa << endl;
            t = t->next;
        }
    }

    Node* searchLinear(const string& id) const {
        Node* t = head;
        while (t) {
            if (t->data.id == id) return t;
            t = t->next;
        }
        return nullptr;
    }

    void selectionSortByID() {
        for (Node* p = head; p != nullptr; p = p->next) {
            Node* minNode = p;
            for (Node* q = p->next; q != nullptr; q = q->next) {
                if (q->data.id < minNode->data.id)
                    minNode = q;
            }
            swap(p->data, minNode->data);
        }
    }

    Node* searchBinary(const string& id) {
        selectionSortByID();

        int n = 0;
        Node* t = head;
        while (t) {
            n++;
            t = t->next;
        }

        int left = 0, right = n - 1;

        // Ham lay node theo chi so
        auto getNodeAt = [&](int index) {
            Node* t = head;
            for (int i = 0; i < index; i++)
                t = t->next;
            return t;
        };

        // Binary Search
        while (left <= right) {
            int mid = (left + right) / 2;
            Node* midNode = getNodeAt(mid);

            if (midNode->data.id == id) return midNode;
            else if (id < midNode->data.id) right = mid - 1;
            else left = mid + 1;
        }
        return nullptr;
    }

    bool removeByID(const string& id) {
        if (!head) return false;

        // neu o dau
        if (head->data.id == id) {
            Node* t = head;
            head = head->next;
            delete t;
            return true;
        }

        Node* t = head;
        while (t->next) {
            if (t->next->data.id == id) {
                Node* del = t->next;
                t->next = del->next;
                delete del;
                return true;
            }
            t = t->next;
        }
        return false;
    }

    bool updateGPA(const string& id, float newGPA) {
        Node* sv = searchLinear(id);
        if (!sv) return false;
        sv->data.gpa = newGPA;
        return true;
    }
};

Student inputStudent() {
    Student s;
    cout << "Nhap ma SV (11 ky tu): ";
    cin >> s.id;
    cin.ignore();

    cout << "Nhap ho ten: ";
    getline(cin, s.name);

    cout << "Nhap lop: ";
    getline(cin, s.lop);

    cout << "Nhap ngay sinh (d m y): ";
    cin >> s.dob.day >> s.dob.month >> s.dob.year;

    cout << "Nhap GPA (0 - 10): ";
    cin >> s.gpa;

    return s;
}

int main() {
    LinkedList list;

     int n;

    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    while (n <= 0) {
        cout << "So luong phai > 0. Nhap lai: ";
        cin >> n;
    }

    for (int i = 0; i < n; i++) {
        cout << "\n=== Nhap sinh vien thu " << i + 1 << " ===\n";
        Student s = inputStudent();
        list.addLast(s);
    }


    cout << "\n=== DANH SACH SINH VIEN ===\n";
    list.printList();

    cout << "\n=== SINH VIEN DAT (GPA >= 5) ===\n";
    list.printPassed();

    cout << "\nNhap ma SV can tim (tuan tu): ";
    string id;
    cin >> id;

    Node* found = list.searchLinear(id);
    if (found)
        cout << "Tim thay: " << found->data.name << " - GPA: " << found->data.gpa << endl;
    else
        cout << "Khong tim thay!\n";

    cout << "\nSap xep danh sach theo ma SV...\n";
    list.selectionSortByID();
    list.printList();

    cout << "\nNhap ma SV can tim nhi phan: ";
    cin >> id;

    Node* found2 = list.searchBinary(id);
    if (found2)
        cout << "Tim thay (nhi phan): " << found2->data.name << endl;
    else
        cout << "Khong tim thay!\n";

    cout << "\nNhap ma SV can xoa: ";
    cin >> id;
    if (list.removeByID(id))
        cout << "Da xoa!\n";
    else
        cout << "Khong tim thay!\n";

    cout << "Danh sach sau xoa:\n";
    list.printList();

    cout << "\nNhap ma SV can cap nhat GPA: ";
    cin >> id;
    cout << "Nhap GPA moi: ";
    float g;
    cin >> g;

    if (list.updateGPA(id, g))
        cout << "Cap nhat thanh cong\n";
    else
        cout << "Khong tim thay!\n";

    cout << "\nDanh sach cuoi cung:\n";
    list.printList();

    return 0;
}

