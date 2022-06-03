#!/bin/bash

set -x

cd ${0%%$(basename $0)}
mkdir build
cd build

if [[ "$OSTYPE" == "linux-gnu" || "$OSTYPE" == "linux" ]]; then
    cmake -DPYTHON_VERSION_SUFFIX=-py3 -DCMAKE_BUILD_TYPE=DEBUG .. && make && make test
fi


