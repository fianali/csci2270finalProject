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
            temp->next = file;
            file->next = NULL;
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

/*
    detects if there has been a change between files of the same name 
*/
bool hasChanged(string pres, string prev)
{
    bool changed = false;
    ifstream inFile1;
    ifstream inFile2;

    string line1;
    string line2;

    inFile1.open(pres);
    inFile2.open(prev);
    int count1 = 0;
    int count2 = 0;

    if (inFile1.is_open() && inFile2.is_open())
    {
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
    }
    else
    {
        cout << "Cannot open files: " + pres + " , " + prev << endl;
    }

    inFile1.close();
    inFile2.close();

    return false;
}

/*
    copies a a file into the .minigit directory
*/
void copyFile(fileNode *fNode)
{

    string file1 = fNode->fileName;
    //read file to copy
    ifstream inFile;
    inFile.open(file1);

    //puts file into .minigit directory
    ofstream outFile;
    string outFilename = ".minigit/" + fNode->fileVersion;
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

/*
    this function updates the version number
*/
void updateChangedFile(fileNode *file)
{
    bool saveFile = false;

    // if either of the files don't exist yet, don't bother checking for changes
    if (file->fileName != "" && file->fileVersion != "" && hasChanged(file->fileName, ".minigit/" + file->fileVersion))
    {
        file->version++;
        saveFile = true; //file has changed, we want to save it
    }

    if (file->version == 0)
    {
        saveFile = true;
    }

    // initialize or update the filename to match the version number
    if (file->fileName != "")
    {
        file->fileVersion = file->fileName + "__(~ ^_^)~" + to_string(file->version);
    }

    if (saveFile)
    {
        copyFile(file);
    }

    // Previous implementation
    //
    // string digits;
    // int version;
    // string s = "";
    // int i = 0;
    // //find the underscore
    // while (file->fileName[i] != '_')
    // {
    //     s = s + file->fileName[i];
    //     i++;
    // }
    // s = s + '_';
    // //change into digit;
    // digits = file->fileName.substr(s.length(), file->fileName.length() - 4);
    // version = stoi(digits);
    // version++;
    // digits = to_string(version);
    // s = s + digits + ".txt";
    // return digits + ".txt";
}

void Minigit::commit(versionNode *vNode)
{
    versionNode *nextVNode = new versionNode;
    nextVNode->commitNumber = (vNode->commitNumber) + 1;
    vNode->next = nextVNode;
    nextVNode->previous = vNode;

    // let's write all of the files to the minigit folder
    // after that, the nextVNode is already doubly-linked so we are done and can move on
    fileNode *curr = vNode->head;
    fileNode *future = nextVNode->head;

    // write all files to ./.minigit/ with a 00 file-version number
    while (curr != NULL)
    {
        updateChangedFile(curr);

        // before moving on, copy the current fileNode to the next temporary Commit
        future = new fileNode();
        future->fileName = curr->fileName;
        future->version = curr->version;
        future->fileVersion = curr->fileVersion;

        curr = curr->next;
        future = future->next;
    }

    //     fileNode *temp = vNode->head;
    //     fileNode *temp3 = new fileNode;
    //     temp3 = temp;
    //     nextVNode->head = temp3;

    //     //copy to new file
    //     while (temp != NULL)
    //     {
    //         fileNode *temp3 = new fileNode;
    //         string abc = (temp->fileName).substr(0, (temp->fileName).length() - 4); //example: f1
    //         //string str = updateChangedFile(temp);
    //         copyFile(vNode, temp, abc + "00.txt"); //first commit will always be version 00
    //         temp3 = temp;
    //         temp3->fileVersion = abc + "00.txt";
    //         temp3 = temp3->next;
    //         temp = temp->next;
    //     }
    //     cout << "Your commit number is: " << vNode->commitNumber << endl;
    //     //increment vNode after copying
    //     vNode = nextVNode;

    //     return;
    // }

    // versionNode *prev = vNode->previous;
    // fileNode *tempPres = vNode->head;
    // fileNode *tempPrev = prev->head;
    // cout << "please" << endl;
    // while (tempPres != NULL && tempPrev != NULL) // looping through each version node
    // {
    //     cout << "hi hoe" << endl;
    //     //getting a string for the beginning of each fileNode to make sure we are comparing the same file
    //     int i = 0;
    //     string s = "";
    //     string s2 = "";
    //     while (tempPres->fileName[i] != '_')
    //     {
    //         s = s + tempPres->fileName[i];
    //         i++;
    //     }
    //     s = s + '_';
    //     while (tempPrev->fileName[i] != '_')
    //     {
    //         s = s + tempPrev->fileName[i];
    //         i++;
    //     }
    //     s2 = s2 + '_';
    //     if (s == s2)
    //     {
    //         if (hasChanged(tempPrev->fileName, tempPres->fileName) == true)
    //         {
    //             cout << "hi hoe" << endl;
    //             string str = updateChangedFile(tempPres);

    //             copyFile(vNode, tempPres, str);
    //             //rename
    //             //thoughts: convert the versionnumber as a digit, increment the number by 1
    //             //then convert it back into a string and update the versionnumber
    //         }
    //     }

    //     tempPrev = tempPrev->next;
    //     tempPres = tempPres->next;
    // }
    // vNode = nextVNode;
}
void Minigit::checkOut(fileNode *file)
{
}