@echo off

for /f %%A in ('cd') do set root_path=%%A
call :submodule_init
call :googletest_build
call :utils_build

:submodule_init
    git submodule init
    git submodule update
    exit /b

:googletest_build
    cd ./thirdparty/googletest
    mkdir build
    cd build
    cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=make.exe -G "MSYS Makefiles" ..
    make -j10
    cd %root_path%
    exit /b

:utils_build
    cd %root_path%
    mkdir cmake_release_build
    cd cmake_release_build
    cmake -DCMAKE_BUILD_TYPE=Release .. -G "MinGW Makefiles"
    make -j10
    make install