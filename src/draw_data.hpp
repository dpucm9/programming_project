#pragma once

#include <cstdint>
#include <vector>

struct Offset {
    std::int32_t x;
    std::int32_t y;
};

struct Color {
    float r;
    float g;
    float b;
};

class DrawData {
public:
    DrawData();
    void set_color(Color color);
    void set_point_size(std::uint32_t size);
    void add_point(Offset offset);

    Color get_color() const;
    std::uint32_t get_point_size() const;
    std::vector<Offset> get_points() const;
private:
    Color m_color;
    std::uint32_t m_point_size;
    std::vector<Offset> m_points;
};