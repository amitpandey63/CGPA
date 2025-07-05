#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

// Function to hash the password (basic XOR for example purposes only)
string simpleHash(string password) {
    for (char &c : password) {
        c = c ^ 0xAA; // XOR with fixed key (not secure, just for demo)
    }
    return password;
}

// Function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter username to register: ";
    cin >> username;

    string filename = "users/" + username + ".txt";
    if (fs::exists(filename)) {
        cout << "Error: Username already exists. Try a different username.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    string hashedPassword = simpleHash(password); // Hashing password

    ofstream outFile(filename);
    outFile << username << endl;
    outFile << hashedPassword << endl;
    outFile.close();

    cout << "Registration successful!\n";
}

// Function to login a user
void loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    string filename = "users/" + username + ".txt";
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Username not found.\n";
        return;
    }

    string storedUsername, storedHashedPassword;
    getline(inFile, storedUsername);
    getline(inFile, storedHashedPassword);
    inFile.close();

    cout << "Enter password: ";
    cin >> password;

    string enteredHashedPassword = simpleHash(password); // Hash entered password

    if (enteredHashedPassword == storedHashedPassword) {
        cout << "Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "Error: Incorrect password.\n";
    }
}

int main() {
    fs::create_directory("users"); // Make sure users directory exists

    int choice;
    cout << "1. Register\n2. Login\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
        registerUser();
    else if (choice == 2)
        loginUser();
    else
        cout << "Invalid choice.\n";

    return 0;
}
