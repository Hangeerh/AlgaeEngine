import Metal
import MetalKit

@_cdecl("_renderer_init")
func renderer_init(nswin_ptr: UnsafeMutableRawPointer)
    -> UnsafeMutableRawPointer
{
    let metalLayer = bridge_metal_layer(nswin_ptr: nswin_ptr)
    let renderer = Renderer(metalLayer: metalLayer)
    let pointer = Unmanaged.passRetained(renderer).toOpaque()
    return pointer
}

@_cdecl("_renderer_deinit")
func renderer_deinit(renderer: UnsafeMutableRawPointer) {
    Unmanaged<Renderer>.fromOpaque(renderer).release()
}

@_cdecl("_renderer_begin_scene")
func renderer_begin_scene(renderer: UnsafeMutableRawPointer) {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    renderer.begin_scene()
}

@_cdecl("_renderer_bind_pipeline")
func renderer_bind_pipeline(
    renderer: UnsafeMutableRawPointer,
    pipeline: UnsafeMutableRawPointer
) {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let pipeline = Unmanaged<MTLRenderPipelineState>.fromOpaque(pipeline)
        .takeUnretainedValue()

    renderer.bind_pipeline(pipeline: pipeline)
}

@_cdecl("_renderer_submit")
func renderer_submit(
    renderer: UnsafeMutableRawPointer,
    vertex_buffer: UnsafeMutableRawPointer,
    index_buffer: UnsafeMutableRawPointer,
    index_count: UInt32,
    uniform_buffer: UnsafeMutableRawPointer
) {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let vertex_buffer = Unmanaged<MTLBuffer>.fromOpaque(vertex_buffer)
        .takeUnretainedValue()
    let index_buffer = Unmanaged<MTLBuffer>.fromOpaque(index_buffer)
        .takeUnretainedValue()
    let uniform_buffer = Unmanaged<MTLBuffer>.fromOpaque(uniform_buffer)
        .takeUnretainedValue()

    renderer.submit(
        vertex_buffer: vertex_buffer,
        index_buffer: index_buffer,
        index_count: index_count,
        uniform_buffer: uniform_buffer
    )
}

@_cdecl("_renderer_end_scene")
func renderer_end_scene(renderer: UnsafeMutableRawPointer) {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    renderer.end_scene()
}

@_cdecl("_renderer_on_window_resize")
func renderer_on_window_resize(
    renderer: UnsafeMutableRawPointer,
    width: UInt32,
    height: UInt32
) {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    renderer.on_window_resize(width: width, height: height)
}

@_cdecl("_renderer_make_buffer")
func renderer_make_buffer(renderer: UnsafeMutableRawPointer, size: Int)
    -> UnsafeMutableRawPointer
{
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let buffer = renderer.make_buffer(size: size)

    return Unmanaged.passRetained(buffer).toOpaque()
}

@_cdecl("_renderer_make_buffer_bytes")
func renderer_make_buffer(
    renderer: UnsafeMutableRawPointer,
    bytes: UnsafeRawPointer,
    size: Int
) -> UnsafeMutableRawPointer {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let buffer = renderer.make_buffer(bytes: bytes, size: size)

    return Unmanaged.passRetained(buffer).toOpaque()
}

@_cdecl("_renderer_make_shader")
func renderer_make_shader(
    renderer: UnsafeMutableRawPointer,
    shader_name: UnsafePointer<Int8>
) -> UnsafeMutableRawPointer {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let shader_name = String(cString: shader_name)
    let shader = renderer.make_shader(shader_name: shader_name)

    return Unmanaged.passRetained(shader).toOpaque()
}

@_cdecl("_release_metal_buffer")
func release_metal_buffer(buffer: UnsafeMutableRawPointer) {
    Unmanaged<MTLBuffer>.fromOpaque(buffer).release()
}

@_cdecl("_mtl_buffer_get_size")
func mtl_buffer_get_size(buffer: UnsafeMutableRawPointer) -> Int {
    let buffer = Unmanaged<MTLBuffer>.fromOpaque(buffer).takeUnretainedValue()
    return buffer.length
}

@_cdecl("_free_metal_shader")
func free_metal_shader(shader: UnsafeMutableRawPointer) {
    Unmanaged<MTLFunction>.fromOpaque(shader).release()
}

@_cdecl("_renderer_make_pipeline")
func renderer_make_pipeline(
    renderer: UnsafeMutableRawPointer,
    vertex_format: UInt32,
    offset: Int,
    buffer_index: Int,
    stride: Int,
    vertex_shader: UnsafeMutableRawPointer,
    fragment_shader: UnsafeMutableRawPointer
) -> UnsafeMutableRawPointer {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let vertex_shader = Unmanaged<MTLFunction>.fromOpaque(vertex_shader)
        .takeUnretainedValue()
    let fragment_shader = Unmanaged<MTLFunction>.fromOpaque(fragment_shader)
        .takeUnretainedValue()

    let format: MTLVertexFormat
    switch vertex_format {
    case 0:
        format = .float
    case 1:
        format = .float2
    case 2:
        format = .float3
    case 3:
        format = .float4
    case 4:
        format = .int
    case 5:
        format = .int2
    case 6:
        format = .int3
    case 7:
        format = .int4
    case 8:
        format = .uint
    case 9:
        format = .uint2
    case 10:
        format = .uint3
    case 11:
        format = .uint4
    case 12:
        format = .half
    case 13:
        format = .half2
    case 14:
        format = .half3
    case 15:
        format = .half4
    case 16:
        format = .short
    case 17:
        format = .short2
    case 18:
        format = .short3
    case 19:
        format = .short4
    case 20:
        format = .ushort
    case 21:
        format = .ushort2
    case 22:
        format = .ushort3
    case 23:
        format = .ushort4
    default:
        format = .float3
    }

    let pipeline = renderer.make_pipeline(
        vertex_format: format,
        offset: offset,
        buffer_index: buffer_index,
        stride: stride,
        vertex_function: vertex_shader,
        fragment_function: fragment_shader
    )

    return Unmanaged.passRetained(pipeline).toOpaque()
}

@_cdecl("_release_metal_pipeline")
func release_metal_pipeline(pipeline: UnsafeMutableRawPointer) {
    Unmanaged<MTLRenderPipelineState>.fromOpaque(pipeline).release()
}
