#include "UI.h"

UI::UI(IntRect texturePos, Vector2f position)
{
	m_Sprite.setPosition(position);
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/ui.png"));
	m_Sprite.setTextureRect(texturePos);
}

void UI::draw(RenderTarget& target)
{
	target.draw(m_Sprite);
}
FloatRect UI::getBounds()
{
	return m_Sprite.getGlobalBounds();
}