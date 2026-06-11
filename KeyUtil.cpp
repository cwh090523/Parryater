#include "KeyUtil.h"
std::string KeyToString(int key)
{
    if (key == VK_SPACE) return "SPACE";
    if (key == VK_RETURN) return "ENTER";
    if (key == VK_ESCAPE) return "ESC";
    if (key == VK_UP) return "UP";
    if (key == VK_DOWN) return "DOWN";
    if (key == VK_LEFT) return "LEFT";
    if (key == VK_RIGHT) return "RIGHT";

    if (key >= 'A' && key <= 'Z')
        return std::string(1, (char)key);

    if (key >= '0' && key <= '9')
        return std::string(1, (char)key);

    return "?";
}