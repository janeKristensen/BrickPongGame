#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
private:
	float height = 20;
	float width = 60;
	float velocity = 300;
	float speed = 1.5F;

	
	Vector2f m_startPos = Vector2f(400.f, 700.f);
	Vector2f m_Pos = m_startPos;

	bool m_moveRight = false;
	bool m_moveLeft = false;


	Vector2f paddleSize;
	RectangleShape m_Rect;

public:
	Paddle();
	void reset();
	void update(float dt, Vector2i resolution);
	void draw(RenderTarget& target);
	void moveRight();
	void moveLeft();
	void stopRight();
	void stopLeft();
	FloatRect getBounds();
	int getWidth();
	Vector2f getPosition();
	void setSpeed(float speedBooster);
};

