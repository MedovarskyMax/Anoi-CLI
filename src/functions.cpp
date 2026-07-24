#include <iostream>
#include <include/functions.h>
#include <include/storage.h>
#include <windows.h>

void printHelp(){
  std::cout << "\033[1mAnoi\033[0m is a lightweight CLI which lets you";
  std::cout << " \033[32mcreate\033[0m, \033[33medit\033[0m, \033[31mremove\033[0m and \033[96mbrowse\033[0m shortcuts\n\n";

  std::cout << "Usage:  anoi <shortcut>             Opens the <url> saved under <shortcut> in default browser\n";
  std::cout << "        anoi add <shortcut> <url>   Assigns a <url> to a <shortcut>\n";
  std::cout << "        anoi edit <shortcut> <url>  Updates the <url> assigned to <shortcut>\n";
  std::cout << "        anoi rm <shortcut>          Removes <shortcut>\n";
  std::cout << "        anoi ls                     Lists all saved <shortcut> : <url> combinations\n";
  std::cout << "        anoi ls -tui                Opens interactive TUI\n";
  std::cout << "        anoi                        Opens interactive TUI\n";
}


void openAnoiTui(){
  
}


void listAllShortcuts(){

}


void openURL(std::string shortcut){
  std::string url = getUrl(shortcut);
  ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}


void removeShortcut(std::string shortcut){

}


void addShortcut(std::string shortcut, std::string url){
  saveJson(shortcut, url);
}


void updateShortcut(std::string shortcut, std::string url){

}