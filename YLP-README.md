# Yorl Packager (ylp)

Package Yorl programs as standalone executables for multiple platforms.

## Installation

Download ylp for your platform:

### Linux
```bash
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp
```

### Windows
Download `ylp-windows-x64.exe` and add to PATH, or rename to `ylp.exe`.

## Usage

### Basic Packaging
```bash
ylp myapp.yorl -o myapp
```

### Multi-Platform
```bash
ylp myapp.yorl -o myapp -p all
```

Creates:
- `myapp` (Linux)
- `myapp.exe` (Windows)
- `myapp-macos` (macOS)

### GUI Applications
```bash
ylp whiteboard.yorl -o gui-app --gui
```

Enables GUI rendering for whiteboard class applications.

## Options

- `-o <output>` - Output name (required)
- `-p <platform>` - Target: `linux`, `windows`, `macos`, `all` (default: linux)
- `-g, --gui` - Enable GUI for whiteboard class
- `--version` - Show version
- `--help` - Show help

## Example

```yorl
^yorl 1.0.0-2437\

class -className=myApp -type=application;
  .config
    .config.name -(txt='My App');
  .data
    .data.message -(txt='Hello World!');

^END_OF_YORL
```

Package:
```bash
ylp myapp.yorl -o myapp
./myapp
```

## Whiteboard GUI Example

```yorl
^yorl 1.0.0-2437\

class -className=board -type=whiteboard;
  .canvas
    .canvas.size -width=800 -height=600;
    .canvas.background -color=#FFFFFF;
  .content
    .content.text -(txt='Hello GUI!');

^END_OF_YORL
```

Package with GUI:
```bash
ylp board.yorl -o board-app --gui
./board-app
```

## How It Works

ylp embeds your Yorl source code into platform-specific executables:
- **Linux/macOS**: Bash script wrapper
- **Windows**: C executable with embedded data
- **GUI mode**: Uses GTK4 (Linux) or Win32 (Windows) for rendering

## Requirements

- No dependencies for basic packaging
- For GUI on Linux: GTK4 (`libgtk-4-dev`)
- For Windows cross-compile: MinGW (`x86_64-w64-mingw32-gcc`)

## Features

- ✅ Standalone - no yolex required at runtime
- ✅ Cross-platform packaging
- ✅ GUI support for whiteboard class
- ✅ Embeds Yorl source in executable
- ✅ Small output size
