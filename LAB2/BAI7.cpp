#include <iostream>
#include <cmath>
using namespace std;

struct Term {
    int coef;  // he so
    int exp;   // so mu
};

class Node {
public:
    Term data;
    Node* next;

    Node(Term t) : data(t), next(nullptr) {}
};

class Polynomial {
private:
    Node* head;

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        Node* t;
        while (head) {
            t = head;
            head = head->next;
            delete t;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    void addTerm(int coef, int exp) {
        if (coef == 0) return;

        Node* p = new Node({coef, exp});

        if (!head || exp > head->data.exp) {
            p->next = head;
            head = p;
            return;
        }

        Node* t = head;
        while (t->next && t->next->data.exp > exp)
            t = t->next;

        if (t->next && t->next->data.exp == exp) {
            t->next->data.coef += coef; // gop he so
            delete p;
            if (t->next->data.coef == 0) { // neu het he so thi xoa luon
                Node* del = t->next;
                t->next = del->next;
                delete del;
            }
        } else {
            p->next = t->next;
            t->next = p;
        }
    }

    // Nhap da thuc
    void inputPolynomial() {
        int n;
        cout << "Nhap so luong hang tu: ";
        cin >> n;

        for (int i = 1; i <= n; i++) {
            int c, e;
            cout << "He so thu " << i <<": ";
            cin >> c;
            cout << "So mu thu " << i <<": ";
            cin >> e;
            addTerm(c, e);
        }
    }

    // In da thuc
    void print() const {
        if (isEmpty()) {
            cout << "0";
            return;
        }

        Node* t = head;
        bool first = true;

        while (t) {
            if (!first && t->data.coef > 0) cout << " + ";
            if (t->data.coef < 0) cout << " - ";

            int absCoef = abs(t->data.coef);

            if (t->data.exp == 0)
                cout << absCoef;
            else if (t->data.exp == 1)
                cout << absCoef << "x";
            else
                cout << absCoef << "x^" << t->data.exp;

            first = false;
            t = t->next;
        }
    }

    // c) Ðao ham
    Polynomial derivative() const {
        Polynomial d;

        Node* t = head;
        while (t) {
            if (t->data.exp > 0)
                d.addTerm(t->data.coef * t->data.exp, t->data.exp - 1);

            t = t->next;
        }
        return d;
    }

    // d) Tinh gia tri tai x
    long long evaluate(int x) const {
        long long result = 0;
        Node* t = head;

        while (t) {
            result += t->data.coef * pow(x, t->data.exp);
            t = t->next;
        }
        return result;
    }

    // e) F1 + F2
    static Polynomial add(const Polynomial& A, const Polynomial& B) {
        Polynomial R;
        Node* p = A.head;
        Node* q = B.head;

        while (p || q) {
            if (q == nullptr || (p && p->data.exp > q->data.exp)) {
                R.addTerm(p->data.coef, p->data.exp);
                p = p->next;
            }
            else if (p == nullptr || (q && q->data.exp > p->data.exp)) {
                R.addTerm(q->data.coef, q->data.exp);
                q = q->next;
            }
            else {
                R.addTerm(p->data.coef + q->data.coef, p->data.exp);
                p = p->next;
                q = q->next;
            }
        }

        return R;
    }

    // f) F1 * F2
    static Polynomial multiply(const Polynomial& A, const Polynomial& B) {
        Polynomial R;

        for (Node* p = A.head; p != nullptr; p = p->next) {
            for (Node* q = B.head; q != nullptr; q = q->next) {
                int newCoef = p->data.coef * q->data.coef;
                int newExp  = p->data.exp + q->data.exp;
                R.addTerm(newCoef, newExp);
            }
        }

        return R;
    }
};

int main() {
    Polynomial F1, F2;

    cout << "=== Nhap da thuc F1 ===\n";
    F1.inputPolynomial();

    cout << "\n=== Nhap da thuc F2 ===\n";
    F2.inputPolynomial();

    cout << "\nF1(x) = ";
    F1.print();

    cout << "\nF2(x) = ";
    F2.print();

    cout << "\n\nDao ham F1: ";
    Polynomial D1 = F1.derivative();
    D1.print();

    cout << "\nDao ham F2: ";
    Polynomial D2 = F2.derivative();
    D2.print();

    int x;
    cout << "\n\nNhap x de tinh F1(x) & F2(x): ";
    cin >> x;

    cout << "F1(" << x << ") = " << F1.evaluate(x) << endl;
    cout << "F2(" << x << ") = " << F2.evaluate(x) << endl;

    cout << "\nTong F1 + F2 = ";
    Polynomial Sum = Polynomial::add(F1, F2);
    Sum.print();

    cout << "\nTich F1 * F2 = ";
    Polynomial Product = Polynomial::multiply(F1, F2);
    Product.print();

    cout << endl;
    return 0;
}

