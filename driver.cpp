#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include "miniGit.h"

void menu()
{
    Minigit m;
    //initialiaze vNode to NULL and stuffs
    versionNode *vNode;
    bool initialized = false; //make sure to make the people initialize using a bool
    int ready = true;         // disallow in check out

    int option;
    //make sure menu loops until user quits
    while (option != 6)
    {
        if (vNode->next != NULL)
        {
            cout << "You are unable to add, remove or commit" << endl;
            ready = false;
        }
        else
        {
            ready = true;
        }

        cout << "+====Main Menu====+" << endl;
        cout << "1. init" << endl;
        if (ready)
        {
            cout << "2. add" << endl
                 << "3. rm" << endl
                 << "4. commit" << endl;
        }
        cout << "5. checkout" << endl
             << "6. quit" << endl
             << "+=================+" << endl;
        cout << "You are on commit number: " << vNode->commitNumber << endl;
        cout << "Select a numerical option:" << endl;

        cin >> option;
        if (cin.fail())
        {
            cout << "Input Error: not a number." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (option)
        {
        case 1:
            m.init();
            initialized = true;
            cout << "Repository initialized." << endl;
            break;
        case 2:
            if (initialized == false)
            {
                cout << "Initialize repository first. Enter 1." << endl;
                break;
            }
            if (ready == true)
            {
                m.add(vNode);
            }
            else
            {
                cout << "You are unable to add" << endl;
            }
            break;
        case 3:
            if (initialized == false)
            {
                cout << "Initialize repository first. Enter 1." << endl;
                break;
            }
            if (ready == true)
            {
                m.remove(vNode);
            }
            else
            {
                cout << "You are unable to remove" << endl;
            }
            break;
        case 4:
            if (initialized == false)
            {
                cout << "Initialize repository first. Enter 1." << endl;
                break;
            }
            if (ready == true)
            {
                vNode = m.commit(vNode);
            }
            else
            {
                cout << "You are unable to commit" << endl;
            }

            break;
        case 5:
            if (initialized == false)
            {
                cout << "Initialize repository first. Enter 1." << endl;
                break;
            }

            vNode = m.checkOutCommit(vNode);
            break;
        case 6:
            cout << "Goodbye!" << endl;
            return;
        default:
            cout << "Invalid option" << endl;
            break;
        }

        // add newline to space out the different commands and logs
        cout << endl;
    }
}

int main()
{
    bool initialized = false;
    Minigit m;
    menu();
}