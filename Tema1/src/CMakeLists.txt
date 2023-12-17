cmake_minimum_required(VERSION 3.10)

project(MyBank VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(money_transfer_service)
add_subdirectory(sha256)

add_executable(MyBank main.cpp)

target_link_libraries(MyBank PUBLIC money_transfer_service)

target_include_directories(MyBank PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/money_transfer_service"
                           )