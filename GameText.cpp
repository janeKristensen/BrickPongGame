#include "GameText.h"

GameText::GameText()
{}

GameText::GameText(int size, Color color, Vector2f position, String strText)
{
    font.loadFromFile("fonts/invText.ttf");

    m_gameText.setFont(font);
    m_gameText.setCharacterSize(size);
    m_gameText.setFillColor(color);
    m_gameText.setPosition(position);
    m_gameText.setString(strText);
}

GameText::GameText(int size, Color color, Vector2f position)
{
    font.loadFromFile("fonts/invText.ttf");

    m_gameText.setFont(font);
    m_gameText.setCharacterSize(size);
    m_gameText.setFillColor(color);
    m_gameText.setPosition(position);
    
}

void GameText::setStr(String& str)
{
    m_gameText.setString(str);
}

void GameText::draw(RenderTarget& target)
{
    target.draw(m_gameText);
}

void GameText::setParam(int size, Color color, Vector2f position, String strText)
{
    font.loadFromFile("fonts/invText.ttf");

    m_gameText.setFont(font);
    m_gameText.setCharacterSize(size);
    m_gameText.setFillColor(color);
    m_gameText.setPosition(position);
    m_gameText.setString(strText);
}