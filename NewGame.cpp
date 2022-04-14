
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "GameText.h"
#include <vector>
#include <fstream>
#include "TextureHolder.h"
#include "UI.h"
#include "ScoreBoard.h"

   using namespace sf;

int main()
{
    Vector2i resolution;
    resolution.x = 800;
    resolution.y = 800;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "New Game", Style::Default);

    enum class State { PLAYING, PAUSED, GAME_OVER, RESTART, LEVEL_UP, LOADING, SCORE  };
    State state = State::LOADING;

    TextureHolder holder;
    ScoreBoard leaderboard;
    leaderboard.loadScore();
    Ball ball;
    Paddle paddle;
    int level = 1;
    std::vector<Brick*>bricks;
    std::ifstream levelRead;
   
    void collision(Ball& m_ball, Paddle& m_paddle);
    void brick_collision(Ball & m_ball, Brick* m_brick, Paddle& m_paddle);

    //HUD

    Vector2f ui_Pos = Vector2f((resolution.x / 2), (resolution.y / 2));
    UI start(IntRect(0, 0, 267, 64), Vector2f((ui_Pos.x - 267/2), (ui_Pos.y - 65*4)));
    UI score(IntRect(0, 66, 267, 64), Vector2f((ui_Pos.x - 267/2), ui_Pos.y -65*2));
    UI quit(IntRect(0, 133, 267, 64), Vector2f((ui_Pos.x - 267/2), (ui_Pos.y)));


    Vector2f livesPos;
    livesPos.x = resolution.x - 200.0f;
    livesPos.y = resolution.y - 50.0f;
    GameText lives(50, Color::White, livesPos);

    Vector2f levelPos;
    levelPos.x = resolution.x /2;
    levelPos.y = resolution.y /2;
    GameText levelText(50, Color::White, levelPos);

    Vector2f scorePos;
    scorePos.x = resolution.x / resolution.x;
    scorePos.y = resolution.y - 50.0f;
    String strScore("Score: 0");
    GameText scoreText(50, Color::White, scorePos, strScore);
    

    Vector2f goPos;
    goPos.x = resolution.x/2 - 120;
    goPos.y = resolution.y/2 - 50;
    String strGO("Game Over");
    GameText gameOver(50, Color::White, goPos, strGO);

    Vector2f pausePos;
    pausePos.x = resolution.x/2 - 250;
    pausePos.y = resolution.y/2 - 50;
    String strP("Press 'Enter' to continue");
    GameText pauseText(30, Color::White, pausePos, strP);

    Vector2f newLevelPos;
    newLevelPos.x = resolution.x / 2 - 120;
    newLevelPos.y = resolution.y / 2 - 50;
    GameText newLevelText(50, Color::White, newLevelPos);
    
    
    Clock clock;
    Time dt;
   
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
        
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
                else if (event.key.code == Keyboard::Enter && state == State::LOADING)
                {
                    state = State::RESTART;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::Enter && state == State::GAME_OVER)
                {
                    state = State::RESTART;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::Enter && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::P && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                else if (event.key.code == Keyboard::Enter && state == State::LEVEL_UP)
                {
                    state = State::PLAYING;
                }
                else if (event.key.code == Keyboard::Enter && state == State::SCORE)
                {
                    state = State::LOADING;
                }
                else if (event.key.code == Keyboard::D)
                {
                    paddle.moveRight();
                }
                else if (event.key.code == Keyboard::A)
                {
                    paddle.moveLeft();
                }
                else if (event.key.code == Keyboard::R)
                {
                    state = State::RESTART;
                }   
            }  
            else if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::D)
                {
                    paddle.stopRight();
                }
                else if (event.key.code == Keyboard::A)
                {
                    paddle.stopLeft();
                }
            }
            else if (Mouse::isButtonPressed(Mouse::Left) && state == State::LOADING)
            {
                Vector2i mousePos = Mouse::getPosition(window);             
                if (start.getBounds().contains(mousePos.x, mousePos.y))
                {
                    state = State::RESTART;
                    clock.restart();
                }
                else if (score.getBounds().contains(mousePos.x, mousePos.y))
                {
                    state = State::SCORE;
                }
                else if (quit.getBounds().contains(mousePos.x, mousePos.y))
                {
                    window.close();
                }
            }
        }


        if (state == State::RESTART)
        {
            ball.resetBall();
            ball.resetLife();
            ball.resetScore();
            paddle.reset();
            level = 1;
            bricks.clear();

            levelRead.open("D:\\Visual Studio stuff\\Projekts\\NewGame\\1.txt", std::ios::in);
            if (!levelRead)
            {
                std::cout << "Unable to load file";
                exit(1);
            }
           
            int seed = 0;
            int temp;
            int line = level * 10;
            signed int offset;
            if (level == 1)
            {
                offset = 0;
            }
            else
            {
                offset = ((level - 1) * (level) / 2) * 10; 
            }

            levelRead.seekg(offset, std::ios::beg);
            char* buffer = new char[line + 1];
            levelRead.read(buffer, line);
            buffer[line] = 0;
            
            for (int i = 0; i < line; i++)
            {
                seed = int(buffer[i]) - 48;  
                bricks.push_back(new Brick(seed));
            }

            levelRead.close();
            delete[] buffer;

            for (unsigned int i = 0; i < bricks.size(); i++)
            {
                int row = i%10;
                int column = i / 10;

                bricks[i]->place(row, column);
            }
            state = State::PLAYING;
        }

        if (state == State::LEVEL_UP)
        {
            bricks.clear();

            levelRead.open("D:\\Visual Studio stuff\\Projekts\\NewGame\\1.txt", std::ios::in);
            if (!levelRead)
            {
                std::cout << "Unable to load file";
                exit(1);
            }

            int seed = 0;
            int temp;
            int line = level * 10;
            signed int offset;
            if (level == 1)
            {
                offset = 0;
            }
            else
            {
                offset = ((level - 1) * (level) / 2) * 10;
            }

            levelRead.seekg(offset, std::ios::beg);
            char* buffer = new char[line + 1];
            levelRead.read(buffer, line);
            buffer[line] = 0;

            for (int i = 0; i < line; i++)
            {
                seed = int(buffer[i]) - 48;
                bricks.push_back(new Brick(seed));
            }

            levelRead.close();
            delete[] buffer;

            for (unsigned int i = 0; i < bricks.size(); i++)
            {
                int row = i % 10;
                int column = i / 10;

                bricks[i]->place(row, column);
            }

            ball.resetBall();
            ball.resetLife();
            paddle.reset(); 
        }

        //Update
        if (state == State::PLAYING)
        {
            for (unsigned int i = 0; i < bricks.size(); i++)
            {
                brick_collision(ball, bricks[i], paddle);
            }

            collision(ball, paddle);

            dt = clock.restart();
            float elapsedTime = dt.asSeconds();

            ball.update(elapsedTime, resolution);
            paddle.update(elapsedTime, resolution);

            for (int i = bricks.size()-1; i >= 0; i--)
            {
                if (bricks[i]->isDestroyed() == true)
                {
                    bricks.erase(bricks.begin() + i);
                }
            }

            if (bricks.size() == 0)
            {
                level++;
                state = State::LEVEL_UP;
            }

            String strLife = "Lives: " + std::to_string(ball.getLife());
            lives.setStr(strLife);
            String strScore = "Score: " + std::to_string(ball.getScore());
            scoreText.setStr(strScore);
            String strLevel = std::to_string(level);
            levelText.setStr(strLevel);
        }

        if (ball.getLife() <= 0)
        {
            leaderboard.addScore(ball.getScore());
            state = State::GAME_OVER;
        }

        if (ball.isReset() == true)
        {
            state = State::PAUSED;
            ball.resetBall();
            paddle.reset();
        }

        //Render
       
        if (state == State::LOADING)
        {
            window.clear();
            start.draw(window);
            score.draw(window);
            quit.draw(window);
            window.display();

        }

        if (state == State::PLAYING)
        {
            window.clear();
            lives.draw(window);
            scoreText.draw(window);
            levelText.draw(window);
            ball.draw(window);
            paddle.draw(window);
            for (unsigned int i = 0; i < bricks.size(); i++)
            {
                bricks[i]->draw(window);
            }
            window.display();
        }

        if (state == State::PAUSED)
        {
            window.clear();
            pauseText.draw(window);
            window.display();
        }

        if (state == State::LEVEL_UP)
        {
            window.clear();
            String strNewLevel = "Next level: " + std::to_string(level);
            newLevelText.setStr(strNewLevel);
            newLevelText.draw(window);
            window.display();  
        }

        if (state == State::SCORE)
        {
            window.clear();
            leaderboard.getScore(window);
            window.display();
        }

        if (state == State::GAME_OVER)
        {
            window.clear();
            gameOver.draw(window);
            leaderboard.getScore(window);
            window.display();
        }
   
    }
    
    for (unsigned int i = 0; i < bricks.size(); i++)
    {
        delete bricks[i];
    }
    bricks.clear();
    
    return 0;
}

void collision(Ball& m_ball, Paddle& m_paddle)
{
    if (m_ball.getBounds().intersects(m_paddle.getBounds()) && !(m_ball.getPosition().y > m_paddle.getPosition().y))
    {
        float velo_x = m_ball.getVeloX();
        float velo_y = m_ball.getVeloY();
        if (m_ball.getPosition().x < m_paddle.getPosition().x + m_paddle.getWidth() / 3)
        {
            m_ball.setVeloY(velo_y * -1);
            m_ball.setVeloX(velo_x * -1);
        }
        else if (m_ball.getPosition().x > m_paddle.getPosition().x + m_paddle.getWidth() / 3 && m_ball.getPosition().x < m_paddle.getPosition().x + 2 *(m_paddle.getWidth() / 3))
        {
            
            m_ball.setVeloY(velo_y * -1);
            m_ball.setVeloX(velo_x * -0.5f);
        }
        else if (m_ball.getPosition().x > m_paddle.getPosition().x + 2*( m_paddle.getWidth() / 3))
        {
            m_ball.setVeloY(velo_y * -1);
            m_ball.setVeloX(velo_x);
        }
        
    }
}

void brick_collision(Ball& m_ball, Brick* m_brick, Paddle& m_paddle)
{
    float velo_y = m_ball.getVeloY();
    if (m_ball.getBounds().intersects(m_brick->getBounds()))
    {
        m_brick->boosterBall(m_ball, m_paddle);
        m_ball.setVeloY(velo_y);
        m_brick->destroy(m_ball);
        
    }
}