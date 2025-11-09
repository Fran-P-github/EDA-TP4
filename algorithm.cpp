#include "algorithm.h"
#include "calculations.h"
#include "config.h"
#include <cmath>
#include <iostream>

static bool attackerPlaying = true;

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &defender);

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &attacker, HomeBot &defender);

static void assignRoles(GameState &game);

void algorithmInit(GameState &game) {
	assignRoles(game);
}

TeamPlan computeTeamPlan(GameState &game) {
	TeamPlan plan = {};
	if (game.homeBot1.getRole() == BotRole::ATTACKER && game.homeBot2.getRole() == BotRole::DEFENDER) {
		Coords defenderPos = game.homeBot2.getPosition();
		Coords attackerPos = game.homeBot1.getPosition();
		// Revisamos si el defensor esta fuera de juego, en ese caso el atacante (bot1) pasa a defender.
		if (defenderPos.y < MAX_HEIGHT) {
			game.homeBot2.setRole(BotRole::ATTACKER);
			game.homeBot1.setRole(BotRole::DEFENDER);
			attackerPlaying = false;
			HomeBotPlan planAFK = { .posXZ = {defenderPos.x, defenderPos.z} };
			plan.hb1Plan = computeDefenderPlan(game, game.homeBot2, game.homeBot1);
			plan.hb2Plan = planAFK;
		}
		else {
			HomeBotPlan attackerPlan;
			attackerPos.y < MAX_HEIGHT ?
				// Si el atacante esta fuera de juego, se lo mantiene AFK
				(attackerPlaying = false, attackerPlan = { .posXZ = {attackerPos.x, attackerPos.z} }) :
				// Si el atacante esta jugando, se llama a su algoritmo.
				(attackerPlaying = true, attackerPlan = computeAttackerPlan(game, game.homeBot1, game.homeBot2));
			plan.hb1Plan = attackerPlan;
			plan.hb2Plan = computeDefenderPlan(game, game.homeBot1, game.homeBot2);
		}
	}
	else if (game.homeBot1.getRole() == BotRole::DEFENDER && game.homeBot2.getRole() == BotRole::ATTACKER) {
		Coords defenderPos = game.homeBot1.getPosition();
		Coords attackerPos = game.homeBot2.getPosition();
		// Revisamos si el defensor esta fuera de juego, en ese caso el atacante (bot1) pasa a defender.
		if (defenderPos.y < MAX_HEIGHT) {
			game.homeBot1.setRole(BotRole::ATTACKER);
			game.homeBot2.setRole(BotRole::DEFENDER);
			attackerPlaying = false;
			HomeBotPlan planAFK = { .posXZ = {defenderPos.x, defenderPos.z} };
			plan.hb2Plan = computeDefenderPlan(game, game.homeBot1, game.homeBot2);
			plan.hb1Plan = planAFK;
		}
		else {
			HomeBotPlan attackerPlan;
			attackerPos.y < MAX_HEIGHT ?
				// Si el atacante esta fuera de juego, se lo mantiene AFK.
				(attackerPlaying = false, attackerPlan = { .posXZ = {attackerPos.x, attackerPos.z} }) :
				// Si el atacante esta jugando, se llama a su algoritmo.
				(attackerPlaying = true, attackerPlan = computeAttackerPlan(game, game.homeBot2, game.homeBot1));
			plan.hb1Plan = computeDefenderPlan(game, game.homeBot2, game.homeBot1);
			plan.hb2Plan = attackerPlan;
		}
	}
	return plan;
}

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &attacker, HomeBot &defender) {
	HomeBotPlan plan = {};
	Coords defenderPos = defender.getPosition();
	Coords ballPos = game.ball.getPosition();
	Coords goalCenter = { -1 * (FIELD_LENGTH / 2) , 0, 0 };
	plan.rotY = getAngle(defenderPos, ballPos);
	if (ballPos.x > 0 && attackerPlaying && getDistance(attacker.getPosition(), ballPos) <= EPSILON) {
		// si nuestro atacante tiene la pelota y esta del lado opuesto de la cancha
		plan.posXZ.z = goalCenter.z;
		plan.posXZ.x = goalCenter.x + DEFENDER_CIRCLE_RADIUS;
	}
	else {
		float theta = getAngle(goalCenter, ballPos) - PI;
		plan.posXZ.x = DEFENDER_CIRCLE_RADIUS * sin(theta) + goalCenter.x;
		plan.posXZ.z = DEFENDER_CIRCLE_RADIUS * cos(theta) + goalCenter.z;
	}
	return plan;
}

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &deffender) {
	HomeBotPlan plan = {};
	Coords attackerPos = attacker.getPosition();
	Coords ballPos = game.ball.getPosition();
	Coords goalCenter = { (FIELD_LENGTH / 2) , 0, 0 };
	plan.rotY = getAngle(attackerPos, ballPos);
	if (attackerPos.x > ballPos.x) { // si el atacante esta detras de la pelota
		float theta = getAngle(ballPos, goalCenter) - PI;
		plan.posXZ.x = -DEFENDER_CIRCLE_RADIUS * sin(theta) + ballPos.x;
		plan.posXZ.z = -DEFENDER_CIRCLE_RADIUS * cos(theta) + ballPos.z;
	}
	else if (attackerPos.x < ballPos.x && getDistance(attackerPos, ballPos) < EPSILON / 1.2) { // si el atacante tiene la pelota
		plan.actions.dribbler = 1;
		plan.rotY = getAngle(attackerPos, goalCenter);
		plan.posXZ.x = goalCenter.x - AREA_LENGTH;
		plan.posXZ.z = goalCenter.z;
	}
	else if (!offLimitsCheck(ballPos) && attackerPos.x < ballPos.x) { // si el atacante esta delante de la pelota
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
