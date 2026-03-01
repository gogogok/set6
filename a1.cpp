#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdint>

struct Edge {
    int u = 0;
    int v = 0;
    long long w = 0;
    int id = 0;
};


class DSU {
public:
    explicit DSU(int n);

    //представитель множества
    int find(int x);

    //true если реально объединили
    bool unite(int a, int b);
};

//ALG1
std::vector<Edge> ALG1(int n, std::vector<Edge> edges) {
    std::ranges::sort(edges,
                      [](const Edge& a, const Edge& b) {
                          if (a.w != b.w) return a.w < b.w;
                          return a.id < b.id;
                      });

    DSU dsu(n);
    std::vector<Edge> T;
    T.reserve(n - 1);

    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            T.push_back(e);
            if (T.size() == n - 1) {
                break;
            }
        }
    }

    return T;
}

//ALG2
std::vector<Edge> ALG2(const int n, std::vector<Edge> edges, std::uint64_t seed = 0) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::ranges::shuffle(edges, rng);

    DSU dsu(n);
    std::vector<Edge> T;
    T.reserve(n - 1);

    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            T.push_back(e);
            if (T.size() == n - 1) {
                break;
            }
        }
    }

    return T;
}

//вспомогательные функции
//bool existsPath(u, v, T)
//Edge maxEdgeOnPath(u, v, T)
//void removeEdge(e, T)
//void addEdge(e, T)
//ALG3
std::vector<Edge> ALG3(std::vector<Edge> edges) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::ranges::shuffle(edges, rng);

    std::vector<Edge> T;

    for (const Edge& e : edges) {

        if (!existsPath(e.u, e.v, T)) {
            addEdge(e, T);
        }
        else {
            Edge eMax = maxEdgeOnPath(e.u, e.v, T);

            if (e.w < eMax.w) {
                removeEdge(eMax, T);
                addEdge(e, T);
            }
        }
    }

    return T;
}

