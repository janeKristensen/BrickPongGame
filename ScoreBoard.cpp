#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	
}

void ScoreBoard::addScore(int score)
{
	
	std::sort(arr, arr + n);
	if (score > arr[0])
	{
		arr[0] = score;
		std::sort(arr, arr + n);
	}
}

void ScoreBoard::loadScore()
{
	stream.open("D:\\Visual Studio stuff\\Projekts\\NewGame\\score.txt", std::ios::in);
	if (!stream)
	{
		std::cout << "Unable to load file";
		exit(1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			int x;
			stream >> x;
			arr[i] = x;
			std::cout << x;
		}
	}
	stream.close();
}

void ScoreBoard::getScore(RenderTarget& target)
{
	for (int i = 0; i < 5; i++)
	{
		int number = i + 1;
		int x = arr[4 - i];
		String strText(std::to_string(number) + ": " + std::to_string(x));
		m_Position = Vector2f(200, 100 + (100 * i) );
		scoreText[i].setParam(m_Size, textColor, m_Position, strText);
		scoreText[i].draw(target);
	}
}