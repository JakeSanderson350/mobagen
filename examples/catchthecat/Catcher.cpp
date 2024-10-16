#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;

  std::vector<Point2D> pathToBorder = generatePath(world);

  //return first point in path
  if (!pathToBorder.empty()) {
    return pathToBorder[0];
  }

  //return random point if path is empty
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
