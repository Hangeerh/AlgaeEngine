#pragma once

#include <string>
#include <cstdint>

namespace alg {

class Window {
public:
    Window(const std::string& title, uint32_t width, uint32_t height);
    ~Window();

    void* get_native_window() const;
    bool should_close() const;
    void poll_events() const;

private:
    void* native_handle;
};

} // namespace alg
