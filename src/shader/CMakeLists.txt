add_library(shader STATIC shader.cpp)

target_link_libraries(shader PRIVATE glfw)

target_include_directories(shader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(shader PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(shader PRIVATE "SHADER_DIR=\"${CMAKE_SOURCE_DIR}/src/shader\"")
