cmake_minimum_required (VERSION 3.6)

project (utils)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS -Wall)
set (CMAKE_CXX_FLAGS_RELEASE -O3)
set (CMAKE_CXX_FLAGS_DEBUG -g)

set (INSTALL_DIR ${CMAKE_SOURCE_DIR}/build)
set (INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories (${INCLUDE_DIR}
                     thirdparty/googletest/googletest/include)

add_library (${PROJECT_NAME})

add_subdirectory (thirdparty/googletest)
add_subdirectory (src)
add_subdirectory (test)

install (TARGETS ${PROJECT_NAME}
         DESTINATION ${INSTALL_DIR}/lib)
install (DIRECTORY ${INCLUDE_DIR}
         DESTINATION ${INSTALL_DIR}
         FILES_MATCHING PATTERN "*.hpp")
