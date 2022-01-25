#include <node.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
extern "C" {
#include <lualib.h>
#include <lauxlib.h>
}

namespace skyone {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

std::string v8string2string(const FunctionCallbackInfo<Value>& args, int index) {
    char* _buffer = (char*) calloc(1, args[index].As<String>()->Utf8Length(args.GetIsolate()));
    args[index].As<String>()->WriteUtf8(args.GetIsolate(), _buffer);
    return _buffer;
}

void doFile(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    if (!args[0]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong type of arguments").ToLocalChecked()));
        return;
    }

    const std::string file_name = v8string2string(args, 0);
    struct stat file_info;
    if (stat(file_name.c_str(), &file_info) != 0) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Lua file not found").ToLocalChecked()));
        return;
    } else if (file_info.st_mode & S_IFDIR) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Target path is a dir (required lua file)").ToLocalChecked()));
        return;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, file_name.c_str());
}

void doFileFunction(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() < 3) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong type of arguments").ToLocalChecked()));
        return;
    }

    const int args_count = args.Length() - 3;

    const std::string file_name = v8string2string(args, 0);
    const std::string function_name = v8string2string(args, 1);
    struct stat file_info;
    if (stat(file_name.c_str(), &file_info) != 0) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Lua file not found").ToLocalChecked()));
        return;
    } else if (file_info.st_mode & S_IFDIR) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Target path is a dir (required lua file)").ToLocalChecked()));
        return;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_loadfile(L, file_name.c_str());
    lua_pcall(L, 0, 0, 0);
    lua_getglobal(L, function_name.c_str());
    for (int i = 0; i < args_count; i++) {
        if (args[i + 3]->IsNumber()) {
            lua_pushnumber(L, args[i + 3].As<Number>()->Value());
        } else {
            lua_pushstring(L, v8string2string(args, i + 3).c_str());
        }
    }
    if (!args[2]->IsString()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong type of arguments").ToLocalChecked()));
        return;
    }
    std::string ret_type = v8string2string(args, 2);
    lua_pcall(L, args_count, 1, 0);
    
    if (ret_type == "number") {
        const double ret = lua_tonumber(L, -1);
        args.GetReturnValue().Set(Number::New(isolate, ret));
    } else {
        const std::string ret = lua_tostring(L, -1);
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, ret.c_str(), NewStringType::kNormal).ToLocalChecked());
    }
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "doFile", doFile);
    NODE_SET_METHOD(exports, "doFileFunction", doFileFunction);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}