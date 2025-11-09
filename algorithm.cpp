#include "algorithm.h"
#include "calculations.h"
#include "config.h"
#include <cmath>
#include <iostream>
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
	Coords ballPos = game.ball.getPosition();
	Coords defenderPos = defender.getPosition();
	Coords goalCenter = { -1 * (FIELD_LENGTH/2) , 0, 0 };
	plan.rotY = getAngle(defenderPos, ballPos);
//	std::cerr << "BallPos: " << ballPos.x << "\nDist: " << getDistance(attacker.getPosition(), ballPos) << "\n\n";
	if (ballPos.x > 0 && getDistance(attacker.getPosition(), ballPos) <= EPSILON) { 
		// si nuestro atacante tiene la pelota y esta del lado opuesto de la cancha
		plan.posXZ.z = goalCenter.z;
		plan.posXZ.x = goalCenter.x + DEFENDER_CIRCLE_RADIUS;
	}
	else {
		float theta = getAngle(goalCenter, ballPos) - PI;
		plan.posXZ.x = DEFENDER_CIRCLE_RADIUS * sin(theta) + goalCenter.x;
		plan.posXZ.z = DEFENDER_CIRCLE_RADIUS * cos(theta) + goalCenter.z;
		//std::cerr << "theta: " << theta << "\n";
	}
	return plan;
}

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &defender) {
	HomeBotPlan plan = {};
	Coords ballPos = game.ball.getPosition();
	Coords attackerPos = attacker.getPosition();
	Coords goalCenter = { (FIELD_LENGTH / 2) , 0, 0 };
	plan.rotY = getAngle(attackerPos, ballPos);
	if (attackerPos.x > ballPos.x) { // si el atacante esta detras de la pelota
		float theta = getAngle(ballPos, goalCenter) - PI;
		plan.posXZ.x = -DEFENDER_CIRCLE_RADIUS * sin(theta) + ballPos.x;
		plan.posXZ.z = -DEFENDER_CIRCLE_RADIUS * cos(theta) + ballPos.z;
	}
	else if (attackerPos.x < ballPos.x && getDistance(attacker.getPosition(), ballPos) < EPSILON / 1.2) { // si el atacante tiene la pelota
		plan.actions.dribbler = 1;
		plan.rotY = getAngle(attackerPos, goalCenter);
		plan.posXZ.x = goalCenter.x - 0.05;
		plan.posXZ.z = goalCenter.z;
	}
	else if (attackerPos.x < ballPos.x) { // si el atacante esta delante de la pelota
		plan.posXZ.x = ballPos.x;
		plan.posXZ.z = ballPos.z;
	}
	else {
		plan.posXZ.x = attackerPos.x;
		plan.posXZ.z = attackerPos.z;
	}
	return plan;
}

static void assignRoles(GameState &game) {
	game.homeBot1.setRole(BotRole::ATTACKER);
	game.homeBot2.setRole(BotRole::DEFENDER);
}
