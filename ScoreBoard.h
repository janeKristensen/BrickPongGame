#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameText.h"
#include <fstream>

using namespace sf;
using namespace std;


class ScoreBoard
{
private:
	int arr[5] = { 100,200,300,400,500 };
	int n = sizeof(arr) / sizeof(arr[0]);
	Color textColor = Color::White;
	int m_Size = 24;
	GameText scoreText[5];
	Vector2f m_Position;
	std::ifstream stream;
	

public:
	ScoreBoard();
	void loadScore();
	void addScore(int score);
	void getScore(RenderTarget& target);
};

