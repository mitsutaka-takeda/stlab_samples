# stlab_sample

**PUPOSE:** Learning the stlab concurrency libraries.

# Build

To build this project, we need clang-5.0, boost 1.65.1, and [stlab.libraries](https://github.com/stlab/libraries).

Use the command like the following:

CC=~/bin/clang CXX=~/bin/clang++ cmake -GNinja -DBOOST_ROOT=~/etc/boost_1_65_1/ -DCMAKE_CXX_FLAGS="-std=c++17" ~/src/cpp/stlab_sample/
