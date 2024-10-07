#include "Agent.h"
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
  auto sideOver2 = w->getWorldSideSize() / 2;

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    Point2D pointTmp = frontier.top();
    frontierSet.erase(pointTmp);

    // mark current as visited
    visited[pointTmp] = true;

    //Check to see if current point is on the border
    if (pointTmp.x == sideOver2 || pointTmp.x == -sideOver2 || pointTmp.y == sideOver2 || pointTmp.y == -sideOver2) {
      borderExit = pointTmp;
      break;
    }

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> allNeighbors = getVisitableNeighbors(w, pointTmp);
    vector<Point2D> visitableNeighbors;
      //Check neighbors against visited and queue
    for (auto neighbor : allNeighbors) {
      if (!visited[neighbor] && !frontierSet.contains(neighbor)) {
        visitableNeighbors.push_back(neighbor);
      }
    }

    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    for (auto neighbor : visitableNeighbors) {
      cameFrom[neighbor] = pointTmp;
      frontier.push(neighbor);
      frontierSet.insert(neighbor);
    }

    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {
    Point2D currentPoint = borderExit;
    while (currentPoint != catPos) {
      path.push_back(currentPoint);
      currentPoint = cameFrom[currentPoint];
    }
  }
  return path;
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> visitables;
  Point2D pointTmp;

  //Check if not cat, not block, and in bounds
  pointTmp = w->NW(p);
  if (w->getCat() != pointTmp && !w->getContent(pointTmp) && w->isValidPosition(pointTmp)) {
    visitables.push_back(w->NW(p));
  }

  pointTmp = w->NE(p);
  if (w->getCat() != pointTmp && !w->getContent(pointTmp) && w->isValidPosition(pointTmp)) {
    visitables.push_back(w->NE(p));
  }

  pointTmp = w->E(p);
  if (w->getCat() != pointTmp && !w->getContent(pointTmp) && w->isValidPosition(pointTmp)) {
    visitables.push_back(w->E(p));
  }

  pointTmp = w->SE(p);
  if (w->getCat() != pointTmp && !w->getContent(pointTmp) && w->isValidPosition(pointTmp)) {
    visitables.push_back(w->SE(p));
  }

  pointTmp = w->SW(p);
  if (w->getCat() != pointTmp && !w->getContent(pointTmp) && w->isValidPosition(pointTmp)) {
    visitables.push_back(w->SW(p));
  }

  pointTmp = w->W(p);
  if (w->getCat() != pointTmp && !w->getContent(pointTmp) && w->isValidPosition(pointTmp)) {
    visitables.push_back(w->W(p));
  }
}
