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

@_cdecl("_pipeline_desc_init")
func pipeline_desc_init() -> UnsafeMutableRawPointer {
    let pipelineDescriptor = MTLRenderPipelineDescriptor()
    return Unmanaged.passRetained(pipelineDescriptor).toOpaque()
}

@_cdecl("_pipeline_desc_set_vertex_function")
func pipeline_desc_set_vertex_function(
    pd: UnsafeMutableRawPointer,
    vf: UnsafeMutableRawPointer
) {
    let pd = Unmanaged<MTLRenderPipelineDescriptor>.fromOpaque(pd)
        .takeUnretainedValue()
    let vf = Unmanaged<MTLFunction>.fromOpaque(vf).takeUnretainedValue()
    pd.vertexFunction = vf
}

@_cdecl("_pipeline_desc_set_fragment_function")
func pipeline_desc_set_fragment_function(
    pd: UnsafeMutableRawPointer,
    ff: UnsafeMutableRawPointer
) {
    let pd = Unmanaged<MTLRenderPipelineDescriptor>.fromOpaque(pd)
        .takeUnretainedValue()
    let ff = Unmanaged<MTLFunction>.fromOpaque(ff).takeUnretainedValue()
    pd.fragmentFunction = ff
}

@_cdecl("_pipeline_desc_set_vertex_desc")
func pipeline_desc_set_vertex_desc(
    pd: UnsafeMutableRawPointer,
    vd: UnsafeMutableRawPointer
) {
    let pd = Unmanaged<MTLRenderPipelineDescriptor>.fromOpaque(pd)
        .takeUnretainedValue()
    let vd = Unmanaged<MTLVertexDescriptor>.fromOpaque(vd)
        .takeUnretainedValue()
    pd.vertexDescriptor = vd
}

@_cdecl("_vertex_desc_init")
func vertex_desc_init() -> UnsafeMutableRawPointer {
    let vertexDescriptor = MTLVertexDescriptor()
    return Unmanaged.passRetained(vertexDescriptor).toOpaque()
}

@_cdecl("_vertex_desc_set_attribute")
func vertex_desc_set_attribute(
    desc: UnsafeMutableRawPointer,
    index: Int32,
    format: Int32,
    offset: Int32,
    buffer_index: Int32
) {
    let desc = Unmanaged<MTLVertexDescriptor>.fromOpaque(desc)
        .takeUnretainedValue()
    desc.attributes[Int(index)].format = mtlVertexFormat(from: format)
    desc.attributes[Int(index)].offset = Int(offset)
    desc.attributes[Int(index)].bufferIndex = Int(buffer_index)
}

@_cdecl("_vertex_desc_set_layout")
func vertex_desc_set_layout(
    desc: UnsafeMutableRawPointer,
    index: Int32,
    step_function: Int32,
    step_rate: Int32,
    stride: Int32
) {
    let desc = Unmanaged<MTLVertexDescriptor>.fromOpaque(desc)
        .takeUnretainedValue()
    desc.layouts[Int(index)].stepFunction = mtlVertexStepFunction(
        from: step_function)
    desc.layouts[Int(index)].stepRate = Int(step_rate)
    desc.layouts[Int(index)].stride = Int(stride)
}

@_cdecl("_release_metal_pipeline_descriptor")
func release_metal_pipeline_descriptor(
    pipeline_descriptor: UnsafeMutableRawPointer
) {
    Unmanaged<MTLRenderPipelineDescriptor>.fromOpaque(pipeline_descriptor)
        .release()
}

@_cdecl("_release_metal_vertex_descriptor")
func release_metal_vertex_descriptor(vertex_descriptor: UnsafeMutableRawPointer) {
    Unmanaged<MTLVertexDescriptor>.fromOpaque(vertex_descriptor).release()
}

@_cdecl("_free_metal_shader")
func free_metal_shader(shader: UnsafeMutableRawPointer) {
    Unmanaged<MTLFunction>.fromOpaque(shader).release()
}

@_cdecl("_renderer_make_pipeline")
func renderer_make_pipeline(
    renderer: UnsafeMutableRawPointer,
    pipeline_descriptor: UnsafeMutableRawPointer
) -> UnsafeMutableRawPointer {
    let renderer = Unmanaged<Renderer>.fromOpaque(renderer)
        .takeUnretainedValue()
    let pipelineDescriptor = Unmanaged<MTLRenderPipelineDescriptor>
        .fromOpaque(pipeline_descriptor).takeUnretainedValue()

    let pipeline = renderer.make_pipeline(
        pipelineDescriptor: pipelineDescriptor)

    return Unmanaged.passRetained(pipeline).toOpaque()
}

@_cdecl("_release_metal_pipeline")
func release_metal_pipeline(pipeline: UnsafeMutableRawPointer) {
    Unmanaged<MTLRenderPipelineState>.fromOpaque(pipeline).release()
}

private func mtlVertexFormat(from format: Int32) -> MTLVertexFormat {
    return MTLVertexFormat(rawValue: UInt(format)) ?? .float3
}

private func mtlVertexStepFunction(
    from step_function: Int32
) -> MTLVertexStepFunction {
    switch step_function {
    case 0:
        return .constant
    case 1:
        return .perVertex
    case 2:
        return .perInstance
    case 3:
        return .perPatch
    case 4:
        return .perPatchControlPoint
    default:
        return .perVertex
    }
}
