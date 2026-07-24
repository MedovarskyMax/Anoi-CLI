#include "include/json.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include "include/storage.h"

using json = nlohmann::json;

std::string getAppDataPath();
std::string getConfigPath();
json loadJson();
void writeJson(const json& data);
void saveJson(std::string shortcut, std::string url);
void removeJson(std::string shortcut);
std::string getUrl(std::string shortcut);

std::string getAppDataPath(){
  const char* appData = std::getenv("APPDATA");

  if (!appData){
    throw std::runtime_error("APPDATA environment variable not found");
  }

  return std::string(appData);
}


std::string getConfigPath(){
  std::string path = getAppDataPath() + "\\anoi";
  std::filesystem::create_directories(path);
  return path + "\\config.json";
}


json loadJson(){
  std::string filePath = getConfigPath();
  std::ifstream inFile(filePath);

  if (!inFile){
    return json::object();
  }

  json data;

  try{
    inFile >> data;
  } catch (const json::parse_error& e){
    std::cerr << "Failed to parse JSON, starting fresh: " << e.what() << "\n";
    return json::object();
  }

  return data;
}


void writeJson(const json& data){
  std::string filePath = getConfigPath();
  std::ofstream outFile(filePath);

  if (!outFile){
    throw std::runtime_error("Failed to open file for writing: " + filePath);
  }

  outFile << data.dump(4);
}


void saveJson(std::string shortcut, std::string url){
  json data = loadJson();
  data[shortcut] = url;
  writeJson(data);
}


void removeJson(std::string shortcut){
  json data = loadJson();

  if (!data.contains(shortcut)){
    std::cout << "Shortcut \"" << shortcut << "\" not found, nothing to remove.\n";
    return;
  }

  data.erase(shortcut);
  writeJson(data);
}


std::string getUrl(std::string shortcut){
  json data = loadJson();
  std::string url = data.value(shortcut, "");

  if (url.empty()){
    throw std::runtime_error("getUrl Error - no such url or shortcut");
  }

  return url;
}


std::vector<std::pair<std::string, std::string>> getShortcutUrlPairs(){
  json data = loadJson();
  std::vector<std::pair<std::string, std::string>> output;

  for (auto& [key, value] : data.items()){
    output.emplace_back(key, value.get<std::string>());
  }

  return output;
}