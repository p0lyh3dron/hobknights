cmake_minimum_required( VERSION 3.10 )

Project( HobKnights VERSION 1.0 )

set( PLATFORM "Linux64" CACHE STRING "Build Type" )

if ( ${PLATFORM} MATCHES "Win64" )
    set( CMAKE_SHARED_LIBRARY_SUFFIX ".dll" )
endif()
if ( ${PLATFORM} MATCHES "Linux64" )
    set( CMAKE_SHARED_LIBRARY_SUFFIX ".so" )
endif()

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0" )
    set( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -g -O0"   )
endif()

add_definitions( -DUSE_SDL )

add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/../chik ${CMAKE_CURRENT_LIST_DIR}/../chik )

add_subdirectory( src/entry )
add_subdirectory( src/game  )