#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define MAX_USERS 100
#define MAX_COMPLAINTS 100

using namespace std;

class User {
public:
    int id;
    string name;
    string email;
    string password;

    User(int userId, const string &userName, const string &userEmail, const string &userPassword)
        : id(userId), name(userName), email(userEmail), password(userPassword) {}
};

class Complaint {
public:
    int id;
    int userId;
    string title;
    string description;
    string status;

    Complaint(int complaintId, int userId, const string &complaintTitle, const string &complaintDescription)
        : id(complaintId), userId(userId), title(complaintTitle), description(complaintDescription), status("Pending") {}
};

// Global vectors for storing users and complaints
vector<User> users;
vector<Complaint> complaints;

// Function prototypes
void loadUsersFromFile();
void saveUsersToFile();
void loadComplaintsFromFile();
void saveComplaintsToFile();
void registerUser();
int loginUser();
void fileComplaint(int userId);
void viewComplaints(int userId);
void resolveComplaint();
void adminMenu();
void userMenu(int userId);

int main() {
    loadUsersFromFile();
    loadComplaintsFromFile();

    int choice;

    while (true) {
        cout << "\n==== E-Governance Platform ====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
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
                    userMenu(userId);
                }
                break;
            }
            case 3:
                adminMenu();
                break;
            case 4:
                cout << "Exiting the platform. Goodbye!\n";
                saveUsersToFile();
                saveComplaintsToFile();
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

void loadUsersFromFile() {
    ifstream inFile("users.txt");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, email, password;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        int id = stoi(idStr);
        users.emplace_back(id, name, email, password);
    }
    inFile.close();
}

void saveUsersToFile() {
    ofstream outFile("users.txt");
    for (const auto &user : users) {
        outFile << user.id << "," << user.name << "," << user.email << "," << user.password << "\n";
    }
    outFile.close();
}

void loadComplaintsFromFile() {
    ifstream inFile("complaints.txt");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, userIdStr, title, description, status;
        getline(ss, idStr, ',');
        getline(ss, userIdStr, ',');
        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, status, ',');
        int id = stoi(idStr);
        int userId = stoi(userIdStr);
        complaints.emplace_back(id, userId, title, description);
        complaints.back().status = status;
    }
    inFile.close();
}

void saveComplaintsToFile() {
    ofstream outFile("complaints.txt");
    for (const auto &complaint : complaints) {
        outFile << complaint.id << "," << complaint.userId << "," << complaint.title << "," << complaint.description << "," << complaint.status << "\n";
    }
    outFile.close();
}

void registerUser() {
    if (users.size() >= MAX_USERS) {
        cout << "User registration limit reached.\n";
        return;
    }

    string name, email, password;
    int userId = users.size() + 1;

    cout << "\nEnter your name: ";
    getline(cin, name);
    cout << "Enter your email: ";
    getline(cin, email);
    cout << "Create a password: ";
    getline(cin, password);

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
        cout << "Login successful! Welcome, " << users[userId - 1].name << ".\n";
        return userId;
    } else {
        cout << "Incorrect password.\n";
        return -1;
    }
}

void fileComplaint(int userId) {
    if (complaints.size() >= MAX_COMPLAINTS) {
        cout << "Complaint limit reached.\n";
        return;
    }

    string title, description;
    int complaintId = complaints.size() + 1;

    cout << "\nEnter complaint title: ";
    getline(cin, title);
    cout << "Enter complaint description: ";
    getline(cin, description);

    complaints.emplace_back(complaintId, userId, title, description);
    cout << "Complaint filed successfully! Complaint ID: " << complaintId << "\n";
}

void viewComplaints(int userId) {
    cout << "\nYour Complaints:\n";
    for (const auto &complaint : complaints) {
        if (complaint.userId == userId) {
            cout << "Complaint ID: " << complaint.id << "\n";
            cout << "Title: " << complaint.title << "\n";
            cout << "Description: " << complaint.description << "\n";
            cout << "Status: " << complaint.status << "\n\n";
        }
    }
}

void resolveComplaint() {
    int complaintId;

    cout << "\nEnter Complaint ID to resolve: ";
    cin >> complaintId;
    cin.ignore();

    if (complaintId < 1 || complaintId > complaints.size()) {
        cout << "Invalid Complaint ID.\n";
        return;
    }

    complaints[complaintId - 1].status = "Resolved";
    cout << "Complaint ID " << complaintId << " has been resolved.\n";
}

void adminMenu() {
    string password;

    cout << "\nEnter Admin Password: ";
    getline(cin, password);

    if (password == "admin123") {
        cout << "Admin login successful.\n";
        while (true) {
            int choice;
            cout << "\n==== Admin Menu ====\n";
            cout << "1. View All Complaints\n";
            cout << "2. Resolve Complaint\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    for (const auto &complaint : complaints) {
                        cout << "\nComplaint ID: " << complaint.id << "\n";
                        cout << "User ID: " << complaint.userId << "\n";
                        cout << "Title: " << complaint.title << "\n";
                        cout << "Description: " << complaint.description << "\n";
                        cout << "Status: " << complaint.status << "\n\n";
                    }
                    break;
                case 2:
                    resolveComplaint();
                    break;
                case 3:
                    cout << "Logging out from admin menu.\n";
                    return;
                default:
                    cout << "Invalid choice! Try again.\n";
            }
        }
    } else {
        cout << "Incorrect admin password.\n";
    }
}

void userMenu(int userId) {
    while (true) {
        int choice;
        cout << "\n==== User Menu ====\n";
        cout << "1. File a Complaint\n";
        cout << "2. View My Complaints\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                fileComplaint(userId);
                break;
            case 2:
                viewComplaints(userId);
                break;
            case 3:
                cout << "Logging out. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
