#include <iostream>
#include <string>


const std::string VERSION = "beta";


int main(int argc, char* argv[]){
  if (argc == 1){
    // opens anoi TUI
    return 0;
  }


  if (argc == 2){
    std::string arg_1 = argv[1];

    if (arg_1 == "--help" || arg_1 == "-h"){
      // print help
      return 0;
    } else if (arg_1 == "--version" || arg_1 == "-v"){
      std::cout << VERSION << "\n";
      return 0;
    } else if (arg_1 == "ls"){
      // list all shortcuts & urls
      return 0;
    } else {
      std::string& shortcut = arg_1;
      // query known keys => if found open associated URL, else throw error
      return 0;
    }
  }


  if (argc == 3){
    std::string arg_1 = argv[1];
    std::string arg_2 = argv[2];

    if (arg_1 == "rm"){
      std::string& shortcut = arg_2;
      // query shortcut in keys, if found remove from storage
      return 0;
    } else if (arg_1 == "ls" && arg_2 == "-tui"){
      // open anoi TUI
      return 0;
    }
  }


  if (argc == 4){
    std::string arg_1 = argv[1];
    std::string arg_2 = argv[2];
    std::string arg_3 = argv[3];

    if (arg_1 == "add"){
      std::string& shortcut = arg_2;
      std::string& url = arg_3;

      // if shortcut not in key list => save shortcut & url, else throw
      return 0;
    } else if (arg_1 == "edit"){
      std::string& shortcut = arg_2;
      std::string& url = arg_3;

      // edit (update) value at shortcut to url
      return 0;
    }
  }

  std::string command;

  for (int i = 0; i < argc; i++){
    if (i == argc - 1){
      command += argv[i];
    } else {
      command = command + argv[i] + " ";
    }
  }

  std::cout << "Invalid command: " << command << "\n";
  return 1;
}
