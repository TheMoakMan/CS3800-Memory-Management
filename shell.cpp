#include "functions.h"

/*
  Takes in a queue containing all command line arguments,
  determines which command is being selected and calls
  the appropriate Shell class member function. 
  If incorrect input is entered, error messages will be displayed. 
*/
void Shell::selectCommand(queue<string> args)
{
  int numArgs = args.size();
  string command = args.front();

  //Check Command and decide on which path to take.
  if(command == "pwd"){
    this->pwd();   
  }
  else if(command == "exit" || command == "quit"){
    this->exit();
  }
  else if(command == "mkdir"){
    numArgs--;
    
    for(int i = 0; i < numArgs; i++){
      args.pop();
      this->mkdir(args.front());
    }
  }
  else if(command == "ls"){
    args.pop();

    if(args.size() > 0){
      if(args.front() == "-l")
        this->ls_l();
    }    
    else  
      this->ls();
  
  }
  else if(command == "rm"){
    numArgs--;
    
    for(int i = 0; i < numArgs; i++){
      args.pop();
      this->rm(args.front());
    }
  }
  else if(command == "rmdir"){
    numArgs--;
    
    for(int i = 0; i < numArgs; i++){
      args.pop();
      this->rmdir(args.front());
    } 
  }
  else if(command == "touch"){
    numArgs--;
    
    for(int i = 0; i < numArgs; i++){
      args.pop();
      this->touch(args.front());
    } 
  }
  else if(command == "cd"){
    if(args.size() > 1){
      args.pop();
      this->cd(args.front());
    }
  }
  else if(command == "chmod"){
    if(args.size() < 3)
      cout << "chmod: missing operand" << endl;
    else{
      args.pop();

      if(valid_int_str(args.front())){
        int perms = stoi(args.front());
        
        if(perms >= 0 && perms <= 777){
          args.pop();
          this->chmod(perms, args.front());
        }
        else
          cout << "chmod: invalid mode: '" << perms << "'" << endl;
      }
    }
  }
  else if(command == "vim"){
    args.pop();
    string vimCommand = "/usr/bin/vim " + args.front();

    system(vimCommand.c_str());
  }
  else if(command == "sudo"){
    args.pop();

    if(args.front() == "apt"){
      args.pop();

      if(args.front() == "install"){
        args.pop();
        this->sudoAptInstall(args.front());
      }
      else
        system("/usr/bin/sudo /usr/bin/apt"); 
    }
  
    else
      system("/usr/bin/sudo");
  }
  else if(command == "make"){
      args.pop();
      if(args.size() > 0){
        if(args.front() == "sandwich" || args.front() == "Sandwich"){
          cout << "\nmake: Target 'sandwich': Not found, " << endl << endl;
          cout << "Try sudo apt install wife" << endl << endl;
        }
        else
          cout << "make: Target '" << args.front() << "': Not found" << endl;
      }  
      else{
        cout << command << ": No targets specified or no makefile found " << endl;
      }
  }
  else{
    cout << "\nCommand '" << command << "' not found, but can be installed with: " << endl << endl;
    cout << "sudo apt install " << command << endl << endl;
    return;
  } 
}

/*~~~Command Functions~~~*/
void Shell::pwd()
{
  cout << getFilepath(currDir) << endl;
}

void Shell::ls()
{
  if(currDir->numFiles() > 0)
    currDir->print();
}

void Shell::ls_l()
{
  currDir->printPerms();
}

void Shell::cd(string fName)
{
  if(fName == ".."){
    //Alters the name of the parent by removing a '/' that is appended
    //for filepath display.

    if(currDir->getParent() != nullptr){
      //Sets the pointer of the current directory to that of the parent.
      Folder * temp = currDir->getParent();
      currDir = temp;

      string origName = currDir->get_name();
      origName.pop_back();

      currDir->set_name(origName);  
    }  
  } 
  else if(currDir->contains(fName)){
    if(currDir->getFile(fName)->is_base()){
      cout << "-bash: cd: " << fName << ": Not a directory" << endl;
    } 
    else{  
      //Appends '/' on to name of current directory for filepath display
      //and updates the currDir pointer.
      Folder * temp = currDir->openFolder(fName);
      
      string altName = currDir->get_name();
      altName.append("/");

      currDir->set_name(altName);

      currDir = temp;  
    } 
  }
  else
    cout << "-bash: cd: " << fName << ": No such file or directory" << endl;
}

void Shell::mkdir(string fName)
{
  if(currDir->contains(fName)){
    cout << "mkdir: cannot create directory '" << fName << "' File exists" << endl;
  }
  else
    currDir->addFile(makeFolder(fName, currDir));
}

void Shell::rmdir(string fName)
{
  if(currDir->contains(fName)){
    if(!(currDir->getFile(fName)->is_base())){
      if(currDir->openFolder(fName)->is_empty())
        currDir->rmFile(fName);
      else
        cout << "rmdir: failed to remove '" << fName << "': Directory not empty" << endl;
    }
    else 
      cout << "rmdir: failed to remove '" << fName << "': Not a directory" << endl;
  } 
  else 
    cout << "rmdir: failed to remove '" << fName << "': No such file or directory" << endl; 
}

void Shell::touch(string fName)
{
  /*
    If a file or directory already exits, just update timestamp.
    If not then create a new file.
  */

  if(currDir->contains(fName)){
    currDir->getFile(fName)->update_logs();
  }
  else 
    currDir->addFile(makeFile(fName));
}

void Shell::rm(string fName)
{
  if(currDir->contains(fName)){  
    if(currDir->getFile(fName)->is_base())
      currDir->rmFile(fName);
    else
      cout << "rm: cannot remove '" << fName << "': Is a directory" << endl;
  }
  else
    cout << "rm: cannot remove '" << fName << "': No such file or directory" << endl;
}
void Shell::chmod(int perms, string fName)
{
  if(currDir->contains(fName)){
    currDir->getFile(fName)->set_permissions(perms);
  }
  else
    cout << "chmod: cannot access '" << fName << "': No such file or directory" << endl;
}

//Recursive function to build a string representing the filepath of a given directory.
string Shell::getFilepath(Folder * dir)
{
  if(dir->getParent() == nullptr)
    return dir->get_name();

  return getFilepath(dir->getParent()) + dir->get_name();
}

//Calls the actual "sudo apt install" command from the system.
//DO NOT RECOMMEND CALLING WITHOUT ADMIN PRIVLEGES.
//This function was written purely for testing the limits of the program.
void Shell::sudoAptInstall(string name)
{
  string path = "/usr/bin/sudo /usr/bin/apt install " + name;
  system(path.c_str());
}



