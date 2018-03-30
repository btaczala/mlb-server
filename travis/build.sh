#!/bin/bash

cmake_command="cmake /home/sources/ -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DBUILD_ALL=$BUILD_ALL -GNinja -DSANITIZER=$SANITIZER"

echo $cmake_command
docker run --rm -e CC -e CXX \
    -v `pwd`:/home/sources bartekt/mlb-docker /bin/bash \
    -c "cd /home/ && rm -rfv build && mkdir build && cd build && $cmake_command && ninja -v && MLB_SERVER_LOG_LEVEL=debug ctest -V"
