#include "canvas.hpp"

using namespace bobcat;

Canvas::Canvas(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h) {
    m_image = new Image(x, y, w, h, "assets/clear.png");
}

Canvas::~Canvas() {
    delete m_image;
}

void Canvas::onMouseDown(std::function<void(bobcat::Widget*, int, int)> cb) {
    onMouseUpCb = cb;
}

void Canvas::onMouseUp(std::function<void(bobcat::Widget*, int, int)> cb) {
    onMouseUpCb = cb;
}

void Canvas::onDrag(std::function<void(bobcat::Widget*, int, int)> cb) {
    onDragCb = cb;
}

void Canvas::add_draw_data(DrawData data) {
    m_draw_data.push_back(data);
}

void Canvas::clear_draw_data() {
    m_draw_data.clear();
}