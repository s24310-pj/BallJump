#ifndef BALLJUMP_TRANSFORMCOMPONENT_H
#define BALLJUMP_TRANSFORMCOMPONENT_H

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {

public:

    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    bool hasGravity = false;
    bool isGrounded = false;

    const float gravity = 0.1f;

    TransformComponent() {
        position.Zero();
    }

    TransformComponent(float x, float y, bool gravitation) {
        position.x = x;
        position.y = y;
        hasGravity = gravitation;
    }

    TransformComponent(float x, float y, int h, int w, int sc) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override {
        velocity.Zero();
    }

    void update() override {

        if (hasGravity) {
            velocity.y += gravity;
        }


        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};

#endif //BALLJUMP_TRANSFORMCOMPONENT_H
