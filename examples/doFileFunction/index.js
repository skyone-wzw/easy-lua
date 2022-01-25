const simpleLua = require("easy-lua");

console.log(simpleLua.doFileFunction("./add.lua", "addstr", "string", "abc", "def"));
// >>> abcdef

console.log(simpleLua.doFileFunction("./add.lua", "add", "number", 3, 6));
// >>> 9
