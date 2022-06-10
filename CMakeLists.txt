cmake_minimum_required(VERSION 3.20)
project(ProgalapTGProjekt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cmake-build-debug)
include_directories(libsakk)
include_directories(main)

add_executable(ProgalapTGProjekt
        .idea/misc.xml
        .idea/modules.xml
        .idea/ProgalapTGProjekt.iml
        .idea/workspace.xml
        libsakk/Makefile
        libsakk/sakk.c
        libsakk/sakk.h
        libsakk/utest-sakk.c
        libsakk/utest-sakk.h
        libsakk/utest.c
        main/Makefile
        main/play-sakk.c
        .gitignore
        clean.sh
        Makefile
        run.sh
        test.sh)