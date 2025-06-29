add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE writebmp 
                                                matrix
                                                parser
                                                vec
                                                fileparser
                                                intogif)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})