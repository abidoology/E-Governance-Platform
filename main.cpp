#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX_USERS 100

class User {
public:
    int id;
    string name;
    string email;
    string password;

    User(int userId, const string& userName, const string& userEmail, const string& userPassword)
        : id(userId), name(userName), email(userEmail), password(userPassword) {}
};

vector<User> users;

void registerUser();
int loginUser();
void fileComplaint();
void viewComplaints();
void resolveComplaint();
void adminMenu();
void userMenu();

int main() {
    int choice;

    while (true) {
        cout << "\n==== User Management System ====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                int userId = loginUser();
                if (userId != -1) {
                    cout << "Welcome, " << users[userId - 1].name << "!\n";
                }
                break;
            }
            case 3:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

void registerUser() {
    if (users.size() >= MAX_USERS) {
        cout << "User registration limit reached.\n";
        return;
    }

    string name, email, password;
    int userId = users.size() + 1;

    do {
        cout << "\nEnter your name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "Name cannot be empty. Please enter your name.\n";
        }
    } while (name.empty());

    do {
        cout << "Enter your email: ";
        getline(cin, email);
        if (email.empty()) {
            cout << "Email cannot be empty. Please enter your email.\n";
        }
    } while (email.empty());

    do {
        cout << "Create a password: ";
        getline(cin, password);
        if (password.empty()) {
            cout << "Password cannot be empty. Please create a password.\n";
        }
    } while (password.empty());

    users.emplace_back(userId, name, email, password);
    cout << "Registration successful! Your User ID is: " << userId << "\n";
}


int loginUser() {
    int userId;
    string password;

    cout << "\nEnter User ID: ";
    cin >> userId;
    cin.ignore();

    if (userId < 1 || userId > users.size()) {
        cout << "Invalid User ID.\n";
        return -1;
    }

    cout << "Enter Password: ";
    getline(cin, password);

    if (users[userId - 1].password == password) {
        cout << "Login successful!\n";
        return userId;
    } else {
        cout << "Incorrect password.\n";
        return -1;
    }
}
