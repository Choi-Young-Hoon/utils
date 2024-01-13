cmake_minimum_required (VERSION 3.6)

project (utils)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS -Wall)
set (CMAKE_CXX_FLAGS_RELEASE -O3)
set (CMAKE_CXX_FLAGS_DEBUG -g)

set (UTILS_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/utils)
set (UTILS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library (${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${UTILS_INCLUDE_DIR})

add_subdirectory (src)
add_subdirectory (test)

install (TARGETS ${PROJECT_NAME}
         DESTINATION ${UTILS_INSTALL_DIR}/lib)
install (DIRECTORY ${INCLUDE_DIR}
         DESTINATION ${UTILS_INSTALL_DIR}
         FILES_MATCHING PATTERN "*.hpp")
