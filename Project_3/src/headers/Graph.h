#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include <vector>

template <typename T> class Graph {
public:
  Graph() {}

  void insert_vertex(const Vertex<T> &ver);
  void add_edge(const Vertex<T> &ver1, const Vertex<T> &ver2, int distance,
                int cost);

  Graph<T> createUndirectedGraph();

  void countConnections();
  void primMST();

  void print() const;

  void DFS(Vertex<T> &ver);
  void BFS(Vertex<T> &ver);

  void dijkstra_shortest_path(const Vertex<T> &src, const Vertex<T> &dest);
  void dijkstra_to_state(const Vertex<T>& src, const T& state);
  void dijkstra_with_stops(const Vertex<T> &src, const Vertex<T> &dest, int stops);
  void kruskalMST();    

private:
  std::vector<Vertex<T>> vertices;      // nodes
  std::vector<std::vector<Edge>> edges; // connections

  void clean_visited();

  void DFS_helper(Vertex<T> &ver);
  int get_vertex_index(const Vertex<T> &ver);

  bool edgeExists(const int &src, const int &dest);
  int getEdgeCost(const int &src, const int &dest);
  void addUndirectedEdge(const int &src, const int &dest, const int &cost);
};

#include "../Graph.tpp"

#endif
