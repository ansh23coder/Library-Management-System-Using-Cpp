#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Library {
    string id, name, author, search;
    fstream file;

public:
    void addBook();
    void showAll();
    void extractBook();
} obj;

int main() {
    char choice;

    while (true) {
        cout << "\n----------------------------------" << endl;
        cout << "1- Show All Books" << endl;
        cout << "2- Extract Book by ID" << endl;
        cout << "3- Add Book (ADMIN)" << endl;
        cout << "4- Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore();  // Clear newline after cin >>

        switch (choice) {
            case '1':
                obj.showAll();
                break;
            case '2':
                obj.extractBook();
                break;
            case '3':
                obj.addBook();
                break;
            case '4':
                cout << "Thank you for using Library Management System!" << endl;
                return 0;
            default:
                cout << "Invalid Choice...! Please try again." << endl;
        }
    }
    return 0;
}

void Library::addBook() {
    cout << "\nEnter Book ID: ";
    getline(cin, id);
    cout << "Enter Book Name: ";
    getline(cin, name);
    cout << "Enter Author's Name: ";
    getline(cin, author);

    file.open("bookData.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << id << "*" << name << "*" << author << endl;
        file.close();
        cout << "\nBook added successfully!" << endl;
    } else {
        cout << "\nError: Could not open file to add book!" << endl;
    }
}

void Library::showAll() {
    file.open("bookData.txt", ios::in);
    if (!file.is_open()) {
        cout << "\nNo books found in the database!" << endl;
        return;
    }

    cout << "\n\n";
    cout << "\tBook ID\t\tBook Name\t\tAuthor" << endl;
    cout << "\t-------\t\t---------\t\t------" << endl;

    while (getline(file, id, '*') && getline(file, name, '*') && getline(file, author)) {
        cout << "\t" << id << "\t\t" << name << "\t\t" << author << endl;
    }

    file.close();
}

void Library::extractBook() {
    cout << "\nEnter Book ID to search: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    if (!file.is_open()) {
        cout << "\nError opening file!" << endl;
        return;
    }

    bool found = false;
    while (getline(file, id, '*') && getline(file, name, '*') && getline(file, author)) {
        if (search == id) {
            cout << "\nBook Found!" << endl;
            cout << "\tBook ID: " << id << endl;
            cout << "\tBook Name: " << name << endl;
            cout << "\tAuthor: " << author << endl;
            found = true;
            break;  // Stop after finding the first match
        }
    }

    if (!found) {
        cout << "\nBook with ID \"" << search << "\" not found!" << endl;
    }

    file.close();
}
