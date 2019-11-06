cmake_minimum_required(VERSION 3.4.1)

add_library (native-lib SHARED interface.cpp)

target_link_libraries(native-lib
        ${PROJECT_NAME}
        )