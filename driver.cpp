#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include "miniGit.h"

void menu()
{
    Minigit m;
    versionNode *vNode;
    bool initialized = false; //make sure to make the people initialize using a bool
    //initialiaze vNOde to NULL and stuffs
    cout << "Select a numerical option:" << endl;
    cout << "+====Main Menu====+" << endl;
    cout << "1. init" << endl
         << "2. add" << endl
         << "3. rm" << endl
         << "4. commit" << endl
         << "5. checkout" << endl
         << "6. quit" << endl
         << "+=================+" << endl;

    int option;
    //make sure menu loops until user quits
    while (option != 6)
    {
        cin >> option;
        switch (option)
        {
        case 1:
            m.init();
            initialized = true;
            cout << "Repository initialized bitch." << endl;
            break;
        case 2:
            if (initialized == false)
            {
                cout << "Initialize repository first bitch. Enter 1." << endl;
                break;
            }
            m.add(vNode);
            break;
        case 3:
            if (initialized == false)
            {
                cout << "Initialize repository first bitch. Enter 1." << endl;
                break;
            }
            m.remove(vNode);
            break;
        case 4:
            if (initialized == false)
            {
                cout << "Initialize repository first bitch. Enter 1." << endl;
                break;
            }
            m.commit(vNode);
            break;
        case 5:
            if (initialized == false)
            {
                cout << "Initialize repository first bitch. Enter 1." << endl;
                break;
            }
            break;
        case 6:
            cout << "Goodbye!" << endl;
            return;
        default:
            cout << "Invalid option" << endl;
            break;
        }
        cout << "Select a numerical option:" << endl;
        cout << "+====Main Menu====+" << endl;
        cout << "1. init" << endl
             << "2. add" << endl
             << "3. rm" << endl
             << "4. commit" << endl
             << "5. checkout" << endl
             << "6. quit" << endl;
    }
}

int main()
{
    bool initialized = false;
    Minigit m;
    menu();
}