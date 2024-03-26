cmake_minimum_required( VERSION 3.10 )

Project( Game VERSION 1.0 )

file( GLOB SOURCES *.c )
file( GLOB BASE_SOURCES ../base/*.c )

get_property( CHIK_GAMES GLOBAL PROPERTY CHIK_GAMES )
get_property( LIBCHIK GLOBAL PROPERTY LIBCHIK )

include_directories( ${LIBCHIK} )

link_directories( "${CMAKE_SOURCE_DIR}/src/thirdparty" )
link_libraries( LibChik SDL2 )

if ( MSVC )
    link_directories( "${LIBCHIK}/../../SDL2/lib/x64" )
    include_directories( "${LIBCHIK}" "${LIBCHIK}/../../SDL2/include" )
endif()

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

add_library( Game SHARED ${SOURCES} ${BASE_SOURCES} )

set_target_properties( 
    Game PROPERTIES

    RUNTIME_OUTPUT_NAME hobknights
    LIBRARY_OUTPUT_NAME hobknights

    RUNTIME_OUTPUT_DIRECTORY ${CHIK_GAMES}/hobknights/bin
    LIBRARY_OUTPUT_DIRECTORY ${CHIK_GAMES}/hobknights/bin
)

# set output directories for all builds (Debug, Release, etc.)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set_target_properties(
    	Game PROPERTIES
    	RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CHIK_GAMES}/hobknights/bin
    	LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CHIK_GAMES}/hobknights/bin
    )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
