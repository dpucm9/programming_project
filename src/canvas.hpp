#pragma once

#include <functional>

#include <bobcat_ui/image.h>
#include "draw_data.hpp"
#include <bobcat_ui/button.h>

class Canvas {
public:
    bobcat::Button* a;
    Canvas(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h);
    ~Canvas();

    std::function<void(bobcat::Widget*, int, int)> onMouseDownCb;
    std::function<void(bobcat::Widget*, int, int)> onMouseUpCb;
    std::function<void(bobcat::Widget*, int, int)> onDragCb;
    void onMouseDown(std::function<void(bobcat::Widget*, int, int)> cb);
    void onMouseUp(std::function<void(bobcat::Widget*, int, int)> cb);
    void onDrag(std::function<void(bobcat::Widget *, int, int)> cb);
    
    void add_draw_data(DrawData data);
    void clear_draw_data();
private:
    bobcat::Image* m_image = nullptr;
    std::vector<DrawData> m_draw_data;
};