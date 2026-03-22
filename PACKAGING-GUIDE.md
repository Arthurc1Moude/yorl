# Yorl Packaging Complete Guide

## Overview

Yorl now has complete packaging support across all platforms with the `ylp` (Yorl Packager) tool.

## What's Available

### 1. Yorl Compiler (yolex)
- **Linux**: `yolex-linux-x64`
- **Windows**: `yolex-windows-x64.exe`
- Compiles `.yorl` files to JSON/AST

### 2. Yorl Packager (ylp)
- **Linux**: `ylp-linux-x64` (764KB, static)
- **Windows**: `ylp-windows-x64.exe` (256KB)
- Packages Yorl apps as standalone executables
- **No yolex dependency** - fully standalone
- Supports GUI for whiteboard class

### 3. Installer Tools
- **CLI**: `install-yolex` (19KB)
- **GUI**: `install-yolex-gui` (40KB, GTK4)
- **Packages**:
  - `.deb` (9.9KB) - Debian/Ubuntu
  - `.rpm` (19KB) - Fedora/RHEL
  - `AppImage` (206KB) - Universal Linux

### 4. SDK Packages
- **Linux SDK**: `yorl-sdk-1.0.0-linux-x64.tar.gz`
- **Windows SDK**: `yorl-sdk-1.0.0-windows-x64.zip`
- Includes: compiler, stdlib, docs

## Installation Methods

### Method 1: Direct Binary (Recommended)
```bash
# Download ylp
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp

# Now you can package Yorl apps!
ylp myapp.yorl -o myapp
```

### Method 2: Using Installer
```bash
# GUI installer
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/install-yolex-gui
chmod +x install-yolex-gui
./install-yolex-gui

# Or CLI installer
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/install-yolex
chmod +x install-yolex
./install-yolex
```

### Method 3: Package Manager
```bash
# Debian/Ubuntu
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yorl-installer_1.0.0.deb
sudo dpkg -i yorl-installer_1.0.0.deb
install-yolex-gui

# Fedora/RHEL
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yorl-installer-1.0.0-1.x86_64.rpm
sudo rpm -i yorl-installer-1.0.0-1.x86_64.rpm
install-yolex-gui

# AppImage (Universal)
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yorl-installer-1.0.0-x86_64.AppImage
chmod +x yorl-installer-1.0.0-x86_64.AppImage
./yorl-installer-1.0.0-x86_64.AppImage
```

### Method 4: Full SDK
```bash
# Linux
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yorl-sdk-1.0.0-linux-x64.tar.gz
tar -xzf yorl-sdk-1.0.0-linux-x64.tar.gz
cd yorl-sdk
sudo ./install.sh

# Windows
# Download yorl-sdk-1.0.0-windows-x64.zip
# Extract and add bin/ to PATH
```

## Using ylp

### Basic Application
```yorl
^yorl 1.0.0-2437\

class -className=myApp -type=application;
  .config
    .config.name -(txt='My Application');
    .config.version -(txt='1.0.0');
  .data
    .data.message -(txt='Hello World!');
    .data.status -(txt='running');

^END_OF_YORL
```

Package:
```bash
ylp myapp.yorl -o myapp
./myapp
```

### GUI Application (Whiteboard)
```yorl
^yorl 1.0.0-2437\

class -className=board -type=whiteboard;
  .canvas
    .canvas.config -size={width:800,height:600};
    .canvas.background -color=#FFFFFF;
  .header
    .header.text -(txt='My GUI App');
    .header.style -font={family:'Arial',size:24};
  .content
    .content.shape -type=rectangle -position={x:100,y:100};
    .content.text -(txt='Hello GUI!');

^END_OF_YORL
```

Package with GUI:
```bash
ylp board.yorl -o board-app --gui
./board-app
```

### Multi-Platform Build
```bash
ylp myapp.yorl -o myapp -p all
```

Creates:
- `myapp` (Linux)
- `myapp.exe` (Windows)
- `myapp-macos` (macOS)

## Platform Support Matrix

| Feature | Linux | Windows | macOS |
|---------|-------|---------|-------|
| Compiler (yolex) | ✅ | ✅ | Build from source |
| Packager (ylp) | ✅ | ✅ | ✅ |
| CLI Packaging | ✅ | ✅ | ✅ |
| GUI Packaging | ✅ (GTK4) | ✅ (Win32) | ✅ |
| Installer GUI | ✅ | ❌ | ❌ |
| .deb Package | ✅ | ❌ | ❌ |
| .rpm Package | ✅ | ❌ | ❌ |
| AppImage | ✅ | ❌ | ❌ |
| SDK | ✅ | ✅ | Build from source |

## File Sizes

| Component | Size | Type |
|-----------|------|------|
| ylp-linux-x64 | 764KB | Static binary |
| ylp-windows-x64.exe | 256KB | Executable |
| yolex-linux-x64 | 45KB | Binary |
| yolex-windows-x64.exe | 277KB | Executable |
| install-yolex-gui | 40KB | GTK4 app |
| yorl-installer.deb | 9.9KB | Package |
| yorl-installer.rpm | 19KB | Package |
| yorl-installer.AppImage | 206KB | Portable |

## Key Features

✅ **Standalone ylp** - No yolex required at runtime  
✅ **Cross-platform** - Build for Linux, Windows, macOS  
✅ **GUI support** - Whiteboard class renders to GTK4/Win32  
✅ **Multiple install methods** - Binary, installer, package manager, SDK  
✅ **Small footprint** - Minimal dependencies  
✅ **Embedded source** - Apps contain Yorl code  

## Distribution

All releases available at:
https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0

## Quick Start

```bash
# Install ylp
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp

# Create app
echo '^yorl 1.0.0-2437\
class -className=app -type=application;
  .data -(txt="Hello!");
^END_OF_YORL' > app.yorl

# Package
ylp app.yorl -o myapp

# Run
./myapp
```

Done! 🎉
