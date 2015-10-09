find_package(Log4cplus)
FIND_PACKAGE(Boost COMPONENTS system filesystem)

FILE(GLOB_RECURSE server_src *.cc)
FILE(GLOB_RECURSE server_hdr *.hh)

SOURCE_GROUP("Header Files" FILES ${server_hdr})
SOURCE_GROUP("Source Files" FILES ${server_src})

INCLUDE_DIRECTORIES(
  ${Boost_INCLUDE_DIRS}
  ${LOG4CPLUS_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ..
)

ADD_EXECUTABLE(${PROJECT_PREFIX}-server
  ${server_src}
  ${server_hdr}
)

TARGET_LINK_LIBRARIES(${PROJECT_PREFIX}-server
  utils
  ${Boost_LIBRARIES}
  ${LOG4CPLUS_LIBRARIES}
)

ADD_DEPENDENCIES(${PROJECT_PREFIX}-server utils)

target_compile_features(${PROJECT_PREFIX}-server PRIVATE ${REQUIRED_CXX_FEATURES})
