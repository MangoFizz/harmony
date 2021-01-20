# SPDX-License-Identifier: GPL-3.0-only

# We need C99 to build Lua
set(CMAKE_C_STANDARD 99)

# C compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra")

# Set Lua source files
add_library(lua STATIC
    ext/lua/lapi.c
    ext/lua/lauxlib.c
    ext/lua/lbaselib.c
    ext/lua/lbitlib.c
    ext/lua/lcode.c
    ext/lua/lcorolib.c
    ext/lua/lctype.c
    ext/lua/ldblib.c
    ext/lua/ldebug.c
    ext/lua/ldo.c
    ext/lua/ldump.c
    ext/lua/lfunc.c
    ext/lua/lgc.c
    ext/lua/linit.c
    ext/lua/liolib.c
    ext/lua/llex.c
    ext/lua/lmathlib.c
    ext/lua/lmem.c
    ext/lua/loadlib.c
    ext/lua/lobject.c
    ext/lua/lopcodes.c
    ext/lua/loslib.c
    ext/lua/lparser.c
    ext/lua/lstate.c
    ext/lua/lstring.c
    ext/lua/lstrlib.c
    ext/lua/ltable.c
    ext/lua/ltablib.c
    ext/lua/ltm.c
    ext/lua/luac.c
    ext/lua/lundump.c
    ext/lua/lutf8lib.c
    ext/lua/lvm.c
    ext/lua/lzio.c
)