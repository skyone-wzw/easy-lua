{
    "targets": [
        {
            "target_name": "nodeLua",
            "include_dirs": [
                "./lib/lua",
            ],
            "sources": [
                "./src/nodeLua.cpp",
                "./lib/lua/lapi.c",
                "./lib/lua/lcode.c",
                "./lib/lua/lctype.c",
                "./lib/lua/ldebug.c",
                "./lib/lua/ldo.c",
                "./lib/lua/ldump.c",
                "./lib/lua/lfunc.c",
                "./lib/lua/lgc.c",
                "./lib/lua/llex.c",
                "./lib/lua/lmem.c",
                "./lib/lua/lobject.c",
                "./lib/lua/lopcodes.c",
                "./lib/lua/lparser.c",
                "./lib/lua/lstate.c",
                "./lib/lua/ltable.c",
                "./lib/lua/ltm.c",
                "./lib/lua/lundump.c",
                "./lib/lua/lvm.c",
                "./lib/lua/lzio.c",
                "./lib/lua/lauxlib.c",
                "./lib/lua/lbaselib.c",
                "./lib/lua/lcorolib.c",
                "./lib/lua/ldblib.c",
                "./lib/lua/lmathlib.c",
                "./lib/lua/loadlib.c",
                "./lib/lua/loslib.c",
                "./lib/lua/lstrlib.c",
                "./lib/lua/lstring.c",
                "./lib/lua/ltablib.c",
                "./lib/lua/liolib.c",
                "./lib/lua/lutf8lib.c",
                "./lib/lua/linit.c",
            ]
        }
    ]
}