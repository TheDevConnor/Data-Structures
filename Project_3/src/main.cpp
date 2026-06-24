#include "headers/Graph.h"
#include "headers/Vertex.h"

#include "headers/config.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int read_csv(std::vector<std::vector<std::string>> *csv_data,
             std::string file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file \"" << file_name << "\"\n";
    return READ_FILE;
  }

  std::string line;
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::vector<std::string> row;
    std::string cell;
    bool in_quotes = false;

    for (char c : line) {
      if (c == '"') {
        in_quotes = !in_quotes;
      } else if (c == ',' && !in_quotes) {
        row.push_back(cell);
        cell.clear();
      } else {
        cell += c;
      }
    }

    row.push_back(cell);

    csv_data->push_back(row);
  }

  return SUCCESS;
}

void section(const std::string &title) {
  std::cout << "================================\n";
  std::cout << " " << title << "\n";
  std::cout << "================================\n";
}

int main() {
  std::vector<std::vector<std::string>> csv_data;
  read_csv(&csv_data, "airports.csv");

  Graph<std::string> airports;

  /*
   * Origin  Destination  City1          City2          Distance  Cost
   * YIP     ATL          Detroit MI     Atlanta GA     595       203
   *  0          1           2              3            4         5
   */
  for (const auto &row : csv_data) {
    if (row.size() < 5)
      continue;

    Vertex<std::string> origin{
        row[0], //* Airport Code
        row[2], //* city
    };

    Vertex<std::string> dest{
        row[1], //*  Airport Code
        row[3], //* City
    };

    airports.insert_vertex(origin);
    airports.insert_vertex(dest);

    int distance = std::stoi(row[4]);

    int cost = 0;
    if (row.size() > 5 && !row[5].empty()) {
      cost = std::stoi(row[5]);
    }

    airports.add_edge(origin, dest, distance, cost);
  }

  section("Graph - Adjancency List");
  airports.print();

  section("Dijkstra — Shortest Path: IAD -> MIA");
  {
    Vertex<std::string> src("IAD");
    Vertex<std::string> dest("MIA");
    airports.dijkstra_shortest_path(src, dest);
  }

  section("Dijkstra — All Airports in GA (from IAD)");
  {
    Vertex<std::string> src("IAD");
    airports.dijkstra_to_state(src, std::string("GA"));
  }

  section("Dijkstra — All Airports in FL (from IAD)");
  {
    Vertex<std::string> src("IAD");
    airports.dijkstra_to_state(src, std::string("FL"));
  }

  section("Dijkstra — No Airports Reachable (bad state)");
  {
    Vertex<std::string> src("IAD");
    airports.dijkstra_to_state(src, std::string("XX"));
  }

  section("Dijkstra — IAD -> MIA with exactly 1 stop");
  {
    Vertex<std::string> src("IAD");
    Vertex<std::string> dst("MIA");
    airports.dijkstra_with_stops(src, dst, 1);
  }

    section("Dijkstra — IAD -> MIA with exactly 2 stops");
  {
    Vertex<std::string> src("IAD");
    Vertex<std::string> dst("MIA");
    airports.dijkstra_with_stops(src, dst, 2);
  }
 
  section("Dijkstra — Impossible stop count");
  {
    Vertex<std::string> src("IAD");
    Vertex<std::string> dst("YKM");
    airports.dijkstra_with_stops(src, dst, 2);
  }

  section("Direct Flight Connections (sorted by total)");
  airports.countConnections();
 
  section("Prim's MST");
  airports.primMST();

  section("sKruskal's MST");
  airports.kruskalMST();

  return 0;
}