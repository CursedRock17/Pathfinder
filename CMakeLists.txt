project(Pathfinder VERSION 1.0)
cmake_minimum_required(3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(${PROJECT_NAME} main.cpp) 

add_subdirectory(src)
add_subdirectory(src/Graphics)

target_include_directories(${PROJECT_NAME}
PUBLIC
"${PROJECT_SOURCE_DIR"
"${PROJECT_SOURCE_DIR}/src"
"${PROJECT_SOURCE_DIR}/src/Graphics"
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
Graphics
)

