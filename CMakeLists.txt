cmake_minimum_required(VERSION 2.5)
project(silly-netlib)

# 最终编译为.so动态库的位置
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --std=c++11")


# 定义参与编译的源文件
aux_source_directory(. SRC_LIST)

# 编译生成动态库
add_library(silly-netlib SHARED ${SRC_LIST})
