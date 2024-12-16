#include "Game.hpp"
#include <fstream>
#include <iostream>

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = alien_lasers.begin(); it != alien_lasers.end();)
    {
        if (!it->active)
        {
            it = alien_lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector< Obstacle > Game::CreateObstacles()
{
    int   obstacle_width = Obstacle::grid[0].size() * 3;
    float gap            = (GetScreenWidth() - (4 * obstacle_width)) / 5;

    for (unsigned int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacle_width;
        float offset_y = GetScreenHeight() - 200;
        obstacles.emplace_back(Obstacle({offset_x, offset_y}));
    }
    return obstacles;
}

std::vector< Alien > Game::CreateAliens()
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
    return aliens;
}

void Game::MoveAliens()
{
    for (auto& alien : aliens)
    {
        if (alien.position.x > GetScreenWidth() - alien.alien_images[alien.GetType() - 1].width - 25)
        {
            aliens_direction = -1;
            MoveDownAliens();
        }
        else if (alien.position.x < 25)
        {
            aliens_direction = 1;
            MoveDownAliens();
        }

        alien.Update(aliens_direction);
    }
}

void Game::MoveDownAliens()
{
    for (auto& alien : aliens)
    {
        alien.position.y += 4;
    }
}

void Game::AlienShootLaser()
{
    if (GetTime() - time_last_alien_fired >= 0.35 && !aliens.empty())
    {
        int    random_index = GetRandomValue(0, aliens.size() - 1);
        Alien& alien        = aliens[random_index];
        float  pos_x        = alien.position.x + alien.alien_images[alien.GetType() - 1].width / 2;
        float  pos_y        = alien.position.y + alien.alien_images[alien.GetType() - 1].height;
        alien_lasers.push_back(Laser({pos_x, pos_y}, 6));
        time_last_alien_fired = GetTime();
    }
}

void Game::CheckForCollisions()
{
    for (auto& laser : spaceship.lasers)
    {

        for (auto it = aliens.begin(); it != aliens.end();)
        {
            if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
            {
                PlaySound(explosion_sound);
                if (it->GetType() == 1)
                {
                    score += 100;
                }
                else if (it->GetType() == 2)
                {
                    score += 200;
                }
                else
                {
                    score += 300;
                }
                CheckForHighscore();

                it           = aliens.erase(it);
                laser.active = false;
            }
            else
            {
                ++it;
            }
        }
        for (auto& obstacle : obstacles)
        {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
                {
                    it           = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }
        if (CheckCollisionRecs(mysteryship.GetRect(), laser.GetRect()))
        {
            PlaySound(explosion_sound);
            score += 500;
            CheckForHighscore();
            mysteryship.active = false;
            laser.active       = false;
        }
    }

    for (auto& laser : alien_lasers)
    {
        if (CheckCollisionRecs(spaceship.GetRect(), laser.GetRect()))
        {
            PlaySound(explosion_sound);
            lives--;
            laser.active = false;
        }
        for (auto& obstacle : obstacles)
        {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(it->GetRect(), laser.GetRect()))
                {
                    it           = obstacle.blocks.erase(it);
                    laser.active = false;
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
        if (CheckCollisionRecs(spaceship.GetRect(), alien.GetRect()))
        {
            GameOver();
        }
        for (auto& obstacle : obstacles)
        {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(it->GetRect(), alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
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
    alien_lasers.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    obstacles                     = CreateObstacles();
    aliens                        = CreateAliens();
    aliens_direction              = 1;
    time_last_alien_fired         = 0.0;
    time_last_mysteryship_spawned = 0.0;
    mysteryship_spawn_interval    = GetRandomValue(10, 20);
    lives                         = 3;
    run                           = true;
    score                         = 0;
    highscore                     = LoadHighscoreFromFile();
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
    music           = LoadMusicStream("Sounds/music.ogg");
    explosion_sound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
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

    for (auto& laser : spaceship.lasers)
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

    for (auto& laser : alien_lasers)
    {
        laser.Draw();
    }

    mysteryship.Draw();
}

void Game::Update()
{
    if (run)
    {

        for (auto& laser : spaceship.lasers)
        {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();

        for (auto& laser : alien_lasers)
        {
            laser.Update();
        }

        DeleteInactiveLasers();

        if (GetTime() - time_last_mysteryship_spawned > mysteryship_spawn_interval)
        {
            mysteryship.Spawn();
            time_last_mysteryship_spawned = GetTime();
            mysteryship_spawn_interval    = GetRandomValue(10, 20);
        }

        mysteryship.Update();

        CheckForCollisions();
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
        else if (IsKeyDown(KEY_SPACE))
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
