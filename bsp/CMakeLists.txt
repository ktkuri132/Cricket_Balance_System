include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/h723)

include_directories(${CMAKE_SOURCE_DIR}/h723_core)
include_directories(${CMAKE_SOURCE_DIR}/h723_core/STM32H7xx_HAL_Driver/inc)

include_directories(gpio)
# 得到当前文件名
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 添加源文件
file(GLOB_RECURSE ${DIR_NAME}_Source
        ./*.c
        h723/*.c
)

add_library(${DIR_NAME}lib ${${DIR_NAME}_Source})

target_link_libraries(${DIR_NAME}lib h723_corelib)

