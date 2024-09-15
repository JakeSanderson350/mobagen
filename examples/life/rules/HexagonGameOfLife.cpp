//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  int neighborsCount;

  for (int y = 0; y < world.SideSize(); y++) {
    for (int x = 0; x < world.SideSize(); x++) {
      Point2D pointTmp = Point2D(x, y);
      neighborsCount = CountNeighbors(world, pointTmp);

      //Check neighbor size
      //If cell is alive
      if (world.Get(pointTmp)) {
        //Cell with 1 or 0 neighbors die
        if(neighborsCount < 2) {
          world.SetNext(pointTmp, false);
        }
        //Cell with 2 neighbors live
        else if (neighborsCount < 3) {
          world.SetNext(pointTmp, true);
        }
        //Cells with 3 or more neighbors die
        else if (neighborsCount >= 3) {
          world.SetNext(pointTmp, false);
        }
      }
      //If cell is dead
      else {
        //Dead cells with 2 neighbors come back to life
        if (neighborsCount == 2) {
          world.SetNext(pointTmp, true);
        }
      }
    }
  }

  world.SwapBuffers();
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  bool rowEven = isEven(point.y);

  if (rowEven) {
    //TopLeft
    count += world.Get(Point2D(point.x - 1, point.y - 1));
    //TopRight
    count += world.Get(Point2D(point.x, point.y - 1));
    //BottomLeft
    count += world.Get(Point2D(point.x - 1, point.y + 1));
    //BottomRight
    count += world.Get(Point2D(point.x, point.y + 1));
  }
  else {
    //TopLeft
    count += world.Get(Point2D(point.x, point.y - 1));
    //TopRight
    count += world.Get(Point2D(point.x + 1, point.y - 1));
    //BottomLeft
    count += world.Get(Point2D(point.x, point.y + 1));
    //BottomRight
    count += world.Get(Point2D(point.x + 1, point.y + 1));
  }

  //Left and right
  count += world.Get(Point2D(point.x - 1, point.y));
  count += world.Get(Point2D(point.x + 1, point.y));

  return count;
}

bool HexagonGameOfLife::isEven(const int num) {
  return num % 2 == 0;
}

