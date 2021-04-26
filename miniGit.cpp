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

bool hasChanged(string pres, string prev)
{
    ifstream inFile1;
    ifstream inFile2;

    string line1;
    string line2;

    inFile1.open(pres);
    inFile2.open(prev);
    int count1 = 0;
    int count2 = 0;

    //count the number of lines
    while (getline(inFile1, line1))
    {
        count1++;
    }
    while (getline(inFile2, line2))
    {
        count2++;
    }
    //different amount of lines -- txt files aren't the same
    if (count1 != count2)
    {
        return true;
    }
    else
    {
        while (getline(inFile1, line1) && getline(inFile2, line2))
        {
            if (line1 != line2)
            {
                return true;
            }
        }
    }
    return false;
}

/*
    this function updates the version number
*/
string fileNameUpdater(fileNode *file)
{
    string s = "";
    int i = 0;
    //find the underscore
    while (file->fileName[i] != '_')
    {
        s = s + file->fileName[i];
        i++;
    }
    s = s + '_';

    return file;
}

/*
    copies a a file into the .minigit directory
*/
void copyFile(string file1, string file2)
{
    //read file to copy
    ifstream inFile;
    inFile.open(file1);

    //puts file into .minigit directory
    ofstream outFile;
    string outFilename = ".minigit/" + file2;
    outFile.open(outFilename);

    string line;

    //copy line for line
    if (inFile.is_open() && outFile.is_open())
    {
        while (getline(inFile, line))
        {
            outFile << line << endl;
        }
    }
    else
    {
        cout << "copy failed whore" << endl;
    }

    inFile.close();
    outFile.close();
}

void Minigit::commit(versionNode *vNode)
{
    if (vNode->commitNumber == 0)
    {
        fileNode *temp = vNode->head;
        int count = 0;

        //copy to new file
        while (temp != NULL)
        {
            copyFile(temp->fileName, "00.txt");
            temp = temp->next;
        }
    }
    else
    {
        versionNode *prev = vNode->previous;
        fileNode *tempPres = vNode->head;
        fileNode *tempPrev = prev->head;

        //while (tempPrev !=)
    }

    // if (vNode->commitNumber == 0) //everything gets committed becuase there is no previous commit
    // {
    //     fileNode *temp = vNode->head;
    //     //create and copy to new file

    //     while (temp != NULL)
    //     {
    //         temp = temp->next;
    //     }
    // }
    // else // must compare current stuff you want to commit to the past stuff
    // {
    //     versionNode *past = vNode->previous;
    //     fileNode
    // }
}

void Minigit::checkOut(fileNode *file)
{
}