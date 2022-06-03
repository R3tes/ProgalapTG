#!/bin/bash

cmake -H. -Bbuild
make -C build -j
printf "\n\n\n"
./build/main/main
printf "\n\n\n"