#include "algorithm.h"


static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker);

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &defender);

static void assignRoles(GameState &game);

void algorithmInit(GameState &game) {
	assignRoles(game);
}

TeamPlan computeTeamPlan(GameState &game) {
	TeamPlan plan = {};
	if (game.homeBot1.getRole() == BotRole::ATTACKER && game.homeBot2.getRole() == BotRole::DEFENDER) {
		plan.hb1Plan = computeAttackerPlan(game, game.homeBot1);
		plan.hb2Plan = computeDefenderPlan(game, game.homeBot2);
	}
	else if (game.homeBot1.getRole() == BotRole::DEFENDER && game.homeBot2.getRole() == BotRole::ATTACKER) {
		plan.hb1Plan = computeDefenderPlan(game, game.homeBot1);
		plan.hb2Plan = computeAttackerPlan(game, game.homeBot2);
	}
	return plan;
}

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &defender) {
	HomeBotPlan plan = {};

	return plan;
}

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker) {
	HomeBotPlan plan = {};

	return plan;
}

static void assignRoles(GameState &game) {
	game.homeBot1.setRole(BotRole::ATTACKER);
	game.homeBot2.setRole(BotRole::DEFENDER);
}
