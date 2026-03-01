#include <vector>
#include <queue>
#include <limits>
#include <iostream>

struct Edge {
  int to = 0;
  int weight = 0;
};

std::vector<int> dijkstraMULT(const std::vector<std::vector<Edge>>& graph, int start) {
  const int n = static_cast<int>(graph.size());
  constexpr int INF = std::numeric_limits<int>::infinity();

  std::vector dist(n, INF);
  std::vector visited(n, false);

  dist[start] = 1;

  typedef std::pair<int, int> State;

  std::priority_queue<State, std::vector<State>,std::greater<State>> pq;
  pq.push(State(dist[start], start));

  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();

    const int v = current.second;

    if (visited[v]) {
        continue;
    }

    visited[v] = true;

    for (std::size_t i = 0; i < graph[v].size(); ++i) {
      int to = graph[v][i].to;
      const int weight = graph[v][i].weight;

      int newDist = dist[v] * weight;

      if (newDist < dist[to]) {
        dist[to] = newDist;
        pq.push(State(newDist, to));
      }
    }
  }
  return dist;
}

std::vector<std::vector<Edge>> restoreGraph(const std::vector<std::vector<int>>& dist) {
    const int n = static_cast<int>(dist.size());
    constexpr int INF = std::numeric_limits<int>::infinity();
    std::vector<std::vector<Edge>> adj(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }

            if (dist[i][j] == INF) {
                continue;
            }

            bool needed = true;

            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) {
                    continue;
                }

                if (dist[i][k] == INF || dist[k][j] == INF) {
                    continue;
                }

                if (dist[i][k] <= INF - dist[k][j] && dist[i][j] == dist[i][k] + dist[k][j]) {
                    needed = false;
                    break;
                }
            }

            if (needed) {
                Edge e;
                e.to = j;
                e.weight = dist[i][j];
                adj[i].push_back(e);
            }
        }
    }
    return adj;
}