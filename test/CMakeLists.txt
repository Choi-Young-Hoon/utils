set(SOURCES main.cpp
            thread.cpp
            logger.cpp
            timer.cpp
            network.cpp
)

set(UTIL_TEST util_test)

#enable_testing() # build/test 폴더 생성됨

add_executable(${UTIL_TEST} ${SOURCES})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(${UTIL_TEST} PRIVATE ${PROJECT_NAME}
                                            GTest::gtest
                                            GTest::gtest_main
                                            GTest::gmock
                                            GTest::gmock_main)