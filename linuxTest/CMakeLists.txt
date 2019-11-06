cmake_minimum_required(VERSION 3.4.1)

add_executable (linuxTest
        main.cpp
        symbolHook.cpp)

target_link_libraries(linuxTest
        ${PROJECT_NAME}
        )

set_property(TARGET linuxTest PROPERTY CXX_STANDARD 11)

add_subdirectory(exampleAttack)

set_property(TARGET linuxTest PROPERTY POSITION_INDEPENDENT_CODE ON)
