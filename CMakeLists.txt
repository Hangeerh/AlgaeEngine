cmake_minimum_required(VERSION 3.16)
project(AlgaeEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include(cmake/swift.cmake)

set(GLFW_BUILD_DOCS OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw)

add_library(AlgaeEngine 
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Core/Application.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Core/Layer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Core/LayerStack.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Core/Window.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Renderer/RenderAPI.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Renderer/Renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Renderer/Buffers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Renderer/Shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/Renderer/VertexArray.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/IO/IOBuffer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/IO/IOAPI.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Algae/IO/IO.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/MetalRenderAPI.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/MetalBuffers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/MetalRenderPipeline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/MetalShader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/MetalVertexArray.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/OSX/OSXWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/OSX/OSXIOAPI.cpp
)

target_include_directories(AlgaeEngine PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

target_include_directories(AlgaeEngine PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

target_link_libraries(AlgaeEngine PUBLIC glfw)

if(APPLE)
  compile_swift_sources(AlgaeEngine
    MODULE_NAME EngineSwift
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/MetalRenderer.swift
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/Metal/c_api.swift
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform/OSX/OSXIOAPI.swift
    COMPILE_FLAGS
      -Xcc -I${CMAKE_CURRENT_SOURCE_DIR}
      -Xcc -I${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/include
  )

  target_link_swift_libraries(AlgaeEngine)
endif()
