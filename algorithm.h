#include <vector>

typedef std::vector<float> Position_t;

enum {
    X_POSITION,
    Z_POSITION,
    ROTATION
};

class HomeBot {
public:
    HomeBot() {

    }
    ~HomeBot() {}
    Position_t getPosition() {
        return std::vector{ x, z, rotation };
    }

private:
    float x, z, rotation;
};