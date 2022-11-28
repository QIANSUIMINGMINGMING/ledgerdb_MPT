cmake_minimum_required(VERSION 3.24)
project(GpuMPT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -lssl -Wall -Wno-unused-function -fPIC")

find_package(TBB REQUIRED)

set(CRYPTOPP_INCLUDE_DIR "/usr/local/include/cryptopp/*.h")
find_path(CRYPTOPP_INCLUDE_DIR cryptopp/*.h PATHS )
include_directories(${CRYPTOPP_INCLUDE_DIR})

find_library(CRYPTOPP_LIB cryptopp)
message(STATUS "finding ${CRYPTOPP_LIB}")

find_path(ROCKSDB_INCLUDE_DIR rocksdb/db.h PATHS)
include_directories(${ROCKSDB_INCLUDE_DIR})

find_library(ROCKSDB_LIB rocksdb)
message(STATUS "finding ${ROCKSDB_LIB}")

find_library(LZ4_LIB lz4)
message(STATUS "finding ${LZ4_LIB}")

set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include)
set(TEST_PATH ${PROJECT_SOURCE_DIR}/test)

file(GLOB SRC_FILES "src/*.cpp")
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

include_directories(
        PUBLIC ${INC_PATH})

add_executable(MerkleTest ${TEST_PATH}/test_merkle_tree.cpp ${SRC_FILES})
add_executable(MPTTest ${TEST_PATH}/test_mpt.cpp ${SRC_FILES})

target_link_libraries(MerkleTest TBB::tbb ${CRYPTOPP_LIB} ${ROCKSDB_LIB} ${LZ4_LIB} -lpthread -lz -lsnappy -lbz2 -lzstd -ldl)
target_link_libraries(MPTTest TBB::tbb ${CRYPTOPP_LIB} ${ROCKSDB_LIB} ${LZ4_LIB} -lpthread -lz -lsnappy -lbz2 -lzstd -ldl)
# target_compile_options(HashSIMD PUBLIC -maxrregcount 64)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

