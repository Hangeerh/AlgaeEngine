add_executable(RendererTests
  ${CMAKE_CURRENT_SOURCE_DIR}/RendererTests.cpp
)

target_link_libraries(RendererTests PRIVATE Engine glfw)

if(APPLE)
    target_link_libraries(RendererTests PRIVATE
        "-framework MetalKit"
        "-framework Metal"
        "-framework QuartzCore"
        "-framework AppKit"
    )
    
    # Needs a bundle structure to access default.metallib embedded by 3DGame
    # Or we can link against the compiled shader
    set_target_properties(RendererTests PROPERTIES
      MACOSX_BUNDLE TRUE
    )
    
    # We must also attach the Metal shaders to the test bundle
    compile_metal_shaders(RendererTests ${CMAKE_SOURCE_DIR}/src/shader.metal)
endif()
