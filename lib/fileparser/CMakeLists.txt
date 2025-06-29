add_library(fileparser fileparser.cpp fileparser.h)
target_link_libraries(fileparser PRIVATE vec)

target_include_directories(fileparser PUBLIC ${PROJECT_SOURCE_DIR})
