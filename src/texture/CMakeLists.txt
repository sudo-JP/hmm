add_library(texture STATIC texture.cpp)

target_link_libraries(texture PRIVATE glfw)

target_include_directories(texture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(texture PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(texture PRIVATE "IMAGE_DIR=\"${CMAKE_SOURCE_DIR}/src/texture\"")
