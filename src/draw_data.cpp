#include "draw_data.hpp"

DrawData::DrawData() {
    m_color = Color {
        .r = 1.0f,
        .g = 0.0f,
        .b = 0.0f
    };
    m_point_size = 7;
}

void DrawData::set_color(Color color) {
    m_color = color;
}

void DrawData::set_point_size(std::uint32_t size) {
    m_point_size = size;
}

void DrawData::add_point(Offset offset) {
    m_points.push_back(offset);
}

Color DrawData::get_color() const {
    return m_color;
}

std::uint32_t DrawData::get_point_size() const {
    return m_point_size;
}

std::vector<Offset> DrawData::get_points() const {
    return m_points;
}