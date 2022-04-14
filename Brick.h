#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

using namespace sf;

class Brick
{
private:

	float width = 70;
	float height = 50;
	int offset = 5;
	Vector2f m_Position;
	int hits = 1;
	int scoreAmount = 0;
	float booster = 1.5f;
	bool m_destroyed = false;
	Sprite m_Sprite;

	RectangleShape m_Rect;

public:
	Brick();
	Brick(int seed);
	void draw(RenderTarget& target);
	void place(int i, int j);
	FloatRect getBounds();
	void destroy(Ball& m_ball);
	bool isDestroyed();
	void boosterBall(Ball& ball, Paddle& paddle);
};

