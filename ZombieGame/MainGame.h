#pragma once

#include <SkeletonEngine/Window.h>
#include <SkeletonEngine/GLSLProgram.h>
#include <SkeletonEngine/Camera2D.h>
#include <SkeletonEngine/InputManager.h>
#include <SkeletonEngine/SpriteBatch.h>

#include "Player.h"
#include "Level.h"
#include "Bullet.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void initLevel();
	void gameLoop();
	void processInput();
	void drawGame();
	void updateAgents();
	void updateBullets();
	void checkVictory();

	SkeletonEngine::Window window_;
	SkeletonEngine::GLSLProgram texture_program_;
	SkeletonEngine::InputManager input_manager_;
	SkeletonEngine::Camera2D camera_;
	SkeletonEngine::SpriteBatch sprite_batch_; ///< for drawing all agents

	int height_;
	int width_;

	std::vector<Level*> levels_;
	std::vector<Human*> humans_;
	std::vector<Zombie*> zombies_;
	std::vector<Bullet> bullets_;
	Player* player_;
	GameState game_state_;
	float fps_;
	int current_level_;

	// stats
	int num_humans_kiled_;
	int num_zombies_killed_;
};

