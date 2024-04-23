#!/bin/bash
cd ..
rm -rf build

cd cryptography
asn1c -fcompound-names login.asn1
rm converter-sample.c
cd ..

mkdir build
cd build
cmake build ../
cmake --build .
