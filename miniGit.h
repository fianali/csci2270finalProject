#ifndef MINIGIT_H
#define MINIGIT_H
#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

struct fileNode
{
    string fileName;    // Name of local file
    int version;        // version number of the file
    string fileVersion; // name of file in miniGit folder
    fileNode *next;     // points to another file, not the next version
};

struct versionNode
{
    int commitNumber;
    fileNode *head;
    versionNode *previous;
    versionNode *next;
};

class Minigit
{
private:
public:
    Minigit();
    void init();
    void add(versionNode *vNode);
    void remove(versionNode *vNode);
    versionNode *commit(versionNode *vNode);
    versionNode *checkOutCommit(versionNode *vNode);
};

#endif