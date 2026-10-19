#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

const int MAX_CONTACTS = 100;

struct Contact {
    string name;
    string phone;
    string email;
};

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

// Convert a character safely to lowercase.
char lowerChar(char ch) {
    return static_cast<char>(tolower(static_cast<unsigned char>(ch)));
}

// Case-insensitive comparison: returns -1, 0, or 1.
int compareNames(const string& a, const string& b) {
    size_t i = 0;
    while (i < a.size() && i < b.size()) {
        char ca = lowerChar(a[i]);
        char cb = lowerChar(b[i]);
        if (ca < cb) return -1;
        if (ca > cb) return 1;
        ++i;
    }
    if (a.size() < b.size()) return -1;
    if (a.size() > b.size()) return 1;
    return 0;
}

void sortContacts() {
    // Bubble sort keeps the project focused on basic DSA concepts.
    for (int i = 0; i < contactCount - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < contactCount - i - 1; ++j) {
            if (compareNames(contacts[j].name, contacts[j + 1].name) > 0) {
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int binarySearchByName(const string& name) {
    int low = 0;
    int high = contactCount - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int result = compareNames(contacts[mid].name, name);

        if (result == 0) return mid;
        if (result < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void printContact(const Contact& c) {
    cout << "Name : " << c.name << '\n';
    cout << "Phone: " << c.phone << '\n';
    cout << "Email: " << c.email << '\n';
}

void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        cout << "Directory is full. Maximum contacts: " << MAX_CONTACTS << ".\n";
        return;
    }

    Contact newContact;
    cout << "Enter full name: ";
    getline(cin, newContact.name);

    if (newContact.name.empty()) {
        cout << "Name cannot be empty.\n";
        return;
    }

    if (binarySearchByName(newContact.name) != -1) {
        cout << "A contact with that name already exists. Use a unique name.\n";
        return;
    }

    cout << "Enter phone number: ";
    getline(cin, newContact.phone);
    cout << "Enter email address: ";
    getline(cin, newContact.email);

    contacts[contactCount] = newContact;
    ++contactCount;
    sortContacts();

    cout << "Contact added successfully.\n";
}

void displayContacts() {
    if (contactCount == 0) {
        cout << "The directory is empty.\n";
        return;
    }

    sortContacts();
    cout << "\n--- Contact Directory (" << contactCount << ") ---\n";
    for (int i = 0; i < contactCount; ++i) {
        cout << "\nContact " << i + 1 << '\n';
        printContact(contacts[i]);
    }
}

void searchContact() {
    if (contactCount == 0) {
        cout << "The directory is empty.\n";
        return;
    }

    sortContacts();
    string name;
    cout << "Enter the exact contact name to search: ";
    getline(cin, name);

    int index = binarySearchByName(name);
    if (index == -1) {
        cout << "Contact not found.\n";
    } else {
        cout << "\nContact found:\n";
        printContact(contacts[index]);
    }
}

void updateContact() {
    if (contactCount == 0) {
        cout << "The directory is empty.\n";
        return;
    }

    sortContacts();
    string name;
    cout << "Enter the exact name of the contact to update: ";
    getline(cin, name);

    int index = binarySearchByName(name);
    if (index == -1) {
        cout << "Contact not found.\n";
        return;
    }

    cout << "Current details:\n";
    printContact(contacts[index]);

    cout << "Enter new phone number: ";
    getline(cin, contacts[index].phone);
    cout << "Enter new email address: ";
    getline(cin, contacts[index].email);

    cout << "Contact updated successfully.\n";
}

void deleteContact() {
    if (contactCount == 0) {
        cout << "The directory is empty.\n";
        return;
    }

    sortContacts();
    string name;
    cout << "Enter the exact name of the contact to delete: ";
    getline(cin, name);

    int index = binarySearchByName(name);
    if (index == -1) {
        cout << "Contact not found.\n";
        return;
    }

    for (int i = index; i < contactCount - 1; ++i) {
        contacts[i] = contacts[i + 1];
    }
    --contactCount;

    cout << "Contact deleted successfully.\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== SMART CONTACT DIRECTORY =====\n";
        cout << "1. Add contact\n";
        cout << "2. Display all contacts\n";
        cout << "3. Search contact (Binary Search)\n";
        cout << "4. Update contact\n";
        cout << "5. Delete contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6: cout << "Thank you for using Smart Contact Directory.\n"; break;
            default: cout << "Invalid choice. Please select 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}
