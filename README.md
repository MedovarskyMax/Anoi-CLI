# Anoi - v1.0.0

A lightweight Windows CLI for saving, browsing, and opening URL shortcuts — with an optional interactive TUI.

## Features

- Save a shortcut name mapped to a URL and open it instantly from the terminal
- Add, edit, and remove shortcuts
- List all saved shortcuts
- Interactive TUI for browsing and managing shortcuts with arrow keys
- Confirmation prompts before destructive actions (remove / remove all)
## Installation
### Dev:
```
git clone https://github.com/MedovarskyMax/Anoi-CLI.git
cd Anoi-CLI
g++ -o build/anoi.exe -I. src/main.cpp src/functions.cpp src/storage.cpp src/tui.cpp
```

> Requires Windows (uses the Windows Console API and `ShellExecuteA`).

---

### Binary:

1. Download the latest .exe file from the [latest release](https://github.com/MedovarskyMax/Anoi-CLI/releases/latest)
2. Move it to a folder and add that folder to your PATH
3. Open a **new Terminal** and run `anoi --version` to see if anoi has been successfully installed 

## Usage

```
anoi                                  Opens interactive TUI
anoi <shortcut>                       Opens the URL saved under <shortcut> in your default browser
anoi add <shortcut> <url>             Saves a new <shortcut> → <url>
anoi edit <shortcut> <url>            Updates the URL assigned to <shortcut>
anoi rm <shortcut> [-f | --force]     Removes <shortcut> (--force skips confirmation)
anoi ls [-t | --tui]                  Lists all shortcuts (--tui opens the list in the TUI)
anoi [-h | --help] [-v | --version]   Shows help / displays version
```

### Examples

```
anoi add gh https://github.com
anoi gh              # opens github.com in your browser
anoi edit gh https://github.com/explore
anoi rm gh
```

## TUI Controls

| Key | Action |
|-----|--------|
| ↑ / ↓ | Move selection |
| o | Open selected shortcut |
| a | Add a new shortcut |
| e | Edit selected shortcut |
| r | Remove selected shortcut |
| d | Remove all shortcuts |
| q | Quit |

## Storage

Shortcuts are stored as JSON in `%APPDATA%\anoi\config.json`.

Example:
```
{
  "gh": "https://www.github.com",
  "shortcut_1": "url_1"
}
```

## Status

Version 1.0.0

Contributions and issue reports welcome.

## License

MIT

## Trivia
Anoi - from the greek `anoígō` meaning `to open`