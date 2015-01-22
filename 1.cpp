#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <math.h>

// Problem variables
int N, M, R, U, V;

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
    double _weight;

    Edge(Office first, Office second) {
        _first = first;
        _second = second;
        _weight = sqrt(pow(first._x - second._x, 2) +
                       pow(first._y - second._y, 2));
        _weight *= _weight > R ? V : U;
    }
};

inline bool operator<(const Edge& a, const Edge& b) {
    return (a._weight < b._weight);
}

// int func(int* a, int& c, int d);
// int b = 10;
// func(&b,b,b);


int main(int argc, char const *argv[]) {

    int cases;
    std::vector<Office> offices;
    std::vector<Edge> edges;
    // disjoint_set components;
    int x, y;

    scanf("%d", &cases);


    for (int cas = 1; cas <= cases; ++cas) {

        scanf("%d %d %d %d %d", &N, &M, &R, &U, &V);

        offices.reserve(N);
        edges.reserve( (N*(N-1)) / 2 );

        // for labels
        Office::_counter = 0;

        // read the offices coordinates
        for (int off = 0; off < N; ++off) {
            scanf("%d %d", &x, &y);
            offices.push_back(Office(x,y));
        }

        for (auto off : offices) {
            printf("(%d, %d, (%d)\n", off._x, off._y, off._label);
        }

        for (int i = 0; i < N; ++i) {
            for (int k = i + 1; k < N; ++k) {
                edges.push_back(Edge(offices[i], offices[k]));
            }
        }

        std::sort(edges.begin(), edges.end());

        for (auto edg : edges) {
            printf("(%d, %d, (%d)) -> (%d, %d, (%d)) | %lf\n",
                    edg._first._x, edg._first._y, edg._first._label,
                    edg._second._x, edg._second._y, edg._second._label,
                    edg._weight);
        }

        int networks = N;
        for (auto edg : edges) {
            // if they are not in the same component
            // if (components.find(edg._first._label) == components.find(edg._second._label))
            {
                // components.union(edg._first._label, edg._second._label);

                networks--;
                if (networks == M) {
                    break;
                }
            }
        }

        printf("Caso #%d: x x\n", cas);

        offices.clear();
        edges.clear();
    }

    return 0;
}

/*std::vector<Edge> MST_Prim(std::vector<Office>& offices) {

    std::priority_queue<Edge> edges;

    Office off = offices.back();
    offices.pop_back();

    for (auto other : offices) {
        edges.push(Edge(off, other));
    }

    return std::vector<Edge>();
}*/
