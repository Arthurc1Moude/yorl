# Yorl Programming Language

<p align="center">
  <img src="icon-otm.png" alt="Yorl Logo" width="128" height="128">
</p>

[![GitHub release](https://img.shields.io/github/v/release/Arthurc1Moude/yorl?style=flat&color=ff00ff&labelColor=0d1117&logo=github&logoColor=ff00ff)](https://github.com/Arthurc1Moude/yorl/releases)
[![GitHub package.json version](https://img.shields.io/github/package-json/v/Arthurc1Moude/yorl?style=flat&color=00ffff&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl)
[![License: MIT](https://img.shields.io/badge/License-MIT-00ff00?style=flat&labelColor=0d1117)](https://opensource.org/licenses/MIT)
[![GitHub issues](https://img.shields.io/github/issues/Arthurc1Moude/yorl?style=flat&color=ff0080&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/issues)
[![GitHub stars](https://img.shields.io/github/stars/Arthurc1Moude/yorl?style=flat&color=ffff00&labelColor=0d1117&logo=github&logoColor=ffff00)](https://github.com/Arthurc1Moude/yorl/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/Arthurc1Moude/yorl?style=flat&color=ff6600&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/network)

A simple configuration programming language (.yol/.yorl) for defining classes with nested configurations and exports.

## Table of Contents
- [Overview](#overview)
- [Package](#package)
- [Features](#features)
- [Quick Start](#quick-start)
- [Language Syntax](#language-syntax)
- [Data Types](#data-types)
- [Built-in System](#built-in-system)
- [Examples](#examples)
- [Building and Installation](#building-and-installation)
- [Usage](#usage)
- [File Extensions](#file-extensions)
- [Syntax Highlighting](#syntax-highlighting)
- [Examples](#examples-1)
- [License](#license)

## Overview

Yorl is a configuration programming language designed for defining structured configurations with classes, functions, imports, and exports. It supports nested configurations, built-in types, and a comprehensive standard library.

## Package

### 📦 Language Support Package
[![npm version](https://img.shields.io/badge/npm-v1.0.0-ff00ff?style=flat&logo=npm&logoColor=ff00ff&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/packages)
[![package size](https://img.shields.io/badge/size-27.1KB-00ffff?style=flat&labelColor=0d1117)](https://github.com/Arthurc1Moude/yorl/packages)

**@arthurc1moude/yorl-language** - VS Code extension with syntax highlighting

```bash
npm install @arthurc1moude/yorl-language
# Or install VSIX:
code --install-extension packages/yorl-language/yorl-language-1.0.0.vsix
```

> **Note**: Compiler source code is protected and not published to npm. Build from source in `packages/yorl-compiler/` directory.

## Features

- **Simple Syntax**: Clean, readable syntax with Python-like indentation
- **Built-in Types**: Comprehensive standard library with core, image, data, and AI modules
- **Nested Configurations**: Infinite nesting depth for complex configurations
- **Import/Export**: Import dependencies and export configurations
- **Exception Marks**: Escape special characters in strings with `/em+N` syntax
- **Comments**: Line comments with `!` and exception marks for special characters
- **Two Implementations**: Python (development) and C (production)

## Quick Start

### Installation

```bash
# Clone the repository
git clone <repository-url>
cd Yorl

# Build the C implementation (recommended for production)
make

# Or use the Python implementation
python3 yorl.py --help
```

### Basic Example

```yorl
^yorl 1.0.0-2437\

! Import dependencies
import @path{/path/to/dependency} -as[alias];

! Define a class
class -className=myBoard -type=board -@set.{board}.color=#FFFFFF;
  .header
    .header.config -size=100 -(txt='Welcome!');
  .content
    .content.config -size=50;

! Export configuration
export class.{myBoard} -as[png] -to(dir='@path{/output}');

^END_OF_YORL @type=config.none
```

## Language Syntax

### Comments and Exception Marks
```yorl
! This is a comment
! Use /em+N to escape special characters inside {} objects/arrays
-(txt='Welcome!')  ! Regular string - no escaping needed
-(data={text:'Hello/em+1 World/em+1'})  ! Inside {} - use /em+1 for !
```

### Data Types
- **Numbers**: `50`, `100`, `3.14`
- **Strings**: `'text'` or `"text"` (no `/em+` escaping needed)
- **Colors**: `#FFFFFF`, `#FF0000`
- **Objects**: `{key:value, nested:{key:value}}` (use `/em+` inside `{}` for special characters)
- **URLs**: `@url{https://example.com}`
- **Paths**: `@path{/absolute/path}`
- **Dependencies**: `@dep{dependencyName}`

### Core Constructs

#### Classes
```yorl
class -className=myClass -type=board -@set.{board}.color=#FFFFFF;
  .config
    .config.config -size=100 -(txt='Hello');
```

#### Functions
```yorl
function -name=process -params={input:string,output:string};
  @set.{function}.input='@path{/input}';
  @call.{dependency.method} -method=process -args={mode:'fast'};
```

#### Imports and Exports
```yorl
import @path{/path/to/dep} -as[alias];
export class.{myClass} -as[png] -to(dir='@path{/output}');
```

## Built-in System

Yorl includes a comprehensive standard library:

### Core Module
- **Types**: `position`, `size`, `color`, `transform`, `font`, `padding`, `margin`
- **Functions**: Math, string, color, and transform operations
- **Constants**: `COLOR.*`, `SIZE.*`, `POSITION.*`

### Image Module
- **Functions**: `load`, `save`, `resize`, `crop`, `rotate`, `blur`, `sharpen`
- **Constants**: `FORMAT.PNG`, `QUALITY.HIGH`, `FILTER.BLUR`

### Data Module
- **Types**: `array`, `dict`, `dataframe`, `series`
- **Functions**: Array operations, statistics, data manipulation
- **Constants**: `DTYPE.INT`, `FORMAT.CSV`, `ENCODING.UTF8`

### AI Module
- **Types**: `model`, `tensor`, `dataset`, `training`
- **Functions**: Model loading, training, prediction
- **Constants**: `MODEL.CNN`, `ACTIVATION.RELU`, `OPTIMIZER.ADAM`

## Examples

### Basic Configuration
```yorl
^yorl 1.0.0-2437\

class -className=myBoard -type=board;
  .header
    .header.config -size=100 -(txt='Welcome');
  .content
    .content.config -size=50;

export class.{myBoard} -as[png] -to(dir='@path{/output}');

^END_OF_YORL @type=config.none
```

### Advanced Example
```yorl
^yorl 1.0.0-2437\

import @path{/libs/imagelib} -as[imglib];

class -className=imageProcessor -type=board;
  .input
    .input.config -(path='@path{/input/image.jpg}');
  .processing
    .processing.config -filters=[
      {type:FILTER.BLUR, intensity:3},
      {type:FILTER.SHARPEN, intensity:2}
    ];

function -name=processImage -params={input:string,output:string};
  @call.{imglib.load} -path='@path{/input.jpg}';
  @call.{imglib.resize} -width=800 -height=600;
  @call.{imglib.save} -format=FORMAT.PNG -quality=QUALITY.HIGH;

export class.{imageProcessor} -as[png] -to(dir='@path{/output}');

^END_OF_YORL @type=config.advanced
```

## Building and Installation

### Prerequisites

**Note**: Compiler source code is located in `packages/yorl-compiler/` directory (not published to npm).

```bash
# Ubuntu/Debian
sudo apt-get install flex bison gcc make

# macOS
brew install flex bison

# Build from packages directory
cd packages/yorl-compiler
make
```

### C Implementation (Production)
```bash
# Navigate to compiler package
cd packages/yorl-compiler

# Build yolex
make

# Run
./yolex file.yorl

# Output JSON
./yolex --json file.yorl
```

### Python Implementation (Development)
```bash
python3 yorl.py file.yorl
python3 yorl.py --debug file.yorl  # Debug mode
python3 yorl.py --list-builtins    # List built-in functions
```

## Usage

### Command Line
```bash
# Parse and display AST
./yolex example.yorl

# Output as JSON
./yolex --json example.yorl

# Parse with Python
python3 yorl.py example.yorl
```

### File Extensions
- `.yorl` - Standard Yorl files (recommended)
- `.yol` - Short form (identical syntax)
- `.ybuiltin` - Built-in definition files

### Built-in Functions
Access built-ins without imports:
```yorl
-size=SIZE.LARGE
-color=COLOR.BLUE
-format=FORMAT.PNG
-optimizer=OPTIMIZER.ADAM
```

## Syntax Highlighting

Yorl includes syntax highlighting for:
- VS Code (via `yorl.tmLanguage.json`)
- Sublime Text
- Vim/Neovim
- Atom

## Performance

| Implementation | Speed | Memory | Use Case |
|----------------|-------|--------|----------|
| C (yolex) | 10-20x faster | 12.5x less memory | Production |
| Python | Development | Higher memory | Development |

## Examples Directory

The repository includes:
- `png-example.yorl` - Basic configuration
- `advanced-example.yorl` - Advanced features
- `builtin-example.yorl` - Built-in usage
- `comments-example.yorl` - Comments and exception marks

## License

MIT License - see LICENSE file for details.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new features
4. Submit a pull request

## Support

- Report issues on GitHub
- Check the examples directory
- Review the language specification

---

**Yorl Language** - A modern configuration language for structured data and transformations.