find_package(GTest REQUIRED)
find_package(Log4cplus)
FIND_PACKAGE(Boost COMPONENTS system filesystem)


include_directories(
  ${GTEST_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${LOG4CPLUS_INCLUDE_DIR}
  ../src
)

add_executable(${PROJECT_PREFIX}-tests
  test_main.cc
  example.cc
)

target_link_libraries(${PROJECT_PREFIX}-tests
  ${GTEST_LIBRARIES}
  ${Boost_LIBRARIES}
  ${LOG4CPLUS_LIBRARIES}
  utils
)

ADD_DEPENDENCIES(${PROJECT_PREFIX}-tests utils)

target_compile_features(${PROJECT_PREFIX}-tests PRIVATE ${REQUIRED_CXX_FEATURES})

add_test(${PROJECT_PREFIX}tests ${BIN_OUTPUT_DIR}/${PROJECT_PREFIX}-tests)
