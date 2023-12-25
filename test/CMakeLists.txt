set(SOURCES main.cpp
            thread.cpp
            logger.cpp
)

set(UTIL_TEST util_test)

enable_testing() # build/test 폴더 생성됨

add_executable(${UTIL_TEST} ${SOURCES})

target_link_libraries(${UTIL_TEST} PRIVATE ${PROJECT_NAME}
                                            gtest
                                            gtest_main
                                            gmock
                                            gmock_main)

install (TARGETS ${UTIL_TEST}
         DESTINATION ${INSTALL_DIR}/test)
