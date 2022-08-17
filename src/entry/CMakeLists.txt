
cmake_minimum_required( VERSION 3.10 )

Project( Entry VERSION 1.0 )

file( GLOB_RECURSE SOURCES *.c )

get_property( CHIK_GAMES GLOBAL PROPERTY CHIK_GAMES )
get_property( LIBCHIK GLOBAL PROPERTY LIBCHIK )

include_directories( ${LIBCHIK} )

link_libraries( LibChik )

add_executable( Entry ${SOURCES} )

set_target_properties( 
    Entry PROPERTIES

    RUNTIME_OUTPUT_NAME run
    LIBRARY_OUTPUT_NAME run

    RUNTIME_OUTPUT_DIRECTORY ${CHIK_GAMES}
    LIBRARY_OUTPUT_DIRECTORY ${CHIK_GAMES}
)
