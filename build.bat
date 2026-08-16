@echo off

if not exist build mkdir build

pushd build

set CC=clang
set CMAKEFLAGS=-DCMAKE_BUILD_TYPE=Debug ^
               -DCMAKE_MSVC_RUNTIME_LIBRARY="MultiThreaded$<$<CONFIG:Debug>:Debug>" ^
               -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

if not exist build.ninja (
    cmake .. -G "Ninja" %CMAKEFLAGS%
    move compile_commands.json ../
)

ninja

popd
