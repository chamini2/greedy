#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <math.h>

// Problem variables
int N, M, R, U, V;

class DisjointSets {
public:
    std::vector<int> _representatives;
    std::vector<int> _ranks;
    int _length;

    DisjointSets() {}

    DisjointSets(int size) {
        this->reserve(size);
    }

    void clear() {
        for (int i = 0; i < _length; ++i) {
            _representatives[i] = i;
            _ranks[i] = 0;
        }
    }

    void reserve(int size) {
        _representatives.reserve(size);
        _ranks.reserve(size);
        _length = size;

        this->clear();
    }

    void unite(int a, int b) {
        int arep, brep;

        arep = this->find(a);
        brep = this->find(b);

        // If they are on different disjoint sets
        if (arep != brep) {
            if (_ranks[arep] > _ranks[brep]) {
                _representatives[brep] = arep;

            } else if (_ranks[arep] < _ranks[brep]) {
                _representatives[arep] = brep;

            } else {
                _representatives[arep] = brep;
                _ranks[brep]++;
            }
        }
    }

    int find(int id) {
        if (0 <= id && id < _length) {
            if (_representatives[id] == id) {
                return id;
            } else {
                _representatives[id] = this->find(_representatives[id]);
                return _representatives[id];
            }
        } else {
            return -1;
        }
    }
};

class Office {
public:
    int _x, _y;
    int _label;
    static int _counter;

    Office() {}
    Office(int x, int y) {
        _x = x;
        _y = y;
        _label = _counter++;
    }
};
int Office::_counter = 0;

class Edge {
public:
    Office _first, _second;
    double _length;

    Edge(Office first, Office second) {
        _first = first;
        _second = second;
        _length = sqrt(pow(first._x - second._x, 2) +
                       pow(first._y - second._y, 2));
    }
};

inline bool operator<(const Edge& a, const Edge& b) {
    return (a._length < b._length);
}

// int func(int* a, int& c, int d);
// int b = 10;
// func(&b,b,b);


int main(int argc, char const *argv[]) {

    int cases;
    std::vector<Office> offices;
    std::vector<Edge> edges;
    DisjointSets components;
    int x, y;

    scanf("%d", &cases);

    for (int cas = 1; cas <= cases; ++cas) {

        scanf("%d %d %d %d %d", &N, &R, &M, &U, &V);

        offices.reserve(N);
        edges.reserve( (N*(N-1)) / 2 );
        components.reserve(N);

        // for labels
        Office::_counter = 0;

        // read the offices coordinates
        for (int off = 0; off < N; ++off) {
            scanf("%d %d", &x, &y);
            offices.push_back(Office(x,y));
        }

        // generate every possible edge
        for (int i = 0; i < N; ++i) {
            for (int k = i + 1; k < N; ++k) {
                edges.push_back(Edge(offices[i], offices[k]));
            }
        }

        // sort the edges
        std::sort(edges.begin(), edges.end());

        /*for (auto edg : edges) {
            printf("(%d, %d, (%d)) -> (%d, %d, (%d)) | %lf\n",
                    edg._first._x, edg._first._y, edg._first._label,
                    edg._second._x, edg._second._y, edg._second._label,
                    edg._length);
        }*/

        // Kruskal's algorithm
        int networks = N;
        double cheap = 0, expensive = 0;
        for (auto edg : edges) {
            if (components.find(edg._first._label) != components.find(edg._second._label)) {
            // if they are not in the same component
                components.unite(edg._first._label, edg._second._label);

                if (edg._length > R) {
                    expensive += edg._length * V;
                } else {
                    cheap += edg._length * U;
                }

                networks--;
                if (networks == M) {
                    break;
                }
            }
        }

        printf("Caso #%d: %.3lf %.3lf\n", cas, cheap, expensive);

        offices.clear();
        edges.clear();
    }

    return 0;
}
