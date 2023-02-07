@echo off

set CC=gcc
set CFLAGS=-O3 -I../include -std=c17 -pedantic -Wall -Wextra -Wno-deprecated-declarations
set LFLAGS=-L../lib -leasy2d -luser32 -lgdi32 -lwinmm
set SRC=*
set EX=%1

pushd ..\build

echo compiling with %CC%...
call %CC% ../src/%SRC%.c -c %CFLAGS%
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

if %errorlevel% == 0 (
   echo building with %CC%...
   call %CC% %EX%.c -o %EX%.exe %CFLAGS% %LFLAGS%
   echo done!
)
