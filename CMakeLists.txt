cmake_minimum_required(VERSION 3.4.1)

project(StaticInjector
        VERSION 1.0
        LANGUAGES CXX C
        )


add_subdirectory(src)
#add_subdirectory(test)
IF (ANDROID)
    add_subdirectory(androidTest) # with linux we include linuxTest here!
endif (ANDROID)

if (UNIX AND NOT APPLE AND NOT ANDROID)
    set(LINUX true)
ENDIF ()
IF (LINUX)
    add_subdirectory(linuxTest)
ENDIF (LINUX)