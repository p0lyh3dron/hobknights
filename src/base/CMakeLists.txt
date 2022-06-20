cmake_minimum_required( VERSION 3.10 )

Project( Base VERSION 1.0 )

file( GLOB SOURCES *.c )

get_property( CHIK_GAMES GLOBAL PROPERTY CHIK_GAMES )
get_property( LIBCHIK GLOBAL PROPERTY LIBCHIK )

include_directories( ${LIBCHIK} )

link_directories( "${CMAKE_SOURCE_DIR}/src/thirdparty" )
link_libraries( "discord_game_sdk.so" )
link_libraries( LibChik )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

add_library( Base SHARED ${SOURCES} )

set_target_properties( 
    Base PROPERTIES

    RUNTIME_OUTPUT_NAME hobknights
    LIBRARY_OUTPUT_NAME hobknights

    RUNTIME_OUTPUT_DIRECTORY ${CHIK_GAMES}/hobknights/bin
    LIBRARY_OUTPUT_DIRECTORY ${CHIK_GAMES}/hobknights/bin
)