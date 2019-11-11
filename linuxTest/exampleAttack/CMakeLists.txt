cmake_minimum_required(VERSION 3.4.1)

add_library (linuxAttack SHARED
        hook.cpp
        libgcc_s.so.1.cpp
        libkrb5support.so.0.cpp
        )

target_include_directories(linuxAttack PUBLIC
        ${CMAKE_SOURCE_DIR}/artifacts/ChickenHook/${CMAKE_LIBRARY_ARCHITECTURE}/include/
        )
target_link_libraries(linuxAttack
        # add chickenhook here
        ${CMAKE_SOURCE_DIR}/artifacts/ChickenHook/${CMAKE_LIBRARY_ARCHITECTURE}/lib/libChickenHook.a
        dl
        pthread
        )

set_property(TARGET linuxAttack PROPERTY CXX_STANDARD 11)
set_property(TARGET linuxAttack PROPERTY POSITION_INDEPENDENT_CODE ON)
