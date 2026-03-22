#!/bin/bash
# Yorl Compiler Installation Script

set -e

echo "Installing Yorl Compiler (yolex)..."

# Download the latest release
RELEASE_URL="https://github.com/Arthurc1Moude/yorl/releases/download/v1.0.0/yolex-linux-x64"

# Download to temporary location
TMP_FILE="/tmp/yolex"
echo "Downloading yolex..."
curl -L -o "$TMP_FILE" "$RELEASE_URL"

# Make executable
chmod +x "$TMP_FILE"

# Install to /usr/local/bin (requires sudo)
echo "Installing to /usr/local/bin/yolex (requires sudo)..."
sudo mv "$TMP_FILE" /usr/local/bin/yolex

echo "✓ Installation complete!"
echo "Run 'yolex --help' to get started"
