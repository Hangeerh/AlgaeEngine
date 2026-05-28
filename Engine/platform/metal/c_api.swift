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

@_cdecl("_renderer_submit")
func renderer_submit(
    renderer: UnsafeMutableRawPointer,
    vertex_shader: UnsafeMutableRawPointer,
    fragment_shader: UnsafeMutableRawPointer,
    vertex_buffer: UnsafeMutableRawPointer,
    index_buffer: UnsafeMutableRawPointer,
    index_count: UInt32
) {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()

    let vertex_shader = Unmanaged<MTLFunction>.fromOpaque(vertex_shader)
        .takeUnretainedValue()
    let fragment_shader = Unmanaged<MTLFunction>.fromOpaque(fragment_shader)
        .takeUnretainedValue()

    let vertex_buffer = Unmanaged<MTLBuffer>.fromOpaque(vertex_buffer)
        .takeUnretainedValue()
    let index_buffer = Unmanaged<MTLBuffer>.fromOpaque(index_buffer)
        .takeUnretainedValue()

    renderer.submit(
        vertex_function: vertex_shader,
        fragment_function: fragment_shader,
        vertex_buffer: vertex_buffer,
        index_buffer: index_buffer,
        index_count: index_count
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
) {}

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
