add_library(intogif intogif.cpp intogif.h)
target_link_libraries(intogif PRIVATE writebmp vec)

target_include_directories(intogif PUBLIC ${PROJECT_SOURCE_DIR})