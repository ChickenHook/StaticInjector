cmake_minimum_required(VERSION 3.4.1)

add_library (spotifyAttack SHARED
        hook.cpp
        )

target_include_directories(spotifyAttack PUBLIC
        ${CMAKE_SOURCE_DIR}/artifacts/ChickenHook/${CMAKE_LIBRARY_ARCHITECTURE}/include/
        )
target_link_libraries(spotifyAttack
        # add chickenhook here
        ${CMAKE_SOURCE_DIR}/artifacts/ChickenHook/${CMAKE_LIBRARY_ARCHITECTURE}/lib/libChickenHook.a
        dl
        pthread
        )

set_property(TARGET spotifyAttack PROPERTY CXX_STANDARD 11)
set_property(TARGET spotifyAttack PROPERTY POSITION_INDEPENDENT_CODE ON)
