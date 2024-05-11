#include "window/Window.h"
#include "src/PointsScene.h"


int main() {
    Mn::Window wnd("Example04-Points", 800, 600);
    return wnd.ShowScene<PointsScene>();
}
