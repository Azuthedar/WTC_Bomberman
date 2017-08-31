#include "../Inc/Render_Engine.hpp"

int main()
{
    Render_Engine tmp("DEZZ NUTZ", 1280, 720);

    tmp.init();
    tmp._render();

    return (0);
}
