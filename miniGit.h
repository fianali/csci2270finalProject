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
    string fileVersion; //name of file in miniGit folder
    fileNode *next;
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
    bool init();
    void add(versionNode *vNode);
    void remove(versionNode *vNode);
    void commit(versionNode *vNode);
    void checkOut(fileNode *file);
};

#endif