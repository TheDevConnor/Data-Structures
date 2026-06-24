#include "headers/Graph.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <climits>
#include <queue>
#include <set>

template <typename T> void Graph<T>::insert_vertex(const Vertex<T> &ver) {
  if (get_vertex_index(ver) == -1) {
    vertices.push_back(ver); // insert the vertex to the array of vertices
    std::vector<Edge> tmp;
    edges.push_back(tmp); // insert empty vector to the edges
  }
}

template <typename T> int Graph<T>::get_vertex_index(const Vertex<T> &ver) {
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i].getData() == ver.getData()) {
      return i;
    }
  }

  return -1;
}

template <typename T>
void Graph<T>::add_edge(const Vertex<T> &ver1, const Vertex<T> &ver2,
                        int distance, int cost) {
  int i1 = get_vertex_index(ver1);
  int i2 = get_vertex_index(ver2);
  if (i1 == -1 || i2 == -1) {
    throw std::string("Add_edge: incorrect vertices");
  }
  Edge v(i1, i2, distance, cost);
  edges[i1].push_back(v);
}

template <typename T> void Graph<T>::print() const {
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << "{ " << vertices[i].getData() << ": ";
    for (int j = 0; j < edges[i].size(); j++) {
      std::cout << '{' << vertices[edges[i][j].dest].getData() << ", ";
      std::cout << edges[i][j].distance << "km, $";
      std::cout << edges[i][j].cost << "} ";
    }
    std::cout << " }\n";
  }
}

template <typename T> void Graph<T>::DFS(Vertex<T> &ver) {
  clean_visited();
  DFS_helper(ver);
  clean_visited();
}

template <typename T> void print_queue(std::queue<Vertex<T>> q) {
  while (!q.empty()) {
    std::cout << q.front().getData() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

template <typename T> void Graph<T>::BFS(Vertex<T> &ver) {
  clean_visited();

  int i = get_vertex_index(ver);
  if (i == -1) {
    throw std::string("BFS: Vertex is not in the graph");
  }
  std::queue<int> q;
  q.push(i);
  vertices[i].setVisited(true);

  while (!q.empty()) {
    int i = q.front();
    std::cout << vertices[i].getData() << ' ';
    for (int j = 0; j < edges[i].size(); j++) {
      int adjacent_ver = edges[i][j].dest;
      if (vertices[adjacent_ver].getVisited() == false) {
        vertices[adjacent_ver].setVisited(true);
        q.push(adjacent_ver);
      }
    }
    q.pop();
  }

  clean_visited();
}

template <typename T> void Graph<T>::clean_visited() {
  for (Vertex<T> &v : vertices) {
    v.setVisited(false);
  }
}

template <typename T> void Graph<T>::DFS_helper(Vertex<T>& ver) {
    int i = get_vertex_index(ver);
    if (i == -1)
        throw std::string("DFS: Vertex is not in the graph");

    vertices[i].setVisited(true);
    std::cout << vertices[i].getData() << ' ';

    for (int j = 0; j < edges[i].size(); j++) {
        Vertex<T> adjacent_ver = vertices[edges[i][j].dest];
        if (!adjacent_ver.getVisited())
            DFS_helper(adjacent_ver);
    }
}

template <typename T>
void Graph<T>::dijkstra_shortest_path(const Vertex<T> &src,
                                      const Vertex<T> &dest) {
  int i_src = get_vertex_index(src);
  int i_dest = get_vertex_index(dest);

  if (i_src == -1 || i_dest == -1) {
    throw std::string("Shortest path: incorrect vertices");
  }

  const int INF = INT_MAX;

  std::vector<int> distance(vertices.size(), INF);
  std::vector<int> cost(vertices.size(), INF);
  std::vector<int> previous(vertices.size(), -1);

  distance[i_src] = 0;
  cost[i_src] = 0;

  clean_visited();

  while (true) {
    int current = -1;
    int min_dist = INF;

    for (int i = 0; i < vertices.size(); i++) {
      if (!vertices[i].getVisited() && distance[i] < min_dist) {
        min_dist = distance[i];
        current = i;
      }
    }

    // No reachable vertices remain
    if (current == -1)
      break;

    // Reached destination
    if (current == i_dest)
      break;

    vertices[current].setVisited(true);

    for (const Edge &edge : edges[current]) {
      int neighbor = edge.dest;

      if (vertices[neighbor].getVisited())
        continue;

      int new_dist = distance[current] + edge.distance;
      int new_cost = cost[current] + edge.cost;

      if (new_dist < distance[neighbor]) {
        distance[neighbor] = new_dist;
        cost[neighbor] = new_cost;
        previous[neighbor] = current;
      }
    }
  }

  if (distance[i_dest] == INF) {
    std::cout << "No path exists.\n";
    return;
  }

  std::vector<int> path;

  for (int c = i_dest; c != -1; c = previous[c]) {
    path.push_back(c);
  }

  std::reverse(path.begin(), path.end());

  std::cout << "Path: ";
  for (int v = 0; v < path.size(); v++) {
    std::cout << vertices[path[v]].getData();

    if (v != path.size() - 1) {
      std::cout << " -> ";
    }
  }

  std::cout << "\nDistance: " << distance[i_dest] << "\nCost: " << cost[i_dest]
            << '\n';

  clean_visited();
}

template<typename T>
void Graph<T>::dijkstra_with_stops(const Vertex<T>& src, const Vertex<T>& dest, int stops) {
    int i_src = get_vertex_index(src);
    int i_dest = get_vertex_index(dest);
    if (i_src == -1 || i_dest == -1) {
        std::cout << "Source or destination airport not found.\n";
        return;
    }

    int hops = stops + 1; // stops = layovers, hops = edges traveled
    int n = vertices.size();
    const int INF = INT_MAX;

    // dp[k][v] = min distance from src to v using exactly k edges
    std::vector<std::vector<int>> dp(hops + 1, std::vector<int>(n, INF));
    std::vector<std::vector<int>> prev(hops + 1, std::vector<int>(n, -1));
    dp[0][i_src] = 0;

    for (int k = 1; k <= hops; k++) {
        for (int u = 0; u < n; u++) {
            if (dp[k - 1][u] == INF) continue;
            for (const Edge& e : edges[u]) {
                int nd = dp[k - 1][u] + e.distance;
                if (nd < dp[k][e.dest]) {
                    dp[k][e.dest] = nd;
                    prev[k][e.dest] = u;
                }
            }
        }
    }

    if (dp[hops][i_dest] == INF) {
        std::cout << "No path from " << src.getData() << " to " << dest.getData()
                  << " with exactly " << stops << " stop(s).\n";
        return;
    }

    std::vector<int> path;
    int cur = i_dest;
    for (int k = hops; k >= 1; k--) {
        path.push_back(cur);
        cur = prev[k][cur];
    }
    path.push_back(i_src);
    std::reverse(path.begin(), path.end());

    std::cout << "Path with " << stops << " stop(s): ";
    for (int v = 0; v < path.size(); v++) {
        std::cout << vertices[path[v]].getData();
        if (v != (int)path.size() - 1) std::cout << " -> ";
    }
    std::cout << "\nDistance: " << dp[hops][i_dest] << "\n";
}

template<typename T>
void Graph<T>::kruskalMST() {
    Graph<T> ug = createUndirectedGraph();
    int n = ug.vertices.size();
    if (n == 0) { std::cout << "Graph is empty.\n"; return; }

    // Collect unique edges
    std::vector<Edge> allEdges;
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++)
        for (const Edge& e : ug.edges[i])
            if (!seen[e.src][e.dest] && !seen[e.dest][e.src]) {
                allEdges.push_back(e);
                seen[e.src][e.dest] = true;
            }

    std::sort(allEdges.begin(), allEdges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    // Union-Find
    std::vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;

    std::function<int(int)> find = [&](int x) -> int {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    auto unite = [&](int x, int y) -> bool {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank[px] < rank[py]) std::swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        return true;
    };

    std::vector<Edge> mstEdges;
    int totalCost = 0;
    for (const Edge& e : allEdges)
        if (unite(e.src, e.dest)) {
            mstEdges.push_back(e);
            totalCost += e.cost;
        }

    std::set<int> roots;
    for (int i = 0; i < n; i++) roots.insert(find(i));

    if (roots.size() > 1)
        std::cout << "Graph is disconnected. Minimum Spanning Forest:\n";
    else
        std::cout << "Minimum Spanning Tree (Kruskal's):\n";

    for (const Edge& e : mstEdges)
        std::cout << ug.vertices[e.src].getData()
                  << " -- " << ug.vertices[e.dest].getData()
                  << " (Cost: " << e.cost << ")\n";

    std::cout << "Total Cost: " << totalCost << "\n";
}

template<typename T>
void Graph<T>::dijkstra_to_state(const Vertex<T>& src, const T& state) {
    int i_src = get_vertex_index(src);
    if (i_src == -1) {
        std::cout << "Source airport not found.\n";
        return;
    }

    const int INF = INT_MAX;
    int n = vertices.size();
    std::vector<int> dist(n, INF);
    std::vector<int> cost(n, INF);
    std::vector<int> prev(n, -1);

    dist[i_src] = 0;
    cost[i_src] = 0;
    clean_visited();

    while (true) {
        int current = -1, min_dist = INF;
        for (int i = 0; i < n; i++)
            if (!vertices[i].getVisited() && dist[i] < min_dist) {
                min_dist = dist[i];
                current = i;
            }
        if (current == -1) break;
        vertices[current].setVisited(true);

        for (const Edge& e : edges[current]) {
            if (vertices[e.dest].getVisited()) continue;
            int nd = dist[current] + e.distance;
            int nc = cost[current] + e.cost;
            if (nd < dist[e.dest]) {
                dist[e.dest] = nd;
                cost[e.dest] = nc;
                prev[e.dest] = current;
            }
        }
    }
    clean_visited();

    bool found = false;
    for (int i = 0; i < n; i++) {
        T city = vertices[i].getCity();
        size_t pos = city.rfind(' ');
        T vertex_state = (pos != T::npos) ? city.substr(pos + 1) : city;

        if (vertex_state != state || dist[i] == INF) continue;
        found = true;

        std::vector<int> path;
        for (int c = i; c != -1; c = prev[c])
            path.push_back(c);
        std::reverse(path.begin(), path.end());

        std::cout << "To " << vertices[i].getData() << ": ";
        for (int v = 0; v < path.size(); v++) {
            std::cout << vertices[path[v]].getData();
            if (v != (int)path.size() - 1) std::cout << " -> ";
        }
        std::cout << " | Distance: " << dist[i] << " | Cost: $" << cost[i] << "\n";
    }

    if (!found)
        std::cout << "No paths found to any airport in " << state << ".\n";
}

template <typename T> Graph<T> Graph<T>::createUndirectedGraph() {
  Graph<T> undirectedGraph;

  for (int i = 0; i < vertices.size(); i++)
    undirectedGraph.insert_vertex(vertices[i]);

  for (int i = 0; i < edges.size(); i++) {
    for (int j = 0; j < edges[i].size(); j++) {
      int dest = edges[i][j].dest;

      if (undirectedGraph.edgeExists(i, dest) ||
          undirectedGraph.edgeExists(dest, i))
        continue;

      int cost = edges[i][j].cost;
      if (edgeExists(dest, i))
        cost = std::min(cost, getEdgeCost(dest, i));

      undirectedGraph.addUndirectedEdge(i, dest, cost);
    }
  }

  return undirectedGraph;
}

template <typename T>
bool Graph<T>::edgeExists(const int &src, const int &dest) {
  for (int j = 0; j < edges[src].size(); j++) {
    if (edges[src][j].dest == dest) {
      return true;
    }
  }
  return false;
}

template <typename T>
int Graph<T>::getEdgeCost(const int &src, const int &dest) {
  for (int j = 0; j < edges[src].size(); j++) {
    if (edges[src][j].dest == dest) {
      return edges[src][j].cost;
    }
  }
  throw std::string("edge does not exist");
}

template <typename T>
void Graph<T>::addUndirectedEdge(const int &src, const int &dest,
                                 const int &cost) {
  for (int j = 0; j < edges[src].size(); j++) {
    if (edges[src][j].dest == dest) {
      edges[src][j].cost = cost;

      bool reverseFound = false;
      for (int k = 0; k < edges[dest].size(); k++) {
        if (edges[dest][k].dest == src) {
          edges[dest][k].cost = cost;
          reverseFound = true;
          break;
        }
      }

      if (!reverseFound) {
        edges[dest].push_back(Edge(dest, src, edges[src][j].distance, cost));
      }
      return;
    }
  }

  edges[src].push_back(Edge(src, dest, 0, cost));
  edges[dest].push_back(Edge(dest, src, 0, cost));
}

template <typename T> void Graph<T>::countConnections() {
  std::vector<int> inbound(vertices.size(), 0);
  std::vector<int> outbound(vertices.size(), 0);
  std::vector<int> total(vertices.size(), 0);
  std::vector<int> order(vertices.size());

  for (int i = 0; i < vertices.size(); i++) {
    outbound[i] = edges[i].size();

    for (int j = 0; j < edges[i].size(); j++) {
      inbound[edges[i][j].dest]++;
    }
  }

  for (int i = 0; i < vertices.size(); i++) {
    total[i] = inbound[i] + outbound[i];
    order[i] = i;
  }

  for (int i = 0; i < order.size() - 1; i++) {
    int maxIndex = i;

    for (int j = i + 1; j < order.size(); j++) {
      if (total[order[j]] > total[order[maxIndex]]) {
        maxIndex = j;
      }
    }

    int temp = order[i];
    order[i] = order[maxIndex];
    order[maxIndex] = temp;
  }

  std::cout << "Airport Connections\n";

  for (int i = 0; i < order.size(); i++) {
    int airport = order[i];

    std::cout << vertices[airport].getData() << " " << total[airport]
              << " connections"
              << " (Inbound: " << inbound[airport]
              << ", Outbound: " << outbound[airport] << ")\n";
  }
}

template <typename T> void Graph<T>::primMST() {
  Graph<T> undirectedGraph = createUndirectedGraph();

  if (undirectedGraph.vertices.empty()) {
    std::cout << "Graph is empty.\n";
    return;
  }

  std::vector<bool> inMST(undirectedGraph.vertices.size(), false);
  std::vector<Edge> mstEdges;

  int totalCost = 0;

  inMST[0] = true;

  for (int count = 0; count < undirectedGraph.vertices.size() - 1; count++) {
    Edge minEdge;
    minEdge.cost = INT_MAX;

    bool foundEdge = false;

    for (int i = 0; i < undirectedGraph.vertices.size(); i++) {
      if (inMST[i]) {
        for (const Edge &edge : undirectedGraph.edges[i]) {
          if (!inMST[edge.dest] && edge.cost < minEdge.cost) {
            minEdge = edge;
            foundEdge = true;
          }
        }
      }
    }

    if (!foundEdge) {
      std::cout << "MST cannot be formed because the graph is disconnected.\n";
      return;
    }

    mstEdges.push_back(minEdge);
    totalCost += minEdge.cost;
    inMST[minEdge.dest] = true;
  }

  std::cout << "Minimum Spanning Tree:\n";

  for (const Edge &edge : mstEdges) {
    std::cout << undirectedGraph.vertices[edge.src].getData() << " -- "
              << undirectedGraph.vertices[edge.dest].getData()
              << " (Cost: " << edge.cost << ")\n";
  }

  std::cout << "Total Cost of MST: " << totalCost << "\n";
}