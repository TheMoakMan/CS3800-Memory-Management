#include "functions.h"

/*~~~File interactions~~~*/

/*
  Dynamically allocates a new File object and returns a pointer
  to to that object.
*/
File * makeFile(string name)
{
  File * f1 = new File(name);
  return f1;
}

/*
  Dynamically allocates a new Folder object and returns a pointer
  to to that object.
*/
File * makeFolder(string name, Folder * parent)
{
  Folder * f1 = new Folder(name, parent);
  return f1;
}

/*
  Casts a pointer to a file object to that of a folder object.
  Should only be called if File object is actually a Folder.
*/
Folder * fCast(File * f)
{
  return static_cast<Folder *>(f);
}

/*
  Converts a valid 3 digit integer into an int string, 
  interprets each digit and builds a new string to represent
  file permissions. 
*/
string perms_convert(int perms)
{
  string bcd = to_string(perms);
  string converted;
  
  for(int i = 0; i < 3; i++){
    if(bcd[i] == '0'){
      converted.append("---");
    }
    else if(bcd[i] == '1'){
      converted.append("--x");
    }
    else if(bcd[i] == '2'){
      converted.append("-w-"); 
    }
    else if(bcd[i] == '3'){
      converted.append("-wx");
    }
    else if(bcd[i] == '4'){
      converted.append("r--");
    }
    else if(bcd[i] == '5'){
      converted.append("r-x");
    }
    else if(bcd[i] == '6'){
      converted.append("rw-");
    }
    else if(bcd[i] == '7'){
      converted.append("rwx");
    }  
  }

  return converted;
}

/*~~~Shell Environment~~~*/
void run_shell()
{
  Shell bash;

  while(bash.is_active()){
    //Wait for user input.
    cout << "ebmy83@Desktop:" << bash.getFilepath(bash.wd()) << "$ ";

    bash.selectCommand(get_input());
  }
}

/*
  Reads input from the user via getline and uses string streams to break
  that input up into substrings with whitespace as a delimiting character.
  Substrings are pushed into a queue data type to be interpreted later.
*/
queue<string> get_input()
{
  queue<string> argQueue;
  string arguments;
  
  getline(cin, arguments, '\n');

  string arg;
  istringstream argStream(arguments);
  while(getline(argStream, arg, ' ')){
    if(arg != "")
      argQueue.push(arg);
  }

   return argQueue;
}

/*
  Checks to see if a given string can represent a 3 digit integer.
*/
bool valid_int_str(string str)
{
  bool is_valid = true;

  if(str.size() != 3)
    is_valid = false;
  else
    for(int i = 0; i < 3; i++){
      if(!(str[i] >= '0' && str[i] <= '9'))
        is_valid = false; 
    }

  return is_valid;
}

/*~~~Extra Functions~~~*/

/*
  Generates a random integer to represent the filesize of a given file
  based on type. Folders and regular files have different ranges.
  Filesize represented in bytes.
  Random numbers are generated via funcitons in the <random> library
*/
int rand_file_size(File * fl)
{
  random_device randDev;
  mt19937 generator(randDev()); 
  
  if(fl->is_base()){
    uniform_int_distribution<int> range(LOW_FILE_SIZE_LIM, UP_FILE_SIZE_LIM);
    return range(generator);
  }
  else{
    uniform_int_distribution<int> range(LOW_FOLDER_SIZE_LIM, UP_FOLDER_SIZE_LIM);
    return range(generator);
  }
}

/*
  Generates a random integer within a ceratin range.
  Random numbers are generated via funcitons in the <random> library
*/
int rand_range(int low, int up)
{
  random_device randDev;
  mt19937 generator(randDev()); 
  
  uniform_int_distribution<int> range(low, up);
  
  return range(generator);
}
