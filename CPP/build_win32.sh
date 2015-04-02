#!/usr/bin/env bash
mkdir -p build/win32
cd build/win32
rm -rf ./*
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-cross-mingw32-linux.cmake -DSTATIC_LINK:BOOL=True ../..
make
cd ../..

