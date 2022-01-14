#pragma once
#include "Component.h"
#include "Vector2.h"

class CircleCollisionComponent :
    public Component
{
public:
    CircleCollisionComponent(Actor* ownerP);
    CircleCollisionComponent() = delete;
    CircleCollisionComponent(const CircleCollisionComponent&) = delete;
    CircleCollisionComponent& operator=(const CircleCollisionComponent&) = delete;

    float getRadius() const;
    void setRadius(float radiusP);

    const Vector2 getCenter() const;

private:
    float radius;
};

bool Intersects(const CircleCollisionComponent& a, const CircleCollisionComponent& b);
