# Easy Lua

Use Lua in Node.js simply.

```js
const simpleLua = require("easy-lua");

simpleLua.doFile("./test.lua");
```
* `doFile(path: string)`

  run a lua file

* `doFileFunction(path: string, funName: string, returnType: string, ...arg)`

  run a funtion with args in a lua file

For dev

```shell
npm i -g node-gyp
node-gyp configure
node-gyp build
```

See [examples](examples)
