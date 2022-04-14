#include "Ball.h"

Ball::Ball() 
{
	startPos.x = 400;
	startPos.y = 650;
	m_Circle.setRadius(m_Radius);
	m_Circle.setPosition(startPos);
	m_Circle.setFillColor(Color::Red);
	m_Circle.setOrigin(m_Radius, m_Radius);
	
}

void Ball::update(float dt, Vector2i resolution)
{
	float currentPosX = m_Circle.getPosition().x;
	float currentPosY = m_Circle.getPosition().y;  

	float tempPosX = currentPosX + veloX * dt * speed;
	if (tempPosX + m_Radius  >= resolution.x || tempPosX - m_Radius <= 0)
	{
		veloX = veloX * -1;
		
	}
	float tempPosY = currentPosY + veloY * dt * speed;
	if(tempPosY - m_Radius <= 0)
	{
		veloY = veloY * -1;
	}
	
	if(tempPosY - m_Radius >= resolution.y)
	{
		life--;
		reset = true;
	}

	m_Circle.setPosition(tempPosX, tempPosY);
}

void Ball::draw(RenderTarget& target)
{
	target.draw(m_Circle);
}

FloatRect Ball::getBounds()
{
	return m_Circle.getGlobalBounds();
}

void Ball::setVeloY(float velo)
{
	veloY = velo;
}

void Ball::setVeloX(float velo)
{
	veloX = velo;
}

float Ball::getVeloX()
{
	return velocity_x;
}

float Ball::getVeloY()
{
	return velocity;
}

Vector2f Ball::getPosition()
{
	return m_Circle.getPosition();
}

bool Ball::isReset()
{
	return reset;
}

void Ball::resetBall()
{
	reset = false;
	veloX = velocity_x;
	veloY = velocity;

	m_Circle.setPosition(startPos.x, startPos.y);
}

void Ball::resetLife()
{
	life = 3;
}

void Ball::resetScore()
{
	score = 0;
}

int Ball::getLife()
{
	return life;
}

void Ball::setScore(int scoreAmount)
{
	score = score + (100 * scoreAmount);
}

int Ball::getScore()
{
	return score;
}

void Ball::setSpeed(float speedBooster)
{
	speed = speedBooster;
}