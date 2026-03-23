# Contributing to Yorl-DBOL

Thank you for your interest in contributing to the Yorl Database of Official Libraries!

## 🎯 Contribution Guidelines

### What Can You Contribute?

1. **New Built-in Libraries** - Add functionality to Yorl
2. **Bug Fixes** - Fix issues in existing libraries
3. **Documentation** - Improve docs and examples
4. **Examples** - Add usage examples
5. **Tests** - Add validation tests

## 📝 Submission Process

### 1. Fork the Repository

```bash
git clone https://github.com/Arthurc1Moude/yorl.git
cd yorl
```

### 2. Create Your Built-in

```bash
# Copy the template
cp yorl-dbol/templates/builtin-template.ybuiltin yorl-dbol/usrsr/mylib.ybuiltin

# Edit your library
nano yorl-dbol/usrsr/mylib.ybuiltin
```

### 3. Follow the Specification

Your `.ybuiltin` file must:
- Start with `^yorl-builtin 1.0.0-2437\`
- Include metadata section
- Define types, functions, and constants
- Include documentation comments
- End with `^END_OF_BUILTIN`

### 4. Test Your Library

```bash
# Validate syntax
yolex --validate yorl-dbol/usrsr/mylib.ybuiltin

# Test with a sample Yorl file
yolex test-mylib.yorl
```

### 5. Document Your Library

Create a README in your library directory:
```bash
echo "# My Library" > yorl-dbol/usrsr/mylib.md
```

Include:
- Description
- Installation
- Usage examples
- API reference
- License

### 6. Submit Pull Request

```bash
git add yorl-dbol/usrsr/mylib.ybuiltin
git commit -m "Add mylib built-in library"
git push origin main
```

Then create a Pull Request on GitHub.

## ✅ Review Criteria

Your submission will be reviewed for:

### Code Quality
- [ ] Follows `.ybuiltin` specification
- [ ] Proper syntax and formatting
- [ ] No syntax errors
- [ ] Consistent naming conventions

### Documentation
- [ ] Includes metadata section
- [ ] Functions have descriptions
- [ ] Constants are documented
- [ ] Usage examples provided

### Functionality
- [ ] Library serves a clear purpose
- [ ] No duplicate functionality
- [ ] Functions are well-designed
- [ ] Constants are meaningful

### Testing
- [ ] Library validates with yolex
- [ ] Example usage works
- [ ] No conflicts with existing libraries

## 📋 Naming Conventions

### Library Names
- Use lowercase
- Use hyphens for multi-word names
- Be descriptive: `web-server.ybuiltin`, not `ws.ybuiltin`
- Avoid conflicts with official libraries

### Function Names
- Use camelCase: `myFunction`
- Be descriptive: `parseJSON`, not `pj`
- Use verbs: `getData`, `setConfig`

### Constant Names
- Use UPPER_CASE: `MY_CONSTANT`
- Use namespaces: `HTTP.OK`, `COLOR.RED`
- Be descriptive: `MAX_CONNECTIONS`, not `MC`

### Type Names
- Use PascalCase: `MyType`
- Be descriptive: `HttpRequest`, not `Req`

## 🚫 What Not to Submit

- Malicious code
- Copyrighted content without permission
- Duplicate functionality
- Poorly documented libraries
- Libraries with security vulnerabilities
- Libraries that violate the license

## 📦 Library Structure

### Minimal Example
```yorl
^yorl-builtin 1.0.0-2437\

@metadata{
  name: "mylib",
  version: "1.0.0",
  author: "Your Name",
  description: "My library description",
  license: "MIT"
}

@function{
  name: "myFunction",
  params: {input:string},
  returns: "string",
  description: "Does something useful"
}

@constant{
  name: "MY_CONST",
  value: 42,
  type: "int"
}

^END_OF_BUILTIN
```

### Complete Example
See [templates/builtin-template.ybuiltin](../templates/builtin-template.ybuiltin)

## 🔄 Update Process

### Updating Your Library

1. Make changes to your library
2. Update version number in metadata
3. Update documentation
4. Test changes
5. Submit new PR

### Versioning
Follow Semantic Versioning:
- `1.0.0` - Initial release
- `1.0.1` - Bug fixes
- `1.1.0` - New features
- `2.0.0` - Breaking changes

## 🏷️ Categories

Tag your library with appropriate categories:

- `web` - Web development
- `database` - Database operations
- `crypto` - Cryptography
- `network` - Networking
- `file` - File operations
- `graphics` - Graphics/UI
- `audio` - Audio processing
- `video` - Video processing
- `ml` - Machine learning
- `iot` - IoT/Hardware
- `testing` - Testing utilities
- `logging` - Logging/Monitoring
- `auth` - Authentication
- `cloud` - Cloud services

## 📧 Contact

- **Issues**: https://github.com/Arthurc1Moude/yorl/issues
- **Discussions**: https://github.com/Arthurc1Moude/yorl/discussions
- **Email**: arthurc1moude@example.com

## 🙏 Thank You!

Your contributions help make Yorl better for everyone!

---

**Happy Contributing!** 🎉
