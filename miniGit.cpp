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

void Minigit::init()
{
    Minigit();
    versionNode *vNode = new versionNode;
    vNode->next = NULL;
    vNode->commitNumber = 0;
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
        if (vNode->head == NULL) // if there is nothing in the linked list, add the first thing
        {
            fileNode *file = new fileNode;
            file->fileName = filename;
            vNode->head = file;
            vNode->head->next = NULL;
            cout << "Successfully added " << filename << "." << endl;
        }
        else
        {
            //go to the last node of linked list
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            //the head is now pointing to the file
            fileNode *file = new fileNode;
            file->fileName = filename;
            temp = file;
            temp->next = NULL;
            cout << "Successfully added " << filename << "." << endl;
        }
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
    fileNode *prev = vNode->head;
    fileNode *pres = vNode->head;

    while (pres != NULL)
    {
        //remove desired filename
        if (pres->fileName == input)
        {
            prev->next = pres->next;
            delete pres;
            pres = NULL;
            cout << "Deleted " << input << ". Bye bye bitch (T_T)" << endl;
            return;
        }
        prev = pres;
        pres = pres->next;
    }
    cout << "File not found. You stupid hoe." << endl;
}

void Minigit::commit(versionNode *vNode)
{
    if (vNode->commitNumber == 0) //everything gets committed
    {
        fileNode *temp = vNode->head;
        while (temp != NULL)
        {
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