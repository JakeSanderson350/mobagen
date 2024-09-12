#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int neighborsCount;

  for (int y = 0; y < world.SideSize(); y++) {
    for (int x = 0; x < world.SideSize(); x++) {
      Point2D pointTmp = Point2D(x, y);
      neighborsCount = CountNeighbors(world, pointTmp);

      //Check neighbor size
      if (world.Get(pointTmp)) {
        if(neighborsCount < 2) {
          world.SetNext(pointTmp, false);
        }
        else if (neighborsCount <= 3) {
          world.SetNext(pointTmp, true);
        }
        else if (neighborsCount > 3) {
          world.SetNext(pointTmp, false);
        }
      }
      else {
        if (neighborsCount == 3) {
          world.SetNext(pointTmp, true);
        }
      }
    }
  }

  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
int count = 0;

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      Point2D pointTmp = Point2D(point.x + x, point.y + y);
      //Check if in bounds
      //Mirroring
      if(y == 0 && x == 0) {
      }
      else {
        count += world.Get(pointTmp);
      }
    }
  }

  return count;
}
