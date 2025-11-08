#include "algorithm.h"
#include "calculations.h"

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &defender);

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &attacker, HomeBot &defender);

static void assignRoles(GameState &game);

void algorithmInit(GameState &game) {
	assignRoles(game);
}

TeamPlan computeTeamPlan(GameState &game) {
	TeamPlan plan = {};
	if (game.homeBot1.getRole() == BotRole::ATTACKER && game.homeBot2.getRole() == BotRole::DEFENDER) {
		plan.hb1Plan = computeAttackerPlan(game, game.homeBot1, game.homeBot2);
		plan.hb2Plan = computeDefenderPlan(game, game.homeBot1, game.homeBot2);
	}
	else if (game.homeBot1.getRole() == BotRole::DEFENDER && game.homeBot2.getRole() == BotRole::ATTACKER) {
		plan.hb1Plan = computeDefenderPlan(game, game.homeBot2, game.homeBot1);
		plan.hb2Plan = computeAttackerPlan(game, game.homeBot2, game.homeBot1);
	}
	return plan;
}

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &attacker, HomeBot &defender) {
	HomeBotPlan plan = {};
	if (game.ball.getPosition().x > 0) { // si nuestro atacante tiene la pelota y esta del lado opuesto de la cancha

	}
	return plan;
}

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &defender) {
	HomeBotPlan plan = {};
	
	return plan;
}

static void assignRoles(GameState &game) {
	game.homeBot1.setRole(BotRole::ATTACKER);
	game.homeBot2.setRole(BotRole::DEFENDER);
}
