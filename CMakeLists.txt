CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(PROJECT_PREFIX "template")
PROJECT(${PROJECT_PREFIX})

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Simple stuff to keep Visual Studio from putting the files in weird locations
SET(BIN_OUTPUT_DIR ${${PROJECT_PREFIX}_BINARY_DIR}/bin)
SET(LIB_OUTPUT_DIR ${${PROJECT_PREFIX}_BINARY_DIR}/lib)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})

include(CheckCXXCompilerFlag)

SET(Boost_USE_STATIC_LIBS ON)

SET(REQUIRED_CXX_FEATURES
  cxx_auto_type
  cxx_constexpr
  cxx_deleted_functions
  cxx_lambdas
  cxx_nullptr
  cxx_override
  cxx_range_for
  cxx_variadic_templates
)

ADD_DEFINITIONS(-DPACKAGE_NAME=${PROJECT_PREFIX})
add_definitions(-DBOOST_THREAD_PROVIDES_FUTURE)
add_definitions(-DBOOST_THREAD_PROVIDES_FUTURE_CONTINUATION)

macro(AddCXXFlagIfSupported flag test)
  check_cxx_compiler_flag(${flag} ${test})
  if (${${test}})
    message("adding ${flag}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
  endif()
endmacro()

if ("Ninja" STREQUAL ${CMAKE_GENERATOR})
  AddCXXFlagIfSupported(-fcolor-diagnostics COMPILER_SUPPORTS_fcolor-diagnostics)
endif()

#-----------------------------------------------------------------------------
# Enable ccache if not already enabled by symlink masquerading and if no other
# CMake compiler launchers are already defined
#-----------------------------------------------------------------------------
find_program(CCACHE_EXECUTABLE ccache)
mark_as_advanced(CCACHE_EXECUTABLE)
if (CCACHE_EXECUTABLE)
  foreach (LANG C CXX)
    if (NOT DEFINED CMAKE_${LANG}_COMPILER_LAUNCHER AND NOT CMAKE_${LANG}_COMPILER MATCHES ".*/ccache$")
      message(STATUS "Enabling ccache for ${LANG}")
      set(CMAKE_${LANG}_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE} CACHE STRING "")
    endif()
  endforeach()
endif()

ENABLE_TESTING()

include_directories(include)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
