project(freertos)
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(TargetName ${CMAKE_PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(${TargetName})
target_compile_options(
  ${TargetName}
  PUBLIC
  "-Wall"
  "-O0"
  -g3
)

find_package(Threads)

set(COMMON_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../common)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)
set(COMPONENT_PATH ${LIB_PATH}/FreeRTOS/FreeRTOS)
set(POSIX_PORT_PATH ${COMPONENT_PATH}/Source/portable/ThirdParty/GCC/Posix)
set(CONFIG_PATH ${PROJECT_SOURCE_DIR})
SET(PROJECT_INCLUDES
  ${COMPONENT_PATH}/Demo/Common/include
  ${COMMON_SOURCE}
  ${PROJECT_SOURCE_DIR}
  ${COMPONENT_PATH}/Source/include
  ${POSIX_PORT_PATH}
	${POSIX_PORT_PATH}/utils
  ${CONFIG_PATH}
)

include_directories(${PROJECT_INCLUDES})

set(PROJECT_LIBRARIES
  m
  ${CMAKE_THREAD_LIBS_INIT}
  rt
)

#include(${CMAKE_MODULE_PATH}/tests.cmake)
target_link_libraries(${TargetName} ${PROJECT_LIBRARIES})
set(PROJECT_SOURCES
  #${COMPONENT_PATH}/Source/croutine.c
	${COMPONENT_PATH}/Source/event_groups.c
	${COMPONENT_PATH}/Source/list.c
	${COMPONENT_PATH}/Source/queue.c
	${COMPONENT_PATH}/Source/stream_buffer.c
	${COMPONENT_PATH}/Source/tasks.c
	${COMPONENT_PATH}/Source/timers.c
	${POSIX_PORT_PATH}/port.c
	${POSIX_PORT_PATH}/utils/wait_for_event.c
  ${PROJECT_SOURCE_DIR}/main.c
  ${PROJECT_SOURCE_DIR}/StreamBufferInterrupt.c
  ${COMMON_SOURCE}/hooks.c
  ${COMPONENT_PATH}/Demo/Common/Minimal/StaticAllocation.c
)
target_sources(${TargetName} PUBLIC ${PROJECT_SOURCES})

#include(${CMAKE_MODULE_PATH}/init_local_projects.cmake)
