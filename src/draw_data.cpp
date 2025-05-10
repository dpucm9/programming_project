#include "draw_data.hpp"

DrawData::DrawData() {
    m_offset_start = { 0.0f, 0.0f };
    m_offset_end = { 0.0f, 0.0f };
    m_layer = 0;
    m_format = Format::Unknown;
    m_color = get_default_color();
    m_point_size = get_default_point_size();
}

void DrawData::set_bounds(Offset start, Offset end) {
    m_offset_start = start;
    m_offset_end = end;
}

void DrawData::set_color(Color color) {
    m_color = color;
}

void DrawData::set_point_size(std::uint32_t size) {
    m_point_size = size;
}

void DrawData::set_format(Format format) {
    m_format = format;
}

void DrawData::add_vertex(Offset offset) {
    m_vertices.push_back(offset);
}

Offset DrawData::get_offset_start() const {
    return m_offset_start;
}

Offset DrawData::get_offset_end() const {
    return m_offset_end;
}

std::size_t DrawData::get_layer() const {
    return m_layer;
}

DrawData::Format DrawData::get_format() const {
    return m_format;
}

Color DrawData::get_color() const {
    return m_color;
}

std::uint32_t DrawData::get_point_size() const {
    return m_point_size;
}

std::vector<Offset> DrawData::get_vertices() const {
    return m_vertices;
}
