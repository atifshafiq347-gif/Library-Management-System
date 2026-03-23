#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class books
{
private:
    int bookid[100];
    char *bookname[100];
    string author[100];
    float price[100];
    bool is_available[100];

    static int countbooks;

public:
    const int totalbooks = 100;
    const string allbooks = "AllBooks.txt";
    const string issuedbooks = "IssuedBooks.txt";
    const string returnBooks = "returnBooks.txt";

    // Copy constructor
    books(const books &other)
    {
        countbooks = other.countbooks;
        for (int i = 0; i < countbooks; i++)
        {
            bookid[i] = other.bookid[i];

            if (other.bookname[i] != nullptr)
            {
                bookname[i] = new char[strlen(other.bookname[i]) + 1];
                strcpy(bookname[i], other.bookname[i]);
            }
            else
            {
                bookname[i] = nullptr;
            }

            author[i] = other.author[i];
            price[i] = other.price[i];
            is_available[i] = other.is_available[i];
        }
        for (int i = countbooks; i < totalbooks; i++)
        {
            bookname[i] = nullptr;
        }
    }

    // Default constructor
    books()
    {
        for (int i = 0; i < totalbooks; i++)
        {
            bookname[i] = nullptr;
        }
    }

    int gettotalbooks()
    {
        return countbooks;
    }

    void saveallbooks()
    {
        ofstream file(allbooks);
        if (!file)
        {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        file << countbooks << endl;

        for (int i = 0; i < countbooks; i++)
        {
            file << bookid[i] << endl;
            file << bookname[i] << endl;
            file << author[i] << endl;
            file << price[i] << endl;
            file << is_available[i] << endl;
        }
        file.close();
    }

    bool loadallbooks()
    {
        ifstream inFile(allbooks);

        if (!inFile)
        {
            cout << "No file found. Starting fresh." << endl;
            return false;
        }

        // Clean up existing data
        for (int i = 0; i < countbooks; i++)
        {
            if (bookname[i] != nullptr)
            {
                delete[] bookname[i];
                bookname[i] = nullptr;
            }
        }

        inFile >> countbooks;
        inFile.ignore();

        char temp[256];

        for (int i = 0; i < countbooks; i++)
        {
            inFile >> bookid[i];
            inFile.ignore();

            inFile.getline(temp, 256);
            bookname[i] = new char[strlen(temp) + 1];
            strcpy(bookname[i], temp);

            getline(inFile, author[i]);

            inFile >> price[i];
            inFile >> is_available[i];
            inFile.ignore();
        }

        inFile.close();
        cout << "Loaded " << countbooks << " books from file." << endl;
        return true;
    }

    void addbook();
    void deletebook();
    void displaybook();
    void updatebook();
    void searchbook();
    void issuebook();
    void returnbook();
    void displayissuedbooks();
    void displayreturnbooks();

    // Destructor
    ~books()
    {
        for (int i = 0; i < totalbooks; i++)
        {
            if (bookname[i] != nullptr)
            {
                delete[] bookname[i];
                bookname[i] = nullptr;
            }
        }
    }
};

int books::countbooks = 0;

void books::addbook()
{
    cout << "How many books do you want to add?" << endl;
    int add;
    cin >> add;

    if (countbooks + add > totalbooks)
    {
        cout << "Not enough space! Maximum books are: " << totalbooks << endl;
        return;
    }

    for (int i = 0; i < add; i++)
    {
        cout << "Enter Book ID for book " << (countbooks + 1) << ": " << endl;
        cin >> bookid[countbooks];

        bookname[countbooks] = new char[100];
        cin.ignore();
        cout << "Enter Book Name: " << endl;
        cin.getline(bookname[countbooks], 100);

        cout << "Enter Author Name: " << endl;
        getline(cin, author[countbooks]);
        cout << "Enter Price: " << endl;
        cin >> price[countbooks];
        is_available[countbooks] = true;
        countbooks++;
    }
    saveallbooks();
    cout << add << " books added. Total books: " << countbooks << endl;
}

void books::deletebook()
{
    if (countbooks == 0)
    {
        cout << "No books in the library!" << endl;
        return;
    }

    int id;
    cout << "Enter Book ID to delete: " << endl;
    cin >> id;

    int foundIndex = -1;
    for (int i = 0; i < countbooks; i++)
    {
        if (bookid[i] == id)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Book not found!" << endl;
        return;
    }

    if (bookname[foundIndex] != nullptr)
    {
        delete[] bookname[foundIndex];
        bookname[foundIndex] = nullptr;
    }

    for (int j = foundIndex; j < countbooks - 1; j++)
    {
        bookid[j] = bookid[j + 1];
        bookname[j] = bookname[j + 1];
        author[j] = author[j + 1];
        price[j] = price[j + 1];
        is_available[j] = is_available[j + 1];
    }

    bookname[countbooks - 1] = nullptr;

    countbooks--;
    saveallbooks();
    cout << "Book deleted successfully!" << endl;
}

void books::displaybook()
{
    if (countbooks == 0)
    {
        cout << "No books in the library!" << endl;
        return;
    }
    cout << "\n=== ALL BOOKS ===" << endl;
    for (int i = 0; i < countbooks; i++)
    {
        cout << "Book ID: " << bookid[i] << endl;
        cout << "Book Name: " << bookname[i] << endl;
        cout << "Author Name: " << author[i] << endl;
        cout << "Price: " << price[i] << endl;

        if (is_available[i])
        {
            cout << "Available: Yes" << endl;
        }
        else
        {
            cout << "Available: No" << endl;
        }
        cout << "-----------------------------" << endl;
    }
}

void books::updatebook()
{
    int id;
    bool found = false;

    cout << "\n--- Update Book ---\n";
    cout << "Enter Book ID which you want to update: ";
    cin >> id;

    for (int i = 0; i < countbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;

            cout << "\nCurrent Book Information:\n";
            cout << "Book ID: " << bookid[i] << endl;
            cout << "Book Name: " << bookname[i] << endl;
            cout << "Author Name: " << author[i] << endl;
            cout << "Price: " << price[i] << endl;
            cout << "Available: " << (is_available[i] ? "Yes" : "No") << endl;

            cout << "\nWhich thing you want to update?" << endl;
            cout << "1. Book ID" << endl;
            cout << "2. Book Name" << endl;
            cout << "3. Author Name" << endl;
            cout << "4. Price" << endl;
            cout << "5. All" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cout << "Enter New Book ID: ";
                cin >> bookid[i];
                cout << "Book ID updated successfully!" << endl;
                break;

            case 2:
            {
                cout << "Enter New Book Name: ";
                char newName[100];
                cin.getline(newName, 100);

                // Delete old name and allocate new one
                delete[] bookname[i];
                bookname[i] = new char[strlen(newName) + 1];
                strcpy(bookname[i], newName);

                cout << "Book Name updated successfully!" << endl;
                break;
            }

            case 3:
                cout << "Enter New Author Name: ";
                getline(cin, author[i]);
                cout << "Author Name updated successfully!" << endl;
                break;

            case 4:
                cout << "Enter New Price: ";
                cin >> price[i];
                cout << "Price updated successfully!" << endl;
                break;

            case 5:
                cout << "Enter New Book ID: ";
                cin >> bookid[i];
                cin.ignore();

                cout << "Enter New Book Name: ";
                char newName2[100];
                cin.getline(newName2, 100);
                delete[] bookname[i];
                bookname[i] = new char[strlen(newName2) + 1];
                strcpy(bookname[i], newName2);

                cout << "Enter New Author Name: ";
                getline(cin, author[i]);
                cout << "Enter New Price: ";
                cin >> price[i];
                cout << "All information updated successfully!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
            }

            saveallbooks();
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

void books::searchbook()
{
    if (countbooks == 0)
    {
        cout << "No books in the library!" << endl;
        return;
    }

    int id;
    cout << "Enter Book ID to search: " << endl;
    cin >> id;

    int foundIndex = -1;
    for (int i = 0; i < countbooks; i++)
    {
        if (bookid[i] == id)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Book not found!" << endl;
        return;
    }

    cout << "Book ID: " << bookid[foundIndex] << endl;
    cout << "Book Name: " << bookname[foundIndex] << endl;
    cout << "Author Name: " << author[foundIndex] << endl;
    cout << "Price: " << price[foundIndex] << endl;
    if (is_available[foundIndex])
    {
        cout << "Available: Yes" << endl;
    }
    else
    {
        cout << "Available: No" << endl;
    }
}

void books::issuebook()
{
    int id;
    bool found = false;

    cout << "\n--- Issue Book ---\n";
    cout << "Enter Book ID which you want to issue: ";
    cin >> id;

    for (int i = 0; i < countbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            if (is_available[i])
            {
                string username, email, department;
                long long int phone;

                cin.ignore();
                cout << "Enter User Name: ";
                getline(cin, username);
                cout << "Enter Email: ";
                getline(cin, email);
                cout << "Enter Phone Number: ";
                cin >> phone;
                cin.ignore();
                cout << "Enter Department: ";
                getline(cin, department);

                is_available[i] = false;

                cout << "\n========== BOOK ISSUED SUCCESSFULLY ==========\n";
                cout << "Book: " << bookname[i] << " by " << author[i] << endl;
                cout << "Issued to: " << username << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Department: " << department << endl;
                cout << "Issue Date: " << __DATE__ << " " << __TIME__ << endl;
                cout << "Please return it.\n";
                cout << "==============================================\n";

                ofstream file(issuedbooks, ios::app);
                if (file.is_open())
                {
                    file << "Book: " << bookname[i] << " by " << author[i] << endl;
                    file << "Issued to: " << username << endl;
                    file << "Email: " << email << endl;
                    file << "Phone: " << phone << endl;
                    file << "Department: " << department << endl;
                    file << "Issue Date: " << __DATE__ << " " << __TIME__ << endl;
                    file << "==============================================\n\n";
                    file.close();
                }

                saveallbooks();
            }
            else
            {
                cout << "Book is already issued to someone else!" << endl;
            }
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

void books::displayissuedbooks()
{
    ifstream inFile(issuedbooks);

    if (!inFile)
    {
        cout << "No issued books record found." << endl;
        return;
    }

    cout << "\n=== ISSUED BOOKS RECORD ===\n";
    cout<<"========================================"<<endl;
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
}

void books::returnbook()
{
    int id;
    bool found = false;

    cout << "\n--- Return Book ---\n";
    cout << "Enter Book ID which you want to return: ";
    cin >> id;

    for (int i = 0; i < countbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            if (!is_available[i])
            {
                is_available[i] = true;

                cout << "Book '" << bookname[i] << "' returned successfully!" << endl;
                cout << "Thank you for returning the book!" << endl;

                // Record the return in issued books file
                ofstream file(returnBooks, ios::app);
                if (file.is_open())
                {
                    file << "Book Returned: " << bookname[i] << " by " << author[i] << endl;
                    file << "Return Date: " << __DATE__ << " " << __TIME__ << endl;
                    file << "==============================================\n\n";
                    file.close();
                }

                saveallbooks();
            }
            else
            {
                cout << "This book was not issued! It is already available." << endl;
            }
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}
void books ::displayreturnbooks()
{
    ifstream returnFile(returnBooks);
    if (!returnFile)
    {
        cout << "No return books record found." << endl;
        return;
    }
    cout << "\n=== RETURNED BOOKS RECORD ===\n";
    string line;
    while (getline(returnFile, line))
    {
        cout << line << endl;
    }
    returnFile.close();
}

class Admin{
   public:
   books *book;
   Admin(){
    book = new books;
    book->loadallbooks();
   }
   ~Admin(){
       delete book;
   }
   void addbooks(){
    book->addbook();
   }
   void displayallbooks(){
    book->displaybook();
   }
   void issuebook(){
    book->issuebook();
   }
   void returnbook(){
    book->returnbook();
   }
   void displayissuedbooksdetail(){
    book->displayissuedbooks();
   }
   void displayreturnbooksdetail(){
    book->displayreturnbooks();
   }
   void searchbook(){
    book->searchbook();
   }
   void deletebook(){
    book->deletebook();
   }
   void updatebook(){
    book->updatebook();
   }

};

int main()
{
    books *book1 = new books;
    book1->loadallbooks();
    // Admin admin;
    // admin.displayallbooks();
    int choice;
    do
    {
        cout << "\n=== LIBRARY SYSTEM ===" << endl;
        cout << "1. Add Books" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Display All Books" << endl;
        cout << "4. Exit" << endl;
        cout << "5. Update Book" << endl;
        cout << "6. Search Book" << endl;
        cout << "7. Issue Book" << endl;
        cout << "8. Return Book" << endl;
        cout << "9. Display Issued Books" << endl;
        cout << "10. Display Returned Books" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            book1->addbook();
            break;
        case 2:
            book1->deletebook();
            break;
        case 3:
            book1->displaybook();
            break;
        case 4:
            cout << "Goodbye!" << endl;
            break;
        case 5:
            book1->updatebook();
            break;
        case 6:
            book1->searchbook();
            break;
        case 7:
            book1->issuebook();
            break;
        case 8:
            book1->returnbook();
            break;
        case 9:
            book1->displayissuedbooks();
            break;
        case 10:
            book1->displayreturnbooks();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    delete book1;
    return 0;
}