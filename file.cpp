#include "functions.h"

const string MONTH = " Sept ";


File::File(File &source)
{
  name = source.name;
  permissions = source.permissions;
  logs = source.logs;
}

/*
  Generates log data listed after permissions with the 
  ls -l command. 
*/
string File::generate_logs()
{
  string logs = " 1 evan evan ";
  int tempRand;

  //Add the file size
  tempRand = rand_file_size(this);
  if(tempRand < 1000){
    if(tempRand < 100)
      logs.append("  ");
    else
      logs.append(" ");

    logs.append(to_string(tempRand));
  }
  else
    logs.append(to_string(tempRand));


  //Add date and time information
  logs.append(" ");

  //Declare time variables and read from system.
  time_t tTime;
  struct tm * ti;

  time(&tTime);
  ti = localtime(&tTime);

  //Add time to the string.
  logs.append(asctime(ti));

  //Modify time to fit proper format.
  logs.erase(logs.size() - 9, logs.size()-1);
  
  return logs;
}