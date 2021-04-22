#include <filesystem>
#include <fstream>
#include "miniGit.h"
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

//constructor
Minigit::Minigit()
{
    fs::remove_all(".minigit");
    fs::create_directories(".minigit");
}

bool Minigit::init()
{
    Minigit();
    versionNode *vNode = new versionNode;
    vNode->next = NULL;
    vNode->commitNumber = 0;
    return true;
}

void Minigit::add(versionNode *vNode)
{
    //checking if file to add exists
    ifstream inFile;
    string filename;
    cout << "Enter existing file name" << endl;
    cin >> filename;
    inFile.open(filename);
    if (inFile.is_open())
    {
        fileNode *temp = vNode->head;
        //go to the last node of linked list
        while (temp != NULL)
        {
            temp = temp->next;
        }
        //the head is now pointing to the file
        fileNode *file = new fileNode;
        file->fileName = filename;
        temp->next = file;
        file->fileName = filename + "00";
    }
    else
    {
        cout << "File name does not exist. Nice try bitch." << endl;
    }
}

void Minigit::remove(versionNode *vNode)
{
    string input;
    cout << "What file do you want to remove?" << endl;
    cin >> input;
    fileNode *prev = vNode->head->next;
    fileNode *pres = vNode->head->next;
    //traverse through linked list
    while (pres->next != NULL)
    {
        //remove desired filename
        if (pres->fileName == input)
        {
            prev->next = pres->next;
            delete pres;
            pres = NULL;
            cout << "Deleted " << input << ". Bye bye bitch (T_T)" << endl;
        }
        prev = pres;
        pres = pres->next;
    }
    //cant find desired file
    if (pres->next == NULL)
    {
        cout << "File not found. You stupid hoe." << endl;
    }
}

void Minigit::commit(versionNode *vNode)
{
    if (vNode->commitNumber == 0) //everything gets committed
    {
        fileNode *temp = vNode->head->next;
        while (temp != NULL)
        {
            ifstream inFile;

            temp = temp->next;
        }
    }
    else
    {
    }
}

void Minigit::checkOut(fileNode *file)
{
}