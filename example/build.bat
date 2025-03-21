@echo off

set CC=cl
set CFLAGS=/c /Fobuild\ /Fdbuild\ /O2 /Iinclude /std:c17 /D_CRT_SECURE_NO_WARNINGS /W4 /wd4255 /wd5105
set SRC=*

pushd ..

call %CC% src/%SRC%.c %CFLAGS% /nologo

if %errorlevel% == 0 (
    if not exist lib mkdir lib
    call lib build\*.obj /out:lib/easy2d.lib /nologo
)

popd

set CFLAGS=/O2 /I..\include /std:c17 /D_CRT_SECURE_NO_WARNINGS /Wall /wd4255
set LFLAGS=/link /libpath:..\lib easy2d.lib user32.lib gdi32.lib winmm.lib
set SRC=%1

call %CC% %1.c %CFLAGS% %LFLAGS% /out:%1.exe /nologo
