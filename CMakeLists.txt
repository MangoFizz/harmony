# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.16)

# Set project info
project(harmony
    VERSION 0.0.1
    LANGUAGES C CXX ASM
)

# Set include path
include_directories(include/)

add_library(harmony MODULE
    src/harmony/harmony.cpp
)

# Set output name
set_target_properties(harmony PROPERTIES PREFIX "")
set_target_properties(harmony PROPERTIES OUTPUT_NAME "nharmony") # new harmony
 
# Set linker flags
set_target_properties(harmony PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++")
target_link_libraries(harmony ${CMAKE_SOURCE_DIR}/lib/libballtze.dll.a)

# Install harmony.dll
install(TARGETS harmony DESTINATION "${CMAKE_INSTALL_PREFIX}")
