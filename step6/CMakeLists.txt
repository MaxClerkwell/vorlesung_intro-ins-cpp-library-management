cmake_minimum_required(VERSION 3.14)
project(library_test)

include(FetchContent)

FetchContent_Declare(
    vorlesungs_cpplib
    GIT_REPOSITORY https://github.com/MaxClerkwell/vorlesungs_cpplib.git
)

FetchContent_MakeAvailable(vorlesungs_cpplib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} vorlesungs_cpplib)