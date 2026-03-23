#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

class userlogin
{
private:
    string username, email, password, storedUser, storedPass, storedEmail;

public:
    const string logindatafile = "Loginrecord.txt";
    userlogin()
    {
        username = "Unknown";
        email = "Unknown";
        password = "Unknown";
    }
    userlogin(string username, string password, string email) : username(username), password(password), email(email) {}
    void displayMainMenu();
    void signup();
    void login();
    void forgotpassword();
    string OTPgenerator();
    bool userExists(const string &username);
    bool emailExists(const string &email);
};

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
    cout << "========================================" << endl;
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

class Admin
{
public:
    books *book;
    Admin()
    {
        book = new books;
        book->loadallbooks();
    }
    ~Admin()
    {
        delete book;
    }
    void addbooks()
    {
        book->addbook();
    }
    void displayallbooks()
    {
        book->displaybook();
    }
    void issuebook()
    {
        book->issuebook();
    }
    void returnbook()
    {
        book->returnbook();
    }
    void displayissuedbooksdetail()
    {
        book->displayissuedbooks();
    }
    void displayreturnbooksdetail()
    {
        book->displayreturnbooks();
    }
    void searchbook()
    {
        book->searchbook();
    }
    void deletebook()
    {
        book->deletebook();
    }
    void updatebook()
    {
        book->updatebook();
    }
};

// Function prototypes
void displayHeader();

void displayHeader()
{
    system("cls");
    system("color 06");
    cout << "\n\n";
cout << "    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.    \n";
cout << "   (                                   )   \n";
cout << "    )        L I B R A R Y            (    \n";
cout << "   (       M A N A G E M E N T         )   \n";
cout << "    )        S Y S T E M              (    \n";
cout << "   (_._._._._._._._._._._._._._._._.._)   \n";
cout << "\n\n";
}

void userlogin ::displayMainMenu()
{
    cout << "  1. Login \n";
    cout << "  2. Sign Up\n";
    cout << "  3. Forgot Password\n";
    cout << "  0. Exit\n\n";
}

void userlogin ::login()
{
    cout << "\n========== LOGIN ==========\n\n";

    bool loginSuccessful = false;

    cin.ignore();

    cout << "Enter Username: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, password);

    cout << "Enter Email: ";
    getline(cin, email);
    userlogin user(username, password, email);

    ifstream file(logindatafile);
    if (!file.is_open())
    {
        cout << "\n No users registered yet. Please sign up first." << endl;
        return;
    }

    while (file >> storedUser >> storedPass >> storedEmail)
    {
        if (storedUser == username && storedPass == password && storedEmail == email)
        {
            loginSuccessful = true;
            break;
        }
    }
    file.close();

    if (loginSuccessful)
    {
        cout << "\n Welcome, " << username << "!" << endl;
        cout << "Press enter to continue...";
        cin.get();
        cin.ignore();
        system("cls");
        books *book1 = new books;
        book1->loadallbooks();
        int choice;
        while(true)
        {
            cout << "\n=== LIBRARY SYSTEM ===" << endl;
            cout << "1. Display All Books" << endl;
            cout << "2. Search Book" << endl;
            cout << "3. Issue Book" << endl;
            cout << "4. Return Book" << endl;
            cout << "5. Exit" << endl;
            cout << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                system("cls");
                system("color 02");
                book1->displaybook();
                break;
            case 2:
                system("cls");
                system("color 03");
                book1->searchbook();
                break;
            case 3:
                system("cls");
                system("color 06");
                book1->issuebook();
                break;
            case 4:
                system("cls");
                system("color 08");
                book1->returnbook();
                break;
            case 5:
                cout<<endl;
                cout << "Goodbye!" << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
            }
        };

        delete book1;
    }
    else
    {
        cout << "\n Login failed!" << endl;
        cout << "Check your credentials or sign up if you're new." << endl;
    }
}

void userlogin ::signup()
{
    cout << "\n========== SIGN UP ==========\n\n";

    cin.ignore();

    while (true)
    {
        cout << "Enter your name : ";
        getline(cin, username);

        if (userExists(username))
        {
            cout << " Username already taken. Please choose another." << endl;
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter Email: ";
        getline(cin, email);

        if (emailExists(email))
        {
            cout << " Email already registered!" << endl;
        }
        else
        {
            break;
        }
    }

    string password = OTPgenerator();
    userlogin user(username, password, email);

    ofstream file(logindatafile, ios::app);
    if (file.is_open())
    {
        file << username << " " << password << " " << email << endl;
        file.close();

        cout << "\n Thank you for signing up, " << username << "!" << endl;
        cout << " Your password (OTP) is: " << password << endl;
    }
    else
    {
        cout << "\n Error saving registration data!" << endl;
    }
}

void userlogin ::forgotpassword()
{
    cout << "\n========== PASSWORD RECOVERY ==========\n\n";

    int choice;
    cout << "1. Search by Username\n";
    cout << "2. Search by Email\n";
    cout << "3. Return to Main Menu\n";
    cout << "Enter your choice: ";

    cin >> choice;

    cin.ignore();

    switch (choice)
    {
    case 1:
    {
        bool found = false;

        cout << "\nEnter your Username: ";
        getline(cin, username);

        ifstream file(logindatafile);
        if (file.is_open())
        {
            while (file >> storedUser >> storedPass >> storedEmail)
            {
                if (storedUser == username)
                {
                    found = true;
                    cout << "\n Account found!" << endl;
                    cout << "   Username: " << storedUser << endl;
                    cout << "   Password: " << storedPass << endl;
                    cout << "   Email: " << storedEmail << endl;
                    break;
                }
            }
            file.close();
        }

        if (!found)
        {
            cout << "\n No account found with that username." << endl;
        }
        break;
    }

    case 2:
    {
        bool found = false;

        cout << "\nEnter your Email: ";
        getline(cin, email);

        ifstream file(logindatafile);
        if (file.is_open())
        {
            while (file >> storedUser >> storedPass >> storedEmail)
            {
                if (storedEmail == email)
                {
                    found = true;
                    cout << "\n Account found!" << endl;
                    cout << "   Username: " << storedUser << endl;
                    cout << "   Password: " << storedPass << endl;
                    cout << "   Email: " << storedEmail << endl;
                    break;
                }
            }
            file.close();
        }

        if (!found)
        {
            cout << "\n No account found with that email." << endl;
        }
        break;
    }

    case 3:
        return;

    default:
        cout << "\n Invalid choice!" << endl;
    }
}

bool userlogin ::userExists(const string &username)
{
    ifstream file(logindatafile);
    if (!file.is_open())
    {
        return false;
    }

    while (file >> storedUser >> storedPass >> storedEmail)
    {
        if (storedUser == username)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool userlogin ::emailExists(const string &email)
{
    ifstream file(logindatafile);
    if (!file.is_open())
    {
        return false;
    }

    string storedUser, storedPass, storedEmail;

    while (file >> storedUser >> storedPass >> storedEmail)
    {
        if (storedEmail == email)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

string userlogin ::OTPgenerator()
{
    int size = 4;
    srand(time(0));
    string numbers = "1234567890";
    string result = "";

    for (int i = 0; i < size; i++)
    {
        result += numbers[rand() % 10];
    }

    cout << "Your OTP code is: " << result << endl;
    return result;
}

int main()
{
    displayHeader();
    userlogin user;
    while (true)
    {

        int choice;
        cout << "1.User" << endl;
        cout << "2.Admin" << endl;
        cout << "3.Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            int loginchoice;
            user.displayMainMenu();
            cout << "Enter your choice: " << endl;
            cin >> loginchoice;

            switch (loginchoice)
            {
            case 1:
            {
                system("cls");
                user.login();
                break;
            }
            case 2:
            {
                system("cls");
                user.signup();
                break;
            }
            case 3:
            {
                system("cls");
                user.forgotpassword();
                break;
            }
            default:
                cout << "Invalid Choice" << endl;
            }
            break;
        }

        case 2:
        {
            system("cls");
            system("color 03");
            cout << "\n========== ADMIN LOGIN ==========\n\n";
            string name;
            int password;
            bool loginSuccessful = false;

            cin.ignore();

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter Password: ";
            cin >> password;
            if (name == "admin" && password == 1234)
            {
                cout << "\n Welcome back, " << name << "!" << endl;
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                system("cls");
                Admin admin;

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
                        system("cls");
                        system("color 01");
                        admin.addbooks();
                        break;
                    case 2:
                        system("cls");
                        system("color 04");
                        admin.deletebook();
                        break;
                    case 3:
                        system("cls");
                        system("color 02");
                        admin.displayallbooks();
                        break;
                    case 4:
                        system("cls");
                        system("color 03");
                        cout << "Goodbye!" << endl;
                        exit(0);
                        break;
                    case 5:
                        system("cls");
                        system("color 05");
                        admin.updatebook();
                        break;
                    case 6:
                        system("cls");
                        system("color 06");
                        admin.searchbook();
                        break;
                    case 7:
                        system("cls");
                        system("color 07");
                        admin.issuebook();
                        break;
                    case 8:
                        system("cls");
                        system("color 08");
                        admin.returnbook();
                        break;
                    case 9:
                        system("cls");
                        system("color 09");
                        admin.displayissuedbooksdetail();
                        break;
                    case 10:
                        system("cls");
                        system("color 0A");
                        admin.displayreturnbooksdetail();
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                    }
                } while (choice != 4);
            }
            else
            {
                cout << "\n Login failed!" << endl;
                cout << "Check your credentials or sign up if you're new." << endl;
                cout<<endl;
            }
            break;
        }

        case 3:
        {
            cout << "Thanks for visiting" << endl;
            exit(0);
        }
        default:
            cout << "Invalid Choice" << endl;
        }
    }

    return 0;
}
