# Publishing Guide for Yorl Language

## VS Code Extension (VSIX)

The VSIX package has been created: `yorl-language-1.0.0.vsix`

### Install Locally
```bash
code --install-extension yorl-language-1.0.0.vsix
```

### Publish to VS Code Marketplace
1. Create a publisher account at https://marketplace.visualstudio.com/manage
2. Get a Personal Access Token from Azure DevOps
3. Publish:
```bash
vsce publish
```

## NPM Package (GitHub Packages)

### Setup GitHub Token

1. Go to GitHub Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Generate new token with these scopes:
   - `write:packages`
   - `read:packages`
   - `delete:packages` (optional)
3. Copy the token

### Set Token in Environment
```bash
export GITHUB_TOKEN=your_token_here
```

Or add to your `~/.bashrc` or `~/.zshrc`:
```bash
echo 'export GITHUB_TOKEN=your_token_here' >> ~/.bashrc
source ~/.bashrc
```

### Publish to GitHub Packages

```bash
# Login to GitHub Packages
npm login --registry=https://npm.pkg.github.com

# Publish
npm publish
```

### Install from GitHub Packages

Users can install your package with:

```bash
# Add .npmrc to their project
echo "@arthurc1moude:registry=https://npm.pkg.github.com" >> .npmrc

# Install
npm install @arthurc1moude/yorl-language
```

## Files Included

### VSIX Package
- `yorl.tmLanguage.json` - Syntax highlighting
- `language-configuration.json` - Language configuration
- `package.json` - Extension metadata
- `README.md` - Documentation
- Example files (`.yorl`, `.yol`)
- Built-in files (`.ybuiltin`)

### NPM Package
- All VSIX files plus:
- Source files for reference
- Build system (Makefile)
- Complete documentation

## Version Bumping

To release a new version:

```bash
# Bump version
npm version patch  # 1.0.0 -> 1.0.1
npm version minor  # 1.0.0 -> 1.1.0
npm version major  # 1.0.0 -> 2.0.0

# Rebuild VSIX
vsce package

# Commit and push
git add -A
git commit -m "Release v1.0.1"
git push origin main
git push origin --tags

# Publish
npm publish
vsce publish
```

## Current Status

✅ VSIX package created: `yorl-language-1.0.0.vsix`
✅ Package.json configured for GitHub Packages
✅ .npmrc configured for GitHub registry
✅ .vscodeignore and .npmignore configured
✅ LICENSE file added (MIT)
✅ All files committed and pushed to GitHub

⏳ Pending: GitHub token setup and npm publish

## Quick Publish Commands

Once you have your GitHub token set:

```bash
# Publish to GitHub Packages
npm publish

# Or publish to both
npm publish && vsce publish
```