# Yorl Packager (ylp)

Package Yorl programs as standalone executables for multiple platforms.

## Installation

Download the ylp binary for your platform from the [releases page](https://github.com/Arthurc1Moude/yorl/releases).

### Linux
```bash
wget https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/ylp-linux-x64
chmod +x ylp-linux-x64
sudo mv ylp-linux-x64 /usr/local/bin/ylp
```

### Windows
Download `ylp-windows-x64.exe` and add to your PATH.

## Usage

### Basic Usage
```bash
ylp myapp.yorl -o myapp
```

### Multi-Platform Build
```bash
ylp myapp.yorl -o myapp -p all
```

This creates:
- `myapp` (Linux)
- `myapp-macos` (macOS)
- `myapp.exe` (Windows, if MinGW is available)

### Platform-Specific Build
```bash
ylp myapp.yorl -o myapp -p linux
ylp myapp.yorl -o myapp -p windows
ylp myapp.yorl -o myapp -p macos
```

## Options

- `-o <output>` - Output executable name (required)
- `-p <platform>` - Target platform: `linux`, `windows`, `macos`, `all`, `current` (default: current)
- `--version` - Show version
- `--help` - Show help

## Example

Create a Yorl application:

```yorl
^yorl 1.0.0-2437\

class -className=myApp -type=application;
  .config
    .config.name -(txt='My App');
    .config.version -(txt='1.0.0');
  .data
    .data.message -(txt='Hello World!');

^END_OF_YORL
```

Package it:

```bash
ylp myapp.yorl -o myapp
```

Run it:

```bash
./myapp
```

## How It Works

1. Compiles `.yorl` source to JSON using `yolex`
2. Embeds the JSON into a platform-specific executable wrapper
3. Creates standalone executables that can run without Yorl installed

## Requirements

- `yolex` compiler must be in PATH
- For Windows cross-compilation: MinGW (`x86_64-w64-mingw32-gcc`)

## Output

The packaged executables contain the compiled Yorl program and can be distributed independently.
