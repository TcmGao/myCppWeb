cmake_minimum_required(VERSION 3.0.0)
project(myCppWebServer VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(CTest)
enable_testing()

# include_directories(include/my_function)
# aux_source_directory(src SRC_LIST)
# aux_source_directory(src/my_function TEXT_LIST)

#add_subdirectory(${PROJECT_SOURCE_DIR}/src)
set(SRC_LIST main.cpp)
add_executable(webServer ${SRC_LIST})

add_subdirectory(my_function)
target_link_libraries(webServer my_message)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)