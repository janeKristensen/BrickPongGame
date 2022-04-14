#include "Brick.h"
#include "TextureHolder.h"

Brick::Brick()
{

}

Brick::Brick(int seed)
{
	//int seed = rand() % 3 + 1;
	Vector2f m_size;
	m_size.x = width;
	m_size.y = height;
	m_Rect.setSize(m_size);
	

	switch (seed)
	{
	case 1:
		//m_Rect.setFillColor(Color(150, 250, 250));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/brick1.png"));
		m_Sprite.setTextureRect(IntRect(0,0,70,48));
		hits = 1;
		scoreAmount = 1;
		booster = 1.8f;
		break;
	case 2:
		//m_Rect.setFillColor(Color(100, 200, 200));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/brick1.png"));
		m_Sprite.setTextureRect(IntRect(0, 49, 70, 48));
		hits = 2;
		scoreAmount = 2;
		booster = 1.5f;
		break;
	case 3:
		//m_Rect.setFillColor(Color(20, 120, 120));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/brick1.png"));
		m_Sprite.setTextureRect(IntRect(0, 96, 70, 48));
		hits = 3;
		scoreAmount = 3;
		booster = 1.5f;
		break; 
	}
}

void Brick::draw(RenderTarget& target)
{
	target.draw(m_Sprite);
}

void Brick::place(int k, int j)
{
	Vector2f placePos;

		placePos.x = 20 + (width * k) + (offset * k);
		placePos.y = 20 + (height * j) + (offset * j);
	

	m_Rect.setPosition(placePos);
	m_Sprite.setPosition(m_Rect.getPosition());
}

FloatRect Brick::getBounds()
{
	return m_Rect.getGlobalBounds();
}

void Brick::destroy(Ball& m_ball)
{
	hits--;

	if(hits <= 0)
	{
		m_destroyed = true;
		m_ball.setScore(scoreAmount);
	}
	
}

bool Brick::isDestroyed()
{
	return m_destroyed;
}

void Brick::boosterBall(Ball& ball, Paddle& paddle)
{
	ball.setSpeed(booster);
	paddle.setSpeed(booster);
}
