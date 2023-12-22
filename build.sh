#!/bin/bash

root_path=$(pwd)

function submodule_update {
	git submodule init
	git submodule update
}

function googletest_build {
	cd thirdparty/googletest
	mkdir build
	cd build
	cmake ..
	make -j10
}

function utils_build {
	cd $root_path
	mkdir cmake_release_build
	cd cmake_release_build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make -j10
	make install
}

submodule_update
googletest_build
utils_build
