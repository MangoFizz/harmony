# SPDX-License-Identifier: GPL-3.0-only

# We need C99 to build Lua
set(CMAKE_C_STANDARD 99)

# C compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra")

# Source path
set(LUA53_SRC ext/lua53)

# Set Lua source files
add_library(lua53 STATIC
    # core
    ${LUA53_SRC}/lapi.c
    ${LUA53_SRC}/lcode.c
    ${LUA53_SRC}/lctype.c
    ${LUA53_SRC}/ldebug.c
    ${LUA53_SRC}/ldo.c
    ${LUA53_SRC}/ldump.c
    ${LUA53_SRC}/lfunc.c
    ${LUA53_SRC}/lgc.c
    ${LUA53_SRC}/llex.c
    ${LUA53_SRC}/lmem.c
    ${LUA53_SRC}/lobject.c
    ${LUA53_SRC}/lopcodes.c
    ${LUA53_SRC}/lparser.c
    ${LUA53_SRC}/lstate.c
    ${LUA53_SRC}/lstring.c
    ${LUA53_SRC}/ltable.c
    ${LUA53_SRC}/ltm.c
    ${LUA53_SRC}/lundump.c
    ${LUA53_SRC}/lvm.c
    ${LUA53_SRC}/lzio.c

    # libraries
    ${LUA53_SRC}/lauxlib.c
    #${LUA53_SRC}/lbaselib.c
    #${LUA53_SRC}/lbitlib.c
    #${LUA53_SRC}/lcorolib.c
    #${LUA53_SRC}/ldblib.c
    #${LUA53_SRC}/linit.c
    #${LUA53_SRC}/liolib.c
    #${LUA53_SRC}/lmathlib.c
    #${LUA53_SRC}/loadlib.c
    #${LUA53_SRC}/loslib.c
    #${LUA53_SRC}/lstrlib.c
    #${LUA53_SRC}/ltablib.c
    #${LUA53_SRC}/lutf8lib.c

    # interpreter
    #${LUA53_SRC}/lua.c

    # compiler
    #${LUA53_SRC}/luac.c
)