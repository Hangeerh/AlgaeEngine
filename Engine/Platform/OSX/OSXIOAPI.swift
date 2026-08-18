import Foundation

@_cdecl("_load_from_osx_bundle")
public func alg_load_bundle_resource(
    name: UnsafePointer<Int8>,
    extension ext: UnsafePointer<Int8>,
    subdirectory: UnsafePointer<Int8>?,
    out_bytes: UnsafeMutablePointer<UnsafeMutablePointer<Int8>?>,
    out_size: UnsafeMutablePointer<Int>
) {
    let nameStr = String(cString: name)
    let extStr = String(cString: ext)
    let subdirStr = subdirectory.map { String(cString: $0) }

    guard let url = Bundle.main.url(
        forResource: nameStr,
        withExtension: extStr,
        subdirectory: subdirStr
    ) else {
        out_bytes.pointee = nil
        out_size.pointee = 0
        return
    }

    guard let data = try? Data(contentsOf: url) else {
        out_bytes.pointee = nil
        out_size.pointee = 0
        return
    }

    let size = data.count
    let ptr = UnsafeMutablePointer<Int8>.allocate(capacity: size)
    data.copyBytes(to: UnsafeMutableRawBufferPointer(start: ptr, count: size))

    out_bytes.pointee = ptr
    out_size.pointee = size
}
