#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  int neighborsCount;

  for (int y = 0; y < world.SideSize(); y++) {
    for (int x = 0; x < world.SideSize(); x++) {
      Point2D pointTmp = Point2D(x, y);
      neighborsCount = CountNeighbors(world, pointTmp);

      //Check neighbor size
      //If cell is alive
      if (world.Get(pointTmp)) {
        //Cell with less than 2 neighbors dies
        if(neighborsCount < 2) {
          world.SetNext(pointTmp, false);
        }
        //Cell with 2 or 3 neighbors live
        else if (neighborsCount <= 3) {
          world.SetNext(pointTmp, true);
        }
        //Cell with more than 3 neighbors dies
        else if (neighborsCount > 3) {
          world.SetNext(pointTmp, false);
        }
      }
      //If cell is dead
      else {
        //Dead cells with 3 neighbors live
        if (neighborsCount == 3) {
          world.SetNext(pointTmp, true);
        }
      }
    }
  }

  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      Point2D pointTmp = Point2D(point.x + x, point.y + y);

      //Don't count itself
      if(y == 0 && x == 0) {
        continue;
      }
      //If cell is alive add to count
      else {
        count += world.Get(pointTmp);
      }
    }
  }

  return count;
}
