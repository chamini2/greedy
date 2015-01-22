#include<iostream>
#include<vector>



class Edge {
    public:
        Edge() {}
        Edge(int,int); 
        int _first, _second;
};

Edge::Edge(int first, int second) {
    _first  = first;
    _second = second;
}

int main() {
    int cases;
    std::vector<Edge> edges;

    std::cin >> cases;

    for (; cases > 0; --cases) {
        int vertex;
        std::cin >> vertex;

        edges.reserve(vertex - 1);

        for (int i = 0; i < vertex - 1; ++i) {
            int first, second;
            std::cin >> first;
            std::cin >> second; 
            edges.push_back(Edge(first, second)); 
        }

        for (auto e : edges) {
            std::cout << e._first << " " << e._second << std::endl; 
        }
    }
}
