#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  if (neighborhood.size() > 1) {
    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    Vector2f centerMass = {0.0f, 0.0f};

    for (const Boid* boidTmp : neighborhood)
    {
      centerMass += boidTmp->getPosition();
    }

    // find center of mass
    centerMass /= neighborhood.size();

    // Get distance from boid to center of mass
    Vector2f cohesionVec = centerMass - boid->getPosition();

    float distance = sqrt((cohesionVec.x * cohesionVec.x) + (cohesionVec.y * cohesionVec.y));

    // Calc force
    float detectionRadius = boid->getDetectionRadius();

    if (distance <= detectionRadius) {
      //Normalize coh vector
      cohesionVec = cohesionVec / distance;
      cohesionForce = cohesionVec;
    }
    else {
      cohesionForce = {0.0f, 0.0f};
    }
  }

  return cohesionForce * weight;
}