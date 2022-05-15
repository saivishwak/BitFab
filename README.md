# BitFab (Bit Fabric)

BitFab is a P2P decentralized blockchain.

Under Development...

# Installation

Make sure you have the following tools installed on your system:
  * cmake (https://cmake.org/install/)
  * protobuf
  * autoconf
  * automake
  * libtool
  * make
  * g++
  * unzip


On Ubuntu/Debian, you can install them with:
sudo apt-get install autoconf automake libtool curl make g++ unzip
sudo apt install protobuf-compiler

On mac, you can install them with:
brew install autoconf automake libtool protobuf

To build initially run:
    ./configureBuild.sh

To run executable:
    cd ./build/bin
    ./bitfab
