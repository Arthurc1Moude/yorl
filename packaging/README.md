# Yorl Installer Packages

This directory contains packaging configurations for the Yorl Installer GUI application.

## Available Formats

### .deb (Debian/Ubuntu)
```bash
sudo dpkg -i yorl-installer_1.0.0.deb
sudo apt-get install -f  # Install dependencies if needed
```

### .rpm (Fedora/RHEL/openSUSE)
```bash
sudo rpm -i yorl-installer-1.0.0-1.x86_64.rpm
# or
sudo dnf install yorl-installer-1.0.0-1.x86_64.rpm
```

### AppImage (Universal)
```bash
chmod +x yorl-installer-1.0.0-x86_64.AppImage
./yorl-installer-1.0.0-x86_64.AppImage
```

### Snap (Ubuntu/Universal)
```bash
snapcraft
sudo snap install yorl-installer_1.0.0_amd64.snap --dangerous
```

### Flatpak (Universal)
```bash
flatpak-builder build com.yorl.installer.yml
flatpak-builder --user --install build com.yorl.installer.yml
```

## Building from Source

### Prerequisites
- GTK4 development libraries
- g++ compiler
- pkg-config

### Build
```bash
g++ install-yolex.cpp -o install-yolex-gui $(pkg-config --cflags --libs gtk4) -std=c++11
```
