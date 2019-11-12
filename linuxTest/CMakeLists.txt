cmake_minimum_required(VERSION 3.4.1)

add_executable (staticInjector
        main.cpp
        )

target_link_libraries(staticInjector
        ${PROJECT_NAME}
        )

set_property(TARGET staticInjector PROPERTY CXX_STANDARD 11)

add_subdirectory(exampleAttack)
add_subdirectory(firefoxAttack)
add_subdirectory(skypeAttack)

set_property(TARGET staticInjector PROPERTY POSITION_INDEPENDENT_CODE ON)
