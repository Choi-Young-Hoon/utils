set(SOURCES main.cpp
            test.cpp)

set(UTIL_TEST util_test)

enable_testing() # build/test 폴더 생성됨

add_executable(${UTIL_TEST} ${SOURCES})

find_package(GTEST REQUIRED)
target_link_libraries(${UTIL_TEST} PRIVATE ${PROJECT_NAME}
        GTEST::gtest
        GTEST::gtest_main
        GTEST::gmock
        GTEST::gmock_main)


install(TARGETS ${UTIL_TEST}
        DESTINATION ${INSTALL_DIR}/bin)