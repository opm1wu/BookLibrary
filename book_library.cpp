#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Book {
    string title, author;
    int year;
    bool isAvailable;
};

vector<Book> library;

void showMenu() {
    cout << "\n=== Book library ===\n"
         << "1. Add a book\n"
         << "2. Show all books\n"
         << "3. Search book\n"
         << "4. Save to file\n"
         << "5. Load from file\n"
         << "0. Exit\n"
         << "Choose action: \n";
}

void addBook(vector<Book>& library) {
    Book newBook;
    printf("Name: "); getline(cin >> ws, newBook.title); // ws убирает лишние пробелы
    printf("Author: "); getline(cin >> ws, newBook.author);
    printf("Realese year: "); cin >> newBook.year;
    newBook.isAvailable = true;
    library.push_back(newBook);
    printf("Book added!\n");
}

void displayBooks(const vector<Book>& library) {
    if (library.empty()) {
        cout << "Library is empty.\n";
        return;
    }
    cout << "\nList of books:\n";
    for (size_t i = 0; i < library.size(); ++i) {
        cout << i + 1 << ". " << library[i].title
             << " (by " << library[i].author << ", " << library[i].year << ")"
             << " [Status: " << (library[i].isAvailable ? "Avaliable" : "Taken") << "]\n";
    }
}

void saveToFile(const vector<Book>& library, const string& filename = "library.txt") {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& book : library) {
            file << book.title << "/" << book.author << "/" << book.year << "/" << book.isAvailable<< endl;
        }
        cout << "Saved to file '" << filename << "'!\n";
    } else {
        cerr << "Saving error!\n";
    }
}

void loadFromFile(vector<Book>& library, const string& filename = "library.txt") {
    ifstream file(filename);
    for (string line; getline(file, line);) {
        vector<string> parts;
        string part; 
        for (stringstream ss(line); getline(ss, part, '/'); parts.push_back(part));
        if (parts.size() == 4) {
            library.push_back({parts[0], parts[1], stoi(parts[2]), parts[3] == "1"});
        }
    }
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void searchByName(const vector<Book>& library){
    string query;
    cout << "Type name: "; cin >> query; query = toLower(query);
    bool found = false;
    
    for (const auto& book : library) {
        string lowerTitle = toLower(book.title);    
        int count = 0;
        if (lowerTitle.find(query) != string::npos)
        {
            cout << "Found: \n" << count + 1 << ". " << book.title
            << " (By " << book.author << ", " << book.year << ")"
            << " [Status: " << (book.isAvailable ? "Avaliable" : "Taken") << "]\n";
            found = true; 
        }
    }
    printf("\n");
    if (!found) cout << "Books not found.\n";
}

void searchByAuthor(vector<Book>& library){} //допишу позже

void searchByYear(vector<Book>& library){} // допишу позже х2 :)

void searchBookMenu(){
    int choise;
    do {
        cout << "1. Search by name\n"
             << "2. Search by author\n"
             << "3. Search by year\n"
             << "0. Return to menu\n"
             << "Choose action: \n";
        cin >> choise; cin.ignore();
        switch (choise){
            case 1: searchByName(library); break;
            case 2: searchByAuthor(library); break;
            case 3: searchByYear(library); break;
            case 0: "Returning...\n";break;
            default: cout << "Wrong action!\n";
        }
        } while (choise != 0);
}

int main() {
    
    int choice;
    loadFromFile(library); // Загружаем данные при старте

    do {
        showMenu(); cin >> choice; cout << "\n" ; cin.ignore(); // Очищаем буфер после ввода числа

        switch (choice) {
            case 1: addBook(library); break;
            case 2: displayBooks(library); break;
            case 3: searchBookMenu(); break;
            case 4: saveToFile(library); break;
            case 5: loadFromFile(library); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Wrong action!\n";
        }
    } while (choice != 0);

    saveToFile(library); // Сохраняем данные перед выходом
    return 0;  //hello
}

