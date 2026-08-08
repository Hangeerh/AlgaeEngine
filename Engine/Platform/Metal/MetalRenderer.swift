import AppKit
import Foundation
import Metal
import MetalKit

func bridge_metal_layer(nswin_ptr: UnsafeMutableRawPointer) -> CAMetalLayer {
    let nswin = Unmanaged<NSWindow>.fromOpaque(nswin_ptr).takeUnretainedValue()
    guard let contentView = nswin.contentView else {
        fatalError()
    }
    let metalLayer = CAMetalLayer()

    contentView.wantsLayer = true
    contentView.layer = metalLayer

    metalLayer.contentsScale = nswin.backingScaleFactor

    return metalLayer
}

class Renderer {
    private let device: MTLDevice
    private let commandQueue: MTLCommandQueue
    private var pipelineState: MTLRenderPipelineState!
    private let pixelFormat: MTLPixelFormat
    private let clearColor: MTLClearColor
    private let layer: CAMetalLayer
    private let library: MTLLibrary

    //Persistent state for current frame
    private var commandBuffer: MTLCommandBuffer?
    private var encoder: MTLRenderCommandEncoder?
    private var drawable: CAMetalDrawable?
    private var renderPassDescriptor: MTLRenderPassDescriptor?

    public init(metalLayer: CAMetalLayer) {
        self.layer = metalLayer

        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("Failed to create metal device")
        }
        self.device = device
        self.layer.device = device

        guard let commandQueue = self.device.makeCommandQueue() else {
            print("Failed to create commandQueue")
            exit(-1)
        }
        self.commandQueue = commandQueue

        self.pixelFormat = MTLPixelFormat.bgra8Unorm
        self.clearColor = MTLClearColorMake(0.1, 0.1, 0.1, 1.0)

        self.library = self.device.makeDefaultLibrary()!
    }

    public func begin_scene() {
        autoreleasepool {
            self.drawable = self.layer.nextDrawable()
            self.commandBuffer = self.commandQueue.makeCommandBuffer()
            self.commandBuffer!.label = "Command Buffer"
        }
    }

    public func bind_pipeline(pipeline: MTLRenderPipelineState) {
        self.pipelineState = pipeline
    }

    public func submit(
        vertex_buffer: MTLBuffer,
        index_buffer: MTLBuffer,
        index_count: UInt32,
        uniform_buffer: MTLBuffer
    ) {
        autoreleasepool {
            self.renderPassDescriptor = MTLRenderPassDescriptor()
            self.renderPassDescriptor?.colorAttachments[0].texture =
                self.drawable?.texture
            self.renderPassDescriptor?.colorAttachments[0].loadAction =
                .clear
            self.renderPassDescriptor?.colorAttachments[0].clearColor =
                MTLClearColorMake(0.1, 0.1, 0.1, 1.0)
            self.renderPassDescriptor?.colorAttachments[0].storeAction =
                .store

            self.encoder = self.commandBuffer?
                .makeRenderCommandEncoder(
                    descriptor: self.renderPassDescriptor!
                )

            self.encoder?.label = "Render Encoder"
            self.encoder?.setRenderPipelineState(
                self.pipelineState
            )

            self.encoder?.setVertexBuffer(
                vertex_buffer,
                offset: 0,
                index: 0
            )

            self.encoder?.setVertexBuffer(
                uniform_buffer,
                offset: 0,
                index: 1
            )

            self.encoder?.drawIndexedPrimitives(
                type: .triangle,
                indexCount: Int(index_count),
                indexType: .uint32,
                indexBuffer: index_buffer,
                indexBufferOffset: 0
            )

            self.encoder?.endEncoding()
        }
    }

    public func end_scene() {
        self.commandBuffer?.present(self.drawable!)
        self.commandBuffer!.commit()

        self.commandBuffer = nil
        self.drawable = nil
    }

    public func on_window_resize(width: UInt32, height: UInt32) {
        self.layer.drawableSize = CGSize(
            width: CGFloat(width),
            height: CGFloat(height)
        )
    }

    public func make_buffer(size: Int) -> MTLBuffer {
        return self.device.makeBuffer(length: size)!
    }

    public func make_buffer(bytes: UnsafeRawPointer, size: Int) -> MTLBuffer {
        return self.device.makeBuffer(bytes: bytes, length: size)!
    }

    public func make_shader(shader_name: String) -> MTLFunction {
        let shader = self.library.makeFunction(name: shader_name)
        return shader!
    }

    public func make_pipeline(
        pipelineDescriptor: MTLRenderPipelineDescriptor
    )
        -> MTLRenderPipelineState
    {
        // TODO unhardcode
        pipelineDescriptor.colorAttachments[0].pixelFormat = self.pixelFormat

        do {
            let pipelineState = try self.device.makeRenderPipelineState(
                descriptor: pipelineDescriptor
            )
            return pipelineState
        } catch {
            print("Failed to create renderPipelineState: \(error)")
            exit(-1)
        }
    }
}
