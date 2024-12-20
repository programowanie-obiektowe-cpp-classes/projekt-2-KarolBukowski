#include "Game.hpp"
#include <fstream>
#include <iostream>

void Game::DeleteInactiveLasers()
{
    auto& spaceship_lasers = spaceship.getLasers();

    for (auto it = spaceship_lasers.begin(); it != spaceship_lasers.end();)
    {
        if (!it->getStatus())
        {
            it = spaceship_lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    auto& alien_lasers = Alien::getLasers();

    for (auto it = alien_lasers.begin(); it != alien_lasers.end();)
    {
        if (!it->getStatus())
        {
            it = alien_lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::CreateObstacles()
{
    int   obstacle_width = Obstacle::getGrid()[0].size() * Block::getBlockSizePixels();
    float gap            = (GetScreenWidth() - (4 * obstacle_width)) / 5;

    for (int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacle_width;
        float offset_y = GetScreenHeight() - 200;
        obstacles.emplace_back(Obstacle({offset_x, offset_y}));
    }
}

void Game::CreateAliens()
{
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alien_type;
            if (row == 0)
            {
                alien_type = 3;
            }
            else if (row == 1 || row == 2)
            {
                alien_type = 2;
            }
            else
            {
                alien_type = 1;
            }

            float pos_x = 75 + column * 55;
            float pos_y = 110 + row * 55;
            aliens.emplace_back(Alien(alien_type, {pos_x, pos_y}));
        }
    }
}

void Game::MoveAliens()
{

    bool change_direction = false;
    for (auto& alien : aliens)
    {
        float alien_position_x = alien.getPosition().x;
        if (alien_position_x >
                GetScreenWidth() - alien.alien_images[alien.getType() - 1].width - WINDOW_OFFSET_SIDE__ ||
            alien_position_x < WINDOW_OFFSET_SIDE__)
        {
            change_direction = true;
            Alien::ChangeDirection();
            break;
        }
    }

    for (auto& alien : aliens)
    {
        alien.MoveSideways();
        if (change_direction)
        {
            alien.MoveDownward();
        }
    }
}

void Game::AlienShootLaser()
{
    for (auto& alien : aliens)
    {
        alien.FireLaser();
    }
}

void Game::CheckForCollisions()
{
    auto& spaceship_lasers = spaceship.getLasers();
    auto& alien_lasers     = Alien::getLasers();
    for (auto& laser : spaceship_lasers)
    {

        for (auto it = aliens.begin(); it != aliens.end();)
        {
            if (CheckCollisionRecs(it->getRect(), laser.getRect()))
            {
                PlaySound(explosion_sound);
                if (it->getType() == 1)
                {
                    score += 100;
                }
                else if (it->getType() == 2)
                {
                    score += 200;
                }
                else
                {
                    score += 300;
                }
                CheckForHighscore();

                it = aliens.erase(it);
                laser.setStatus(false);
            }
            else
            {
                ++it;
            }
        }
        for (auto& obstacle : obstacles)
        {
            auto& blocks = obstacle.getBlocks();
            for (auto it = blocks.begin(); it != blocks.end();)
            {
                if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                {
                    it = blocks.erase(it);
                    laser.setStatus(false);
                }
                else
                {
                    ++it;
                }
            }
        }
        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect()))
        {
            PlaySound(explosion_sound);
            score += 500;
            CheckForHighscore();
            mysteryship.setStatus(false);
            laser.setStatus(false);
        }
    }

    for (auto& laser : alien_lasers)
    {
        if (CheckCollisionRecs(spaceship.getRect(), laser.getRect()))
        {
            PlaySound(explosion_sound);
            lives--;
            laser.setStatus(false);
        }
        for (auto& obstacle : obstacles)
        {
            auto& blocks = obstacle.getBlocks();

            for (auto it = blocks.begin(); it != blocks.end();)
            {
                if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                {
                    it = blocks.erase(it);
                    laser.setStatus(false);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    for (auto& alien : aliens)
    {
        if (CheckCollisionRecs(spaceship.getRect(), alien.getRect()))
        {
            GameOver();
        }
        for (auto& obstacle : obstacles)
        {
            auto& blocks = obstacle.getBlocks();

            for (auto it = blocks.begin(); it != blocks.end();)
            {
                if (CheckCollisionRecs(it->getRect(), alien.getRect()))
                {
                    it = blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }
}

void Game::GameOver()
{
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    Alien::getLasers().clear();
    obstacles.clear();
}

void Game::InitGame()
{
    CreateObstacles();
    CreateAliens();
    Alien::ApplyDifficulty(difficulty);
    Spaceship::ApplyDifficulty(difficulty);
    lives     = 3;
    level     = 1;
    run       = true;
    score     = 0;
    highscore = LoadHighscoreFromFile();
}

void Game::InitNextLevel()
{
    difficulty.IncreaseDifficulty();
    Reset();
    CreateObstacles();
    CreateAliens();
    Alien::ApplyDifficulty(difficulty);
    Spaceship::ApplyDifficulty(difficulty);
    level++;
    lives++;
}

void Game::CheckForHighscore()
{
    if (score > highscore)
    {
        highscore = score;
        SaveHighscoreToFile(highscore);
    }
}

void Game::SaveHighscoreToFile(int highscore)
{
    std::ofstream highscore_file("highscore.txt");
    if (highscore_file.is_open())
    {
        highscore_file << highscore;
        highscore_file.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::LoadHighscoreFromFile()
{
    int           loaded_highscore = 0;
    std::ifstream highscore_file("highscore.txt");
    if (highscore_file.is_open())
    {
        highscore_file >> loaded_highscore;
        highscore_file.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file" << std::endl;
    }
    return loaded_highscore;
}

Game::Game()
{
    music           = LoadMusicStream("sounds/music.ogg");
    explosion_sound = LoadSound("sounds/explosion.ogg");
    PlayMusicStream(music);
    Alien::LoadImages();
    InitGame();
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(explosion_sound);
    Alien::UnloadImages();
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser : spaceship.getLasers())
    {
        laser.Draw();
    }

    for (auto& obstacle : obstacles)
    {
        obstacle.Draw();
    }

    for (auto& alien : aliens)
    {
        alien.Draw();
    }

    for (auto& laser : Alien::getLasers())
    {
        laser.Draw();
    }

    mysteryship.Draw();
}

void Game::Update()
{
    if (run)
    {

        for (auto& laser : spaceship.getLasers())
        {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();

        for (auto& laser : Alien::getLasers())
        {
            laser.Update();
        }

        DeleteInactiveLasers();

        mysteryship.Update();

        CheckForCollisions();

        if (aliens.empty())
        {
            InitNextLevel();
        }

        if (lives == 0)
        {
            GameOver();
        }
    }
}

void Game::HandleInput()
{
    if (run)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        }
        if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireLaser();
        }
    }
    else if (IsKeyDown(KEY_ENTER))
    {
        Reset();
        InitGame();
    }
}

bool Game::getStatus()
{
    return run;
}

int Game::getLives()
{
    return lives;
}

int Game::getLevel()
{
    return level;
}

int Game::getScore()
{
    return score;
}

int Game::getHighscore()
{
    return highscore;
}