//
// Created by Ivan on 12.6.2024..
//
// ch02 e01_empty
void update(const Mn::Input& input, double ) {
    red = (float(input.get_mouse_x_position()) + 1.0f) / 2.0f;
    green = (float(input.get_mouse_y_position()) + 1.0f) / 2.0f;
//        if (input.is_clicked(Mn::key::a)) {
//            std::cout << input.get_mouse_x_position() << "\n";
//            red += 0.1f;
//            if (red > 1.0f) red = 0.0f;
//        }

    if (input.is_pressed(Mn::key::space ))
        std::cout << "Space\n";
    if (input.is_pressed(Mn::key::right))
        std::cout << "Right Arrow\n";
    if (input.is_pressed(Mn::key::a))
        std::cout << "Letter A\n";
}
