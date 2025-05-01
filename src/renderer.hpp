#pragma once

#include "draw_data.hpp"

class Renderer {
public:
    void render_draw_data();
private:
    std::vector<DrawData> m_draw_data;
};