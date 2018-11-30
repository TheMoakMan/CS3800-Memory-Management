#ifndef SHELL_H
#define SHELL_H

#include <queue>
#include "MemManager.h"

class Shell
{
  private:
    bool running;
    Folder * rootDir;          //Root Directory
    Folder * currDir;          //Current working directory
    MemManager mem_man;

  public:
    //Constructor creates root directory and sets 
    Shell() {running = true; rootDir = new Folder("/user/local/home/sdrive", nullptr); currDir = rootDir;}
    ~Shell() {delete rootDir;}

    //Accessors
    bool is_active() {return running;}
    Folder * home() {return rootDir;}
    Folder * wd() {return currDir;}
    string getFilepath(Folder * dir);
  
    //Operation
    void exit() {running = false;}
    void selectCommand(queue<string> args);
  
    //File Management
    void pwd();
    void ls();
    void ls_l();
    void cd(string filePath);
    void mkdir(string fName);
    void rmdir(string fName);
    void touch(string fName);
    void rm(string fName);
    void chmod(int perms, string fName);
    void sudoAptInstall(string name);
};

#endif