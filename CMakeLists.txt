project(freertos)
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(TargetName ${CMAKE_PROJECT_NAME})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_CONFIG_DIR ${PROJECT_SOURCE_DIR}/config)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${TargetName})
target_compile_options(
  ${TargetName}
  PUBLIC
  "-Wall"
  "-O0"
)

find_package(Threads)

set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib)
set(COMPONENT_PATH ${LIB_PATH}/FreeRTOS/FreeRTOS)
set(POSIX_PORT_PATH ${LIB_PATH}/freertos-addons/Linux/portable/GCC/Linux)
set(CONFIG_PATH ${PROJECT_SOURCE_DIR})
SET(PROJECT_INCLUDES
  ${COMPONENT_PATH}/Source/include
  ${POSIX_PORT_PATH}
  ${CONFIG_PATH}
)

include_directories(${PROJECT_INCLUDES})

if(OFF)
file(GLOB FREERTOS_SOURCES
    "${PROJECT_SOURCE_DIR}/lib/FreeRTOS_Kernel/*.c"
    "${PROJECT_SOURCE_DIR}/lib/FreeRTOS_Kernel/portable/GCC/Posix/*.c"
    "${PROJECT_SOURCE_DIR}/lib/FreeRTOS_Kernel/portable/MemMang/*.c")
file(GLOB GFX_SOURCES "${PROJECT_SOURCE_DIR}/lib/Gfx/*.c")
file(GLOB ASYNC_SOURCES "${PROJECT_SOURCE_DIR}/lib/AsyncIO/*.c")
file(GLOB SIMULATOR_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

SET(PROJECT_SOURCES
    ${SIMULATOR_SOURCES} ${FREERTOS_SOURCES} ${GFX_SOURCES} ${ASYNC_SOURCES}
)
endif()

set(PROJECT_LIBRARIES
  m
  ${CMAKE_THREAD_LIBS_INIT}
  rt
)

#include(${CMAKE_MODULE_PATH}/tests.cmake)
target_link_libraries(${TargetName} ${PROJECT_LIBRARIES})
set(PROJECT_SOURCES
	${COMPONENT_PATH}/Source/croutine.c
	${COMPONENT_PATH}/Source/event_groups.c
	${COMPONENT_PATH}/Source/list.c
	${COMPONENT_PATH}/Source/queue.c
	${COMPONENT_PATH}/Source/stream_buffer.c
	${COMPONENT_PATH}/Source/tasks.c
	${COMPONENT_PATH}/Source/timers.c
	${COMPONENT_PATH}/Source/portable/MemMang/heap_4.c
	${POSIX_PORT_PATH}/port.c
  ${PROJECT_SOURCE_DIR}/main.c
)
target_sources(${TargetName} PUBLIC ${PROJECT_SOURCES})

#include(${CMAKE_MODULE_PATH}/init_local_projects.cmake)
