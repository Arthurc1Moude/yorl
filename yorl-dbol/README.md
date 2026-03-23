# Yorl-DBOL: Database of Official Libraries

**Yorl Database of Official Libraries** - A community-driven repository for Yorl built-in libraries, inspired by PLDB (Programming Language Database).

## 📚 What is Yorl-DBOL?

Yorl-DBOL is the official registry and database for Yorl built-in libraries (`.ybuiltin` files). It allows the community to:
- Create custom built-in libraries
- Share libraries with other Yorl users
- Contribute to the official Yorl ecosystem
- Discover and use community-created libraries

## 🗂️ Directory Structure

```
yorl-dbol/
├── opensrc/          # Official open-source built-in libraries
│   ├── core.ybuiltin
│   ├── image.ybuiltin
│   ├── data.ybuiltin
│   ├── ai.ybuiltin
│   ├── network.ybuiltin
│   ├── crypto.ybuiltin
│   ├── file.ybuiltin
│   ├── json.ybuiltin
│   ├── xml.ybuiltin
│   ├── datetime.ybuiltin
│   ├── math.ybuiltin
│   ├── string.ybuiltin
│   ├── array.ybuiltin
│   └── regex.ybuiltin
├── usrsr/            # User Shared Resources (community contributions)
│   ├── web.ybuiltin
│   ├── database.ybuiltin
│   └── ...
├── templates/        # Templates for creating new built-ins
│   └── builtin-template.ybuiltin
└── docs/            # Documentation
    ├── CONTRIBUTING.md
    ├── BUILTIN-SPEC.md
    └── EXAMPLES.md
```

## 🚀 Quick Start

### Using a Built-in Library

```yorl
^yorl 1.0.0-2437\

! Import official built-in
import @builtin{core} -as[core];

! Import community built-in from usrsr
import @builtin{usrsr/web} -as[web];

class -className=myApp -type=application;
  .config
    .config.server -port=8080 -host='localhost';
  .data
    .data.response -status=web.HTTP.OK;

^END_OF_YORL
```

### Creating Your Own Built-in

1. **Fork this repository**
2. **Copy the template**:
   ```bash
   cp yorl-dbol/templates/builtin-template.ybuiltin yorl-dbol/usrsr/mylib.ybuiltin
   ```
3. **Edit your built-in** (see [BUILTIN-SPEC.md](docs/BUILTIN-SPEC.md))
4. **Test it** with yolex
5. **Submit a Pull Request**

## 📦 Official Built-ins (opensrc/)

### Core Module (`core.ybuiltin`)
- **Types**: position, size, color, transform, font
- **Functions**: Math, string, color operations
- **Constants**: COLOR.*, SIZE.*, POSITION.*

### Image Module (`image.ybuiltin`)
- **Functions**: load, save, resize, crop, rotate, blur, sharpen
- **Constants**: FORMAT.PNG, QUALITY.HIGH, FILTER.BLUR

### Data Module (`data.ybuiltin`)
- **Types**: array, dict, dataframe, series
- **Functions**: Array operations, statistics
- **Constants**: DTYPE.INT, FORMAT.CSV, ENCODING.UTF8

### AI Module (`ai.ybuiltin`)
- **Types**: model, tensor, dataset, training
- **Functions**: Model loading, training, prediction
- **Constants**: MODEL.CNN, ACTIVATION.RELU, OPTIMIZER.ADAM

### Network Module (`network.ybuiltin`)
- **Types**: Socket, Packet
- **Functions**: connect, send, receive
- **Constants**: PROTOCOL.*, PORT.*

### Crypto Module (`crypto.ybuiltin`)
- **Types**: Key, Hash
- **Functions**: encrypt, decrypt, hash, generateKey
- **Constants**: ALGORITHM.*, HASH.*

### File Module (`file.ybuiltin`)
- **Types**: File, Directory
- **Functions**: read, write, append, delete, compress
- **Constants**: ENCODING.*, COMPRESSION.*

### JSON Module (`json.ybuiltin`)
- **Functions**: parse, stringify, validate, merge
- **Constants**: TYPE.*

### XML Module (`xml.ybuiltin`)
- **Types**: Element
- **Functions**: parse, stringify, xpath, validate

### DateTime Module (`datetime.ybuiltin`)
- **Types**: DateTime
- **Functions**: now, parse, format, add, diff
- **Constants**: FORMAT.*, UNIT.*

### Math Module (`math.ybuiltin`)
- **Functions**: abs, sqrt, pow, sin, cos, tan, log, random
- **Constants**: PI, E, PHI

### String Module (`string.ybuiltin`)
- **Functions**: length, upper, lower, trim, split, join, replace, match
- **Functions**: contains, startsWith, endsWith

### Array Module (`array.ybuiltin`)
- **Functions**: length, push, pop, shift, unshift, slice, splice
- **Functions**: map, filter, reduce, sort, reverse

### Regex Module (`regex.ybuiltin`)
- **Types**: Pattern, Match
- **Functions**: compile, test, match, matchAll, replace
- **Constants**: FLAG.*

## 🌟 Community Built-ins (usrsr/)

Community-contributed libraries are stored in the `usrsr/` (User Shared Resources) directory.

### Available Libraries

| Library | Description | Author | Version |
|---------|-------------|--------|---------|
| `web.ybuiltin` | HTTP, WebSocket, REST APIs | Community | 1.0.0 |
| `database.ybuiltin` | SQL, NoSQL database operations | Community | 1.0.0 |
| `crypto.ybuiltin` | Encryption, hashing, security | Community | 1.0.0 |
| `network.ybuiltin` | TCP/UDP, sockets, protocols | Community | 1.0.0 |
| `file.ybuiltin` | File I/O, compression, formats | Community | 1.0.0 |

*Submit your library to be listed here!*

## 🤝 Contributing

We welcome contributions! Here's how to add your built-in library:

### Step 1: Fork & Clone
```bash
git clone https://github.com/Arthurc1Moude/yorl.git
cd yorl/yorl-dbol
```

### Step 2: Create Your Built-in
```bash
cp templates/builtin-template.ybuiltin usrsr/mylib.ybuiltin
# Edit usrsr/mylib.ybuiltin
```

### Step 3: Follow the Spec
Your `.ybuiltin` file must follow the [BUILTIN-SPEC.md](docs/BUILTIN-SPEC.md):
- Start with `^yorl-builtin 1.0.0-2437\`
- Define types, functions, constants
- Include documentation comments
- End with `^END_OF_BUILTIN`

### Step 4: Test
```bash
yolex --validate usrsr/mylib.ybuiltin
```

### Step 5: Submit PR
1. Commit your changes
2. Push to your fork
3. Create a Pull Request
4. Wait for review and merge

## 📋 Built-in Specification

### Basic Structure
```yorl
^yorl-builtin 1.0.0-2437\

! Library metadata
@metadata{
  name: "mylibrary",
  version: "1.0.0",
  author: "Your Name",
  description: "Library description",
  license: "MIT"
}

! Define types
@type{
  name: "MyType",
  fields: {field1:string, field2:int}
}

! Define functions
@function{
  name: "myFunction",
  params: {input:string, output:string},
  returns: "boolean",
  description: "Function description"
}

! Define constants
@constant{
  name: "MY_CONSTANT",
  value: 42,
  type: "int"
}

^END_OF_BUILTIN
```

## 🔍 Discovery

Browse available libraries:
```bash
# List all official libraries
ls yorl-dbol/official/

# List community libraries
ls yorl-dbol/usrsr/

# Search for specific functionality
grep -r "database" yorl-dbol/usrsr/
```

## 📖 Documentation

- [CONTRIBUTING.md](docs/CONTRIBUTING.md) - Contribution guidelines
- [BUILTIN-SPEC.md](docs/BUILTIN-SPEC.md) - Built-in specification
- [EXAMPLES.md](docs/EXAMPLES.md) - Example built-ins

## 🏆 Featured Libraries

### Web Library (`usrsr/web.ybuiltin`)
```yorl
import @builtin{usrsr/web} -as[web];

class -className=server -type=application;
  .config
    .config.server -port=web.PORT.HTTP -host='0.0.0.0';
  .routes
    .routes.get -path='/' -handler=web.handlers.index;
```

### Database Library (`usrsr/database.ybuiltin`)
```yorl
import @builtin{usrsr/database} -as[db];

class -className=connection -type=data;
  .config
    .config.db -type=db.TYPE.POSTGRESQL -host='localhost';
  .query
    .query.select -table='users' -where={active:true};
```

## 📊 Statistics

- **Official Libraries (opensrc/)**: 14
- **Community Libraries (usrsr/)**: Growing!
- **Total Functions**: 150+
- **Total Constants**: 300+
- **Contributors**: Community-driven

## 🔗 Links

- **Main Repository**: https://github.com/Arthurc1Moude/yorl
- **Issues**: https://github.com/Arthurc1Moude/yorl/issues
- **Discussions**: https://github.com/Arthurc1Moude/yorl/discussions

## 📜 License

- **Official Libraries**: Proprietary (Download & Share Only)
- **Community Libraries**: As specified by each author (typically MIT)

## 🎯 Roadmap

- [ ] Web interface for browsing libraries
- [ ] Package manager integration
- [ ] Automated testing for submissions
- [ ] Library versioning system
- [ ] Dependency resolution
- [ ] Library search API

## 💡 Ideas for New Libraries

Looking for inspiration? Consider creating:
- Graphics/Gaming library
- Audio/Video processing
- Machine Learning utilities
- Cloud services integration
- IoT/Hardware control
- Testing/Mocking utilities
- Logging/Monitoring
- Authentication/Authorization

## 🙏 Acknowledgments

Inspired by:
- [PLDB](https://pldb.com) - Programming Language Database
- [npm](https://npmjs.com) - Node Package Manager
- [PyPI](https://pypi.org) - Python Package Index

---

**Yorl-DBOL** - Building the Yorl ecosystem together! 🚀

**Version**: 1.0.0  
**Last Updated**: March 22, 2026
