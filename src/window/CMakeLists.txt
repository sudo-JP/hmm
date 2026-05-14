add_library(window STATIC window.cpp)

target_link_libraries(window PRIVATE glfw)

target_include_directories(window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(window PUBLIC ${CMAKE_SOURCE_DIR}/include)
