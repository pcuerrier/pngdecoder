@echo off

SET PROJECT_DRIVE=C:\
SET BUILD_DIR=%PROJECT_DRIVE%\dev\pngdecoder\build\
SET PROJECT_NAME=pngdecoder
SET PROJECT_BUILD_DIR=%BUILD_DIR%

SET PROJECT_BIN=%PROJECT_BUILD_DIR%bin\
set PROJECT_BIN_INT=%PROJECT_BUILD_DIR%bin-int\

SET PROJECT_BIN_DEBUG=%PROJECT_BIN%debug_x64\
set PROJECT_BIN_INT_DEBUG=%PROJECT_BIN_INT%debug_x64\
SET PROJECT_BIN_RELEASE=%PROJECT_BIN%release_x64\
set PROJECT_BIN_INT_RELEASE=%PROJECT_BIN_INT%release_x64\

IF NOT EXIST %BUILD_DIR% MKDIR %BUILD_DIR%
IF NOT EXIST %PROJECT_BUILD_DIR% MKDIR %PROJECT_BUILD_DIR%

IF NOT EXIST %PROJECT_BIN%              MKDIR %PROJECT_BIN%
IF NOT EXIST %PROJECT_BIN_INT%          MKDIR %PROJECT_BIN_INT%
IF NOT EXIST %PROJECT_BIN_DEBUG%        MKDIR %PROJECT_BIN_DEBUG%
IF NOT EXIST %PROJECT_BIN_INT_DEBUG%    MKDIR %PROJECT_BIN_INT_DEBUG%
IF NOT EXIST %PROJECT_BIN_RELEASE%      MKDIR %PROJECT_BIN_RELEASE%
IF NOT EXIST %PROJECT_BIN_INT_RELEASE%  MKDIR %PROJECT_BIN_INT_RELEASE%

set CPP_FILES=.\src\*.cpp
set COMMON_COMPILER_FLAGS=/UUNICODE /U_UNICODE /FC /WX /W4 /wd4100 /wd4189 /wd4201 /EHa /nologo
set COMMON_LINKER_FLAGS=/link /incremental:no /opt:ref

REM "/FC", // File fullnames
REM "/Od", // No optimization
REM "/O2", // Full optimization
REM "/MTd", // Link static version of the C-Standard Library - Debug version (DEFINES _DEBUG)
REM "/MT", // Link static version of the C-Standard Library
REM "/Z7", // Produce Debug file
REM "/WX", // Treat warnings as errors
REM "/W4", // Warning level
REM "/wd4100", // Unreferenced formal parameter
REM "/wd4189", // Unsused local variables (will be optimized out by compiler)
REM "/wd4201", // Nameless struct
REM "/EHsc", // Disables synchronous Exception handling
REM "/EHa", // Disables asynchronous Exception handling
REM "/nologo", // Disable Microsoft C++ banner

REM DEBUG x64
echo Building DEBUG...
cl.exe %COMMON_COMPILER_FLAGS% /Od /MTd /Z7 /Fo:%PROJECT_BIN_INT_DEBUG% /Fe:%PROJECT_BIN_DEBUG%%PROJECT_NAME%.exe %CPP_FILES% %COMMON_LINKER_FLAGS%

REM RELEASE x64
echo Building RELEASE...
cl.exe %COMMON_COMPILER_FLAGS% /O2 /MT /Fo:%PROJECT_BIN_INT_RELEASE% /Fe:%PROJECT_BIN_RELEASE%%PROJECT_NAME%.exe %CPP_FILES% %COMMON_LINKER_FLAGS%