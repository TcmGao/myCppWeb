cmake_minimum_required(VERSION 3.5.0)
project(myCppWebServer VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(CTest)
enable_testing()

set(SRC_LIST main.cpp)
add_executable(webServer ${SRC_LIST})

add_subdirectory(my_function)
target_link_libraries(webServer my_message)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)