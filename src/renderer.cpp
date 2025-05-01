#include "renderer.hpp"

#include <GL/gl.h>

void Renderer::render_draw_data() {
    for (std::size_t i = 0; i < m_draw_data.size(); ++i) {
        const Color color = m_draw_data[i].get_color();
        glColor3f(color.r, color.g, color.b);

        const std::uint32_t point_size = m_draw_data[i].get_point_size();
        glPointSize(static_cast<GLfloat>(point_size));

        const std::vector<Offset> points = m_draw_data[i].get_points();
        if (!points.empty()) {
            glBegin(GL_POINTS);
            for (std::size_t j = 0; j < points.size(); ++j) {
                glVertex2f(static_cast<GLfloat>(points[j].x), static_cast<GLfloat>(points[j].y));
            }
            glEnd();
        }
    }
}