# Android NDK r16 support:
# * https://gitlab.kitware.com/cmake/cmake/issues/17253
cmake_minimum_required(VERSION 3.9.2)

# For Android Studio we will force generated toolchain
if(HELLOJNI_ANDROID_STUDIO)
  set(gen_toolchain "${CMAKE_CURRENT_BINARY_DIR}/generated/toolchain.cmake")
  file(TO_CMAKE_PATH "${CMAKE_TOOLCHAIN_FILE}" CMAKE_TOOLCHAIN_FILE_CMAKE_PATH)
  configure_file(
      "${CMAKE_CURRENT_LIST_DIR}/cmake/template/toolchain.cmake.in"
      "${gen_toolchain}"
      @ONLY
  )
  set(CMAKE_TOOLCHAIN_FILE "${gen_toolchain}" CACHE PATH "" FORCE)
endif()

# Example of stepping into external sources.
# USE CAREFULLY, please check documentation:
# * https://docs.hunter.sh/en/latest/reference/user-variables.html#hunter-keep-package-sources
option(HUNTER_KEEP_PACKAGE_SOURCES "Keep third party sources" ON)

option(HUNTER_STATUS_DEBUG "Print debug info" ON)

include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.3.tar.gz"
    SHA1 "2c421912930d183c24512590014f955ff073424b"
)

project(hello-jni)

option(CMAKE_VERBOSE_MAKEFILE "Verbose makefile" ON)

add_library(hello-jni SHARED hello-jni.cpp)

# If CMAKE_DEBUG_POSTFIX is emtpy Hunter will initialize with 'd'.
# We have to explicitly set DEBUG_POSTFIX to simplify library
# load from Java code.
set_target_properties(hello-jni PROPERTIES DEBUG_POSTFIX "")

# https://docs.hunter.sh/en/latest/packages/pkg/md5.html
hunter_add_package(md5)
find_package(md5 CONFIG REQUIRED)

target_link_libraries(hello-jni PUBLIC md5::md5)
