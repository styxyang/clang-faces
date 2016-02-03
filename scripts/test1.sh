#!/bin/bash

set -x
./build/clang-faces --once --clang-opts='-x c -std=c++' ~/p/demo/avl.c
