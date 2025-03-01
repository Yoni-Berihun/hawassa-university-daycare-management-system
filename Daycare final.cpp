/* Title : Hawassa University Daycare Management System:
    Group Memebers             ID NO
    Yeabkal Zenebe           NaScRR/0803/15
    Yonatan Berihun          NaScR/3962/16
    Milto  Workisa           NaScR/2990/16
    Dagimawi Teferi          NaScR/1750/16
    Firew Kassa              NaScR/5158/16
    Eden Tesfaye             NaScR/1868/16
    Lalistu Dagne            NaScR/2656/16
                                           */
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>//background color
using namespace std;

const int MAX_CHILDREN = 40;

void clearScreen()
{
    system("cls");
}

struct Child {
    string id;
    string name;
    int age;
    string parentName;
    string parentContact;
    string emeName;
    string emeContact;
}newChild;

Child children[MAX_CHILDREN];
int childCount = 0;

void adminMenu();
void addNewChild();
void showChildren();
void searchChild();
void modifyChild();
void deleteChild();

int getMenuChoice()
{
    int choice;
    clearScreen();
    cout << "\nMenu:\n";
    cout << "1. Add new child\n";
    cout << "2. Show all children\n";
    cout << "3. Search for a child\n";
    cout << "4. Update child details\n";
    cout << "5. Remove a child\n";
    cout << "6. Logout\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void adminMenu()
{
    int choice;
    do {
        choice = getMenuChoice();
        switch (choice) {
            case 1:
                addNewChild();
                break;
            case 2:
                showChildren();
                break;
            case 3:
                searchChild();
                break;
            case 4:
                modifyChild();
                break;
            case 5:
                deleteChild();
                break;
            case 6:
                cout << "Logged out successfully.\n";
                Sleep(2000);
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(2000);
                break;
        }
    } while (choice != 6);
}

void addNewChild()
{
    clearScreen();
    fstream file;
    if (childCount == MAX_CHILDREN) {
        cout << "Maximum child limit reached.\n";
        return;
    }


    while (true) { 
        cout << "Enter child ID: ";
        if (cin >> newChild.id) {
            break;
        } else {
            cout << "Invalid input! Please enter a valid ID.\n";
           // cin.clear();
           // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore();
    cout << "Enter child name: ";
    getline(cin, newChild.name);
    
    while (true) { 
        cout << "Enter child age: ";
        if (cin >> newChild.age) {
            break;
        }
	 else {
            cout << "Invalid input! Please enter a valid ID.\n";
           // cin.clear();
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore();
    cout << "Enter parent name: ";
    getline(cin, newChild.parentName);
    cout << "Enter parent contact: ";
    getline(cin, newChild.parentContact);
    cout << "Enter emergency person: ";
    getline(cin, newChild.emeName);
    cout<< "enetr emergency person Contact:";
    getline(cin, newChild.emeContact);
    file.open("children.txt", ios::out | ios::app);
    file << newChild.id << "\n";
    file << newChild.name << "\n";
    file << newChild.age << "\n";
    file << newChild.parentName << "\n";
    file << newChild.parentContact << "\n";
    file << newChild.emeName << "\n";
    file << newChild.emeContact << "\n";
    file.close();

    children[childCount++] = newChild;

    cout << "Child added successfully!\n";
    Sleep(1500);
}

void showChildren()
{
    clearScreen();
    fstream file;
    Child child;
    file.open("children.txt", ios::in);
    if (!file) {
        cout << "No children are currently registered.\n";
        Sleep(1500);
        return;
    }

    cout << "\nRegistered Children:\n";
    while (file >> child.id) {
        file.ignore();
        getline(file, child.name);
        file >> child.age;
        file.ignore();
        getline(file, child.parentName);
        getline(file, child.parentContact);
        getline(file, child.emeName);
        getline(file, child.emeContact);
        cout << "ID: " << child.id << endl;
        cout << "Name: " << child.name << endl;
        cout << "Age: " << child.age << endl;
        cout << "Parent Name: " << child.parentName << endl;
        cout << "Parent Contact: " << child.parentContact << endl;
        cout << "Emergency person Name: " << child.emeName << endl;
        cout << "Emergency person Contact:" << child.emeContact << endl;
        
        cout << "--------------------------\n";
    }
    file.close();
    Sleep(1500);
}

void searchChild()
{
    clearScreen();
    fstream file;
    Child child;
    file.open("children.txt", ios::in);
    if (!file) {
        cout << "No children are currently registered.\n";
        Sleep(1500);
        return;
    }

    string searchID;
    cout << "Enter child ID to search: ";
    cin >> searchID;

    while (file >> child.id) {
        file.ignore();
        getline(file, child.name);
        file >> child.age;
        file.ignore();
        getline(file, child.parentName);
        getline(file, child.parentContact);
        getline(file, child.emeName);
        getline(file, child.emeContact);
        if (child.id == searchID) {
            cout << "\nChild Details:\n";
            cout << "ID: " << child.id << endl;
            cout << "Name: " << child.name << endl;
            cout << "Age: " << child.age << endl;
            cout << "Parent Name: " << child.parentName << endl;
            cout << "Parent Contact: " << child.parentContact << endl;
            cout << "Emergency person name: " << child.emeName << endl;
            cout << "Emergency person Contact:" << child.emeContact<<endl;
            file.close();
            Sleep(1500);
            return;
        }
    }

    cout << "Child with ID " << searchID << " not found.\n";
    file.close();
    Sleep(1500);
}

void modifyChild()
{
    clearScreen();
    fstream file, tempFile;
    Child child;
    bool found = false;

    file.open("children.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    if (!file || !tempFile) {
        cout << "Error accessing files.\n";
        return;
    }

    string modifyID;
    cout << "Enter child ID to modify: ";
    cin >> modifyID;

    while (file >> child.id) {
        file.ignore();
        getline(file, child.name);
        file >> child.age;
        file.ignore();
        getline(file, child.parentName);
        getline(file, child.parentContact);
        getline(file, child.emeName);
        getline(file, child.emeContact);
        if (child.id == modifyID) {
            found = true;
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, child.name);
            cout << "Enter new age: ";
            cin >> child.age;
            cin.ignore();
            cout << "Enter new parent name: ";
            getline(cin, child.parentName);
            cout << "Enter new parent contact: ";
            getline(cin, child.parentContact);
            cout << "Enter new Emergency Person Name: ";
            getline(cin, child.emeName);
            cout<< "Enetr person Contact :";
            getline(cin, child.emeContact);
            cout << "Child details updated successfully!\n";
        }
        tempFile << child.id << "\n";
        tempFile << child.name << "\n";
        tempFile << child.age << "\n";
        tempFile << child.parentName << "\n";
        tempFile << child.parentContact << "\n";
        tempFile << child.emeName<< "\n";
        tempFile << child.emeContact <<"\n";
    }

    file.close();
    tempFile.close();
    remove("children.txt");
    rename("temp.txt", "children.txt");

    if (!found) {
        cout << "Child with ID " << modifyID << " not found.\n";
    }
    Sleep(1500);
}

void deleteChild()
{
    clearScreen();
    fstream file, tempFile;
    Child child;
    bool found = false;

    file.open("children.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    if (!file || !tempFile) {
        cout << "Error accessing files.\n";
        return;
    }

   string deleteID;
    cout << "Enter child ID to delete: ";
    cin >> deleteID;

    while (file >> child.id) {
        file.ignore();
        getline(file, child.name);
        file >> child.age;
        file.ignore();
        getline(file, child.parentName);
        getline(file, child.parentContact);
        getline(file, child.emeName);
        getline(file, child.emeContact);
        if (child.id == deleteID) {
            found = true;
            cout << "Child removed successfully!\n";
            continue;
        }
        tempFile << child.id << "\n";
        tempFile << child.name << "\n";
        tempFile << child.age << "\n";
        tempFile << child.parentName << "\n";
        tempFile << child.parentContact << "\n";
        tempFile << child.emeName << "\n";
        tempFile << child.emeContact <<"\n";
        
    }

    file.close();
    tempFile.close();
    remove("children.txt");
    rename("temp.txt", "children.txt");

    if (!found) {
        cout << "Child with ID " << deleteID << " not found.\n";
    }
    Sleep(1500);
}
void asciart()
 {
cout<<" _    _ _    _    _____                                    \n";
cout<<"| |  | | |  | |  |  __ \                                   \n";
cout<<"| |__| | |  | |  | |  | | __ _ _   _    ___ __ _ _ __ ___  \n";
cout<<"|  __  | |  | |  | |  | |/ _` | | | |  / __/ _` | '__/ _ \ \n";
cout<<"| |  | | |__| |  | |__| | (_| | |_| | | (_| (_| | | |  __/ \n";
cout<<"|_|  |_|\____/    |_____/ \__,_|\__, |       \___\__,_|_|  \___| \n";
cout<<"                               __/ |                    \n";  
cout<<"                              |___/                      \n";
Sleep(2500);
}

int main()
{
	system("color 3F");
	asciart();
    
    
    
    int choice;
    do {
        clearScreen();
        cout << "Welcome to the Daycare Management System\n";
        cout << "1. Admin\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                cout << "Goodbye!\n";
                Sleep(1500);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                Sleep(1500);
                break;
        }
    } while (choice != 2);

    return 0;
}
