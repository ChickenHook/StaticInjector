cmake_minimum_required(VERSION 3.4.1)

add_executable (linuxTest main.cpp)

target_link_libraries(linuxTest
        ${PROJECT_NAME}
        )

set_property(TARGET linuxTest PROPERTY CXX_STANDARD 11)