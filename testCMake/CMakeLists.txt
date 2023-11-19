# cmake 版本
# cmake -H. -Bbuild和在build目录下使用cmake ..效果相同
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# 项目名称，这会定义PROJECT_BINARY_DIR ->构建目录
# 和PROJECT_SOURCE_DIR->CMakeLists.txt所在目录
project(myCppWebServer LANGUAGES CXX)

set(SRC_LIST main.cpp)

add_executable(webServer ${SRC_LIST})

