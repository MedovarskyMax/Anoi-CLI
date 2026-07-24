#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

extern void saveJson(std::string shortcut, std::string url);
extern void removeJson(std::string shortcut);
extern std::string getUrl(std::string shortcut);
extern std::vector<std::pair<std::string, std::string>> getShortcutUrlPairs();

#endif