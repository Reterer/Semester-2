cmake_minimum_required( VERSION 2.8 )

project( CP9 LANGUAGES C )
set( CMAKE_C_FLAGS "-Wall -pedantic -std=c99 -Isrc" )

include_directories(src)
add_executable( cp9 src/main.c src/sort.c src/table.c)
