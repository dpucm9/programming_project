#pragma once

#include <bobcat_ui/all.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/textbox.h>
#include "canvas.hpp"
#include "draw_data.hpp"

class Application : public bobcat::Application_ {
public:
    enum Mode {
        Paint,
        Erase,
        Select,
        ShapeTriangle,
        ShapeRectangle,
        ShapePolygon,
        ShapeCircle
    };
    enum InputEvent {
        MouseDown,
        MouseUp,
        MouseDrag
    };
    Application();
    friend struct::AppTest;
private:
    Mode m_application_mode;
    DrawData m_paint_mode_temp_draw_data;

    bobcat::Window* m_window = nullptr;
    bobcat::Image* m_tool_paint_brush = nullptr;
    bobcat::Image* m_tool_eraser = nullptr;
    bobcat::Image* m_tool_clear_screen = nullptr;
    bobcat::Image* m_tool_select = nullptr;
    bobcat::Image* m_tool_shape_triangle = nullptr;
    bobcat::Image* m_tool_shape_rectangle = nullptr;
    bobcat::Image* m_tool_shape_polygon = nullptr;
    bobcat::Image* m_tool_shape_circle = nullptr;

    bobcat::IntInput* m_paint_brush_size_input = nullptr;
    bobcat::Button* m_color_picker_preview = nullptr;
    bobcat::IntInput* m_color_picker_red_input = nullptr;
    bobcat::IntInput* m_color_picker_green_input = nullptr;
    bobcat::IntInput* m_color_picker_blue_input = nullptr;
    std::size_t m_point_size;
    Color m_color;

    Canvas* m_canvas = nullptr;

    void cb_interaction_handler(InputEvent input_event, float mouse_x, float mouse_y);
    void cb_interaction_mouse_down(bobcat::Widget* sender, float mouse_x, float mouse_y);
    void cb_interaction_mouse_up(bobcat::Widget* sender, float mouse_x, float mouse_y);
    void cb_interaction_drag(bobcat::Widget* sender, float mouse_x, float mouse_y);

    void cb_tool_paint_brush(bobcat::Widget* sender);
    void cb_tool_eraser(bobcat::Widget* sender);
    void cb_tool_select(bobcat::Widget* sender);
    void cb_tool_clear_screen(bobcat::Widget* sender);
    void cb_tool_shape_triangle(bobcat::Widget* sender);
    void cb_tool_shape_rectangle(bobcat::Widget* sender);
    void cb_tool_shape_polygon(bobcat::Widget* sender);
    void cb_tool_shape_circle(bobcat::Widget* sender);

    void cb_size_input(bobcat::Widget* sender);
    void cb_red_input(bobcat::Widget* sender);
    void cb_green_input(bobcat::Widget* sender);
    void cb_blue_input(bobcat::Widget* sender);

    Offset m_shape_start;
    Offset m_shape_end;
    DrawData* m_selected_data;
    void interaction_handler_paint(InputEvent input_event, float mouse_x, float mouse_y);
    void interaction_handler_erase(InputEvent input_event, float mouse_x, float mouse_y);
    void interaction_handler_select(InputEvent input_event, float mouse_x, float mouse_y);
    void interaction_handler_shape_triangle(InputEvent input_event, float mouse_x, float mouse_y);
    void interaction_handler_shape_rectangle(InputEvent input_event, float mouse_x, float mouse_y);
    void interaction_handler_shape_polygon(InputEvent input_event, float mouse_x, float mouse_y);
    void interaction_handler_shape_circle(InputEvent input_event, float mouse_x, float mouse_y);

    // ensures offsets always follow a top left to bottom right pattern.
    void validate_shape_offsets();
};
