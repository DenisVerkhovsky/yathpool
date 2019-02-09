cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(yathpool CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -Werror=return-type")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file("${CMAKE_SOURCE_DIR}/yathpool.pc.cmake"
               "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc")

set(THREAD_POOL_HEADERS
    src/yathpool.h
    )

set(THREAD_POOL_SOURCES
    src/yathpool.cpp
    )

add_library(yathpool SHARED
    ${THREAD_POOL_SOURCES})

install(TARGETS yathpool
        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")

install(FILES        ${THREAD_POOL_HEADERS}
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/yathpool")

install(FILES        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")
