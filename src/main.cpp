#include <iostream>
#include <string>
#include "include/functions.h"


const std::string VERSION = "beta";


int main(int argc, char* argv[]){
  if (argc == 1){
    openAnoiTui();
    return 0;
  }


  if (argc == 2){
    std::string arg_1 = argv[1];

    if (arg_1 == "--help" || arg_1 == "-h"){
      printHelp();
      return 0;
    } else if (arg_1 == "--version" || arg_1 == "-v"){
      std::cout << VERSION << "\n";
      return 0;
    } else if (arg_1 == "ls"){
      listAllShortcuts();
      return 0;
    } else {
      std::string& shortcut = arg_1;
      openURL(shortcut);
      return 0;
    }
  }


  if (argc == 3){
    std::string arg_1 = argv[1];
    std::string arg_2 = argv[2];

    if (arg_1 == "rm"){
      std::string& shortcut = arg_2;
      removeShortcut(shortcut, false);
      return 0;
    } else if (arg_1 == "ls" && (arg_2 == "-t" || arg_2 == "--tui")){
      openAnoiTui();
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

      addShortcut(shortcut, url);
      return 0;
    } else if (arg_1 == "edit"){
      std::string& shortcut = arg_2;
      std::string& url = arg_3;

      updateShortcut(shortcut, url);
      return 0;
    } else if (arg_1 == "rm" && (arg_3 == "-f" || arg_3 == "--force")){
      std::string& shortcut = arg_2;
      removeShortcut(shortcut, true);
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
