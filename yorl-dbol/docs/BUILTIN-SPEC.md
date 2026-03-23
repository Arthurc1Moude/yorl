# Yorl Built-in Specification

This document defines the specification for creating `.ybuiltin` files for Yorl.

## 📋 File Structure

### Header
Every `.ybuiltin` file must start with:
```yorl
^yorl-builtin 1.0.0-2437\
```

### Footer
Every `.ybuiltin` file must end with:
```yorl
^END_OF_BUILTIN
```

## 🏷️ Metadata Section

Required metadata for every built-in:

```yorl
@metadata{
  name: "library-name",
  version: "1.0.0",
  author: "Author Name",
  description: "Library description",
  license: "MIT",
  homepage: "https://example.com",
  repository: "https://github.com/user/repo",
  keywords: {web,http,server},
  dependencies: {core,image}
}
```

### Metadata Fields

| Field | Required | Type | Description |
|-------|----------|------|-------------|
| `name` | Yes | string | Library name (lowercase, hyphens) |
| `version` | Yes | string | Semantic version (x.y.z) |
| `author` | Yes | string | Author name or organization |
| `description` | Yes | string | Brief description |
| `license` | Yes | string | License identifier (MIT, Apache-2.0, etc.) |
| `homepage` | No | string | Library homepage URL |
| `repository` | No | string | Source repository URL |
| `keywords` | No | array | Search keywords |
| `dependencies` | No | array | Required built-in libraries |

## 🔧 Type Definitions

Define custom types:

```yorl
@type{
  name: "TypeName",
  description: "Type description",
  fields: {
    field1: string,
    field2: int,
    field3: boolean,
    nested: {
      subfield1: float,
      subfield2: string
    }
  },
  methods: {
    method1: {params: {input:string}, returns: "boolean"},
    method2: {params: {x:int, y:int}, returns: "int"}
  }
}
```

### Supported Field Types
- `string` - Text data
- `int` - Integer numbers
- `float` - Floating-point numbers
- `boolean` - true/false
- `array` - List of items
- `object` - Key-value pairs
- `color` - Color values (#RGB)
- `path` - File paths
- `url` - URLs

## 📦 Function Definitions

Define functions:

```yorl
@function{
  name: "functionName",
  description: "Function description",
  params: {
    param1: string,
    param2: int,
    optional: {type: boolean, default: true}
  },
  returns: "string",
  throws: {InvalidInput, NetworkError},
  examples: {
    "Basic usage": "functionName('hello', 42)",
    "With optional": "functionName('world', 100, false)"
  }
}
```

### Function Fields

| Field | Required | Description |
|-------|----------|-------------|
| `name` | Yes | Function name (camelCase) |
| `description` | Yes | What the function does |
| `params` | Yes | Input parameters |
| `returns` | Yes | Return type |
| `throws` | No | Possible exceptions |
| `examples` | No | Usage examples |

## 🔢 Constant Definitions

Define constants:

```yorl
@constant{
  name: "CONSTANT_NAME",
  value: 42,
  type: "int",
  description: "Constant description"
}

! Namespaced constants
@constant{
  namespace: "HTTP",
  constants: {
    OK: {value: 200, type: "int", description: "Success"},
    NOT_FOUND: {value: 404, type: "int", description: "Not found"},
    ERROR: {value: 500, type: "int", description: "Server error"}
  }
}
```

### Constant Types
- `int` - Integer constant
- `float` - Float constant
- `string` - String constant
- `boolean` - Boolean constant
- `color` - Color constant (#RGB)

## 🎨 Namespace Organization

Organize related items in namespaces:

```yorl
@namespace{
  name: "HTTP",
  description: "HTTP protocol constants",
  items: {
    STATUS: {
      OK: 200,
      CREATED: 201,
      NOT_FOUND: 404,
      ERROR: 500
    },
    METHOD: {
      GET: "GET",
      POST: "POST",
      PUT: "PUT",
      DELETE: "DELETE"
    }
  }
}
```

## 📝 Comments

Use `!` for comments:

```yorl
! This is a comment
! Comments can explain functionality

@function{
  name: "myFunc",  ! Inline comment
  description: "Does something"
}
```

## ✅ Complete Example

```yorl
^yorl-builtin 1.0.0-2437\

! Web Server Built-in Library
! Provides HTTP server functionality

@metadata{
  name: "web-server",
  version: "1.0.0",
  author: "Yorl Community",
  description: "HTTP web server library",
  license: "MIT",
  keywords: {web,http,server,rest},
  dependencies: {core}
}

! Server configuration type
@type{
  name: "ServerConfig",
  description: "HTTP server configuration",
  fields: {
    host: string,
    port: int,
    ssl: boolean,
    routes: array
  }
}

! HTTP request type
@type{
  name: "HttpRequest",
  description: "HTTP request object",
  fields: {
    method: string,
    path: string,
    headers: object,
    body: string
  }
}

! Start server function
@function{
  name: "startServer",
  description: "Start HTTP server",
  params: {
    config: ServerConfig,
    callback: function
  },
  returns: "boolean",
  throws: {PortInUse, InvalidConfig},
  examples: {
    "Basic": "startServer({host:'localhost',port:8080}, handler)"
  }
}

! HTTP status codes
@constant{
  namespace: "HTTP",
  constants: {
    OK: {value: 200, type: "int", description: "Success"},
    CREATED: {value: 201, type: "int", description: "Created"},
    NOT_FOUND: {value: 404, type: "int", description: "Not found"},
    ERROR: {value: 500, type: "int", description: "Server error"}
  }
}

! HTTP methods
@constant{
  namespace: "METHOD",
  constants: {
    GET: {value: "GET", type: "string"},
    POST: {value: "POST", type: "string"},
    PUT: {value: "PUT", type: "string"},
    DELETE: {value: "DELETE", type: "string"}
  }
}

^END_OF_BUILTIN
```

## 🔍 Validation

Your built-in will be validated for:

1. **Syntax** - Correct `.ybuiltin` syntax
2. **Metadata** - All required fields present
3. **Types** - Valid type definitions
4. **Functions** - Proper function signatures
5. **Constants** - Valid constant definitions
6. **Naming** - Follows naming conventions
7. **Documentation** - Adequate descriptions

## 🚀 Best Practices

1. **Be Descriptive** - Use clear names and descriptions
2. **Use Namespaces** - Organize related constants
3. **Document Everything** - Add descriptions and examples
4. **Follow Conventions** - Use standard naming patterns
5. **Keep It Simple** - Don't overcomplicate
6. **Test Thoroughly** - Validate before submitting
7. **Version Properly** - Use semantic versioning

## 📚 References

- [CONTRIBUTING.md](CONTRIBUTING.md) - Contribution guidelines
- [EXAMPLES.md](EXAMPLES.md) - Example built-ins
- [Main README](../README.md) - Yorl-DBOL overview

---

**Specification Version**: 1.0.0  
**Last Updated**: March 22, 2026
