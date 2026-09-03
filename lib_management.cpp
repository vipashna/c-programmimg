#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Book class to manage individual book details
class Book {
private:
    int id;
    string title;
    string author;
    bool isIssued;

public:
    Book() : id(0), title(""), author(""), isIssued(false) {}
    Book(int bookId, string bookTitle, string bookAuthor, bool status = false) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        isIssued = status;
    }

    // Getters
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }

    // Setters
    void issueBook() { isIssued = true; }
    void returnBook() { isIssued = false; }

    void display() const {
        cout << "ID: " << id 
             << " | Title: " << title 
             << " | Author: " << author 
             << " | Status: " << (isIssued ? "Issued" : "Available") << "\n";
    }
};

// File handling functions
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream inFile("library_data.txt");
    if (!inFile) return books;

    int id;
    string title, author;
    bool status;

    while (inFile >> id) {
        inFile.ignore();
        getline(inFile, title);
        getline(inFile, author);
        inFile >> status;
        books.push_back(Book(id, title, author, status));
    }
    inFile.close();
    return books;
}

void saveBooks(const vector<Book>& books) {
    ofstream outFile("library_data.txt");
    for (const auto& b : books) {
        outFile << b.getId() << "\n" 
                << b.getTitle() << "\n" 
                << b.getAuthor() << "\n" 
                << b.getIsIssued() << "\n";
    }
    outFile.close();
}

// 1. Add a New Book
void addBook(vector<Book>& books) {
    int id;
    string title, author;

    cout << "\nEnter Book ID: ";
    cin >> id;

    for (const auto& b : books) {
        if (b.getId() == id) {
            cout << "Book with this ID already exists!\n";
            return;
        }
    }

    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Author Name: ";
    getline(cin, author);

    books.push_back(Book(id, title, author));
    saveBooks(books);
    cout << "Book added successfully!\n";
}

// 2. Display All Books
void displayAllBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "\nNo books available in the library.\n";
        return;
    }

    cout << "\n--- Library Catalog ---\n";
    for (const auto& b : books) {
        b.display();
    }
}

// 3. Search Book by Title or Author
void searchBook(const vector<Book>& books) {
    if (books.empty()) {
        cout << "\nLibrary is empty!\n";
        return;
    }

    cin.ignore();
    string keyword;
    cout << "\nEnter Title or Author to search: ";
    getline(cin, keyword);

    bool found = false;
    cout << "\n--- Search Results ---\n";
    for (const auto& b : books) {
        if (b.getTitle().find(keyword) != string::npos || b.getAuthor().find(keyword) != string::npos) {
            b.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}

// 4. Issue a Book
void issueBook(vector<Book>& books) {
    int id;
    cout << "\nEnter Book ID to issue: ";
    cin >> id;

    for (auto& b : books) {
        if (b.getId() == id) {
            if (b.getIsIssued()) {
                cout << "Book is already issued to someone else!\n";
            } else {
                b.issueBook();
                saveBooks(books);
                cout << "Book issued successfully!\n";
            }
            return;
        }
    }
    cout << "Book ID not found!\n";
}

// 5. Return a Book
void returnBook(vector<Book>& books) {
    int id;
    cout << "\nEnter Book ID to return: ";
    cin >> id;

    for (auto& b : books) {
        if (b.getId() == id) {
            if (!b.getIsIssued()) {
                cout << "This book was not issued.\n";
            } else {
                b.returnBook();
                saveBooks(books);
                cout << "Book returned successfully!\n";
            }
            return;
        }
    }
    cout << "Book ID not found!\n";
}

// Main Menu
int main() {
    vector<Book> books = loadBooks();
    int choice;

    do {
        cout << "\n===============================\n";
        cout << "   LIBRARY MANAGEMENT SYSTEM   \n";
        cout << "===============================\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book (Title/Author)\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(books); break;
            case 2: displayAllBooks(books); break;
            case 3: searchBook(books); break;
            case 4: issueBook(books); break;
            case 5: returnBook(books); break;
            case 6: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice! Select 1-6.\n";
        }
    } while (choice != 6);

    return 0;
}
