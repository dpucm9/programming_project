#pragma once

#include <bobcat_ui/all.h>
#include "canvas.hpp"

class Application : public bobcat::Application_ {
public:
    enum Mode {
        Paint,
        Erase,
        Select
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
    bobcat::Window* m_window = nullptr;
    bobcat::Image* m_tool_paint_brush = nullptr;
    bobcat::Image* m_tool_eraser = nullptr;
    bobcat::Image* m_tool_clear_screen = nullptr;
    bobcat::Image* m_tool_color_picker = nullptr;
    bobcat::Image* m_tool_shape_square = nullptr;
    bobcat::Image* m_tool_shape_triangle = nullptr;
    bobcat::Image* m_tool_shape_circle = nullptr;
    bobcat::Image* m_tool_shape_polygon = nullptr;
    bobcat::Image* m_tool_selector = nullptr;
    Canvas* m_canvas = nullptr;
    // ^
    void resize();
    void change_color();
    void move(); // drag
    void move_forward();
    void move_back();

    void cb_interaction_handler(InputEvent input_event, int mouse_x, int mouse_y);
    void cb_interaction_mouse_down(bobcat::Widget* sender, int mouse_x, int mouse_y);
    void cb_interaction_mouse_up(bobcat::Widget* sender, int mouse_x, int mouse_y);
    void cb_interaction_drag(bobcat::Widget* sender, int mouse_x, int mouse_y);
    void cb_tool_paint_brush(bobcat::Widget* sender);
    void cb_tool_eraser(bobcat::Widget* sender);
};