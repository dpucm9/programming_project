#include "application.hpp"
#include "draw_data.hpp"
#include <FL/Enumerations.H>
#include <GL/gl.h>
#include <bobcat_ui/bobcat_ui.h>

using namespace bobcat;

Application::Application() {
    constexpr std::uint32_t width = 400;
    constexpr std::uint32_t height = 400;

    m_window = new Window(100, 100, width, height, "Paint Application");
    m_tool_paint_brush = new Image(0, 0, 50, 50, "assets/pencil.png");
    m_tool_eraser = new Image(50, 0, 50, 50, "assets/eraser.png");
    m_tool_clear_screen = new Image(100, 0, 50, 50, "assets/clear.png");
    m_tool_select = new Image(150, 0, 50, 50, "assets/mouse.png");
    m_tool_shape_triangle = new Image(200, 0, 50, 50, "assets/triangle.png");
    m_tool_shape_rectangle = new Image(250, 0, 50, 50, "assets/rectangle.png");
    m_tool_shape_polygon = new Image(300, 0, 50, 50, "assets/polygon.png");
    m_tool_shape_circle = new Image(350, 0, 50, 50, "assets/circle.png");

    ON_CLICK(m_tool_paint_brush, Application::cb_tool_paint_brush);
    ON_CLICK(m_tool_eraser, Application::cb_tool_eraser);
    ON_CLICK(m_tool_clear_screen, Application::cb_tool_clear_screen);
    ON_CLICK(m_tool_select, Application::cb_tool_select);
    ON_CLICK(m_tool_shape_triangle, Application::cb_tool_shape_triangle);
    ON_CLICK(m_tool_shape_rectangle, Application::cb_tool_shape_rectangle);
    ON_CLICK(m_tool_shape_polygon, Application::cb_tool_shape_polygon);
    ON_CLICK(m_tool_shape_circle, Application::cb_tool_shape_circle);

    m_paint_brush_size_input = new IntInput(0, 70, 50, 50, "Size");
    m_color_picker_preview = new Button(0, 200, 50, 50);
    m_color_picker_red_input = new IntInput(0, 250, 50, 50);
    m_color_picker_green_input = new IntInput(0, 300, 50, 50);
    m_color_picker_blue_input = new IntInput(0, 350, 50, 50);
    m_point_size = 14;
    m_color = Color {
        .r = 255.0f,
        .g = 0.0f,
        .b = 0.0f
    };
    m_color_picker_preview->color(fl_rgb_color(m_color.r, m_color.g, m_color.b));
    m_paint_brush_size_input->value(m_point_size);
    m_color_picker_red_input->value(m_color.r);
    m_color_picker_green_input->value(m_color.g);
    m_color_picker_blue_input->value(m_color.b);

    ON_CHANGE(m_paint_brush_size_input, Application::cb_size_input);
    ON_CHANGE(m_color_picker_red_input, Application::cb_red_input);
    ON_CHANGE(m_color_picker_green_input, Application::cb_green_input);
    ON_CHANGE(m_color_picker_blue_input, Application::cb_blue_input);

    m_canvas = new Canvas(50, 50, width - 50, height - 50);

    ON_MOUSE_DOWN(m_canvas, Application::cb_interaction_mouse_down);
    ON_MOUSE_UP(m_canvas, Application::cb_interaction_mouse_up);
    ON_DRAG(m_canvas, Application::cb_interaction_drag);

    m_window->show();
}

void Application::cb_interaction_handler(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (m_application_mode) {
        case Mode::Paint:
            interaction_handler_paint(input_event, mouse_x, mouse_y);
            break;
        case Mode::Erase:
            interaction_handler_erase(input_event, mouse_x, mouse_y);
            break;
        case Mode::Select:
            interaction_handler_select(input_event, mouse_x, mouse_y);
            break;
        case Mode::ShapeTriangle: 
            interaction_handler_shape_triangle(input_event, mouse_x, mouse_y);
            break;
        case Mode::ShapeRectangle: 
            interaction_handler_shape_rectangle(input_event, mouse_x, mouse_y);
            break;
        case Mode::ShapePolygon: 
            interaction_handler_shape_polygon(input_event, mouse_x, mouse_y);
            break;
        case Mode::ShapeCircle: 
            interaction_handler_shape_circle(input_event, mouse_x, mouse_y);
            break;
    }
}

void Application::cb_interaction_mouse_down(bobcat::Widget* sender, float mouse_x, float mouse_y) {
    cb_interaction_handler(InputEvent::MouseDown, mouse_x, mouse_y);
}

void Application::cb_interaction_mouse_up(bobcat::Widget* sender, float mouse_x, float mouse_y) {
    cb_interaction_handler(InputEvent::MouseUp, mouse_x, mouse_y);
}

void Application::cb_interaction_drag(bobcat::Widget* sender, float mouse_x, float mouse_y) {
    cb_interaction_handler(InputEvent::MouseDrag, mouse_x, mouse_y);
}

void Application::cb_tool_paint_brush(Widget* sender) {
    m_application_mode = Mode::Paint;
}

void Application::cb_tool_eraser(Widget* sender) {
    m_application_mode = Mode::Erase;
}

void Application::cb_tool_clear_screen(bobcat::Widget* sender) {
    m_canvas->clear_draw_data();
    m_canvas->redraw();
}

void Application::cb_tool_select(bobcat::Widget* sender) {
    m_application_mode = Select;
}

void Application::cb_tool_shape_triangle(bobcat::Widget* sender) {
    m_application_mode = ShapeTriangle;
}

void Application::cb_tool_shape_rectangle(bobcat::Widget* sender) {
    m_application_mode = ShapeRectangle;
}

void Application::cb_tool_shape_polygon(bobcat::Widget* sender) {
    m_application_mode = ShapePolygon;
}

void Application::cb_tool_shape_circle(bobcat::Widget* sender) {
    m_application_mode = ShapeCircle;
}

void Application::cb_tool_selector(bobcat::Widget* sender) {

}

void Application::cb_size_input(bobcat::Widget* sender) {
    if (m_paint_brush_size_input->empty()) {
        m_paint_brush_size_input->value(1);
    }
    m_point_size = static_cast<std::size_t>(m_paint_brush_size_input->value());
    m_canvas->set_point_size(m_point_size);
}

void Application::cb_red_input(bobcat::Widget* sender) {
    if (m_color_picker_red_input->empty()) {
        m_color_picker_red_input->value(0);
    }
    m_color.r = static_cast<float>(m_color_picker_red_input->value() / 255.0f);
    m_canvas->set_color(Color { m_color.r / 255.0f, m_color.g / 255.0f, m_color.b / 255.0f});

    m_color_picker_preview->color(fl_rgb_color(m_color.r, m_color.g, m_color.b));
    m_color_picker_preview->redraw();
}

void Application::cb_green_input(bobcat::Widget* sender) {
    if (m_color_picker_green_input->empty()) {
        m_color_picker_green_input->value(0);
    }
    m_color.g = static_cast<float>(m_color_picker_green_input->value());
    m_canvas->set_color(Color { m_color.r / 255.0f, m_color.g / 255.0f, m_color.b / 255.0f});

    m_color_picker_preview->color(fl_rgb_color(m_color.r, m_color.g, m_color.b));
    m_color_picker_preview->redraw();
}

void Application::cb_blue_input(bobcat::Widget* sender) {
    if (m_color_picker_blue_input->empty()) {
        m_color_picker_blue_input->value(0);
    }
    m_color.b = static_cast<float>(m_color_picker_blue_input->value());
    m_canvas->set_color(Color { m_color.r / 255.0f, m_color.g / 255.0f, m_color.b / 255.0f});

    m_color_picker_preview->color(fl_rgb_color(m_color.r, m_color.g, m_color.b));
    m_color_picker_preview->redraw();
}

void Application::interaction_handler_paint(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (input_event) {
        case InputEvent::MouseDown:
            m_canvas->set_point_size(m_point_size);
            m_canvas->set_color(m_color);
            m_canvas->prepare_next_draw_data(DrawData::Format::Points);
            break;
        case InputEvent::MouseUp:
            break;
        case InputEvent::MouseDrag: {
            m_canvas->next_draw_data_add_vertex(Offset { .x = mouse_x, .y = mouse_y });
            m_canvas->redraw();
            break;
        }
    }
}

void Application::interaction_handler_erase(InputEvent input_event, float mouse_x, float mouse_y) {
        switch (input_event) {
            case InputEvent::MouseDown:
                m_canvas->set_point_size(m_point_size);
                m_canvas->set_color(Color { .r = 255, .g = 255, .b = 255 });
                m_canvas->prepare_next_draw_data(DrawData::Format::Points);
                break;
            case InputEvent::MouseUp:
                break;
            case InputEvent::MouseDrag: {
                m_canvas->next_draw_data_add_vertex(Offset { .x = mouse_x, .y = mouse_y });
                m_canvas->redraw();
                break;
            }
        }
}

void Application::interaction_handler_select(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (input_event) {
        case InputEvent::MouseDown:
            m_selected_data = m_canvas->point_selection(mouse_x, mouse_y);
            m_selected_data->set_color(Color { 0.0f, 1.0f, 0.0f });
            break;
        case InputEvent::MouseUp:
            break;
        case InputEvent::MouseDrag:
            if (m_selected_data != nullptr) {
                std::int32_t x0, y0;
                m_canvas->convert_pixel_coordinates(mouse_x, mouse_y, &x0, &y0);
                // TODO TODO TODO
            }
            break;
    }
}

void Application::interaction_handler_shape_triangle(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (input_event) {
        case InputEvent::MouseDown:
            m_canvas->set_point_size(m_point_size);
            m_canvas->set_color(m_color);
            m_canvas->prepare_next_draw_data(DrawData::Format::Triangle);
            m_shape_start = Offset { .x = mouse_x, .y = mouse_y };
            break;
        case InputEvent::MouseUp:
            m_shape_end = Offset { .x = mouse_x, .y = mouse_y };
            validate_shape_offsets();
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x + ((m_shape_end.x - m_shape_start.x) / 2.0f), .y = m_shape_start.y });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x, .y = m_shape_end.y });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_end.x, .y = m_shape_end.y });
            m_canvas->redraw();
            break;
        case InputEvent::MouseDrag:
            break;
    }
}

void Application::interaction_handler_shape_rectangle(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (input_event) {
        case InputEvent::MouseDown:
            m_canvas->set_point_size(m_point_size);
            m_canvas->set_color(m_color);
            m_canvas->prepare_next_draw_data(DrawData::Format::Triangle);
            m_shape_start = Offset { .x = mouse_x, .y = mouse_y };
            break;
        case InputEvent::MouseUp:
            m_shape_end = Offset { .x = mouse_x, .y = mouse_y };
            validate_shape_offsets();
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x, .y = m_shape_start.y });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x + (m_shape_end.x - m_shape_start.x), .y = m_shape_start.y });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x, .y = m_shape_start.y + (m_shape_end.y - m_shape_start.y) });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x + (m_shape_end.x - m_shape_start.x), .y = m_shape_start.y });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x + (m_shape_end.x - m_shape_start.x), .y = m_shape_start.y + (m_shape_end.y - m_shape_start.y) });
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x, .y = m_shape_start.y + (m_shape_end.y - m_shape_start.y) });
            m_canvas->redraw();
            break;
        case InputEvent::MouseDrag:
            break;
    }
}

void Application::interaction_handler_shape_polygon(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (input_event) {
        case InputEvent::MouseDown:
            m_canvas->set_point_size(m_point_size);
            m_canvas->set_color(m_color);
            m_canvas->prepare_next_draw_data(DrawData::Format::Polygon);
            m_shape_start = Offset { .x = mouse_x, .y = mouse_y };
            break;
        case InputEvent::MouseUp: {
            m_shape_end = Offset { .x = mouse_x, .y = mouse_y };
            validate_shape_offsets();
            m_canvas->next_draw_data_add_vertex(Offset{ .x = m_shape_start.x + ((m_shape_end.x - m_shape_start.x) / 2.0f), .y = m_shape_start.y }); // tm
            m_canvas->next_draw_data_add_vertex(Offset { .x = m_shape_start.x, .y = m_shape_start.y + (m_shape_end.y - m_shape_start.y) / 2 }); // tl
            m_canvas->next_draw_data_add_vertex(Offset { .x = m_shape_start.x + (m_shape_end.x - m_shape_start.x), .y = m_shape_start.y + (m_shape_end.y - m_shape_start.y) / 2 }); // tr
            m_canvas->next_draw_data_add_vertex(Offset { .x = m_shape_end.x - (m_shape_end.x - m_shape_start.x) / 8, .y = m_shape_end.y }); // br
            m_canvas->next_draw_data_add_vertex(Offset { .x = m_shape_start.x + (m_shape_end.x - m_shape_start.x) / 8, .y = m_shape_end.y }); // tr
            m_canvas->next_draw_data_add_vertex(Offset { .x = m_shape_start.x, .y = m_shape_start.y + (m_shape_end.y - m_shape_start.y) / 2 }); // tl
            //m_canvas->next_draw_data_add_vertex(Offset { .x = 0, .y = 0 });
            m_canvas->redraw();
            break;
        }
        case InputEvent::MouseDrag:
            break;
    }
}

void Application::interaction_handler_shape_circle(InputEvent input_event, float mouse_x, float mouse_y) {
    switch (input_event) {
        case InputEvent::MouseDown:
            m_canvas->set_point_size(m_point_size);
            m_canvas->set_color(m_color);
            m_canvas->prepare_next_draw_data(DrawData::Format::Polygon);
            break;
        case InputEvent::MouseUp: {
            validate_shape_offsets(); // remember !!
            float inc = 2 * M_PI / 60;
            float radius = m_point_size / 100.0f;
            for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
                m_canvas->next_draw_data_add_vertex(Offset { .x = static_cast<float>(mouse_x + radius * cos(theta)), .y = static_cast<float>(mouse_y + radius * sin(theta)) });
            }
            m_canvas->redraw();
            break;
        }
        case InputEvent::MouseDrag:
            break;
    }
}

void Application::validate_shape_offsets() {
    // convert screen coordinates to pixel coordinates
    std::int32_t x0, y0, x1, y1;
    m_canvas->convert_pixel_coordinates(m_shape_start.x, m_shape_start.y, &x0, &y0);
    m_canvas->convert_pixel_coordinates(m_shape_end.x, m_shape_end.y, &x1, &y1);
    // adjust coordinates
    if (x1 < x0) {
        float old_x0 = x0;
        x0 = x1;
        x1 = old_x0;
    }
    if (y1 > y0) {
        float old_y0 = y0;
        y0 = y1;
        y1 = old_y0;
    }
    // convert validated pixel coordinates to screen coordinates
    int canvas_width, canvas_height;
    m_canvas->get_size(&canvas_width, &canvas_height);
    float half_width = static_cast<float>(canvas_width) / 2;
    float half_height = static_cast<float>(canvas_height) / 2;
    m_shape_start.x = (x0 - half_width) / half_width;
    m_shape_start.y = (y0 - half_height) / half_height;
    m_shape_end.x = (x1 - half_width) / half_width;
    m_shape_end.y = (y1 - half_height) / half_height;
}
