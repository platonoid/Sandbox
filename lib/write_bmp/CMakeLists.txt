add_library(writebmp write_bmp.cpp write_bmp.h)
target_link_libraries(writebmp PRIVATE vec)
target_include_directories(writebmp PUBLIC ${PROJECT_SOURCE_DIR})