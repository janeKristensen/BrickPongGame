#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameText 
{
private:
    Font font;
    Text m_gameText;
  
public:
    GameText();
    GameText(int size, Color color, Vector2f position, String strText);
    GameText(int size, Color color, Vector2f position);
    void setStr(String& str);
    void draw(RenderTarget& target);
    void setParam(int size, Color color, Vector2f position, String strText);
};

