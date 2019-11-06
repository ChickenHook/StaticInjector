
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source _original_code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        ${PROJECT_NAME}

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        BinaryEditor.cpp
        platforms/IBinary.cpp
        platforms/linux/Elf.cpp
        platforms/darwin/Macho.cpp
        tools/HexDump.cpp
        tools/LoggingCallback.cpp)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/chickenHook/staticInjector/>
        $<INSTALL_INTERFACE:include/chickenHook/staticInjector>  # <prefix>/include/mylib
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        include/
        ./
        )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)