#pragma once

#include <vector>

typedef std::vector<float> Parameters_t;

enum {
    X_POSITION,
    Z_POSITION,
    ROTATION
};

enum {
    DRIBBLER,
    KICK,
    CHIRP
};

class HomeBot {
public:
    HomeBot(float xInitial, float zInitial, float InitialRot) {
        x = xInitial;
        z = zInitial;
        rotation = InitialRot;
        dribbler = 0;
        kick = 0;
        chirp = 0;
    }

    Parameters_t getPosition() {
        return Parameters_t{ x, z, rotation };
    }

    Parameters_t getBallControl() {
        return Parameters_t{ dribbler, kick, chirp };
    }

    void setBallControl(float dribblerValue, float kickValue, float chirpValue) {
        dribbler = dribblerValue;
        kick = kickValue;
        chirp = chirpValue;
    }

    void setPosition(float xValue, float zValue, float rotationValue) {
        x = xValue;
        z = zValue;
        rotation = rotationValue;
    }

private:
    float x, z, rotation;
    float dribbler, kick, chirp;
};