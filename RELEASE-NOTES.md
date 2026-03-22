# Yorl v1.0.0 - Final Release

## 🎉 Complete Release Package

### Core Tools

#### 1. Yorl Compiler (yolex)
- **yolex-linux-x64** (831KB) - Linux x64 static binary
- **yolex-windows-x64.exe** (284KB) - Windows x64 executable
- Compiles `.yorl` files to JSON/AST
- Full language support with comments, exception marks, built-in stdlib

#### 2. Yorl Packager (ylp)
- **ylp-linux-x64** (763KB) - Linux x64 static binary
- **ylp-windows-x64.exe** (255KB) - Windows x64 executable
- Package Yorl apps as standalone executables
- Cross-platform: Linux, Windows, macOS
- GUI support with `--gui` flag
- No dependencies - fully standalone

#### 3. GUI Renderer
- **yorl-gui-renderer-linux-x64** (17KB) - GTK4 renderer
- Renders whiteboard class to real GUI windows
- Displays graphics, text, colors from Yorl code
- 800x600 canvas with full drawing support

### Installation Tools

#### CLI Installer
- **install-yolex** (18KB) - Bash script installer
- Downloads and installs yolex to ~/.local/bin
- Simple one-command installation

#### GUI Installer
- **install-yolex-gui** (39KB) - GTK4 GUI installer
- Progress bar and status updates
- Error/success dialogs
- User-friendly installation experience

### Package Formats

#### Debian/Ubuntu
- **yorl-installer_1.0.0.deb** (9KB)
- Install: `sudo dpkg -i yorl-installer_1.0.0.deb`

#### Fedora/RHEL/openSUSE
- **yorl-installer-1.0.0-1.x86_64.rpm** (18KB)
- Install: `sudo rpm -i yorl-installer-1.0.0-1.x86_64.rpm`

#### Universal Linux
- **yorl-installer-1.0.0-x86_64.AppImage** (205KB)
- Run: `chmod +x *.AppImage && ./yorl-installer-1.0.0-x86_64.AppImage`

### SDK Packages

#### Linux SDK
- **yorl-sdk-1.0.0-linux-x64.tar.gz** (26KB)
- Complete development kit
- Includes: compiler, stdlib, docs, installer

#### Windows SDK
- **yorl-sdk-1.0.0-windows-x64.zip** (124KB)
- Complete development kit
- Includes: compiler, stdlib, docs, README

## 📦 What's Included

### Language Features
- ✅ Yorl syntax with `^yorl` header
- ✅ Classes, functions, imports
- ✅ Properties, objects, arrays
- ✅ Comments with `!`
- ✅ Exception marks `/em+N` for escaping
- ✅ Built-in stdlib: core, image, data, ai
- ✅ Whiteboard class for GUI apps

### Packaging Features
- ✅ Standalone executables
- ✅ Cross-platform builds
- ✅ GUI rendering support
- ✅ Embedded source code
- ✅ No runtime dependencies

### Distribution Methods
- ✅ Direct binary download
- ✅ Package managers (.deb, .rpm)
- ✅ AppImage (portable)
- ✅ GUI/CLI installers
- ✅ Full SDK packages

## 🚀 Quick Start

### Install ylp (Recommended)
```bash
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp
```

### Create Your First App
```yorl
^yorl 1.0.0-2437\

class -className=myApp -type=application;
  .config
    .config.name -(txt='My First Yorl App');
  .data
    .data.message -(txt='Hello World!');

^END_OF_YORL
```

### Package It
```bash
ylp myapp.yorl -o myapp
./myapp
```

### Create GUI App
```yorl
^yorl 1.0.0-2437\

class -className=board -type=whiteboard;
  .canvas
    .canvas.config -size={width:800,height:600};
  .header
    .header.text -(txt='My GUI App');
  .content
    .content.shape -type=rectangle -position={x:100,y:100};

^END_OF_YORL
```

### Package with GUI
```bash
ylp board.yorl -o board-app --gui
./board-app
```

## 📊 File Sizes Summary

| Component | Size | Platform |
|-----------|------|----------|
| yolex-linux-x64 | 831KB | Linux |
| yolex-windows-x64.exe | 284KB | Windows |
| ylp-linux-x64 | 763KB | Linux |
| ylp-windows-x64.exe | 255KB | Windows |
| yorl-gui-renderer | 17KB | Linux |
| install-yolex-gui | 39KB | Linux |
| yorl-installer.deb | 9KB | Debian/Ubuntu |
| yorl-installer.rpm | 18KB | Fedora/RHEL |
| yorl-installer.AppImage | 205KB | Universal Linux |

## 🔗 Download

All releases available at:
**https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0**

## 📚 Documentation

- **YLP-README.md** - Yorl Packager guide
- **PACKAGING-GUIDE.md** - Complete packaging guide
- **README.md** - Main documentation

## ✨ Highlights

- **Standalone ylp** - No yolex dependency needed
- **Real GUI rendering** - GTK4 windows for whiteboard class
- **Cross-platform** - Build for Linux, Windows, macOS
- **Multiple install methods** - Choose what works for you
- **Small footprint** - Minimal dependencies
- **Production ready** - Stable v1.0.0 release

## 🎯 Use Cases

1. **CLI Applications** - Data processing, automation
2. **GUI Applications** - Whiteboard, drawing apps
3. **Configuration** - Structured config files
4. **Data Modeling** - Classes and objects
5. **Prototyping** - Quick app development

---

**Built with ❤️ by Arthurc1Moude**

Version: 1.0.0-2437  
Release Date: March 22, 2026  
License: Proprietary (Download & Share Only)
