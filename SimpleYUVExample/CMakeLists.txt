project(SimpleYuv)

set(src_list src/main.c)

#message(STATUS "Begin build yuv "${SimpleYuv_SOURCE_DIR})

add_executable(simpleyuv ${src_list})
