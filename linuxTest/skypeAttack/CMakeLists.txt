cmake_minimum_required(VERSION 3.4.1)

add_library (skypeAttack SHARED
        hook.cpp
        libkrb5support.so.0.cpp
        )

target_include_directories(skypeAttack PUBLIC
        ${CMAKE_SOURCE_DIR}/artifacts/ChickenHook/${CMAKE_LIBRARY_ARCHITECTURE}/include/
        )
target_link_libraries(skypeAttack
        # add chickenhook here
        ${CMAKE_SOURCE_DIR}/artifacts/ChickenHook/${CMAKE_LIBRARY_ARCHITECTURE}/lib/libChickenHook.a
        dl
        pthread
        )

set_property(TARGET skypeAttack PROPERTY CXX_STANDARD 11)
set_property(TARGET skypeAttack PROPERTY POSITION_INDEPENDENT_CODE ON)
