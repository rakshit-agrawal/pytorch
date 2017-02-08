#!/bin/bash

if [[ $(basename $(pwd)) != "THD" ]]; then
  echo "The build script has to be executed from the root directory of THD!"
  exit 2
fi

cd ..
lib_dir="$(pwd)"
cd THD

mkdir -p build
cd build
cmake .. -DCMAKE_CXX_FLAGS=" -I${lib_dir}/tmp_install/include -pthread "  \
         -DCMAKE_SHARED_LINKER_FLAGS="-L${lib_dir}/tmp_install/lib " \
         -DCMAKE_EXE_LINKER_FLAGS="-L${lib_dir}/tmp_install/lib -pthread " \
   -DTorch_FOUND="1"
make
