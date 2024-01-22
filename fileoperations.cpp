#include <iostream>
#include <fstream>


using namespace std;

struct User {
    char* name;
    char* surname;
    int age;
};

const char* FILENAME = "user_data.txt";
const int MAX_USERS = 100;

void writeUserToFile(ofstream& file, const User& user, int userNumber) {
    file << "User " << userNumber << "\nName: " << user.name << "\nSurname: " << user.surname << "\nAge: " << user.age << "\n\n";
}

void readAndDisplayFromFile(ifstream& file) {
    cout << "\nUser Information from File:\n";

    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
}

void releaseMemory(User* users, int numUsers) {
    for (int i = 0; i < numUsers; ++i) {
        delete[] users[i].name;
        delete[] users[i].surname;
    }
    delete[] users;
}

int main() {
    ofstream outFile(FILENAME, ios::app);

    if (!outFile.is_open()) {
        cerr << "Error opening file for writing.\n";
        return 1;
    }

    User* users = new User[MAX_USERS];
    int numUsers;

    cout << "Enter the number of users (1-" << MAX_USERS << "): ";
    cin >> numUsers;

    if (numUsers <= 0 || numUsers > MAX_USERS) {
        cerr << "Invalid number of users. Exiting.\n";
        delete[] users;
        return 1;
    }

    for (int i = 0; i < numUsers; ++i) {
        users[i].name = new char[50];
        users[i].surname = new char[50];

        cout << "\nEnter information for user " << i + 1 << ":\n";

        cout << "Name: ";
        cin >> users[i].name;

        cout << "Surname: ";
        cin >> users[i].surname;

        cout << "Age: ";
        cin >> users[i].age;

        writeUserToFile(outFile, users[i], i + 1);
    }

    outFile.close();

    ifstream inFile(FILENAME);

    if (!inFile.is_open()) {
        cerr << "Error opening file for reading.\n";
        releaseMemory(users, numUsers);
        return 1;
    }

    readAndDisplayFromFile(inFile);

    inFile.close();

    releaseMemory(users, numUsers);

    return 0;
}
