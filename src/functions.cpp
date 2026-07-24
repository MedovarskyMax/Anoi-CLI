#include <iostream>
#include <include/functions.h>
#include <include/storage.h>
#include <include/tui.h>
#include <windows.h>
#include <string>
#include <vector>


bool confirmDelete();


void printHelp(){
  std::cout << "\033[1mAnoi\033[0m is a lightweight CLI which lets you";
  std::cout << " \033[32mcreate\033[0m, \033[33medit\033[0m, \033[31mremove\033[0m and \033[96mbrowse\033[0m shortcuts\n\n";

  std::cout << "Usage:  anoi <shortcut>                      Opens the <url> saved under <shortcut> in default browser\n";
  std::cout << "        anoi add <shortcut> <url>            Assigns a <url> to a <shortcut>\033[2m, <shortcut> cannot already be defined\033[0m\n";
  std::cout << "        anoi edit <shortcut> <url>           Updates the <url> assigned to <shortcut>\n";
  std::cout << "        anoi rm <shortcut> \033[2m[-f | --force]\033[0m    Removes <shortcut>\033[2m, using optional force flag skips remove confirmation\033[0m\n";
  std::cout << "        anoi ls \033[2m[-t | --tui]\033[0m                 Lists all saved <shortcut> : <url> combinations\033[2m, optional TUI flag opens the list in a TUI\033[0m\n";
  std::cout << "        anoi \033[2m[-h | --help] [-v | --version]\033[0m  Opens interactive TUI\033[2m, optional help flag shows help & optional version flag display version\033[0m\n";
}


void openAnoiTui(){
  startInteractiveTUI();
}


void listAllShortcuts(){
  for (auto& [shortcut, url] : getShortcutUrlPairs()){
    std::cout << shortcut << ": " << url << "\n";
  }
}


void openURL(std::string shortcut){
  std::string url = getUrl(shortcut);
  ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}


bool removeShortcut(std::string shortcut, bool force){
  if (!force){
    if (confirmDelete()){
      if (removeJson(shortcut)){
        std::cout << "Successfully removed: " << shortcut << "\n";
        return true;
      }
    } else{
      std::cout << "Confirmation Failed\n";
    }
    return false;

  } else {
    if (removeJson(shortcut)){
      std::cout << "Successfully removed: " << shortcut << "\n";
      return true;
    }
    return false;
  }
}


void addShortcut(std::string shortcut, std::string url){
  bool isKeyConflict = false;
  bool invalidShortcutName = false;

  for (const auto& p : getShortcutUrlPairs()){
    if (p.first == shortcut){
      isKeyConflict = true;
      break;
    }
  }

  if (shortcut.find(" ") != std::string::npos){
    invalidShortcutName = true;
  }


  if (isKeyConflict){
    std::cout << "Shortcut conflict, save aborted.\n";
    return;
  }

  if (invalidShortcutName){
    std::cout << "Invalid shortcut name, save aborted.\n";
    return;
  }

  saveJson(shortcut, url);
}


void updateShortcut(std::string shortcut, std::string url){
  if (!removeJson(shortcut)){
    return;
  }

  saveJson(shortcut, url);
}


bool confirmDelete(){
  std::string confirmation;
  std::cout << "Type \"\033[91mdelete\033[0m\" to confirm deletion: \033[91m";
  std::getline(std::cin, confirmation);
  std::cout << "\033[0m";

  if (confirmation == "delete"){
    return true; 
  }

  return false;
}

bool confirmDeleteAll(){
  std::string confirmation;
  std::cout << "Type \"\033[91mdelete all\033[0m\" to confirm deletion: \033[91m";
  std::getline(std::cin, confirmation);
  std::cout << "\033[0m";

  if (confirmation == "delete all"){
    return true;
  }

  return false;
}
