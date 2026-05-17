add_library(camera STATIC camera.cpp)

target_link_libraries(camera PRIVATE glfw)

target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(camera PUBLIC ${CMAKE_SOURCE_DIR}/include)
