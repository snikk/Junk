add_library (Hello hello.cpp)
message("PROJECT_SOURCE_DIR in Hello points to " ${PROJECT_SOURCE_DIR})
target_include_directories (Hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
