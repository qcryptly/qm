#!/bin/bash
rm -rf build/*
cd build && cmake ..
make
bash ../kernels/test.sh
cd -
