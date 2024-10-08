#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"

#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  //Add initial point to stack. Code by Gerald Kaufman
  auto sideOver2 = w->GetSize() / 2;
  if (stack.empty() && !visited[-sideOver2][-sideOver2]) {
    stack.emplace_back(-sideOver2, -sideOver2);
    return true;
  }

  if(!stack.empty()) {
    Point2D pointTmp = stack.back();
    std::vector<Point2D> visitables = getVisitables(w, pointTmp);

    //Check for neighbors
    if (!visitables.empty()) {
      //Mark top cell as visited
      w->SetNodeColor(pointTmp, Color::Red);
      visited[pointTmp.x][pointTmp.y] = true;

      //Choose neighbor
      Point2D nextPoint = visitables[getRandomNumber() % visitables.size()];
      Point2D directionToPoint = nextPoint - pointTmp;

      //Remove the wall in direction
      if(directionToPoint.y == -1) { //Up
        w->SetNorth(pointTmp, false);
      }
      else if (directionToPoint.x == 1) { //Right
        w->SetEast(pointTmp, false);
      }
      else if (directionToPoint.y == 1) { //Down
        w->SetSouth(pointTmp, false);
      }
      else if (directionToPoint.x == -1) { //Left
        w->SetWest(pointTmp, false);
      }

      //Add new point to stack
      stack.push_back(nextPoint);
    }
    else {
      w->SetNodeColor(pointTmp, Color::Black);
      stack.pop_back();
    }
  }
  //If stack empty return false
  return !stack.empty();
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

int RecursiveBacktrackerExample::getRandomNumber() {
  int randomNumbers[] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7,
    30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60,
    28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53,
    51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13,
    12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  randomNumIndex++;
  if(randomNumIndex > sizeof(randomNumbers) / sizeof(randomNumbers[0])) {
    randomNumIndex = 0;
  }

  return randomNumbers[randomNumIndex];
}


std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  //Check colors of neighboring points, visited list, and bounds to determine if they have been visited
  if(w->GetNodeColor(p.Up()) == Color::DarkGray && !visited[p.x][p.y - 1] && abs(p.y - 1) <= sideOver2) {
    visitables.push_back(Point2D(p.x, p.y - 1));
  }
  if(w->GetNodeColor(p.Right()) == Color::DarkGray && !visited[p.x + 1][p.y] && abs(p.x + 1) <= sideOver2) {
    visitables.push_back(Point2D(p.x + 1, p.y));
  }
  if(w->GetNodeColor(p.Down()) == Color::DarkGray && !visited[p.x][p.y + 1] && abs(p.y + 1) <= sideOver2) {
    visitables.push_back(Point2D(p.x, p.y + 1));
  }
  if(w->GetNodeColor(p.Left()) == Color::DarkGray && !visited[p.x - 1][p.y] && abs(p.x - 1) <= sideOver2) {
    visitables.push_back(Point2D(p.x - 1, p.y));
  }

  return visitables;
}
