#pragma once

#include "game.h"

class Comm {
public: 
	bool updateGame(GameState &game);
private: 
	void poseHomeBots(HomeBotPlan &homeBot1, HomeBotPlan &homeBot2);
};