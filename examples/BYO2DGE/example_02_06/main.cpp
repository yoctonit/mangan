#include "window/Window.h"
#include "src/Core.h"

int main() {
    Mn::Window window("Example_02_o6", 800, 600);

    return window.ShowStaticScene<Core>();
}
