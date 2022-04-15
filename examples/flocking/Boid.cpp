#include "Boid.h"
#include "behaviours/FlockingRule.h"
#include <iostream>
#include "World.h"

using namespace utils;

std::vector<Boid*> Boid::computeBoidNeighborhood() {
    std::vector<Boid*> neighborhood;

    float detectionRadiusSquared = detectionRadius * detectionRadius;
    auto position = getPosition();

    //We compare distance to squared distances to avoid doing square roots.

    for (const auto& boid : world->boids) {
        if (boid != this) {

            float squareDistance = Vector2::getSquaredDistance(position, boid->getPosition());

            //Verify if boid is close enough to be part of the neighborhood
            if (squareDistance <= detectionRadiusSquared)
            {
                neighborhood.push_back(boid);
            }
        }

    }

    return neighborhood;
}


Boid::Boid(Engine *pEngine, World *pWorld) : Particle(pEngine), world(pWorld) {}

void Boid::Update(const float deltaTime) {
    Particle::Update(deltaTime);
    std::vector<Boid*> neighbordhood = computeBoidNeighborhood();

    for (auto& rule : rules)
    {
        auto weightedForce = rule->computeWeightedForce(neighbordhood, this);
        //std::cout << typeid(*rule).name() << " Force : " << vector2::getMagnitude(weightedForce) << std::endl;
        applyForce(weightedForce);
    }
}

void Boid::OnDraw(SDL_Renderer *renderer) {
    Particle::OnDraw(renderer); // super()

    if (drawDebugRadius)
        circle.Draw(
                renderer,
                transform.position,
                {detectionRadius,detectionRadius},
                Vector2::zero(),
                Vector3::Blue());

    //Display rules
    if (drawDebugRules)
        for (auto& rule : rules)
            if (rule->isEnabled)
                rule->draw(*this, renderer);
}
