#include "canvas.hpp"
#include <GL/gl.h>

using namespace bobcat;

Canvas::Canvas(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h) : Canvas_(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)) {

}

Canvas::~Canvas() {
    
}

void Canvas::set_color(Color color) {
    m_color = color;
}

void Canvas::set_point_size(std::size_t size) {
    m_point_size = size;
}

void Canvas::prepare_next_draw_data(DrawData::Format format) {
    m_draw_data.resize(m_draw_data.size() + 1);
    m_draw_data.back().set_color(m_color);
    m_draw_data.back().set_point_size(m_point_size);
    m_draw_data.back().set_format(format);
}

void Canvas::next_draw_data_add_vertex(Offset offset) {
    if (m_draw_data.empty()) {
        throw "unreachable";
    }
    m_draw_data.back().add_vertex(offset);
}

void Canvas::push_draw_data(DrawData data) {
    m_draw_data.push_back(data);
}

void Canvas::clear_draw_data() {
    m_draw_data.clear();
}

void Canvas::render() {
    for (std::size_t i = 0; i < m_draw_data.size(); ++i) {
        const DrawData data = m_draw_data[i];
        glColor3f(data.get_color().r, data.get_color().g, data.get_color().b);
        glPointSize(data.get_point_size());

        const std::vector<Offset> vertices = data.get_vertices();
        switch (data.get_format()) {
            case DrawData::Format::Points: {
                glBegin(GL_POINTS); // switch modes per type
                for (std::size_t j = 0; j < vertices.size(); ++j) {
                    glVertex2f(vertices[j].x, vertices[j].y);
                }
                glEnd();
                break;
            }
            case DrawData::Format::Triangle: {
                glBegin(GL_TRIANGLES);
                for (std::size_t j = 0; j < vertices.size(); ++j) {
                    glVertex2f(vertices[j].x, vertices[j].y);
                }
                glEnd();
                break;
            }
            case DrawData::Format::Rectangle: {
                glBegin(GL_TRIANGLES);
                for (std::size_t j = 0; j < vertices.size(); ++j) {
                    glVertex2f(vertices[j].x, vertices[j].y);
                }
                glEnd();
                break;
            }
            case DrawData::Format::Polygon: {
                glBegin(GL_POLYGON);
                for (std::size_t j = 0; j < vertices.size(); ++j) {
                    glVertex2f(vertices[j].x, vertices[j].y);
                }
                glEnd();
                break;
            }
        }
    }
}