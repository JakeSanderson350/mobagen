#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

    float desiredDistance = desiredMinimalDistance;

    /*// todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2f position = boid->transform.position;
        int countCloseFlockmates = 0;
        // todo: find and apply force only on the closest mates
    }*/

  for (const Boid* boidTmp : neighborhood)
  {
    //Remove self
    if(boidTmp->getPosition() == boid->getPosition()) {
      continue;
    }

    //Calc Separation vector
    Vector2f separationVec = boid->getPosition() - boidTmp->getPosition();

    //Calc distance
    float distance = sqrt((separationVec.x * separationVec.x) + (separationVec.y * separationVec.y));

    //If inside sep radius add force
    if (distance < desiredDistance && distance > 0.01f) {
      //normalize sep vector
      separationVec = separationVec / distance;
      float forceApply = 1 / distance;
      separatingForce = separationVec * forceApply;
    }
  }

  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
