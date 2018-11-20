#include "functions.h"

Folder::Folder(Folder &source)
{
  name = source.name;
  permissions = source.permissions;
  parentDir = source.parentDir;
  logs = source.logs;
  contents = source.contents;

  is_base_file = false;
}

Folder::~Folder()
{
  //Delete physical file objects that are contained within the folder.
  for(auto it = contents.begin(); it != contents.end(); it++)
  {
    delete it->second;
  }
}

/*
  Adds a file object to the map.
*/
void Folder::addFile(File * source)
{
  contents[source->get_name()] = source;
}

/*
  Removes a file object from the map.
*/
void Folder::rmFile(string fName)
{
  //Deallocate memory that element of key
  //fName points to and remove that element from the map.
  delete contents[fName];
  contents.erase(fName);
}

/*
  Returns a pointer to file matching the given key in the map.
*/
File * Folder::getFile(string fName)
{
  return contents.at(fName);
}

/*
  Returns a pointer to a folder within the map,
  matching a given key.
  Should only be called if it is known that the object is a folder.
*/
Folder * Folder::openFolder(string fName)
{
  return fCast(contents.at(fName));
}

/*
  Returns true of the map contains an element matching the given
  key.
*/
bool Folder::contains(string fName)
{
  auto it = contents.find(fName);

  if(it == contents.end())
    return false;
  else 
    return true;
}

/*
  Prints contents of directory.
*/
void Folder::print()
{
  int numElms = 0;
  for(auto it = contents.begin(); it != contents.end(); it++){
     if(numElms > 8){
       numElms = 0;
       cout << endl;
     }

     cout << it->second->get_name() << " ";
     numElms++;
  }

  cout << endl;
}

/*
  Prints permissions for the ls -l command.
*/
void Folder::printPerms()
{
  for(auto it = contents.begin(); it != contents.end(); it++){
    if(it->second->is_base())
      cout << "-";                //Field for file identifier
    else
      cout << "d";                //Field for directory identifier

    cout.fill('0');
    cout << perms_convert(it->second->get_permissions()) << it->second->get_logs() << " " << it->second->get_name() << endl;
  }
}
