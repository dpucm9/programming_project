#pragma once

#include <cstdint>
#include <vector>

struct Offset {
    float x;
    float y;
};

struct Color {
    float r;
    float g;
    float b;
};

class DrawData {
public:
    enum Format {
        Points,
        Triangle,
        Rectangle,
        Polygon
    };
    DrawData();
    void set_color(Color color);
    void set_point_size(std::uint32_t size);
    void set_format(Format format);
    void add_vertex(Offset offset);

    Color get_color() const;
    std::uint32_t get_point_size() const;
    Format get_format() const;
    std::vector<Offset> get_vertices() const;
private:
    Format m_format;
    Color m_color;
    std::uint32_t m_point_size;
    std::vector<Offset> m_vertices;
};