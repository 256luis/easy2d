@echo off

set CC=cl
set CFLAGS=/c /Fobuild\ /Fdbuild\ /Od /Zi /Iinclude /std:c17 /D_CRT_SECURE_NO_WARNINGS /W4 /wd4255 /wd5105
set SRC=%1

if not defined SRC (
    set SRC=*
)

echo compiling with %CC%...
call %CC% src/%SRC%.c %CFLAGS% /nologo
echo done!
echo -----------------------------

if %errorlevel% == 0 (
    echo creating archive...
    if not exist lib mkdir lib
    call lib build\*.obj /out:lib/easy2d.lib /nologo
    echo done!
    echo -----------------------------
)
