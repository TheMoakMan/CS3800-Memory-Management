#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <random>
#include <ctime>
#include <string>
#include "folder.h"
#include "shell.h"

const int LOW_FILE_SIZE_LIM = 50;
const int UP_FILE_SIZE_LIM = 1100;
const int LOW_FOLDER_SIZE_LIM = 1000;
const int UP_FOLDER_SIZE_LIM = 4500;

//File And Folder manipulation
File * makeFile(string name);
File * makeFolder(string name, Folder * parent);
Folder * fCast(File * f);
string perms_convert(int perms);

//Shell interaction
void run_shell();
queue<string> get_input();
bool valid_int_str(string str);

//Extra Functionality
int rand_file_size(File * fl);
int rand_range(int low, int up);

#endif