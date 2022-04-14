#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"

using namespace sf;

class UI
{
private:
	Sprite m_Sprite;
	

public:
	UI(IntRect texturePos, Vector2f position);
	void draw(RenderTarget& target);
	FloatRect getBounds();
};

