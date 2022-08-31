add_library(Graphics Graphics.cpp)

find_package(glad REQUIRED)

target_link_libraries(Graphics
PUBLIC
glad::glad

)