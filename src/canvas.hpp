#pragma once

#include <bobcat_ui/canvas.h>
#include "draw_data.hpp"

class Canvas : public bobcat::Canvas_ {
public:
    Canvas(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h);
    ~Canvas();

    void set_color(Color color);
    void set_point_size(std::size_t size);

    void prepare_next_draw_data(DrawData::Format format);
    void next_draw_data_add_vertex(Offset offset);
    void push_draw_data(DrawData data);
    void clear_draw_data();
    
    void render();
private:
    Color m_color;
    std::size_t m_point_size;
    std::vector<DrawData> m_draw_data;
};