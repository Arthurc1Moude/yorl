# Yorl-DBOL Examples

Example built-in libraries and usage patterns.

## 📚 Example Libraries

### Web Library

```yorl
^yorl 1.0.0-2437\

import @builtin{usrsr/web} -as[web];

class -className=server -type=application;
  .config
    .config.server -host='localhost' -port=web.PORT.DEV -ssl=false;
  .routes
    .routes.home -path='/' -method=web.METHOD.GET;
    .routes.api -path='/api' -method=web.METHOD.POST;
  .response
    .response.status -code=web.HTTP.OK;

^END_OF_YORL
```

### Database Library

```yorl
^yorl 1.0.0-2437\

import @builtin{usrsr/database} -as[db];

class -className=connection -type=data;
  .config
    .config.db -type=db.TYPE.POSTGRESQL -host='localhost' -port=db.PORT.POSTGRESQL;
    .config.db.database -name='myapp' -username='user' -password='pass';
  .query
    .query.select -table='users' -where={active:true};
    .query.insert -table='logs' -data={message:'Hello',timestamp:1234567890};

^END_OF_YORL
```

### Combined Example

```yorl
^yorl 1.0.0-2437\

import @builtin{core} -as[core];
import @builtin{usrsr/web} -as[web];
import @builtin{usrsr/database} -as[db];

class -className=webapp -type=application;
  .server
    .server.config -host='0.0.0.0' -port=web.PORT.HTTP;
  .database
    .database.config -type=db.TYPE.MYSQL -host='localhost';
  .routes
    .routes.users -path='/users' -method=web.METHOD.GET;
    .routes.create -path='/users' -method=web.METHOD.POST;

^END_OF_YORL
```

## 🎯 Usage Patterns

### Pattern 1: Simple Import

```yorl
import @builtin{usrsr/mylib} -as[mylib];

class -className=app -type=application;
  .config
    .config.value -const=mylib.MY_CONSTANT;
```

### Pattern 2: Selective Import

```yorl
import @builtin{usrsr/mylib} -as[mylib] -only={function1,function2};

class -className=app -type=application;
  .process
    .process.step1 -func=mylib.function1;
```

### Pattern 3: Namespace Usage

```yorl
import @builtin{usrsr/mylib} -as[mylib];

class -className=app -type=application;
  .status
    .status.code -value=mylib.STATUS.SUCCESS;
  .mode
    .mode.type -value=mylib.MODE.FAST;
```

---

More examples coming soon!
