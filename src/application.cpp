#include "application.hpp"
#include <bobcat_ui/bobcat_ui.h>

using namespace bobcat;

Application::Application() {
    // what if the window is resizable? handle it.
    constexpr std::uint32_t width = 400;
    constexpr std::uint32_t height = 400;

    m_window = new Window(100, 100, width, height, "Paint Application");
    m_tool_paint_brush = new Image(0, 0, 50, 50, "assets/pencil.png");
    m_tool_eraser = new Image(50, 0, 50, 50, "assets/eraser.png");
    m_canvas = new Canvas(0, 50, width, height - 50);

    ON_CLICK(m_tool_paint_brush, Application::cb_tool_paint_brush);
    ON_CLICK(m_tool_eraser, Application::cb_tool_eraser);

    //ON_CLICK(m_canvas, Application::cb_interaction_click);
    ON_MOUSE_DOWN(m_canvas, Application::cb_interaction_mouse_down);
    ON_MOUSE_UP(m_canvas, Application::cb_interaction_mouse_up);
    ON_DRAG(m_canvas, Application::cb_interaction_drag);
    m_window->show();
}

void Application::cb_interaction_handler(InputEvent input_event, int mouse_x, int mouse_y) {
    switch (m_application_mode) {
        case Mode::Paint:
            std::cout << "paint" << std::endl;
            switch (input_event) {
                case InputEvent::MouseDown:
                    std::cout << "pass" << std::endl;
                    break;
                case InputEvent::MouseUp:
                    break;
                case InputEvent::MouseDrag:
                    break;
            }
            break;
        case Mode::Erase:
            break;
        case Mode::Select:
            break;
    }
}

void Application::cb_interaction_mouse_down(bobcat::Widget* sender, int mouse_x, int mouse_y) {
    std::cout << "mouse_down_>no_handler" << std::endl;
    cb_interaction_handler(InputEvent::MouseDown, 0, 0);
}

void Application::cb_interaction_mouse_up(bobcat::Widget* sender, int mouse_x, int mouse_y) {
    cb_interaction_handler(InputEvent::MouseUp, 0, 0);
}

void Application::cb_interaction_drag(bobcat::Widget* sender, int mouse_x, int mouse_y) {
    cb_interaction_handler(InputEvent::MouseDrag, mouse_x, mouse_y);
}

void Application::cb_tool_paint_brush(Widget* sender) {
    m_application_mode = Mode::Paint;
    std::cout << "paint_clicked" << std::endl;
}

void Application::cb_tool_eraser(Widget* sender) {
    m_application_mode = Mode::Erase;
}