#include iostream
#include fstream
#include cstdlib
#include conio.h
#include algorithm
#include string

using namespace std;

 Node structure for a contact
struct ContactNode {
    string firstName;
    string lastName;
    string phoneNumber;
    string email;   Add this line
    ContactNode next;
};


 Function declarations
void addContact();
void searchContact();
void displayContacts();
void editContact();
void deleteContact();
void selfExit();
bool checkDigits(const string&);
bool checkNumbers(const string&);
void binarySearchByName(const string&);
int hashFunction(const string&);

 Global variables
ContactNode contactList = nullptr;
const int hashTableSize = 26;
ContactNode hashTable[hashTableSize] = {nullptr};

int main() {
    short int choice;

    do {
        system(cls);
        system(color 0A);
        cout  nnntttContact Management System;
        cout  nnt1. Add Contactnt2. Search Contactnt3. Display Contactsnt4. Edit Contactnt5. Delete Contactnt6. Exitnt ;
        cin  choice;

        switch (choice) {
    case 1
        addContact();
        break;
    case 2
        searchContact();
        break;
    case 3
        displayContacts();
        break;
    case 4
        selfExit();
        break;
    case 5
        editContact();
        break;
    case 6
        deleteContact();
        break;
    default
        cout  nntInvalid Input!;
        cout  ntPress Any Key To Continue..;
        getch();
}

    } while (choice != 4);

    return 0;
}

void selfExit() {
     Free memory before exiting
    ContactNode current = contactList;
    while (current != nullptr) {
        ContactNode temp = current;
        current = current-next;
        delete temp;
    }

    for (int i = 0; i  hashTableSize; ++i) {
        current = hashTable[i];
        while (current != nullptr) {
            ContactNode temp = current;
            current = current-next;
            delete temp;
        }
    }

    system(cls);
    cout  nnnttThank You For Using!;
    exit(0);
}

void addContact() {
    system(cls);
    string fname, lname, phoneNum, email;

    cout  nntEnter First Name  ;
    cin  fname;
    cout  ntEnter Last Name  ;
    cin  lname;
    cout  ntEnter 10-Digit Phone Number  ;
    cin  phoneNum;
    cout  ntEnter Email  ;
    cin  email;

    if (checkDigits(phoneNum) && checkNumbers(phoneNum)) {
         Create a new contact node
        ContactNode newContact = new ContactNode{fname, lname, phoneNum, email, nullptr};

         Add the new contact to the linked list
        if (contactList == nullptr) {
            contactList = newContact;
        } else {
            ContactNode current = contactList;
            while (current-next != nullptr) {
                current = current-next;
            }
            current-next = newContact;
        }

         Add the new contact to the hash table
        int hashValue = hashFunction(fname);
        if (hashTable[hashValue] == nullptr) {
            hashTable[hashValue] = newContact;
        } else {
            newContact-next = hashTable[hashValue];
            hashTable[hashValue] = newContact;
        }

        cout  ntContact Saved Successfully!;
    } else {
        cout  ntInvalid Phone Number!;
    }

    cout  ntPress Any Key To Continue..;
    getch();
}


void searchContact() {
    system(cls);
    int searchChoice;
    cout  ntSearch Contact Bynt1. Nament2. Phone Numbernt3. Backnt ;
    cin  searchChoice;

    switch (searchChoice) {
        case 1
            {
                string keyword;
                cout  ntEnter Name To Search  ;
                cin.ignore();   Ignore the newline character in the buffer
                getline(cin, keyword);
                binarySearchByName(keyword);
            }
            break;
        case 2
            {
                string phoneNumber;
                cout  ntEnter Phone Number To Search  ;
                cin  phoneNumber;
                 Add search by phone number logic here
                 Modify the ContactNode structure and functions accordingly
            }
            break;
        case 3
            return;   Go back to the main menu
        case 4
            editContact();
            break;
        case 5
            deleteContact();
            break;

        default
            cout  ntInvalid Choice!;
    }

    cout  ntPress Any Key To Continue..;
    getch();
}

void binarySearchByName(const string& name) {
    int arraySize = 0;
    ContactNode sortedArray[100]; 

    for (int i = 0; i  hashTableSize; ++i) {
        ContactNode current = hashTable[i];
        while (current != nullptr) {
            sortedArray[arraySize++] = current;
            current = current-next;
        }
    }

    for (int i = 0; i  arraySize - 1; ++i) {
        for (int j = 0; j  arraySize - i - 1; ++j) {
            if (sortedArray[j]-firstName  sortedArray[j + 1]-firstName) {
                swap(sortedArray[j], sortedArray[j + 1]);
            }
        }
    }

     Binary search
    int low = 0, high = arraySize - 1;
    while (low = high) {
        int mid = (low + high)  2;
        if (sortedArray[mid]-firstName == name) {
             Contact found
            cout  nnnttContact details..;
            cout  nntFirst Name    sortedArray[mid]-firstName;
            cout  ntLast Name    sortedArray[mid]-lastName;
            cout  ntPhone Number    sortedArray[mid]-phoneNumber;
            return;
        } else if (sortedArray[mid]-firstName  name) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout  ntNo Such Contact Found;
}

int hashFunction(const string& name) {
    char firstChar = toupper(name[0]);   Convert to uppercase for case-insensitive hashing
    int index = int(firstChar) - int('A');
    return index = 0 && index  hashTableSize  index  -1;
}

bool checkDigits(const string& str) {
    return str.length() == 10 && all_of(str.begin(), str.end(), isdigit);
}

bool checkNumbers(const string& str) {
    return all_of(str.begin(), str.end(), isdigit);
}

void displayContacts() {
    system(cls);
    cout  nnttContact Listnn;

     Display contacts from the linked list
    ContactNode current = contactList;
    while (current != nullptr) {
        cout  ntFirst Name   current-firstName;
        cout  ntLast Name   current-lastName;
        cout  ntPhone Number   current-phoneNumber;
        cout  ntEmail   current-email  nn;
        current = current-next;
    }

    cout  ntPress Any Key To Continue..;
    getch();
}
void editContact() {
    system(cls);
    string nameToEdit;
    cout  ntEnter Name to Edit  ;
    cin.ignore();
    getline(cin, nameToEdit);

     Search for the contact to edit
    int hashValue = hashFunction(nameToEdit);
    ContactNode current = hashTable[hashValue];
    ContactNode prev = nullptr;

    while (current != nullptr) {
        if (current-firstName == nameToEdit) {
             Edit the contact information
            cout  ntEnter New First Name  ;
            cin  current-firstName;
            cout  ntEnter New Last Name  ;
            cin  current-lastName;
            cout  ntEnter New Phone Number  ;
            cin  current-phoneNumber;
            cout  ntEnter New Email  ;
            cin  current-email;

            cout  ntContact Edited Successfully!;
            cout  ntPress Any Key To Continue..;
            getch();
            return;
        }

        prev = current;
        current = current-next;
    }

    cout  ntNo Such Contact Found;
    cout  ntPress Any Key To Continue..;
    getch();
}

void deleteContact() {
    system(cls);
    string nameToDelete;
    cout  ntEnter Name to Delete  ;
    cin.ignore();
    getline(cin, nameToDelete);

     Search for the contact to delete
    int hashValue = hashFunction(nameToDelete);
    ContactNode current = hashTable[hashValue];
    ContactNode prev = nullptr;

    while (current != nullptr) {
        if (current-firstName == nameToDelete) {
             Delete the contact
            if (prev == nullptr) {
                hashTable[hashValue] = current-next;
            } else {
                prev-next = current-next;
            }

            delete current;

            cout  ntContact Deleted Successfully!;
            cout  ntPress Any Key To Continue..;
            getch();
            return;
        }

        prev = current;
        current = current-next;
    }

    cout  ntNo Such Contact Found;
    cout  ntPress Any Key To Continue..;
    getch();
}