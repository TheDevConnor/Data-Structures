#ifndef VERTEX_H
#define VERTEX_H

template <typename T> class Vertex {
public:
  Vertex(const T &airportCode = T(), const T &city = T(), const T &state = T())
      : airportCode(airportCode), city(city), state(state), visited(false) {};

  const T &getData() const { return airportCode; }
  const T &getCity() const { return city; }
  bool getVisited() const { return visited; }
  void setVisited(bool v) { visited = v; }

private:
  T airportCode;
  T city;
  T state;
  bool visited;
};

#endif