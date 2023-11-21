set(SRC_LIST message.cpp)

add_library(my_message STATIC ${SRC_LIST})

target_include_directories(my_message PUBLIC ${CMAKE_SOURCE_DIR}/include)
