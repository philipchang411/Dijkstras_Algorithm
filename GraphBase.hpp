#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <vector>
#include <string>

class GraphBase {
  virtual void addVertex(std::string label) = 0;
  virtual void removeVertex(std::string label) = 0;
  virtual void addEdge(std::string label1, std::string label2, unsigned long weight) = 0;
  virtual void removeEdge(std::string label1, std::string label2) = 0;
  virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) = 0;
};

#endif