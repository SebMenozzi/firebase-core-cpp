set(OPT_FLAGS, "-Ofast")

# SETUP
cmake_minimum_required(VERSION 3.12)
project(core)

# BUILD OPTIONS
set (CMAKE_CXX_STANDARD 11)

# -Wall -Werror -Wextra -pedantic
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -fsanitize=address")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Add gRPC
message(STATUS "Using gRPC via add_subdirectory (FetchContent).")
include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.33.2
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

# Add Firebase
add_subdirectory("firebase_cpp_sdk" bin/ EXCLUDE_FROM_ALL)

# Add sources
file(GLOB_RECURSE SRC_PROTO
    "src/*.cc"
)

# Directories containing headers must be specified in the include_directories()
include_directories(src)

add_executable(core)
target_sources(core PRIVATE "src/main.cc" ${SRC_PROTO})

set(firebase_libs firebase_auth firebase_app)

target_link_libraries(core 
  PRIVATE
  grpc++ 
)


target_link_libraries(core
  PRIVATE
  "${firebase_libs}" 
  pthread
  "-framework CoreFoundation"
  "-framework Foundation"
  "-framework Security"
)
