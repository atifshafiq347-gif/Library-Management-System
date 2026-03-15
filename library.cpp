#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

const string logindata = "LoginData.txt";
const string allbooks = "AllBooks.txt";
const string issuedbooks = "IssuedBooks.txt";

class adminlibrary
{
private:
    int bookid[100];
    string bookname[100];
    string author[100];
    float price[100];
    bool available[100];
    int totalbooks;

    void loadBooksFromFile();
    void saveAllBooksToFile();

public:
    adminlibrary()
    {
        totalbooks = 0;
        loadBooksFromFile();
    }

    void adminmenu();
    void adminswitch();
    void addbook();
    void deletebook();
    void updatebook();
    void searchbook();
    void issuebook();
    void returnbook();
    void displayallbooks();
};

class userlibrary
{
private:
    int bookid[100];
    string bookname[100];
    string author[100];
    float price[100];
    bool available[100];
    int totalbooks;

    void loadBooksFromFile();

public:
    userlibrary()
    {
        totalbooks = 0;
        loadBooksFromFile();
    }

    void usermenu();
    void userswitch();
    void searchbook();
    void issuebook();
    void returnbook();
    void displayallbooks();
};

class Login
{
private:
    string username;
    string password;
    string email;
    string storedUser;
    string storedPass;
    string storedEmail;

    void clearScreen();
    void displayHeader();
    string generateOTP();
    bool userExists(const string &username);
    bool emailExists(const string &email);
    void pressenter();

public:
    void displayMainMenu();
    void performLogin();
    void performSignup();
    void performForgotPassword();
    void loginswitch();
    void mainswitch();
    void performadminlogin();
};

void adminlibrary::loadBooksFromFile()
{
    ifstream file(allbooks);
    if (!file.is_open())
    {
        return;
    }

    while (file >> bookid[totalbooks] >> ws &&
           getline(file, bookname[totalbooks]) &&
           getline(file, author[totalbooks]) &&
           file >> price[totalbooks] >> available[totalbooks])
    {
        totalbooks++;
        if (totalbooks >= 100)
            break;
    }
    file.close();
}

void adminlibrary::saveAllBooksToFile()
{
    ofstream file(allbooks);
    if (!file.is_open())
    {
        cout << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (int i = 0; i < totalbooks; i++)
    {
        file << "-----------------------------" << endl;
        file << bookid[i] << endl;
        file << bookname[i] << endl;
        file << author[i] << endl;
        file << price[i] << endl;
        file << available[i] << endl;
        file << "-----------------------------" << endl;
    }
    file.close();
}

void adminlibrary::adminmenu()
{
    system("cls");
    system("color 04");
    cout << "\n========== LIBRARY MANAGEMENT SYSTEM (ADMIN) ==========\n";
    cout << "1. Add Book" << endl;
    cout << "2. Delete Book" << endl;
    cout << "3. Update Book" << endl;
    cout << "4. Search Book" << endl;
    cout << "5. Issue Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Books" << endl;
    cout << "8. Exit" << endl;
    cout << "========================================================\n";
}

void adminlibrary::addbook()
{
    system("cls");
    system("color 04");
    if (totalbooks >= 100)
    {
        cout << "Library is full! Cannot add more books." << endl;
        return;
    }

    cout << "\n--- Add New Book ---\n";
    cout << "Enter Book ID: ";
    cin >> bookid[totalbooks];

    for (int i = 0; i < totalbooks; i++)
    {
        if (bookid[i] == bookid[totalbooks])
        {
            cout << "Book ID already exists! Please use different ID." << endl;
            return;
        }
    }

    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, bookname[totalbooks]);
    cout << "Enter Author Name: ";
    getline(cin, author[totalbooks]);
    cout << "Enter Price: ";
    cin >> price[totalbooks];

    available[totalbooks] = true;
    totalbooks++;

    saveAllBooksToFile();

    cout << "Book added successfully! Total books: " << totalbooks << endl;
}

void adminlibrary::deletebook()
{
    system("cls");
    system("color 06");
    int id;
    bool found = false;

    cout << "\n--- Delete Book ---\n";
    cout << "Enter Book ID which you want to delete: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            for (int j = i; j < totalbooks - 1; j++)
            {
                bookid[j] = bookid[j + 1];
                bookname[j] = bookname[j + 1];
                author[j] = author[j + 1];
                price[j] = price[j + 1];
                available[j] = available[j + 1];
            }
            totalbooks--;
            saveAllBooksToFile();

            cout << "Book deleted successfully!" << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

void adminlibrary::updatebook()
{
    system("cls");
    system("color 06");
    int id;
    bool found = false;

    cout << "\n--- Update Book ---\n";
    cout << "Enter Book ID which you want to update: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;

            cout << "\nCurrent Book Information:\n";
            cout << "Book Name: " << bookname[i] << endl;
            cout << "Author Name: " << author[i] << endl;
            cout << "Price: " << price[i] << endl;
            if (available[i])
            {
                cout << "Status: Available" << endl;
            }
            else
            {
                cout << "Status: Issued" << endl;
            }

            cout << "\nWhich thing you want to update?" << endl;
            cout << "1. Book Name" << endl;
            cout << "2. Author Name" << endl;
            cout << "3. Price" << endl;
            cout << "4. All" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cout << "Enter New Book Name: ";
                getline(cin, bookname[i]);
                cout << "Book Name updated successfully!" << endl;
                break;

            case 2:
                cout << "Enter New Author Name: ";
                getline(cin, author[i]);
                cout << "Author Name updated successfully!" << endl;
                break;

            case 3:
                cout << "Enter New Price: ";
                cin >> price[i];
                cout << "Price updated successfully!" << endl;
                break;

            case 4:
                cout << "Enter New Book Name: ";
                getline(cin, bookname[i]);
                cout << "Enter New Author Name: ";
                getline(cin, author[i]);
                cout << "Enter New Price: ";
                cin >> price[i];
                cout << "All information updated successfully!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
            }

            saveAllBooksToFile();
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

void adminlibrary::searchbook()
{
    system("cls");
    system("color 09");
    int id;
    bool found = false;

    cout << "\n--- Search Book ---\n";
    cout << "Enter Book ID which you want to search: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            cout << "\n========== BOOK DETAILS ==========\n";
            cout << "Book ID: " << bookid[i] << endl;
            cout << "Book Name: " << bookname[i] << endl;
            cout << "Author Name: " << author[i] << endl;
            cout << "Price: $" << price[i] << endl;
            if (available[i])
            {
                cout << "Status: Available" << endl;
            }
            else
            {
                cout << "Status: Issued" << endl;
            }
            cout << "===================================\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

void adminlibrary::issuebook()
{
    system("cls");
    system("color 04");
    int id;
    bool found = false;

    cout << "\n--- Issue Book ---\n";
    cout << "Enter Book ID which you want to issue: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            if (available[i])
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

                available[i] = false;

                saveAllBooksToFile();

                cout << "\n========== BOOK ISSUED SUCCESSFULLY ==========\n";
                cout << "Book: " << bookname[i] << " by " << author[i] << endl;
                cout << "Issued to: " << username << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Department: " << department << endl;
                cout << "Please return within 15 days.\n";
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

void adminlibrary::returnbook()
{
    system("cls");
    system("color 06");
    int id;
    bool found = false;

    cout << "\n--- Return Book ---\n";
    cout << "Enter Book ID which you want to return: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            if (!available[i])
            {
                available[i] = true;

                saveAllBooksToFile();

                cout << "Book '" << bookname[i] << "' returned successfully!" << endl;
                cout << "Thank you for returning the book!" << endl;

                ofstream file(issuedbooks, ios::app);
                if (file.is_open())
                {
                    file << "Book Returned: " << bookname[i] << " by " << author[i] << endl;
                    file << "Return Date: " << __DATE__ << " " << __TIME__ << endl;
                    file << "==============================================\n\n";
                    file.close();
                }
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

void adminlibrary::displayallbooks()
{
    system("cls");
    system("color 08");
    if (totalbooks == 0)
    {
        cout << "\nNo books in the library!" << endl;
        return;
    }

    cout << "\n========== ALL BOOKS ==========\n";
    cout << "Total Books: " << totalbooks << endl;
    cout << "--------------------------------\n";

    for (int i = 0; i < totalbooks; i++)
    {
        cout << "Book ID: " << bookid[i] << endl;
        cout << "Name: " << bookname[i] << endl;
        cout << "Author: " << author[i] << endl;
        cout << "Price: $" << price[i] << endl;
        if (available[i])
        {
            cout << "Status: Available" << endl;
        }
        else
        {
            cout << "Status: Issued" << endl;
        }
        cout << "--------------------------------\n";
    }
}

void adminlibrary::adminswitch()
{
    int choice;

    while (true)
    {
        adminmenu();
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addbook();
            break;
        case 2:
            deletebook();
            break;
        case 3:
            updatebook();
            break;
        case 4:
            searchbook();
            break;
        case 5:
            issuebook();
            break;
        case 6:
            returnbook();
            break;
        case 7:
            displayallbooks();
            break;
        case 8:
            cout << "\nThank you for using Library Management System!\n";
            cout << "Goodbye!\n";
            exit(0);
            break;
        default:
            cout << "Invalid choice! Please enter between 1-8." << endl;
        }

        if (choice != 8)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

void userlibrary::loadBooksFromFile()
{
    ifstream file(allbooks);
    if (!file.is_open())
    {
        return;
    }

    while (file >> bookid[totalbooks] >> ws &&
           getline(file, bookname[totalbooks]) &&
           getline(file, author[totalbooks]) &&
           file >> price[totalbooks] >> available[totalbooks])
    {
        totalbooks++;
        if (totalbooks >= 100)
            break;
    }
    file.close();
}

void userlibrary::usermenu()
{
    system("cls");
    system("color 02");
    cout << "\n========== LIBRARY MANAGEMENT SYSTEM (USER) ==========\n";
    cout << "1. Search Book" << endl;
    cout << "2. Issue Book" << endl;
    cout << "3. Return Book" << endl;
    cout << "4. Display All Books" << endl;
    cout << "5. Exit" << endl;
    cout << "=======================================================\n";
}

void userlibrary::searchbook()
{
    system("cls");
    int id;
    bool found = false;

    cout << "\n--- Search Book ---\n";
    cout << "Enter Book ID which you want to search: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            cout << "\n========== BOOK DETAILS ==========\n";
            cout << "Book ID: " << bookid[i] << endl;
            cout << "Book Name: " << bookname[i] << endl;
            cout << "Author Name: " << author[i] << endl;
            cout << "Price: $" << price[i] << endl;
            if (available[i])
            {
                cout << "Status: Available" << endl;
            }
            else
            {
                cout << "Status: Issued" << endl;
            }
            cout << "===================================\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

void userlibrary::issuebook()
{
    system("cls");
    int id;
    bool found = false;

    cout << "\n--- Issue Book ---\n";
    cout << "Enter Book ID which you want to issue: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            if (available[i])
            {
                string username, email, department;
                long long int phone;

                cin.ignore();
                cout << "Enter Your Name: ";
                getline(cin, username);
                cout << "Enter Your Email: ";
                getline(cin, email);
                cout << "Enter Phone Number: ";
                cin >> phone;
                cin.ignore();
                cout << "Enter Department: ";
                getline(cin, department);

                available[i] = false;
                cout << "\n========== BOOK ISSUED SUCCESSFULLY ==========\n";
                cout << "Book: " << bookname[i] << " by " << author[i] << endl;
                cout << "Issued to: " << username << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                cout << "Department: " << department << endl;
                cout << "Please return within 15 days.\n";
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

void userlibrary::returnbook()
{
    system("cls");
    system("color 06");
    int id;
    bool found = false;

    cout << "\n--- Return Book ---\n";
    cout << "Enter Book ID which you want to return: ";
    cin >> id;

    for (int i = 0; i < totalbooks; i++)
    {
        if (id == bookid[i])
        {
            found = true;
            if (!available[i])
            {
                available[i] = true;

                cout << "Book '" << bookname[i] << "' returned successfully!" << endl;
                cout << "Thank you for returning the book!" << endl;

                ofstream file(issuedbooks, ios::app);
                if (file.is_open())
                {
                    file << "Book Returned: " << bookname[i] << " by " << author[i] << endl;
                    file << "Return Date: " << __DATE__ << " " << __TIME__ << endl;
                    file << "==============================================\n\n";
                    file.close();
                }
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

void userlibrary::displayallbooks()
{
    system("cls");
    system("color 07");
    if (totalbooks == 0)
    {
        cout << "\nNo books in the library!" << endl;
        return;
    }

    cout << "\n========== ALL BOOKS ==========\n";
    cout << "Total Books: " << totalbooks << endl;
    cout << "--------------------------------\n";

    for (int i = 0; i < totalbooks; i++)
    {
        cout << "Book ID: " << bookid[i] << endl;
        cout << "Name: " << bookname[i] << endl;
        cout << "Author: " << author[i] << endl;
        cout << "Price: $" << price[i] << endl;
        if (available[i])
        {
            cout << "Status: Available" << endl;
        }
        else
        {
            cout << "Status: Issued" << endl;
        }
        cout << "--------------------------------\n";
    }
}

void userlibrary::userswitch()
{
    int choice;

    while (true)
    {
        usermenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            searchbook();
            break;
        case 2:
            issuebook();
            break;
        case 3:
            returnbook();
            break;
        case 4:
            displayallbooks();
            break;
        case 5:
            cout << "\nThank you for using Library Management System!\n";
            cout << "Goodbye!\n";
            exit(0);
            break;
        default:
            cout << "Invalid choice! Please enter between 1-5." << endl;
        }

        if (choice != 5)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

void Login ::mainswitch()
{
    displayHeader();
    int choice;
    cout << "How are you? " << endl;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        performadminlogin();
        break;
    case 2:
        loginswitch();
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        mainswitch();
    }
}

void Login::performadminlogin()
{
    clearScreen();
    cout << "\n========== LOGIN ==========\n\n";

    bool loginSuccessful = false;

    cin.ignore();

    cout << "Enter name: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, password);

    if (username == "Atif" && password == "1234")
    {
        loginSuccessful = true;
    }

    if (loginSuccessful)
    {
        cout << "\n Welcome back, " << username << "!" << endl;
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        adminlibrary admin;
        admin.adminswitch();
    }
    else
    {
        cout << "\n Login failed!" << endl;
        cout << "Check your credentials or sign up if you're new." << endl;
    }
}

void Login::clearScreen()
{
    system("cls");
}

void Login::displayHeader()
{
    system("cls");
    system("color 06");
    cout << "\n\n----------------------------------------\n";
    cout << "-----  LIBRARY MANAGEMENT SYSTEM   -----\n";
    cout << "----------------------------------------\n\n";
}

void Login::pressenter()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

string Login::generateOTP()
{
    int size = 4;
    srand(time(0));
    string numbers = "1234567890";
    string result = "";

    for (int i = 0; i < size; i++)
    {
        result += numbers[rand() % 10];
    }
    return result;
}

bool Login::userExists(const string &username)
{
    ifstream file(logindata);
    string storedUser, storedPass, storedEmail;

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

bool Login::emailExists(const string &email)
{
    ifstream file(logindata);
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

void Login::displayMainMenu()
{
    system("cls");
    system("color 03");
    cout << "  1. Login \n";
    cout << "  2. Sign Up\n";
    cout << "  3. Forgot Password\n";
    cout << "  0. Exit\n\n";
}

void Login::performLogin()
{
    clearScreen();
    cout << "\n========== LOGIN ==========\n\n";

    bool loginSuccessful = false;

    cin.ignore();

    cout << "Enter Username: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, password);

    cout << "Enter Email: ";
    getline(cin, email);

    ifstream file(logindata);
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
        cout << "\n Welcome back, " << username << "!" << endl;
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        userlibrary user;
        user.userswitch();
    }
    else
    {
        cout << "\n Login failed!" << endl;
        cout << "Check your credentials or sign up if you're new." << endl;
    }
}

void Login::performSignup()
{
    clearScreen();
    cout << "\n========== SIGN UP ==========\n\n";

    cin.ignore();

    while (true)
    {
        cout << "Enter Username: ";
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

    password = generateOTP();

    ofstream file(logindata, ios::app);
    if (file.is_open())
    {
        file << username << " " << password << " " << email << endl;
        file.close();

        cout << "\n Thank you for signing up, " << username << "!" << endl;
        cout << " Your password (OTP) is: " << password << endl;
    }
    else
    {
        cout << " Error!" << endl;
    }
}

void Login::performForgotPassword()
{
    clearScreen();
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
        string searchUsername;
        bool found = false;

        cout << "\nEnter your Username: ";
        getline(cin, searchUsername);

        ifstream file(logindata);
        if (file.is_open())
        {
            while (file >> storedUser >> storedPass >> storedEmail)
            {
                if (storedUser == searchUsername)
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
        string searchEmail;
        bool found = false;

        cout << "\nEnter your Email: ";
        getline(cin, searchEmail);

        ifstream file(logindata);
        if (file.is_open())
        {
            while (file >> storedUser >> storedPass >> storedEmail)
            {
                if (storedEmail == searchEmail)
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

void Login::loginswitch()
{
    clearScreen();
    displayHeader();
    displayMainMenu();

    int choice;
    cout << "Enter your choice (1-3, 0 to exit): ";
    cin >> choice;

    switch (choice)
    {
    case 0:
        cout << "\nThank you for using our system. Goodbye!" << endl;
        return;
    case 1:
        performLogin();
        pressenter();
        break;
    case 2:
        performSignup();
        pressenter();
        break;
    case 3:
        performForgotPassword();
        pressenter();
        break;
    default:
        cout << "Please enter a valid number (0-3)" << endl;
        pressenter();
        mainswitch();
        break;
    }
}

int main()
{
    Login loginSystem;
    loginSystem.mainswitch();
    return 0;
}