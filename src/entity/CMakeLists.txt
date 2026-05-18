add_library(entity STATIC entity.cpp)

target_link_libraries(entity PRIVATE glfw)
target_link_libraries(entity PRIVATE mesh)
target_link_libraries(entity PRIVATE shader)

target_include_directories(entity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(entity PUBLIC ${CMAKE_SOURCE_DIR}/include)
