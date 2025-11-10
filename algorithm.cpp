#include "algorithm.h"
#include "calculations.h"
#include "config.h"
#include <cmath>
#include <iostream>

static bool attackerPlaying = true;

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &defender);

static HomeBotPlan computeDefenderPlan(GameState &game, HomeBot &attacker, HomeBot &defender);

static void assignRoles(HomeBot &attacker, HomeBot &defender);

void algorithmInit(GameState &game) {
	assignRoles(game.homeBot1, game.homeBot2);
}

TeamPlan computeTeamPlan(GameState &game) {
	TeamPlan plan = {};
	if (game.homeBot1.getRole() == BotRole::ATTACKER && game.homeBot2.getRole() == BotRole::DEFENDER) {
		Coords defenderPos = game.homeBot2.getPosition();
		Coords attackerPos = game.homeBot1.getPosition();
		// Revisamos si el defensor esta fuera de juego, en ese caso el atacante (bot1) pasa a defender.
		if (defenderPos.y < MAX_HEIGHT) {
			assignRoles(game.homeBot2, game.homeBot1);
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
		// Revisamos si el defensor esta fuera de juego, en ese caso el atacante (bot2) pasa a defender.
		if (defenderPos.y < MAX_HEIGHT) {
			assignRoles(game.homeBot1, game.homeBot2);
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
	plan.actions.kicker = 1;
	return plan;
}

static HomeBotPlan computeAttackerPlan(GameState &game, HomeBot &attacker, HomeBot &deffender) {
	Coords attackerPos = attacker.getPosition();
	HomeBotPlan plan = { .posXZ = {attackerPos.x, attackerPos.z} };
	Coords ballPos = game.ball.getPosition();
	Coords rivalGoalCenter = { (FIELD_LENGTH / 2) , 0, 0 };
	plan.rotY = getAngle(attackerPos, ballPos);
	// Si el atacante esta detras de la pelota
	float theta = getAngle(ballPos, rivalGoalCenter) - PI;
	if (attackerPos.x >= ballPos.x) { 
		Coords destination = { 
			-ATTACKER_BALL_DISTANCE * sin(theta) + ballPos.x ,
			attackerPos.y, 
			-ATTACKER_BALL_DISTANCE * cos(theta) + ballPos.z 
		};

		// Si el destino esta fuera del campo de juego el robot se dirige hasta la posicion limite.
		if(offLimitsCheck(destination)) {
			// Se revisa el limite en la coordenada x.
			if (destination.x < Y_MIN + AREA_LENGTH) {
				destination.x = Y_MIN + AREA_LENGTH + EPSILON;
			}
			else if (destination.x > Y_MAX) {
				destination.x = Y_MAX - EPSILON;
			}
			// Se revisa el limite en la coordenada z.
			if (destination.z < X_MIN) {
				destination.z = X_MIN + EPSILON;
			}
			else if (destination.z > X_MAX) {
				destination.z = X_MAX - EPSILON;
			}
		}

		plan.posXZ.x = destination.x;
		plan.posXZ.z = destination.z;
	}
	// Si el atacante esta delante de la pelota y esta se encuentra dentro de la cancha.
	else if (!offLimitsCheck(ballPos) && attackerPos.x < ballPos.x) { 
		float attackerRot = attacker.getRotation().rotY + PI;
		plan.posXZ.x = -ATTACKER_SHOOT_DISTANCE * sin(theta) + ballPos.x;
		plan.posXZ.z = -ATTACKER_SHOOT_DISTANCE * cos(theta) + ballPos.z;
		float bestAngle = getAngle(attackerPos, rivalGoalCenter);
		bool shouldKick = attackerRot <= bestAngle-PI + ANGLE_EPSILON && attackerRot >= bestAngle-PI - ANGLE_EPSILON;
		if (getDistance(attackerPos, ballPos) < EPSILON && !shouldKick) {
			plan.actions.dribbler = 1;
			plan.actions.kicker = 0;
		}
		if (shouldKick) {
			plan.actions.dribbler = 0;
			plan.actions.kicker = 1;
		}
		else {
			plan.rotY = bestAngle;
		}
	}
	return plan;
}

static void assignRoles(HomeBot &attacker, HomeBot &defender) {
	defender.setRole(BotRole::DEFENDER);
	attacker.setRole(BotRole::ATTACKER);
}
