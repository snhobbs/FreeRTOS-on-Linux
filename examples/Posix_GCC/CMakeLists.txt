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
)

target_compile_definitions(
  ${TargetName}
  PUBLIC
  projCOVERAGE_TEST=1
  )
find_package(Threads)

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)
set(COMPONENT_PATH ${LIB_PATH}/FreeRTOS/FreeRTOS)
set(PROJECT_SOURCE_DIR ${COMPONENT_PATH}/Demo/Posix_GCC)
set(POSIX_PORT_PATH ${COMPONENT_PATH}/Source/portable/ThirdParty/GCC/Posix)
SET(PROJECT_INCLUDES
  ${PROJECT_SOURCE_DIR}
  ${COMPONENT_PATH}/Source/include
  ${COMPONENT_PATH}/Demo/Common/include
  ${POSIX_PORT_PATH}
  ${POSIX_PORT_PATH}/utils
  ${COMPONENT_PATH}-Plus
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-Trace/Include
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-TCP/include
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-TCP/portable/Compiler/GCC
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-TCP/portable/NetworkInterface/linux/
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
	${COMPONENT_PATH}/Source/croutine.c
	${COMPONENT_PATH}/Source/event_groups.c
	${COMPONENT_PATH}/Source/list.c
	${COMPONENT_PATH}/Source/queue.c
	${COMPONENT_PATH}/Source/stream_buffer.c
	${COMPONENT_PATH}/Source/tasks.c
	${COMPONENT_PATH}/Source/timers.c
  ${COMPONENT_PATH}/Source/portable/MemMang/heap_3.c
  #${COMPONENT_PATH}/Source/portable/MemMang/heap_1.c
  # posix port
	${POSIX_PORT_PATH}/port.c
	${POSIX_PORT_PATH}/utils/wait_for_event.c
  #Demo
  ${PROJECT_SOURCE_DIR}/main.c
  ${PROJECT_SOURCE_DIR}/SimpleTCPEchoServer.c
  ${PROJECT_SOURCE_DIR}/console.c
  ${PROJECT_SOURCE_DIR}/main_full.c
  ${PROJECT_SOURCE_DIR}/TCPEchoClient_SingleTasks.c
  ${PROJECT_SOURCE_DIR}/main.c
  ${PROJECT_SOURCE_DIR}/main_networking.c
  ${PROJECT_SOURCE_DIR}/code_coverage_additions.c
  ${PROJECT_SOURCE_DIR}/main_blinky.c
  ${PROJECT_SOURCE_DIR}/run-time-stats-utils.c

  ${COMPONENT_PATH}/Demo/Common/Minimal/StaticAllocation.c
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-Trace/trcKernelPort.c
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-Trace/trcSnapshotRecorder.c
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-Trace/trcStreamingRecorder.c
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-Trace/streamports/File/trcStreamingPort.c
  ${COMPONENT_PATH}-Plus/Source/FreeRTOS-Plus-Trace/

)
target_sources(${TargetName} PUBLIC ${PROJECT_SOURCES})

#include(${CMAKE_MODULE_PATH}/init_local_projects.cmake)
