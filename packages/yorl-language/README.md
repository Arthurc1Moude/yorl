# Yorl Language Support for VS Code

[![VS Code Extension](https://img.shields.io/badge/VS%20Code-v1.4.1-00ffff?style=flat&labelColor=0d1117&logo=visualstudiocode)](https://marketplace.visualstudio.com/items?itemName=MoudeAI.yorl-language)
[![GitHub release](https://img.shields.io/github/v/release/Arthurc1Moude/yorl?style=flat&color=ff00ff&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/releases)
[![License](https://img.shields.io/badge/License-Proprietary-00ff00?style=flat&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/blob/main/LICENSE)

**Syntax highlighting and language support for Yorl programming language with built-in compiler!**

## ✨ What's Included

This extension provides complete Yorl language support for VS Code:

### 🎨 Syntax Highlighting
- Classes, functions, imports, exports
- Whiteboard/GUI keywords (canvas, header, content, shape, drawing)
- Properties and configurations
- Colors (#RGB, #RRGGBB)
- Comments with `!`
- Exception marks `/em+N`
- Objects and arrays
- Built-in types and constants

### 🔧 Built-in Tools
- **yolex** (45KB) - Yorl compiler included in extension
- Compile `.yorl` files directly from VS Code
- No separate installation needed

### 📁 File Support
- `.yorl` - Standard Yorl files
- `.yol` - Short form
- `.ybuiltin` - Built-in definitions
- Custom file icons for light/dark themes

## 🚀 Quick Start

### Installation

Install from VS Code Marketplace:
```
ext install MoudeAI.yorl-language
```

Or download from: https://marketplace.visualstudio.com/items?itemName=MoudeAI.yorl-language

### Using yolex (Compiler)

The extension includes the `yolex` compiler. After installation:

```bash
# Compile a Yorl file
yolex myapp.yorl

# Output as JSON
yolex myapp.yorl > output.json
```

### Using ylp (Packager)

For packaging Yorl apps as executables, download `ylp`:

**Linux:**
```bash
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp
```

**Windows:**
Download `ylp-windows-x64.exe` from [releases](https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0)

**Usage:**
```bash
# Package as executable
ylp myapp.yorl -o myapp

# Package for all platforms
ylp myapp.yorl -o myapp -p all

# Package with GUI support
ylp gui-app.yorl -o gui-app --gui
```

## 📖 Language Overview

### Basic Syntax

```yorl
^yorl 1.0.0-2437\

! This is a comment

class -className=myApp -type=application;
  .config
    .config.name -(txt='My Application');
    .config.version -(txt='1.0.0');
  .data
    .data.message -(txt='Hello World!');
    .data.settings -config={debug:true,port:8080};

^END_OF_YORL
```

### GUI Applications

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

## 🎯 Features

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

### Extension Features
- ✅ Syntax highlighting for all Yorl features
- ✅ File icons (light/dark theme support)
- ✅ Language configuration
- ✅ Built-in yolex compiler
- ✅ Command palette integration
- ✅ Auto-activation on .yorl files

## 📦 Available Tools

### yolex (Compiler) - Included in Extension
- **Size**: 45KB
- **Function**: Compiles .yorl to JSON/AST
- **Location**: Bundled with extension
- **Usage**: `yolex file.yorl`

### ylp (Packager) - Download Separately
- **Linux**: 763KB static binary
- **Windows**: 255KB executable
- **Function**: Package Yorl apps as executables
- **Download**: [GitHub Releases](https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0)
- **Usage**: `ylp file.yorl -o output`

### yorl-gui-renderer (GUI Renderer) - Optional
- **Size**: 17KB
- **Function**: Renders whiteboard class to GTK4 windows
- **Download**: [GitHub Releases](https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0)
- **Usage**: Automatically used by ylp with `--gui` flag

## 🔗 Links

- **GitHub Repository**: https://github.com/Arthurc1Moude/yorl
- **Releases**: https://github.com/Arthurc1Moude/yorl/releases/tag/v1.0.0
- **VS Code Marketplace**: https://marketplace.visualstudio.com/items?itemName=MoudeAI.yorl-language
- **Issues**: https://github.com/Arthurc1Moude/yorl/issues

## 📚 Documentation

- [Main README](https://github.com/Arthurc1Moude/yorl/blob/main/README.md)
- [YLP Guide](https://github.com/Arthurc1Moude/yorl/blob/main/YLP-README.md)
- [Packaging Guide](https://github.com/Arthurc1Moude/yorl/blob/main/PACKAGING-GUIDE.md)
- [Release Notes](https://github.com/Arthurc1Moude/yorl/blob/main/RELEASE-NOTES.md)

## 🎨 Syntax Highlighting Examples

The extension provides rich syntax highlighting for:

- **Keywords**: `class`, `import`, `function`, `export`
- **Types**: `application`, `board`, `whiteboard`, `config`, `data`
- **Properties**: `-className`, `-type`, `-size`, `-color`
- **Colors**: `#FFFFFF`, `#FF6600`, `#333`
- **Strings**: `'text'`, `"text"`, `-(txt='text')`
- **Numbers**: `42`, `3.14`, `800`
- **Comments**: `! This is a comment`
- **Exception Marks**: `/em+1`, `/em+2`
- **Objects**: `{key:value, nested:{...}}`
- **Special Syntax**: `@path{...}`, `@url{...}`, `@dep{...}`

## 🛠️ Commands

- **Yorl: Compile Current File** - Compile the active .yorl file

## 📄 License

Proprietary License - Download & Share Only

See [LICENSE](https://github.com/Arthurc1Moude/yorl/blob/main/LICENSE) for details.

## 🤝 Contributing

Issues and feature requests are welcome!

Visit the [issues page](https://github.com/Arthurc1Moude/yorl/issues).

## 👨‍💻 Author

**Arthurc1Moude**

- GitHub: [@Arthurc1Moude](https://github.com/Arthurc1Moude)

---

**Version**: 1.4.1  
**Release Date**: March 22, 2026  
**Built with ❤️ by Arthurc1Moude**
