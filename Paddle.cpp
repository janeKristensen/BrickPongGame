#include "Paddle.h"

Paddle::Paddle()
{
	paddleSize.x = width;
	paddleSize.y = height;
	m_Rect.setSize(paddleSize);
	m_Rect.setFillColor(Color(100, 200, 200));
	m_Rect.setPosition(m_startPos);
}

void Paddle::reset()
{
	m_Rect.setPosition(m_startPos);
}

void Paddle::update(float dt, Vector2i resolution)
{
	float currentPosX = m_Rect.getPosition().x;
	float tempPosX = currentPosX;

	if(m_moveRight == true )
	{
		tempPosX = currentPosX + velocity * dt * speed;
		if (tempPosX + width >= resolution.x)
		{
			m_moveRight = false;
		}
	}
	else if (m_moveLeft == true)
	{
		tempPosX = currentPosX - velocity * dt * speed;

		if (tempPosX <= 0)
		{
			m_moveLeft = false;
		}
	}
	
	m_Rect.setPosition(tempPosX, m_Pos.y);
}

void Paddle::draw(RenderTarget& target)
{
	target.draw(m_Rect);
}

void Paddle::moveRight()
{
	m_moveRight = true;
	m_moveLeft = false;
	
}

void Paddle::moveLeft()
{
	m_moveLeft = true;
	m_moveRight = false;
	
}

void Paddle::stopRight()
{
	m_moveRight = false;
}

void Paddle::stopLeft()
{
	m_moveLeft = false;
}

FloatRect Paddle::getBounds()
{
	return m_Rect.getGlobalBounds();
}

int Paddle::getWidth()
{
	return width;
}

Vector2f Paddle::getPosition()
{
	return m_Rect.getPosition();
}

void Paddle::setSpeed(float speedBooster)
{
	speed = speedBooster;
}