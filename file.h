#ifndef FILE_H
#define FILE_H

using namespace std;

class File{
  protected:
    string name;
    int permissions;
    bool is_base_file = true;    //Flag to check if a given file is base file or a folder.
    string logs;

  public:
    File() {}
    File(string nName) : name(nName), permissions(777) {logs = generate_logs();}
    File(File &source);

    //Accessors
    string get_name() {return name;}
    int get_permissions() {return permissions;}
    bool is_base() {return is_base_file;}
    string get_logs() {return logs;}

    //Mutators
    void set_name(string & nName) {name = nName;}
    void set_permissions(int & perms) {permissions = perms;}
    void update_logs() {logs = generate_logs();}
    string generate_logs();

};

#endif