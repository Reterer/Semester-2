cmake_minimum_required( VERSION 2.8 )

project( CP6 LANGUAGES C )
set( CMAKE_C_FLAGS "-Wall -pedantic -std=c99 -Isrc" )

include_directories(src)
set( COMMON_FILES
    src/record/record.c
)

add_executable( avocado-converter ${COMMON_FILES} src/avocado-converter.c )
add_executable( avocado-finder ${COMMON_FILES} src/avocado-finder.c )
