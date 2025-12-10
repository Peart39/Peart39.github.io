#include <bits/stdc++.h>
using namespace std;

struct Movie {
    string title;
    string genre;   // "hinh su", "tinh cam", "hai"
    string director;
    string actor_male;
    string actor_female;
    int year;
};

class Node {
public:
    Movie data;
    Node* next;

    Node(const Movie& m) : data(m), next(nullptr) {}
};

class MovieList {
private:
    Node* head;

public:
    MovieList() : head(nullptr) {}

    ~MovieList() {
        Node* tmp;
        while (head) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void addLast(const Movie& m) {
        Node* p = new Node(m);
        if (!head) {
            head = p;
            return;
        }
        Node* t = head;
        while (t->next) t = t->next;
        t->next = p;
    }

    void readFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) {
            cout << "Khong mo duoc file!\n";
            return;
        }

        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            Movie m;
            string yearStr;

            getline(ss, m.title, '#');
            getline(ss, m.genre, '#');
            getline(ss, m.director, '#');
            getline(ss, m.actor_male, '#');
            getline(ss, m.actor_female, '#');
            getline(ss, yearStr, '#');

            m.year = stoi(yearStr);

            addLast(m);
        }
        fin.close();
    }

    void writeToFile(const string& filename) const {
        ofstream fout(filename);
        Node* t = head;
        while (t) {
            fout << t->data.title << "#"
                 << t->data.genre << "#"
                 << t->data.director << "#"
                 << t->data.actor_male << "#"
                 << t->data.actor_female << "#"
                 << t->data.year << "\n";
            t = t->next;
        }
    }

    void updateGenre(const string& title, const string& newGenre) {
        Node* t = head;
        bool found = false;

        while (t) {
            if (t->data.title == title) {
                t->data.genre = newGenre;
                found = true;
            }
            t = t->next;
        }

        if (!found)
            cout << "Khong tim thay ten phim!\n";
        else
            cout << "Cap nhat thanh cong!\n";
    }

    void print() const {
        Node* t = head;
        cout << left << setw(20) << "Ten phim"
             << setw(12) << "The loai"
             << setw(20) << "Dao dien"
             << setw(20) << "Nam chinh"
             << setw(20) << "Nu chinh"
             << setw(6) << "Nam" << endl;

        while (t) {
            cout << setw(20) << t->data.title
                 << setw(12) << t->data.genre
                 << setw(20) << t->data.director
                 << setw(20) << t->data.actor_male
                 << setw(20) << t->data.actor_female
                 << setw(6) << t->data.year << endl;
            t = t->next;
        }
    }

    void filterByActorMaleToFile(const string& actor) const {
        string filename = actor + ".txt";
        ofstream fout(filename);

        Node* t = head;
        bool found = false;
        while (t) {
            if (t->data.actor_male == actor) {
                fout << t->data.title << "#"
                     << t->data.genre << "#"
                     << t->data.director << "#"
                     << t->data.actor_male << "#"
                     << t->data.actor_female << "#"
                     << t->data.year << "\n";
                found = true;
            }
            t = t->next;
        }
        fout.close();
        if (found)
            cout << "Da tao file: " << filename << endl;
        else
            cout << "Khong co phim nao cua dien vien nay.\n";
    }

    void writeByDirector() const {
        map<string, ofstream*> files;

        Node* t = head;
        while (t) {
            string fname = t->data.director + ".txt";

            if (files.find(fname) == files.end())
                files[fname] = new ofstream(fname);

            *files[fname] << t->data.title << "#"
                          << t->data.genre << "#"
                          << t->data.director << "#"
                          << t->data.actor_male << "#"
                          << t->data.actor_female << "#"
                          << t->data.year << "\n";

            t = t->next;
        }

        for (auto& f : files) {
            f.second->close();
            delete f.second;
        }

        cout << "Da tao file thong ke theo dao dien.\n";
    }

    void writeNewest3() const {
        vector<Movie> arr;
        Node* t = head;
        while (t) {
            arr.push_back(t->data);
            t = t->next;
        }

        sort(arr.begin(), arr.end(), [](Movie a, Movie b) {
            return a.year > b.year;
        });

        ofstream fout("PhimMoi.txt");
        for (int i = 0; i < min(3, (int)arr.size()); i++) {
            fout << arr[i].title << "#"
                 << arr[i].genre << "#"
                 << arr[i].director << "#"
                 << arr[i].actor_male << "#"
                 << arr[i].actor_female << "#"
                 << arr[i].year << "\n";
        }
        fout.close();
        cout << "Da tao file PhimMoi.txt\n";
    }
};



int main() {
    MovieList list;

    //a)
    list.readFromFile("Input.txt");
    list.print(); 
    
    //b)
    string title, newGenre;
    cout << "\nNhap ten phim can cap nhat the loai: ";
    cin >> title;
    cout << "Nhap the loai moi (hinh su / tinh cam / hai): ";
    cin.ignore();
    getline(cin, newGenre);
    list.updateGenre(title, newGenre);
    list.writeToFile("Input.txt");

	//c)
    cout << "\n=== DANH SACH PHIM ===\n";
    list.print();
    
    //d)
    string actor;
    cout << "\nNhap ten dien vien nam: ";
    getline(cin, actor);
    list.filterByActorMaleToFile(actor);

    //e)
    list.writeByDirector();

    //f)
    list.writeNewest3();

    return 0;
}

