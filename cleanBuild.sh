#!/bin/bash
CURRDIR=${PWD}
echo "*** Running clean build script ***"
echo "*** Current Directory : $CURRDIR ***"
echo "*** Compiling protobuff files using the protoc compiler from vendor ***"

rm ./src/proto/models/*

$CURRDIR/vendor/protobuf-3.19.4/install/bin/protoc --proto_path=$CURRDIR/src/proto $CURRDIR/src/proto/*.proto --cpp_out=$CURRDIR/src/proto/models/

echo "*** Running Make clean ***"
cd build
make clean

echo "*** Running Make ***"
make