
cmake_minimum_required(VERSION 3.16)
project(AlgaeEngine LANGUAGES CXX)

include(cmake/swift.cmake)

add_library(AlgaeEngine 
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Engine.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/Renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/Buffers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/Shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/VertexArray.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalRenderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalBuffers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalRenderPipeline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalShader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/platform/metal/MetalVertexArray.cpp
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
