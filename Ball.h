#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;



class Ball
{
private:

	const float m_Radius = 20;
	const float velocity = 300;
	const float velocity_x = 100;

	float veloX = velocity_x;
	float veloY = velocity;
	float speed = 1.5F;

	int life = 3;
	int score = 0;
	bool reset = false;
	Vector2f startPos;


	CircleShape m_Circle;

public:
	Ball();
	void update(float dt, Vector2i resolution);
	void draw(RenderTarget& target);
	FloatRect getBounds();
	void setVeloY(float velo);
	void setVeloX(float velo);
	float getVeloX();
	float getVeloY();
	Vector2f getPosition();
	bool isReset();
	void resetBall();
	void resetLife();
	void resetScore();
	int getLife();
	void setScore(int scoreAmount);
	int getScore();
	void setSpeed(float speedBooster);
};

