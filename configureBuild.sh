#!/bin/bash
CURRDIR=${PWD}
echo "*** Running start script to run configurations ***"
echo "*** Current Directory : $CURRDIR ***"

echo "*** Make for jsoncpp ***"
cd $CURRDIR/vendor/jsoncpp
rm -rf ./build
cmake . -B build
cd build
make

echo "*** Make for spdlog ***"
cd $CURRDIR/vendor/spdlog
rm -rf ./build
cmake . -B build
cd build
make

echo "*** Make for protobuf ****"
cd $CURRDIR/vendor/protobuf-3.19.4
make clean
rm -rf ./install
mkdir install
./autogen.sh
./configure --with-protoc=protoc --prefix=${PWD}/install/
make install
cd $CURRDIR

rm ./src/proto/models/*
echo "*** Compiling protobuff files using the protoc compiler from vendor ***"
$CURRDIR/vendor/protobuf-3.19.4/install/bin/protoc --proto_path=$CURRDIR/src/proto $CURRDIR/src/proto/*.proto --cpp_out=$CURRDIR/src/proto/models/

echo "*** Removing any existing build folder ***"
rm -rf ./build/
cmake . -B build
cd build
echo "*** Running Make ***"
make