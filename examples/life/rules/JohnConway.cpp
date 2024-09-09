#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int neighborsCount, y, x;

  for (y = 0; y < world.SideSize(); y++) {
    for (x = 0; x < world.SideSize(); x++) {
      Point2D pointTmp = Point2D(x, y);
      neighborsCount = CountNeighbors(world, pointTmp);

      //Check neighbor size
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
int count = 0;

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      Point2D pointTmp = Point2D(point.x + x, point.y + y);
      //Check if in bounds
      //Mirroring
      count += world.Get(pointTmp);
    }
  }

  return count;
}
