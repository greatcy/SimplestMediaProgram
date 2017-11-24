project(SimpleYuv)

set(src_list src/main.c src/yuv.c src/rgb.c)

#message(STATUS "Begin build yuv "${SimpleYuv_SOURCE_DIR})

add_executable(simpleyuv ${src_list})
