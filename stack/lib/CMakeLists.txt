add_library(
    lib STATIC "src/clist.c" "src/cstack.c"
)

target_include_directories(
    lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)