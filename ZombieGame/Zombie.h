#pragma once
#include "Agent.h"

class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos);

	virtual void update(const std::vector<std::string>& level_data,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		float delta_time) override;

private:
	Human* getNearestHuman(std::vector<Human*> humans);
};

