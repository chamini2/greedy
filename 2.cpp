#include <stdio.h>
#include <algorithm> // std::sort
#include <vector>
#include <stack>


// We will user a pair for the queries:
// (R, x) and (Q, -1) where the -1 is ignored
typedef std::pair<char, int> Query;

// Class Edge
// Members: first_, second_, removed_
// Description: Class that contains in first and second the
// vertex that conform the edge. Removed is a label
// that is used to check whether the edge is in the graph or not
class Edge {
    public:
        Edge();
        Edge(int,int);
        int first_, second_;
        bool removed() { return removed_; }
        void remove() { removed_ = true;  }
    private:
        bool removed_;
};

Edge::Edge() {
    first_   = -1;
    second_  = -1;
    removed_ = false;
}

Edge::Edge(int first, int second) {
    first_   = first;
    second_  = second;
    removed_ = false;
}

// Class DisjointSets
// Description: We will use the disjoint sets data structure with
// some modifications to handle the connected components representation
// We will only document functions that are not implemented in a
// common disjoint sets structure.
// For further information http://en.wikipedia.org/wiki/Disjoint-set_data_structure
class DisjointSets {
    public:
        DisjointSets();
        ~DisjointSets();
        DisjointSets(int size);
        void unify(int,int);
        int find(int);
        std::vector<int> representatives() { return representatives_; }
        std::vector<int> ranks() { return ranks_; }
        std::vector<int> sizes() { return sizes_; }
        int size() { return size_; }

    private:
        std::vector<int> representatives_;
        std::vector<int> ranks_;
        std::vector<int> sizes_; // Size of each component in the graph.
                                 // Component represented by 'i' will have its size in sizes_[i].
        int size_;               // Number of vertex in the graph
};

DisjointSets::DisjointSets(int size) {

    // We will go until size + 1 to handle 1-indexed edges
    for (int i = 0; i < size + 1; ++i) {
        representatives_.push_back(i);
        ranks_.push_back(0);
        sizes_.push_back(1);

    }
    size_       = size;

}

DisjointSets::~DisjointSets() {
}


int DisjointSets::find(int id) {
    // id between 1 and size + 1 to handle 1-indexed edges
    if (1 <= id && id < size_ + 1) {
        if (representatives_[id] == id) {
            return id;
        } else {
            representatives_[id] = this->find(representatives_[id]);
            return representatives_[id];
        }
    }

    return -1;
}

void DisjointSets::unify(int a, int b) {

    int arep = this->find(a);
    int brep = this->find(b);

    if (arep == -1 || brep == -1)
        return;

    // If they are on different disjoint sets
    if (arep != brep) {
        if (ranks_[arep] > ranks_[brep]) {
            representatives_[brep] = arep;
            sizes_[arep] += sizes_[brep];

        } else if (ranks_[arep] < ranks_[brep]) {
            representatives_[arep] = brep;
            sizes_[brep] += sizes_[arep];

        } else {
            representatives_[arep] = brep;
            sizes_[brep] += sizes_[arep];
            ++ranks_[brep];
        }
    }
}


// Function: disconnectedOffices
// Arguments: edges : vector of Edge, queries: vector of Query
// Description: This function does the following:
// 1 -> Removes all edges that are asked to be removed in the queries
// 2 -> Going backwards in queries:
//      if there's a 'Q' query ->
//          it pushes the number of pairs disconnected
//          by removing the size(A)*size(B) from the last number of pairs
//          being A and B the two components that are being unified
//          to the stack 'pairs'
//      if there's a 'R x' query ->
//          it unifies the vertex in edge[x].
// 3 -> Finally, it pops each elem in 'pairs' and print it
void disconnectedOffices(std::vector<Edge>& edges, std::stack<Query>& queries) {

    int nVertex = edges.size();
    // Graph without edges (separated components)
    DisjointSets components(nVertex);
    std::stack<unsigned long long> pairs;
    int frep, srep;

    unsigned long long nPairs = (nVertex * (nVertex - 1)) / 2;

    // Unify not labeled edges
    for (auto edge : edges) {
        if (!edge.removed()) {
            frep = components.find(edge.first_);
            srep = components.find(edge.second_);

            if (frep == srep) {
                continue;
            }
            nPairs -= components.sizes()[frep] * components.sizes()[srep];
            components.unify(edge.first_, edge.second_);
        }
    }

    // Going backwards on the queries
    while (!queries.empty()) {
        Query& query = queries.top();
        queries.pop();

        // If there's a 'show' query, we count the pairs and push into the results
        if (query.first == 'Q') {
            pairs.push(nPairs);
        // If it's a remove query, unify the removed edges
        } else {
            Edge& edge = edges[query.second];

            frep = components.find(edge.first_);
            srep = components.find(edge.second_);

            if (frep == srep) {
                continue;
            }

            nPairs -= components.sizes()[frep] * components.sizes()[srep];
            components.unify(edge.first_, edge.second_);
        }

    }

    // Print number of pairs in the right order
    while (!pairs.empty()) {
        printf("%llu\n", pairs.top());
        pairs.pop();
    }
}

int main() {
    int cases;

    scanf("%d", &cases);
    for (; cases > 0; --cases) {
        int N;
        scanf("%d", &N);

        std::vector<Edge> edges;
        edges.reserve(N - 1);

        // Handling 1-indexed edges
        edges.push_back(Edge());

        // Push edges in vector
        for (int i = 0; i < N - 1; ++i) {
            int first, second;
            scanf("%d %d", &first, &second);
            //printf("%d %d\n", first, second);
            edges.push_back(Edge(first, second));
        }

        int M, vertex;
        std::stack<Query> queries;
        char query;

        scanf("%d", &M);

        // Push queries in vector
        for (; M > 0; --M) {
            scanf(" %c", &query);
            // Queries 'Q' will have vertex = -1
            vertex = -1;
            // Queries 'R x' will have vertex = x
            if (query == 'R') {
                scanf("%d", &vertex);
                edges[vertex].remove();
            }
            //printf("%c %d\n", query, vertex);


            queries.push(std::make_pair(query, vertex));
        }



        // Print number of paris disconnected
        disconnectedOffices(edges, queries);
        if (cases > 1) printf("\n"); // endline
    }

    return 0;
}
