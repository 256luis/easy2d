@echo off

set CC=tcc
set CFLAGS=-c -O0 -g -I../include -std=c17 -pedantic -Wall -Wextra -Wno-deprecated-declarations
set LFLAGS=-luser32 -lgdi32
set SRC=%1

if not defined SRC (
    set SRC= ../src/drawing.c ../src/event.c ../src/text.c ../src/time.c ../src/window.c ../src/winmain.c ../src/image.c
)

pushd build

echo compiling with %CC%...
call %CC% %SRC% %CFLAGS%
echo done!
echo -----------------------------

if %errorlevel% == 0 (
    echo creating archive...
    if not exist ..\lib mkdir ..\lib
    call ar rcs ../lib/libeasy2d.a *.o  
    echo done!
    echo -----------------------------
)

popd
