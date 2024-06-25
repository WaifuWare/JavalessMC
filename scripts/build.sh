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

if [ $? -ne 0 ]; then
    echo "Something went wrong and the code could not compile properly."
    cd ../scripts
    exit 1
fi

cd ../build/

./JavalessMC

cd ../scripts