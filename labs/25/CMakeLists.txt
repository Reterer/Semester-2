cmake_minimum_required( VERSION 2.8 )

project( lab26 LANGUAGES C )
set( CMAKE_C_FLAGS "-Wall -pedantic -std=c99 -Isrc" )

include_directories(src)
set( SOURCES
    src/main.c
    src/log/log.c
    src/sort/sort.c
    src/udt/udt.c
)

add_executable( ${CMAKE_PROJECT_NAME} ${SOURCES} )
