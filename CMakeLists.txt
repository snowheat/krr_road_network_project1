cmake_minimum_required(VERSION 3.9)
project(clion_project1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES_TRUE)

add_executable(clion_project1 main.cpp)

set(SFML_ROOT "C:/Program Files (x86)/CodeBlocks/sfml")

#https://stackoverflow.com/questions/28243397/issues-configuring-clion-cmake-and-sfml
#https://stackoverflow.com/questions/48044025/sfml-doesnt-work-with-clion-on-windows

set(CMAKE_MODULE_PATH "C:/Program Files (x86)/CodeBlocks/sfml/cmake/Modules/")
find_package(SFML 2 REQUIRED graphics network audio window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()