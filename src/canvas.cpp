#include "canvas.hpp"
#include <GL/gl.h>

Canvas::Canvas(std::int32_t x, std::int32_t y, std::uint32_t w, std::uint32_t h) : Canvas_(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)) {
    m_color = DrawData::get_default_color();
    m_point_size = DrawData::get_default_point_size();
}

Canvas::~Canvas() {
    
}

void Canvas::get_size(int* width, int* height) {
    get_size_range(width, height);
}

void Canvas::set_color(Color color) {
    m_color = color;
}

void Canvas::set_point_size(std::size_t size) {
    m_point_size = size;
}

void Canvas::prepare_next_draw_data(DrawData::Format format) {
    m_draw_data.push_back(DrawDataInfo info = {
        .offset = { 0.0f, 0.0f },
        .extent = { 0.0f, 0.0f },
        .color = m_color,
        .size = m_point_size,
        .format = format
    });
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

void Canvas::convert_pixel_coordinates(float screen_x, float screen_y, std::int32_t* pixel_x, std::int32_t* pixel_y) {
    int canvas_width, canvas_height;
    get_size(&canvas_width, &canvas_height);
    if (x0 != nullptr) {
        *pixel_x = (screen_x + 1) * canvas_width / 2;
    }
    if (y0 != nullptr) {
        *pixel_y = (screen_y + 1) * canvas_height / 2;
    }
}

DrawData* Canvas::point_selection(float mouse_x, float mouse_y) {
    std::vector<std::size_t> hit_indices;
    for (std::size_t i = 0; i < m_draw_data.size(); ++i) {
        const Offset start = m_draw_data[i].get_offset_start();
        const Offset end = m_draw_data[i].get_offset_end();
        std::int32_t x0, y0, x1, y1;
        screen_to_pixel_coordinates(start.x, start.y, &x0, &y0);
        screen_to_pixel_coordinates(end.x, end.y, &x1, &y1);
        if (mouse_x >= x0 && mouse_x <= x1) {
            if (mouse_y >= y0 && mouse_y <= y1) {
                hit_indices.push_back(i);
            }
        }
    }
    if (hit_indices.empty()) {
        return nullptr;
    }

    std::size_t topmost_layer = 0;
    std::size_t topmost_hit_index = 0;
    for (std::size_t i = 0; i < hit_indices.size(); ++i) {
        const std::size_t layer = m_draw_data[hit_indicies[i]].get_layer();
        if (layer > topmost_layer) {
            topmost_layer = layer;
            topmost_hit_index = i;
        }
    }
    return &m_draw_data[topmost_hit_index];
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
