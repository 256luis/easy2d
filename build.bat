@echo off

pushd build

clang -c %~dp0/src/*.c -I%~dp0/include -O3 -Wall -Wextra -Wpedantic -Wno-strict-prototypes -std=c17

popd

pushd lib

if %errorlevel% == 0 (
   llvm-ar rcs %~dp0/lib/easy2d.lib %~dp0/build/*.o
)

popd
