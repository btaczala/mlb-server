#!/bin/bash

cmake_command="cmake /home/sources/ -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -DDISABLE_3rdParty=ON -GNinja -DSANITIZER=$SANITIZER"

docker run --rm -e CC -e CXX \
    -v `pwd`:/home/sources bartekt/mlb-docker /bin/bash \
    -c "cd /home/ && rm -rfv build && mkdir build && cd build && $cmake_command && ninja && ctest --repeat-until-fail 10"
