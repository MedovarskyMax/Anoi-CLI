#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

extern void printHelp();
extern void openAnoiTui();
extern void listAllShortcuts();
extern void openURL(std::string shortcut);
extern bool removeShortcut(std::string shortcut, bool force);
extern void addShortcut(std::string shortcut, std::string url);
extern void updateShortcut(std::string shortcut, std::string url);
extern bool confirmDeleteAll();

#endif