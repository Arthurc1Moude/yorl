# Yorl Language Installation Guide

## VS Code Extension

### Option 1: Install from VSIX (Local)
```bash
code --install-extension yorl-language-1.0.0.vsix
```

### Option 2: Install from GitHub Release
1. Go to https://github.com/Arthurc1Moude/yorl/releases
2. Download `yorl-language-1.0.0.vsix`
3. Install: `code --install-extension yorl-language-1.0.0.vsix`

## NPM Package (GitHub Packages)

### Install from GitHub Packages

1. Create or update `.npmrc` in your project:
```bash
echo "@arthurc1moude:registry=https://npm.pkg.github.com" >> .npmrc
```

2. Authenticate (if needed):
```bash
npm login --registry=https://npm.pkg.github.com
```

3. Install the package:
```bash
npm install @arthurc1moude/yorl-language
```

### Use in Your Project

```javascript
// Import syntax highlighting
const yorl = require('@arthurc1moude/yorl-language');

// Or use the built-in definitions
const builtins = require('@arthurc1moude/yorl-language/builtin');
```

## Build from Source

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install flex bison gcc make

# macOS
brew install flex bison gcc make
```

### Build
```bash
# Clone repository
git clone https://github.com/Arthurc1Moude/yorl.git
cd yorl

# Build the compiler
make

# Test
./yolex png-example.yorl
```

## Package Information

- **NPM Package**: `@arthurc1moude/yorl-language@1.0.0`
- **Registry**: GitHub Packages (https://npm.pkg.github.com)
- **Repository**: https://github.com/Arthurc1Moude/yorl
- **License**: MIT

## Features

- ✅ Syntax highlighting for `.yorl`, `.yol`, `.ybuiltin` files
- ✅ Language configuration (auto-closing, comments, etc.)
- ✅ Built-in standard library (4 modules)
- ✅ Example files included
- ✅ C compiler (yolex) for production use

## Verify Installation

### VS Code Extension
1. Open VS Code
2. Open a `.yorl` file
3. Check syntax highlighting is active

### NPM Package
```bash
npm list @arthurc1moude/yorl-language
```

### Compiler
```bash
./yolex --version
```

## Uninstall

### VS Code Extension
```bash
code --uninstall-extension yorl-language
```

### NPM Package
```bash
npm uninstall @arthurc1moude/yorl-language
```

## Support

- Issues: https://github.com/Arthurc1Moude/yorl/issues
- Documentation: https://github.com/Arthurc1Moude/yorl#readme

## Package Contents

### VS Code Extension (VSIX)
- Syntax highlighting grammar
- Language configuration
- Example files (`.yorl`, `.yol`)
- Built-in library files (`.ybuiltin`)
- Documentation

### NPM Package
- All extension files
- Source code (`.l`, `.y`, `.c`, `.h`)
- Build system (Makefile)
- Complete documentation
- VSIX package included