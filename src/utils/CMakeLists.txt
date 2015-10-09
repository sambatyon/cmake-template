find_package(Log4cplus)
FIND_PACKAGE(Boost COMPONENTS system filesystem)

FILE(GLOB_RECURSE utils_src *.cc)
FILE(GLOB_RECURSE utils_hdr *.hh)

SOURCE_GROUP("Header Files" FILES ${utils_hdr})
SOURCE_GROUP("Source Files" FILES ${utils_src})

INCLUDE_DIRECTORIES(
  ${Boost_INCLUDE_DIRS}
  ${LOG4CPLUS_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ..
)

ADD_LIBRARY(utils STATIC ${utils_src} ${utils_hdr})

target_compile_features(utils PRIVATE ${REQUIRED_CXX_FEATURES})
