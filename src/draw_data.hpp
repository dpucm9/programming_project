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
        Unknown,
        Points,
        Triangle,
        Rectangle,
        Polygon
    };

    static constexpr Color get_default_color() {
        return Color {
            .r = 1.0f,
            .g = 0.0f,
            .b = 0.0f
        };
    }

    static constexpr std::uint32_t get_default_point_size() {
        return 7;
    }

    DrawData();
    void set_bounds(Offset start, Offset end);
    void increment_layer(std::int32_t offset);
    void set_color(Color color);
    void set_point_size(std::uint32_t size);
    void set_format(Format format);
    void add_vertex(Offset offset);

    Offset get_offset_start() const;
    Offset get_offset_end() const;
    std::size_t get_layer() const;
    Format get_format() const;
    Color get_color() const;
    std::uint32_t get_point_size() const;
    std::vector<Offset> get_vertices() const;
    std::vector<Offset>* get_vertices_ptr();
private:
    Offset m_offset_start;
    Offset m_offset_end;
    std::int32_t m_layer;
    Format m_format;
    Color m_color;
    std::uint32_t m_point_size;
    std::vector<Offset> m_vertices;
};
