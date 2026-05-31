
cmake_minimum_required(VERSION 3.16)
project(AlgaeEngine LANGUAGES CXX)

include(cmake/swift.cmake)

add_library(AlgaeEngine 
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Engine.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/renderer/renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/renderer/buffers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/renderer/shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/renderer/vertex_array.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalRenderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/metal_buffers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/metal_render_pipeline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/metal_shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/metal_vertex_array.cpp
)

target_include_directories(AlgaeEngine PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

target_include_directories(AlgaeEngine PRIVATE
  ${CMAKE_SOURCE_DIR}/thirdparty/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

if(APPLE)
  compile_swift_sources(AlgaeEngine
    MODULE_NAME EngineSwift
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalRenderer.swift
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/c_api.swift
    COMPILE_FLAGS
      -Xcc -I${CMAKE_CURRENT_SOURCE_DIR}
      -Xcc -I${CMAKE_SOURCE_DIR}/thirdparty/glfw/include
  )

  target_link_swift_libraries(AlgaeEngine)
endif()
