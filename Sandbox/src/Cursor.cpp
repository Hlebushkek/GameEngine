#include "../include/Cursor.hpp"

Cursor::Cursor()
    : UIObject("Cursor.png", *(new Engine::Rect()), glm::vec2(0, 0), glm::vec2(0), glm::vec2(0.1))
{

}