# 添加头文件路径
include_directories(${CMAKE_SOURCE_DIR}/h723_core)
include_directories(${CMAKE_SOURCE_DIR}/h723_core/STM32H7xx_HAL_Driver/inc)
include_directories(${CMAKE_SOURCE_DIR}/bsp)
include_directories(${CMAKE_SOURCE_DIR}/include)
# 得到当前文件名
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 添加源文件
file(GLOB_RECURSE ${DIR_NAME}_Source
        Dev/*.c
)


add_library(${DIR_NAME}lib ${${DIR_NAME}_Source})

target_link_libraries(${DIR_NAME}lib bsplib h723_corelib)

# 添加当前头文件路径
target_include_directories(${DIR_NAME}lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${DIR_NAME}lib PRIVATE ${CMAKE_SOURCE_DIR})


