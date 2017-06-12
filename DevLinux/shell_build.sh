#! /bin/bash

./autogen.sh
if [ $? -eq 1 ]; then
	exit 1
fi

rm -rf build_linux
mkdir -p build_linux && cd build_linux && \
../configure --prefix=/opt/icdrec/bot && make -j9
if [ $? -eq 1 ]; then
	exit 1
fi
exit 0




