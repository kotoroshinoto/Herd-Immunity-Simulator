#!/usr/bin/env bash
mkdir -p lib
git clone git://git.code.sf.net/p/tclap/code lib/tclap_src
cd lib/tclap_src
./autotools.sh
libPath=$(readlink -f ./..)
./configure -prefix=$libPath/tclap
make
make install
#rm -rf lib/tclap
cd ../..
rm -rf lib/tclap_src
