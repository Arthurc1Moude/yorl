# Yorl Programming Language

<p align="center">
  <img src="icon-otm.png" alt="Yorl Logo" width="128" height="128">
</p>

[![GitHub release](https://img.shields.io/github/v/release/Arthurc1Moude/yorl?style=flat&color=ff00ff&labelColor=0d1117&logo=github&logoColor=ff00ff)](https://github.com/Arthurc1Moude/yorl/releases)
[![VS Code Extension](https://img.shields.io/badge/VS%20Code-v1.4.0-00ffff?style=flat&labelColor=0d1117&logo=visualstudiocode)](https://marketplace.visualstudio.com/items?itemName=MoudeAI.yorl-language)
[![License](https://img.shields.io/badge/License-Proprietary-00ff00?style=flat&labelColor=0d1117)](LICENSE)
[![GitHub issues](https://img.shields.io/github/issues/Arthurc1Moude/yorl?style=flat&color=ff0080&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/issues)
[![GitHub stars](https://img.shields.io/github/stars/Arthurc1Moude/yorl?style=flat&color=ffff00&labelColor=0d1117&logo=github&logoColor=ffff00)](https://github.com/Arthurc1Moude/yorl/stargazers)

A modern programming language for configuration, data modeling, and GUI applications with whiteboard support.

## 🚀 Quick Start

### Install ylp (Yorl Packager)
```bash
# Linux
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp

# Windows
# Download ylp-windows-x64.exe and add to PATH
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

### Package and Run
```bash
ylp myapp.yorl -o myapp
./myapp
```

## 📦 Available Tools

### Core Tools
- **yolex** - Yorl compiler (831KB Linux, 284KB Windows)
- **ylp** - Yorl packager (763KB Linux, 255KB Windows)
- **yorl-gui-renderer** - GUI renderer for whiteboard apps (17KB)

### Installation Methods
- **Direct Binary** - Download and run
- **GUI Installer** - GTK4 installer (39KB)
- **Package Managers** - .deb (9KB), .rpm (18KB), AppImage (205KB)
- **SDK** - Full development kit (26KB Linux, 124KB Windows)

### VS Code Extension
[![Install Extension](https://img.shields.io/badge/Install-VS%20Code%20Extension-00ffff?style=flat&logo=visualstudiocode)](https://marketplace.visualstudio.com/items?itemName=MoudeAI.yorl-language)

```bash
code --install-extension MoudeAI.yorl-language
```

## ✨ Features

### Language Features
- ✅ Classes, functions, imports, exports
- ✅ Nested configurations with dot notation
- ✅ Properties, objects, arrays
- ✅ Comments with `!`
- ✅ Exception marks `/em+N` for escaping
- ✅ Built-in stdlib: core, image, data, ai
- ✅ Whiteboard class for GUI applications
- ✅ Color support (#RGB, #RRGGBB)
- ✅ Path references (@path, @url, @dep)

### Packaging Features
- ✅ Standalone executables (no runtime needed)
- ✅ Cross-platform builds (Linux, Windows, macOS)
- ✅ GUI rendering with GTK4/Win32
- ✅ Embedded source code
- ✅ Small output size

## 🎨 GUI Applications

Create GUI apps with the whiteboard class:

```yorl
^yorl 1.0.0-2437\

class -className=board -type=whiteboard;
  .canvas
    .canvas.config -size={width:800,height:600} -background=#FFFFFF;
  .header
    .header.text -(txt='My GUI App');
    .header.style -font={family:'Arial',size:24,weight:bold} -color=#333333;
  .content
    .content.drawing -type=rectangle -position={x:100,y:100} -size={width:200,height:150} -color=#FF6600;
    .content.text -(txt='Hello GUI!') -position={x:120,y:160} -color=#FFFFFF;

^END_OF_YORL
```

Package with GUI:
```bash
ylp board.yorl -o board-app --gui
./board-app
```

## 📖 Language Syntax

### Basic Structure
```yorl
^yorl 1.0.0-2437\

! This is a comment

class -className=myClass -type=application;
  .config
    .config.name -(txt='My App');
    .config.version -(txt='1.0.0');
  .data
    .data.items -list={item1,item2,item3};
    .data.settings -config={debug:true,port:8080};

^END_OF_YORL
```

### Data Types
- **Strings**: `'text'` or `"text"`
- **Numbers**: `42`, `3.14`
- **Colors**: `#FF6600`, `#FFF`
- **Objects**: `{key:value,key2:value2}`
- **Arrays**: `{item1,item2,item3}`
- **Booleans**: `true`, `false`

### Special Syntax
- **Properties**: `-propertyName=value`
- **Text/Image**: `-(txt='text')`, `-(img='path')`
- **Paths**: `@path{/path/to/file}`
- **URLs**: `@url{https://example.com}`
- **Dependencies**: `@dep{depName}`
- **Exception Marks**: `/em+N` (inside objects/arrays only)

## 🔧 Building from Source

### Prerequisites
- flex (lexer generator)
- bison (parser generator)
- gcc (C compiler)
- make

### Build
```bash
make
```

### Build All Platforms
```bash
# Linux
gcc -o yolex-linux-x64 lex.yy.o yorl.tab.o yorl_json.o version.o -static

# Windows (cross-compile)
x86_64-w64-mingw32-gcc -o yolex-windows-x64.exe lex.yy.c yorl.tab.c yorl_json.c version.c
```

## 📥 Installation

### Method 1: Direct Binary (Recommended)
```bash
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp
```

### Method 2: GUI Installer
```bash
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/install-yolex-gui
chmod +x install-yolex-gui
./install-yolex-gui
```

### Method 3: Package Manager
```bash
# Debian/Ubuntu
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yorl-installer_1.0.0.deb
sudo dpkg -i yorl-installer_1.0.0.deb

# Fedora/RHEL
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yorl-installer-1.0.0-1.x86_64.rpm
sudo rpm -i yorl-installer-1.0.0-1.x86_64.rpm

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
cd yorl-sdk && sudo ./install.sh

# Windows
# Download yorl-sdk-1.0.0-windows-x64.zip
# Extract and add bin/ to PATH
```

## 📚 Documentation

- [YLP-README.md](YLP-README.md) - Yorl Packager guide
- [PACKAGING-GUIDE.md](PACKAGING-GUIDE.md) - Complete packaging guide
- [RELEASE-NOTES.md](RELEASE-NOTES.md) - v1.0.0 release notes

## 🔗 Links

- **GitHub**: https://github.com/Arthurc1Moude/yorl
- **Releases**: https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0
- **VS Code Extension**: https://marketplace.visualstudio.com/items?itemName=MoudeAI.yorl-language
- **Issues**: https://github.com/Arthurc1Moude/yorl/issues

## 📊 File Sizes

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

## 🎯 Use Cases

1. **Configuration Files** - Structured config with nested properties
2. **Data Modeling** - Classes and objects for data structures
3. **GUI Applications** - Whiteboard class for visual apps
4. **Prototyping** - Quick app development and testing
5. **Automation** - CLI tools and scripts

## 📄 License

Proprietary License - Download & Share Only

See [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Issues and feature requests are welcome!

See [issues page](https://github.com/Arthurc1Moude/yorl/issues).

## 👨‍💻 Author

**Arthurc1Moude**

- GitHub: [@Arthurc1Moude](https://github.com/Arthurc1Moude)

---

**Version**: 1.0.0-2437  
**Release Date**: March 22, 2026  
**Built with ❤️ by Arthurc1Moude**
