#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "include/storage.h"
#include "include/functions.h"


void enableRawMode();
void restoreMode();
int readKey();
void render(std::vector<std::pair<std::string, std::string>> pairs, int seleceted, bool firstRender);


HANDLE hStdin, hStdout;
DWORD origInMode, origOutMode;

bool firstRender = true;

const int KEY_UP = 1000;
const int KEY_RIGHT = 1001;
const int KEY_DOWN = 1002;
const int KEY_LEFT = 1003;
const int KEY_Q = 1004;
const int KEY_O = 1005;
const int KEY_A = 1006;
const int KEY_E = 1007;
const int KEY_R = 1008;
const int KEY_D = 1009;

void startInteractiveTUI(){   // MAIN
  bool restart = true;
  while (restart){
    restart = false;
    bool running = true;
    enableRawMode();

    int selected = 0;

    if (firstRender){
      std::cout << "-----------------------------------------------------------------------------------------\n";
      render(getShortcutUrlPairs(), selected, firstRender);
      firstRender = false;
    }

    std::vector<std::pair<std::string, std::string>> pairs;

    while (running){
      int c = readKey();
      pairs = getShortcutUrlPairs();
      int pairsNum = (int) pairs.size();

      if (c == KEY_Q){ break; }

      switch (c){
        case KEY_UP: {
          selected = (selected - 1 + pairsNum) % pairsNum;
          render(pairs, selected, firstRender);
          break;
        };

        case KEY_DOWN: {
          selected = (selected + 1) % pairsNum;
          render(pairs, selected, firstRender);
          break;
        };

        case KEY_O: {
          openURL(pairs[selected].first);
          break;
        };

        case KEY_A: {
          running = false;
          restoreMode();

          std::cout << "Shortcut: ";
          std::string shortcut;
          std::getline(std::cin, shortcut); 

          std::cout << "Url: ";
          std::string url;
          std::getline(std::cin, url);

          addShortcut(shortcut, url);

          firstRender = true;
          restart = true;
          break;
        };

        case KEY_E: {
          running = false;
          restoreMode();

          std::string shortcut = pairs[selected].first;

          std::cout << "Url: ";
          std::string url;
          std::getline(std::cin, url);

          updateShortcut(shortcut, url);

          firstRender = true;
          restart = true;
          break;
        };

        case KEY_R: {
          running = false;
          restoreMode();

          std::string shortcut = pairs[selected].first;

          bool removed = removeShortcut(shortcut, false);

          if (pairs.size() != 1 || !removed){
            firstRender = true;
            restart = true;
          }
          break;
        };

        case KEY_D: {
          running = false;
          restoreMode();

          if (confirmDeleteAll()){
            for (const auto& [shortcut, url] : pairs){
              removeShortcut(shortcut, true);
            }
            break;
          } else {
            std::cout << "Confirmation Failed\n";
            firstRender = true;
            restart = true;
            break;
          }        
        }
      }
    }

    restoreMode();
  }
}


void enableRawMode() {
  hStdin  = GetStdHandle(STD_INPUT_HANDLE);
  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

  GetConsoleMode(hStdin, &origInMode);
  GetConsoleMode(hStdout, &origOutMode);

  // Disable line buffering and echo -> get keys immediately, one at a time
  DWORD rawIn = origInMode;
  rawIn &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
  SetConsoleMode(hStdin, rawIn);

  // Enable ANSI escape sequence support for output (cursor moves, clearing)
  DWORD rawOut = origOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hStdout, rawOut);

  std::cout << "\x1b[?25l";
}


void restoreMode() {
  SetConsoleMode(hStdin, origInMode);
  SetConsoleMode(hStdout, origOutMode);
  std::cout << "\x1b[?25h";
}


int readKey(){
  INPUT_RECORD rec;
  DWORD read;
  
  while (true){
    ReadConsoleInputA(hStdin, &rec, 1, &read);
    if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown){
      WORD vk = rec.Event.KeyEvent.wVirtualKeyCode;
      char key_ascii = rec.Event.KeyEvent.uChar.AsciiChar;

      if (vk == VK_UP) return KEY_UP;
      if (vk == VK_RIGHT) return KEY_RIGHT;
      if (vk == VK_DOWN) return KEY_DOWN;
      if (vk == VK_LEFT) return KEY_LEFT;

      if (key_ascii == 'q') return KEY_Q;
      if (key_ascii == 'o') return KEY_O;
      if (key_ascii == 'a') return KEY_A;
      if (key_ascii == 'e') return KEY_E;
      if (key_ascii == 'r') return KEY_R;
      if (key_ascii == 'd') return KEY_D;
    }
  }
}


void render(std::vector<std::pair<std::string, std::string>> pairs, int selected, bool firstRender){
  if (!firstRender){
    std::cout << "\x1b[" << pairs.size() + 2 << "A";
  }

  for (size_t i = 0; i < pairs.size(); i++){
    std::cout << "\x1b[2K";

    std::string prefix = ((int) i == selected) ? "\033[1m> " : "  ";

    std::cout << prefix << pairs[i].first << ": " << pairs[i].second << "\033[0m\n";
  }

  std::cout << "-----------------------------------------------------------------------------------------\n";
  std::cout << "\033[96m[o] to Open\033[0m | \033[92m[a] to Add\033[0m | \033[33m[e] to Edit\033[0m | \033[91m[r] to Remove\033[0m | \033[31m[d] to Remove All\033[0m | [q] to Exit\n";
  std::cout.flush();
}