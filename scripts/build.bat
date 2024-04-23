@echo off

rm -rf build
mkdir build
cd cryptography
asn1c -fcompound-names login.asn1
del converter-example.c

cd ..
cd build
cmake ..
cmake --build . --config Release
cd ..