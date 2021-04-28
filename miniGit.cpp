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

/*
    initializes repository
*/
void Minigit::init()
{
    Minigit();
    versionNode *vNode = new versionNode;
    vNode->next = NULL;
    vNode->commitNumber = 0;
}

/*
    adds a file to the repository
*/
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
        fileNode *alreadyExists = vNode->head;
        while (alreadyExists != NULL)
        {
            if (alreadyExists->fileName == filename)
            {
                cout << "File already exists." << endl;
                return;
            }
            alreadyExists = alreadyExists->next;
        }

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
        cout << "File name does not exist. Please try again." << endl;
    }
}

/*
    removes a file that was added
*/
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
            cout << "Deleted " << input << "." << endl;
            return;
        }
        prev = pres;
        pres = pres->next;
    }
    cout << "File not found. Try again." << endl;
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

    if (inFile1.is_open() && inFile2.is_open())
    {
        // loop through each line in file1
        while (getline(inFile1, line1))
        {
            // if there's a line with a matching line number in file2
            if (getline(inFile2, line2))
            {
                // compare the lines
                if (line1 != line2)
                {
                    // lines were different
                    return true;
                }
            }
            // no matching line in file2
            else
            {
                // file1 has more lines than file2
                return true;
            }
        }
        // we are out of lines from file1, if file2 has lines remaining
        if (getline(inFile2, line2))
        {
            // file2 has more lines than file1
            return true;
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
    copies file1 over file2
*/
void copyFile(string file1, string file2)
{
    std::ifstream src(file1, std::ios::binary);
    std::ofstream dst(file2, std::ios::binary);

    dst << src.rdbuf();
    // // read file to copy
    // ifstream inFile;
    // inFile.open(file1);

    // // puts file into destination (file2)
    // ofstream outFile;
    // outFile.open(file2);

    // string line;

    // //copy line for line
    // if (inFile.is_open() && outFile.is_open())
    // {
    //     while (getline(inFile, line))
    //     {
    //         outFile << line << endl;
    //     }
    // }
    // else
    // {
    //     cout << "copy failed" << endl;
    // }

    // inFile.close();
    // outFile.close();
}

/*
    this function updates the version number
*/
bool updateChangedFile(fileNode *file)
{
    bool saveFile = false;

    // if either of the files don't exist yet, don't bother checking for changes
    if (file->fileName != "" && file->fileVersion != "" && hasChanged(file->fileName, ".minigit/" + file->fileVersion))
    {
        file->version++;
        saveFile = true; //file has changed, we want to save it
        cout << "- " << file->fileName << " changed to version " << file->version << endl;
    }

    if (file->version == 0 && file->fileVersion == "")
    {
        saveFile = true;
        cout << "- " << file->fileName << " is a new file" << endl;
    }

    // initialize or update the filename to match the version number
    if (file->fileName != "")
    {
        file->fileVersion = file->fileName + "__(~ ^_^)~" + to_string(file->version);
    }

    if (saveFile)
    {
        // store file into the ./.minigit directory
        copyFile(file->fileName, ".minigit/" + file->fileVersion);
    }
    else
    {
        cout << "- " << file->fileName << " is unchanged @ version " << file->version << endl;
    }

    return saveFile;
}

/*
    this function commits the changes that the user makes to a file
*/
versionNode *Minigit::commit(versionNode *vNode)
{
    versionNode *nextVNode = new versionNode;
    nextVNode->commitNumber = (vNode->commitNumber) + 1;
    nextVNode->next = NULL; // This needs to be here to ensure the new temp commit has a null next addr

    bool saveCommit = false;

    // let's write all of the files to the minigit folder
    // after that, the nextVNode is already doubly-linked so we are done and can move on
    fileNode *curr = vNode->head;

    if (curr != NULL)
    {
        nextVNode->head = new fileNode;
    }
    fileNode *future = nextVNode->head;

    // write all files to ./.minigit/ with a 00 file-version number
    while (curr != NULL)
    {
        if (updateChangedFile(curr))
        {
            saveCommit = true;
        }

        // before moving on, copy the current fileNode to the next temporary Commit
        future->fileName = curr->fileName;
        future->version = curr->version;
        future->fileVersion = curr->fileVersion;

        curr = curr->next;

        if (curr != NULL)
        {
            future->next = new fileNode;
        }
        future = future->next;
    }

    if (saveCommit)
    {
        // doubly-link up the new commit to the old one
        vNode->next = nextVNode;
        nextVNode->previous = vNode;
        cout << "New commit created: " << vNode->commitNumber << endl;

        // return the next working vNode
        return nextVNode;
    }

    cout << "No changes were made." << endl;
    return vNode;
}

// unpacks the files from the current version into the working copy
void unpackFiles(versionNode *vNode)
{
    fileNode *curr = vNode->head;
    while (curr != NULL)
    {
        // overwrite working file with the versioned copy from the ./.minigit dir
        copyFile(".minigit/" + curr->fileVersion, curr->fileName);
        curr = curr->next;
    }
}

/*
    overrides the original file with a previous version
*/
versionNode *Minigit::checkOutCommit(versionNode *vNode)
{
    int desiredCommit;
    cout << "Enter your desired commit number:" << endl;
    cin >> desiredCommit;
    if (cin.fail())
    {
        cout << "Input Error: not a number." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // versionNode *start = vNode;
    // int count = 0;
    // //to get to start of DLL
    // while (start->previous != NULL)
    // {
    //     start = start->previous;
    // }
    // // //now at the start
    // // //count the number of nodes in the DLL
    // versionNode *end = start;
    // while (end->next != NULL)
    // {
    //     end = end->next;
    //     count++;
    // }

    // // desiredCommit exists as a version number
    // if (desiredCommit < 0 || desiredCommit > count)
    // {
    //     cout << "Could not find version number: " << desiredCommit << endl;
    // }
    // else
    // {
    //     for (int i = 0; i < desiredCommit; i++)
    //     {
    //         start = start->next;
    //     }
    //     //start is now where we want to checkout
    //     cout << "Checking out commit version " << desiredCommit << endl;
    //     cout << "Unpacking: " << endl;
    //     unpackFiles(start);
    //     return start;
    // }
    // return vNode;

    // //find the vNode to commit to
    if (desiredCommit > vNode->commitNumber)
    {
        cout << "desired was bigger" << endl;
        versionNode *temp = vNode;
        while (temp != NULL)
        {
            cout << "commit: " << temp->commitNumber << endl;
            if (temp->commitNumber == desiredCommit)
            {
                cout << "unpacking" << endl;
                unpackFiles(temp);
                return temp;
            }
            temp = temp->next;
        }
        cout << "Could not find version number: " << desiredCommit << endl;
    }
    else if (desiredCommit < vNode->commitNumber)
    {
        cout << "desired was smaller" << endl;
        versionNode *temp = vNode;
        while (temp != NULL)
        {
            cout << "commit: " << temp->commitNumber << endl;
            if (temp->commitNumber == desiredCommit)
            {
                cout << "unpacking" << endl;
                unpackFiles(temp);
                return temp;
            }
            temp = temp->previous;
        }
        cout << "Could not find version number: " << desiredCommit << endl;
    }
    else
    {
        cout << "You are already on version " << vNode->commitNumber << " st00pid" << endl;
    }

    return vNode;
}
