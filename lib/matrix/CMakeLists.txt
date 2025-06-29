add_library(matrix matrix.h matrix.cpp)
target_link_libraries(matrix PRIVATE vec)

target_include_directories(matrix PUBLIC ${PROJECT_SOURCE_DIR})