#include "algorithm.h"


static HomeBotPlan computeAttackerPlan(GameState &game);

static HomeBotPlan computeDefenderPlan(GameState &game);

static void assignRoles(GameState &game);

TeamPlan computeTeamPlan(GameState &game) {
	TeamPlan plan = {};
	return plan;
}

static HomeBotPlan computeDefenderPlan(GameState &game) {

}

static HomeBotPlan computeAttackerPlan(GameState &game) {

}

static void assignRoles(GameState &game) {
	game.homeBot1.setRole(BotRole::ATTACKER);
	game.homeBot2.setRole(BotRole::DEFENDER);
}
