#include "Player.h"

#include <SDL/SDL.h>

#include "Gun.h"

Player::Player() : curr_gun_idx_(-1)
{
	//Empty
}

Player::~Player()
{
	//Empty
}


void Player::init(float speed, glm::vec2 pos, SkeletonEngine::InputManager* input_manager, SkeletonEngine::Camera2D* camera, std::vector<Bullet>* bullet)
{
	speed_ = speed;
	position_ = pos;
	color_ = {0, 0, 185, 255};
	input_manager_ = input_manager;
	camera_ = camera;
	bullets_ = bullet;
	health_ = 150.0f;
}

void Player::update(const std::vector<std::string>& level_data,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float delta_time)
{
	// vertical movement
	if (input_manager_->isKeyDown(SDLK_w))
	{
		position_.y += speed_ * delta_time;
	}
	else if (input_manager_->isKeyDown(SDLK_s))
	{
		position_.y -= speed_ * delta_time;
	}

	// horizontal movement
	if (input_manager_->isKeyDown(SDLK_d))
	{
		position_.x += speed_ * delta_time;
	}
	else if (input_manager_->isKeyDown(SDLK_a))
	{
		position_.x -= speed_ * delta_time;
	}

	// selecting guns
	if (input_manager_->isKeyDown(SDLK_1) && guns_.size() >= 0)
	{
		curr_gun_idx_ = 0;
	}
	else if (input_manager_->isKeyDown(SDLK_2) && guns_.size() >= 1)
	{
		curr_gun_idx_ = 1;
	}
	else if (input_manager_->isKeyDown(SDLK_3) && guns_.size() >= 2)
	{
		curr_gun_idx_ = 2;
	}

	if (curr_gun_idx_ != -1)
	{
		glm::vec2 mouse_coords = input_manager_->getMouseCoords();
		mouse_coords = camera_->convertScreenToWorldCoords(mouse_coords);

		glm::vec2 center_pos = position_ + glm::vec2(AGENT_RADIUS);
		glm::vec2 direction = glm::normalize(mouse_coords - center_pos);

		guns_[curr_gun_idx_]->update(input_manager_->isKeyDown(SDL_BUTTON_LEFT),		// TODO: change back to isKeyDown at some point, test isKeyPressed
			center_pos,
			direction,
			*bullets_,
			delta_time);
	}

	collideWithLevel(level_data);
}

void Player::addGun(Gun* gun)
{
	guns_.push_back(gun);

	// if no gun equipped, equip gun
	if (curr_gun_idx_ == -1)
	{
		curr_gun_idx_ = 0;
	}
}
